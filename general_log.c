/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

               HUAWEI General Log Packet Processing Common Routines

General Description
 Core General Log processing routines that are common to all targets.

Copyright (c) 2008-2115 by HUAWEI, Incorporated.  All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/
/*===========================================================================

                          Edit History

$Header:

when       who            what, where, why
--------   ---            ----------------------------------------------------
09-07-30   duangan        BQ4D000dg:create.

===========================================================================*/

/*
使用方法_例子
（1）初始化
#define DLOAD_LOG_BUFFER_LEN        16*1024
#define DLOAD_LOG_ITEM_MAX          128
#define DLOAD_LOG_DIR               "brew/dload"
#define DLOAD_LOG_NAME              "dload_log"

uint8 dload_log_buffer[DLOAD_LOG_BUFFER_LEN];
int32 log_handle;

int32 dload_log_init ()
{
 general_log_param log_param;
 int32 ret = 0;

 memset(dload_log_buffer,0,sizeof(dload_log_buffer));

 log_param.log_type        = MEMORY_LOG;
 log_param.save_policy     = SAVE_FUTURE_ALL;
 log_param.buffer_ptr      = dload_log_buffer;
 log_param.buffer_len      = DLOAD_LOG_BUFFER_LEN;
 log_param.item_max_len    = DLOAD_LOG_ITEM_MAX;
 log_param.msg_ID          = 0;
 log_param.msg_mask        = 0;
 // strncpy(log_param.dir_name,DLOAD_LOG_DIR,GENERAL_LOG_DIR_LEN);
 // strncpy(log_param.file_name,DLOAD_LOG_NAME,GENERAL_LOG_FILE_LEN);

 log_handle = general_log_init(log_param);

 if(log_handle < 0)
 {
   return FALSE;
 }
  
 ret = GENERAL_LOG_PRINT(log_handle,"**** SD download log ****",0,0,0);

 return TRUE;
}

// 在 tmc_init() 中调用 dload_log_init()，准备打印
dload_log_init();

（2）打印代码
// 使用宏，将原有打印代码无缝切换到新实现。
#define save_dload_log(msg_handle,msg_log,num1,num2,num3) GENERAL_LOG_PRINT(msg_handle,msg_log,num1,num2,num3)

// 使用宏，分级打印
#define MSG_ONE(msg_log,num1,num2,num3)  GENERAL_LOG_PRINT(msg_handle,msg_log,num1,num2,num3)
#define MSG_TWO(msg_log,num1,num2,num3)  GENERAL_LOG_PRINT(msg_handle,msg_log,num1,num2,num3)

// 实际打印代码
 save_dload_log( log_handle, "dload_in:udl_chk_vvs_need_restore()",0,0,0);
 save_dload_log( log_handle, "vvs status is %d;vvs string=%s.",(uint32)vvs_need_restore,(uint32)&oper_vvs_parame,0);

（3）结束打印
// 在 hw_power_off()中结束打印
// <BQ4D000dg duangan 2009-8-20 begin
extern int32 general_log_end(uint32 handle);

general_log_end(log_handle);
// BQ4D000dg duangan 2009-8-20 end>
*/

#include "timetick.h"
#include "rex.h"
#include "general_log.h"
#include "stdio.h"

#ifdef FEATURE_EFS
#include "fs_public.h"
#endif

#ifdef FEATURE_DIAG_TASK
#include "msg.h"
#endif

#define GENERAL_LOG_MAGIC_NUMBER   0x20c8320c

// general log 句柄数
#define GENERAL_LOG_HANDLE_MAX     16

// general log control(52B)
typedef struct
{
  uint32            magic_number;
  general_log_type  log_type;
  general_log_save_policy  save_policy;
  char              dir_name[GENERAL_LOG_DIR_LEN+1];       /* log路径，最长16字节. */
  char              file_name[GENERAL_LOG_FILE_LEN+1];     /* log文件名，16字节,不含扩展名，
                                                        扩展名默认为.txt,可以在手机中直接查看. */
  uint8 *           buffer_ptr;
  uint32            buffer_len;
  uint32            item_max_len;   /* 每条log的最大长度 */
  uint32            msg_ID;         /* 指qxdm id */
  uint8             msg_mask;       /* 指qxdm mask */
  uint32            buffer_index;   /* 初始化为0 */
  int32             file_handle;    /* 似乎不需要保存. */
  rex_crit_sect_type    crit_sect;
  uint32                buffer_over_count;  /* buffer full count. */
}general_log_control;


