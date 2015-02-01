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
ԭ�д�ӡת��Ϊ�´�ӡ�ĺ�:
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

// save type(ֻ���sd card �� efs log)
// TODO:����һ�ֱ��淽ʽ��ƹ��buffer.�����Ҫ����ȫ����ӡ��ͬʱ�ִ�ӡ�ǳ���������
typedef enum
{
  SAVE_TYPE_MIN,
  SAVE_NOW,                 /* ÿ��ӡһ��log ��ֱ�ӱ��浽�ļ�ϵͳ�С�ϵͳ�����󣬲�����ʹ�á� */
  SAVE_FUTURE_ALL,          /* ��buffer�д�ӡ��buffer��������. close ʱ�ᱣ��ʣ������. */
  SAVE_FUTURE_CIRCLE,       /* ��buffer�д�ӡ��buffer������ͷ����. close ʱ�ű�����������. */
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
   
  /* log·�����16�ֽ�. */
  /* ·����ʽ����:
  flash �еģ�"/brew/update.app";
  SD���ϵģ� "/mmc1/dload/update.app"; */
  char              dir_name[GENERAL_LOG_DIR_LEN+1];
   
  /* log�ļ�����16�ֽ�,������չ������չ��Ĭ��Ϊ.txt,�������ֻ���ֱ�Ӳ鿴. */
  char              file_name[GENERAL_LOG_FILE_LEN+1];     
  uint8 *           buffer_ptr;
  uint32            buffer_len;
  uint32            item_max_len;   /* ÿ��log����󳤶� */
  uint32            msg_ID;         /* ָqxdm id */
  uint8             msg_mask;       /* ָqxdm mask */
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
Description  : ��ӡ log
Input        :
               const char * file  code file name
               const uint16 line  code file line
               const uint32 handle  
               const char *format     
               const int32 a    param 1  (֧�ָ���)
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

