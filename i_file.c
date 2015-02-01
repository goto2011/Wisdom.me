/******************************************************************************
            Wisdom.me - Library of functions for C programming.
            Copyright (C), 2010.02-2010.04  duan.gandhi@gmail.com


  File Name     : i_file.c
  Version       : Initial Draft
  Author        : duangan
  Created       : 2010/2/11
  Description   : 文件处理代码文件
  History       :
  				 1. 2010/2/11			duangan			Created file
  				 2. 
  				 3. 

******************************************************************************/

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/
#include "i_file.h"
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
 Others       : 已定事宜:
                1. Read operator will retain the file handle, until close the file.
                This means you can open a file one time at the same time.
                未定事宜:
                1. 将来最后一个参数, 应该改为可选;
 
 History      : 
               1. 2010/2/12		 duangan			Created function

*****************************************************************************/
char * i_file_read(
        const char *                file_name,
        const I_FILE_OPERATOR_TYPE  file_operator_type,
        const uint32                read_size,
        I_FILE_RW_STATE *           read_state,
        const I_FILE_OPEN_TYPE      open_type
        )
{
  int32 file_link;
  I_FILE_RW_STATE * my_link_state;
  
  // 1. check file exist.
  read_state = i_file_check_exist(file_name);
  if(!read_state)
  {
    return NULL;
  }
  
  // 2. check file is opened.

  // 3. alloc buffer
  // 这里还是要改.
  file_link = i_get_file_link(file_name,open_type,&read_state);
  if(-1 == file_link)
  {
    return NULL;
  }
  
  // 4. open the file
  

  // 5. read data to buffer.

  // 6. if operator_type is line read, find newline symbol.
  //    if exist, remalloc the buffer to delete unwanted code.

  // 7. if not exist, so remalloc 4 times biger buffer to read back data. such-and-such...
  //    But the max line length is 64K.
  
}