static general_log_control log_control[GENERAL_LOG_HANDLE_MAX];

static boolean gen_log_inited = FALSE;

/*****************************************************************************
Prototype    : log_file_open
Description  : 创建/打开log 文件
Input        : const char *dir_name   
               const char *file_name  
Output       : None
Return Value :
Calls        :
Called By    :

 History        :
 1.Date         : 2009/7/23
   Author       : duangan
   Modification : Created function

*****************************************************************************/
static int32 log_file_open (const char *dir_name , const char *file_name)
{
 int32 file_handle = -1;
 struct fs_stat sbuf;
 char  log_file_route[GENERAL_LOG_DIR_LEN + GENERAL_LOG_FILE_LEN + 5];

 memset(log_file_route, 0 ,sizeof(log_file_route));
 snprintf(log_file_route,sizeof(log_file_route)-1,"%s/%s.txt",dir_name,file_name);

 /* 0 means success, -1 means fail. */
 if(0 != efs_stat(dir_name, &sbuf))
 {
   /* create dir */
   if(-1 == efs_mkdir(dir_name,0777))
   {
     return DIR_CREATE_FAIL;
   }
 }
  
 /* Open the EFS file */
 file_handle = efs_open(log_file_route, O_RDWR | O_APPEND | O_CREAT, 0755);
 if (-1 == file_handle)
 {
   return FILE_CREATE_FAIL;
 }

 return file_handle;
}


/*****************************************************************************
Prototype    : log_item_print
Description  : print log item
Input        : const general_log_control * self,(合法性由调用方保障)
               const char *format  
               const uint32 a    param 1  
               const uint32 b    param 2    
               const uint32 c    param 3    
                
Output       : None
Return Value :
Calls        :
Called By    :

 History        :
 1.Date         : 2009/7/30
   Author       : duangan
   Modification : Created function

*****************************************************************************/
static int32 log_item_print
(
 const char * file,
 const uint16 line,
 general_log_control * self,
 const char *format,
 const int32 a,
 const int32 b,
 const int32 c
)
{
 uint32 my_connt = 0;
 int32  ret = LOG_OK;
 uint32 head_len = 0;
  
 // 时间精度是千分之一秒
 my_connt = timetick_get_safe()/32.768;
    
 head_len = sprintf((char *)&self->buffer_ptr[self->buffer_index],
   "%d-%d-%s-%d-",self->buffer_over_count,my_connt,file,line);
  
 self->buffer_index += head_len;
    
 self->buffer_index += snprintf((char *)&self->buffer_ptr[self->buffer_index],
   self->item_max_len - head_len -2 ,(format),(a),(b),(c));
  
 self->buffer_ptr[self->buffer_index++] = 0x0D;
 self->buffer_ptr[self->buffer_index++] = 0x0A;

 // buffer full.
 if((self->buffer_len - self->buffer_index) < self->item_max_len)
 {
   ret = BUFFER_FULL;
 }

 return ret;
}

/*****************************************************************************
Prototype    : log_handle_check
Description  : check log handle valid
Output       : None
Return Value :
Calls        :
Called By    :

 History        :
 1.Date         : 2009/7/31
   Author       : duangan
   Modification : Created function

*****************************************************************************/
int32 log_handle_check(int32 handle)
{
 general_log_control * self = NULL;
 int32  ret = LOG_OK;

 if(handle > GENERAL_LOG_HANDLE_MAX)
 {
   ret = HANDLE_INVALIDE;
 }
  
 if(!ret)
 {
   self = &log_control[handle];
    
   if(self->magic_number != GENERAL_LOG_MAGIC_NUMBER)
   {
     ret = HANDLE_INVALIDE;
   }
 }

 return ret;
}


/*****************************************************************************
Prototype    : log_file_save
Description  : 将log保存至efs的指定文件.
Input        : const general_log_control * self (合法性由调用方保障)
Output       : None
Return Value :
Calls        :
Called By    :

 History        :
 1.Date         : 2009/7/23
   Author       : duangan
   Modification : Created function

*****************************************************************************/
static int32 log_file_save(general_log_control * self)
{
 int32  ret = LOG_OK;
 uint32 write_count = 0;
    
 // if buffer has log data,save.
 if(self->buffer_index > 0)
 {
   /* open the log file. */
   self->file_handle = log_file_open(self->dir_name, self->file_name);
    
   /* write the prepared string to file */
   if(self->file_handle >= 0)
   {
     write_count = efs_write(self->file_handle, self->buffer_ptr, (uint32)self->buffer_index);

     if(!write_count)
     {
       ret = FILE_SYSTEM_WRITE_FAIL;
     }
     else if(write_count < self->buffer_index)
     {
       ret = FILE_SYSTEM_WRITE_Incomplete;
     }
     else
     {
       ret = FILE_SYSTEM_WRITE_OK;
     }
    
     efs_close(self->file_handle);
   }
   else
   {
     // 返回错误.
     ret = self->file_handle;
   }
 }
 else
 {
   ret = BUFFER_IS_EMPTY;
 }
  
 return ret;
}


