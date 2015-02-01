/******************************************************************************
            Wisdom.me - Library of functions for C programming.
            Copyright (C), 2010.02-2010.04  duan.gandhi@gmail.com


  File Name     : i_file_adapter.h
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

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/
// define a conut limit of opened at the same time.
#define I_FILE_OPENED_COUNT_MAX  128

// define file handle type.
#define I_FILE_HANDLE_TYPE int32
#define I_FILE_HANDLE_NULL -1

/* define file SEEK operation origin */
#define I_FILE_SEEK_START       FS_SEEK_SET
#define I_FILE_SEEK_CURRENT     FS_SEEK_CURRENT
#define I_FILE_SEEK_END         FS_SEEK_EOF

#define I_FILE_OPEN_MODE_READ   O_RDONLY
#define I_FILE_OPEN_MODE_RW     O_RDWR | O_CREAT | O_TRUNC


/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/
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
               1. 2010/2/12      duangan            Created function

*****************************************************************************/
I_FILE_RW_STATE i_file_check_exist(char * file_name);

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
I_FILE_HANDLE_TYPE i_file_open(const char * file_name, int32 open_mode);

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/

