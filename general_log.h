#ifndef GENERAL_LOG_H
#define GENERAL_LOG_H

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

#define GENERAL_LOG_DIR_LEN        16
#define GENERAL_LOG_FILE_LEN       16

/*
原有打印转化为新打印的宏:
example1:
#define dload_log_write(msg_log) GENERAL_LOG_PRINT(dload_log_handle,(msg_log),0,0,0)

example2:
#define save_dload_log(msg_handle,msg_log,num1,num2,num3) GENERAL_LOG_PRINT(msg_handle,msg_log,num1,num2,num3)
*/

#define GENERAL_LOG_PRINT(handle,msg_string,num1,num2,num3)  \
   general_log_print(__MODULE__,__LINE__,(handle),(msg_string),(num1),(num2),(num3))

// general log type
typedef enum
{
  LOG_TYPE_MIN,
  MEMORY_LOG,       /* memory log */
  SD_CARD_LOG,      /* sd card log */
  EFS_LOG,          /* efs log */
  QXDM_LOG,         /* qxdm log(via usb) */
  LOG_TYPE_MAX
}general_log_type;

// save type(只针对sd card 和 efs log)
// TODO:还有一种保存方式，乒乓buffer.针对需要保持全部打印，同时又打印非常多的情况。
typedef enum
{
  SAVE_TYPE_MIN,
  SAVE_NOW,                 /* 每打印一条log 都直接保存到文件系统中。系统开销大，不建议使用。 */
  SAVE_FUTURE_ALL,          /* 往buffer中打印，buffer满即保存. close 时会保存剩余数据. */
  SAVE_FUTURE_CIRCLE,       /* 往buffer中打印，buffer满即从头覆盖. close 时才保存所有数据. */
  SAVE_TYPE_MAX
}general_log_save_policy;


// log error
typedef enum
{
  HANDLE_FULL                   = -23,          /* handle full. */
  BUFFER_IS_EMPTY               = -22,          /* buffer is empty. */
  DIR_CREATE_FAIL               = -20,          /* dir create fail */
  FILE_CREATE_FAIL              = -19,          /* file create fail */
  HANDLE_INVALIDE               = -18,          /* handle invalide */
  MAGIC_NUMBER_ERROR            = -17,          /* magic number error */
  TYPE_NOT_SUPPORT              = -16,
  BUFFER_PTR_IS_INVALID         = -15,
  BUFFER_LEN_IS_INVALID         = -14,
  FILE_SYSTEM_WRITE_FAIL        = -13,
  FILE_SYSTEM_WRITE_Incomplete  = -12,
  LOG_OK                        = 0,
  BUFFER_FULL                   = 1,          /* buffer full */
  FILE_SYSTEM_WRITE_OK          = 2,
}general_log_error_type;

// general log control(52B)
typedef struct
{
  general_log_type  log_type;
  general_log_save_policy  save_policy;
   
  /* log路径，最长16字节. */
  /* 路径格式如下:
  flash 中的："/brew/update.app";
  SD卡上的： "/mmc1/dload/update.app"; */
  char              dir_name[GENERAL_LOG_DIR_LEN+1];
   
  /* log文件名，16字节,不含扩展名，扩展名默认为.txt,可以在手机中直接查看. */
  char              file_name[GENERAL_LOG_FILE_LEN+1];     
  uint8 *           buffer_ptr;
  uint32            buffer_len;
  uint32            item_max_len;   /* 每条log的最大长度 */
  uint32            msg_ID;         /* 指qxdm id */
  uint8             msg_mask;       /* 指qxdm mask */
}general_log_param;


/*****************************************************************************
Prototype    : general_log_init
Description  : general log init
Input        : const general_log_param log_param  
Output       : nono
Return Value : if return < 0,indicate a error occur. return is general_log_error_type
Calls        :
Called By    :

 History        :
 1.Date         : 2009/7/30
   Author       : duangan
   Modification : Created function

*****************************************************************************/
int32 general_log_init(const general_log_param log_param);

/*****************************************************************************
Prototype    : general_log_print
Description  : 打印 log
Input        :
               const char * file  code file name
               const uint16 line  code file line
               const uint32 handle  
               const char *format     
               const int32 a    param 1  (支持负数)
               const int32 b    param 2    
               const int32 c    param 3    
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
);

/*****************************************************************************
Prototype    : general_log_close
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
int32 general_log_end(uint32 handle);

#endif /* GENERAL_LOG_H */

