/******************************************************************************
            Wisdom.me - Library of functions for C programming.
            Copyright (C), 2010.02-2010.04  duan.gandhi@gmail.com


  File Name     : i_file_adapter.c
  Version       : Initial Draft
  Author        : duangan
  Created       : 2010/2/12
  Description   : 文件系统适配层
  History       :
  				 1. 2010/2/12			duangan			Created file
  				 2. 
  				 3. 

******************************************************************************/

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/
#include "i_file_adapter.h"

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/

#ifdef I_REX_L4_ADAPTER
/*****************************************************************************
 Prototype    : i_file_check_exist
 Description  : check file exist.
 Input        : file_name  
 Output       : None
 Return Value : I_FILE_RW_STATE
 Calls        : 
 Called By    : 
 Others       : 
 
 History      : 
               1. 2010/2/12		 duangan			Created function

*****************************************************************************/
I_FILE_RW_STATE i_file_check_exist(char * file_name)
{
  // if the volume is not exist
  return I_FILE_ERROR_VOLUME_NOT_EXIST;

  // if the directory is not exist
  return I_FILE_ERROR_DIR_NOT_EXIST;

  // if the file is not exist
  return I_FILE_ERROR_FILE_NOT_EXIST;

  // if file exist
  return I_FILE_STATE_OK;
}

/*****************************************************************************
 Prototype    : i_file_open
 Description  : 打开文件
 Input        : file_name  
                open_mode  
 Output       : None
 Return Value : I_FILE_HANDLE_TYPE
 Calls        : 
 Called By    : 
 Others       : 
 
 History      : 
               1. 2010/2/23		 duangan			Created function

*****************************************************************************/
I_FILE_HANDLE_TYPE i_file_open(const char * file_name, int32 open_mode)
{
  I_FILE_HANDLE_TYPE fd = I_FILE_HANDLE_NULL;
  
  if(I_FILE_OPEN_MODE_RW == open_mode)
  {
    fd = efs_open(file_name, open_mode, 0666);
  }
  else
  {
    fd = efs_open(file_name, open_mode);
  }

  return fd;
}
#endif
