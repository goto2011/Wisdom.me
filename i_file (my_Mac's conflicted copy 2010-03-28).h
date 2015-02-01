/******************************************************************************
            Wisdom.me - Library of functions for C programming.
            Copyright (C), 2010.02-2010.04  duan.gandhi@gmail.com


  File Name     : i_file.h
  Version       : Initial Draft
  Author        : duangan
  Created       : 2010/2/11
  Description   : 文件处理头文件
  History       :
  				 1. 2010/2/11			duangan			Created file
  				 2. 
  				 3. 

******************************************************************************/

#ifndef I_FILE_H
#define I_FILE_H

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/
// file operator type define.
typedef enum
{
    I_FILE_TYPE_MIN = 0,        // reserved.
    I_FILE_READ_BINARY,         // binary read.
    I_FILE_READ_SHORT_LINE,     // line read, and the most long line is shorter then 1KB.
    I_FILE_READ_LONG_LINE,      // line read, and the most long line is more then 1KB.
    I_FILE_WRITE_BINARY,        // binary write.
    I_FILE_WRITE_LINE,          // line write.
    I_FILE_TYPE_MAX
} I_FILE_OPERATOR_TYPE;

// file operator state define.
typedef enum
{
    I_FILE_STATE_OK = 0,
    I_FILE_ERROR_VOLUME_NOT_EXIST,
    I_FILE_ERROR_DIR_NOT_EXIST,
    I_FILE_ERROR_FILE_NOT_EXIST,
    I_FILE_ERROR_FILE_BUSY,
    I_FILE_ERROR_LINK_FULL,
    I_FILE_ERROR_LINK_INDEX_ERROR,
    I_FILE_ERROR_LINK_FREE_ERROR,
    I_FILE_ERROR_FILE_IS_OPEN,
    I_FILE_ERROR_FILE_IS_CLOSE,
    I_FILE_ERROR_
    
}I_FILE_RW_STATE;


// file open type
typedef enum
{
    I_FILE_ONCE,        // read/write once.
    I_FILE_RETAIN,      // read/write retain.
    I_FILE_RUNNING,     // read/write running.
}I_FILE_OPEN_TYPE;

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * functions declare                            *
 *----------------------------------------------*/
/*****************************************************************************
 Prototype    : i_file_read
 Description  : read a file.
 Input        : file_name           :file name
                file_operator_type  :flie operator type
                read_size           :read buffer size(if line read,the param only means the frist try buffer size, 
                                     so, if your lines is too long , no problem.)
                read_state          :read state.
                open_type           :file open type.
 Output       : None
 Return Value : char *              :return read buffer.
 Calls        : 
 Called By    : 
 Others       : Read operator will retain the file handle, until close the file.
                This means you can open a file one time at the same time.
 
 History      : 
               1. 2010/2/12		 duangan			Created function

*****************************************************************************/
char * i_file_read(
        const char * file_name,
        const I_FILE_OPERATOR_TYPE file_operator_type,
        const uint32 read_size,
        I_FILE_RW_STATE * read_state,
        const I_FILE_OPEN_TYPE  open_type
        );

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/







#endif