/*****************************************************************************
Prototype    : log_qxdm_f3_print
Description  : print QXDM F3 msg.
Input        : general_log_control * self  
               const char *format          
               const uint32 a              
               const uint32 b              
               const uint32 c              
               const char * file           
               const uint16 line           
Output       : None
Return Value :
Calls        :
Called By    :

 History        :
 1.Date         : 2009/8/3
   Author       : duangan
   Modification : Created function

*****************************************************************************/
static int32 log_qxdm_f3_print
(
 const char * file,
 const uint16 line,
 const general_log_control * self,
 const char *format,
 const int32 a,
 const int32 b,
 const int32 c
)
{
 // TODO:这部分还是有很多问题，比如ss_id 如何确认.
#if 0
#define MSG(xx_ss_id, xx_ss_mask, xx_fmt) \
   do { \
     /*lint -e506 -e774*/ \
     if (xx_ss_mask & (MSG_BUILD_MASK_ ## xx_ss_id)) { \
     /*lint +e506 +e774*/ \
       XX_MSG_CONST (xx_ss_id, xx_ss_mask, xx_fmt); \
       /*lint -e571 */ \
       msg_send (&xx_msg_const); \
       /*lint +e571 */ \
     } \
   /*lint -e717 */ \
   } while (0) \
    
#define XX_MSG_CONST(xx_ss_id, xx_ss_mask, xx_fmt) \
                   XX_MSG_CONST_SAVE(xx_ss_id, xx_ss_mask, xx_fmt, TRUE)

#define XX_MSG_CONST_SAVE(xx_ss_id, xx_ss_mask, xx_fmt, do_save) \
static const msg_const_type xx_msg_const = { \
 {__LINE__, (xx_ss_id), (xx_ss_mask)}, (xx_fmt), msg_file, do_save}
#endif

 msg_const_type msg_print = {0};
  
 msg_print.desc.line = line;
 msg_print.desc.ss_id = self->msg_ID;
 msg_print.desc.ss_mask = self->msg_mask;
 msg_print.fmt = format;
 msg_print.fname = file;
 msg_print.do_save = TRUE;
    
 msg_send_3(&msg_print,  (uint32)(a),(uint32)(b),  (uint32)(c));
}


/*****************************************************************************
Prototype    : general_log_init
Description  : general log init
Input        : const general_log_param log_param  
Output       : nono
Return Value : log handle.
               if return < 0,indicate a error occur. return is general_log_error_type
Calls        :
Called By    :

 History        :
 1.Date         : 2009/7/30
   Author       : duangan
   Modification : Created function

*****************************************************************************/
int32 general_log_init(const general_log_param log_param)
{
 uint32 index = 0;
 uint8 * temp_ptr = NULL;
 general_log_control * self = NULL;
  
 if(!gen_log_inited)
 {
   memset(log_control,0,sizeof(log_control));
   gen_log_inited = TRUE;
 }

 if((SD_CARD_LOG == log_param.log_type) || (EFS_LOG == log_param.log_type))
 {
#ifndef FEATURE_EFS
   return TYPE_NOT_SUPPORT;
#endif
 }

 if(QXDM_LOG == log_param.log_type)
 {
#ifndef FEATURE_DIAG_TASK
   return TYPE_NOT_SUPPORT;
#endif
 }

 // check buffer ptr is valid.
 if(NULL == log_param.buffer_ptr)
 {
   return BUFFER_PTR_IS_INVALID;
 }
  
 // check buffer length is valid.
 if((0 == log_param.buffer_len) || (log_param.buffer_len < log_param.item_max_len))
 {
   return BUFFER_LEN_IS_INVALID;
 }
  
 for(index = 0; index < GENERAL_LOG_HANDLE_MAX; index++)
 {
   // magic_number 既是魔数，也是分配的标志位。这种设计不够好.
   if(GENERAL_LOG_MAGIC_NUMBER == log_control[index].magic_number)
   {
     continue;
   }
   else
   {
     // copy parameter.
     self = &log_control[index];

     memset((void *)self,0,sizeof(general_log_control));
     self->magic_number = GENERAL_LOG_MAGIC_NUMBER;
      
     temp_ptr = (uint8 *)&(self->log_type);
     memcpy(temp_ptr,(void *)&log_param,sizeof(log_param));

     // init crit section.
     rex_init_crit_sect(&(self->crit_sect));

     // 考虑到log打印开始时，文件系统不一定初始化完成，所以在需要使用文件时再打开.
     #if 0
     // create log file.
     if((SD_CARD_LOG == self->log_type) || (EFS_LOG == self->log_type)
       && (SAVE_NOW == self->save_policy))
     {
       self->file_handle = log_file_open(self->dir_name,self->file_name);

       // file create fail.
       if(self->file_handle < 0)
       {
         return FILE_CREATE_FAIL;
       }
     }
     #endif

     break;
   }
 }

 if(GENERAL_LOG_HANDLE_MAX == index)
 {
   return HANDLE_FULL;
 }
 else
 {
   return index;
 }
}


/*****************************************************************************
Prototype    : general_log_print
Description  : 打印 log
Input        : uint32 handle  
               const char *format     
               const uint32 a    param 1  
               const uint32 b    param 2    
               const uint32 c    param 3    
               const char * file  code file name
               const uint16 line  code file line
   for example:
   general_log_print(__FILE__,__LINE__,msg_handle,"SICD OUT usb_sicd_free_buffer(), buffer_ptr is 0x%X",
       my_buffer, 0, 0);
Output       : None
Return Value : if return < 0,indicate a error occur. return is general_log_error_type.
Calls        :
Called By    :

 History        :
 1.Date         : 2009/7/23
   Author       : duangan
   Modification : Created function

*****************************************************************************/
int32 general_log_print
(
  const char * file,
  const uint16 line,
  const uint32 handle,
  const char * format,
  const int32 a,
  const int32 b,
  const int32 c
)
{
 general_log_control * self = NULL;
 int32  ret = LOG_OK;

 ret = log_handle_check(handle);
 if(ret < 0)
 {
   return ret;
 }
  
 self = &log_control[handle];
  
 rex_enter_crit_sect(&(self->crit_sect));
  
 ret = log_item_print(file,line,self,format,a,b,c);
  
 switch(self->log_type)
 {
   case SD_CARD_LOG:
   case EFS_LOG:
       switch(self->save_policy)
       {
         // save now!
         case SAVE_NOW:
             ret = log_file_save(self);
             self->buffer_index = 0;
             memset(self->buffer_ptr,0,self->buffer_len);
             break;
              
         // if full,save.
         case SAVE_FUTURE_ALL:
             if(BUFFER_FULL == ret)
             {
               ret = log_file_save(self);
               self->buffer_index = 0;
               memset(self->buffer_ptr,0,self->buffer_len);
             }
             break;
              
         // unless close,not save.
         case SAVE_FUTURE_CIRCLE:
             break;
    
         default:
             break;
       }
       break;
      
   case MEMORY_LOG:
       break;
      
   case QXDM_LOG:
       log_qxdm_f3_print(file,line,self,format,a,b,c);
       self->buffer_index = 0;
       memset(self->buffer_ptr,0,self->buffer_len);
       break;
        
   default:
       break;
 }
  
 rex_leave_crit_sect(&(self->crit_sect));

 return ret;
}


/*****************************************************************************
Prototype    : general_log_end
Description  : log print end
Input        : uint32 handle  
Output       : None
Return Value :
Calls        :
Called By    :

 History        :
 1.Date         : 2009/7/31
   Author       : duangan
   Modification : Created function

*****************************************************************************/
int32 general_log_end(uint32 handle)
{
 general_log_control * self = NULL;
 int32  ret = LOG_OK;
  
 ret = log_handle_check(handle);
 if(ret < 0)
 {
   return ret;
 }
  
 self = &log_control[handle];

 // print log end stirng.
 log_item_print(__MODULE__,__LINE__,self, "---general_log_end!---",0,0,0);

 switch(self->log_type)
 {
   case SD_CARD_LOG:
   case EFS_LOG:
       ret = log_file_save(self);
       break;
        
   case MEMORY_LOG:
       break;
        
   case QXDM_LOG:
       break;
        
   default:
       break;
 }
  
 // TODO: momory log 是否要清空结构待定.
 memset(self,0,sizeof(general_log_control));

 return ret;
}

