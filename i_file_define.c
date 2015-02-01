/******************************************************************************
            Wisdom.me - Library of functions for C programming.
            Copyright (C), 2010.02-2010.04  duan.gandhi@gmail.com


  File Name     : i_file_define.c
  Version       : Initial Draft
  Author        : duangan
  Created       : 2010/2/12
  Description   : 文件系统全局属性及其访问接口.
  History       :
  				 1. 2010/2/12			duangan			Created file
  				 2. 
  				 3. 

******************************************************************************/

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/
#include "i_file_define.h"
#include "i_file.h"

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/
#define I_CHECK_FILE_HANDLE_VALID(m) (((m).magic_start == FILE_HANDLE_MAGIC_NUMBER_START) && \
                                     ((m).magic_end == FILE_HANDLE_MAGIC_NUMBER_END))

#define I_CHECK_FILE_HANDLE_INIT(m) \
    do \
    {  \
      (m).magic_start = FILE_HANDLE_MAGIC_NUMBER_START;  \
      (m).magic_end = FILE_HANDLE_MAGIC_NUMBER_END;      \
    }while(0)
    
/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/
// 定义路径最大长度 (默认值为2048 B)
static uint32 i_file_route_max_length = 2048;

// 定义文件名最大长度 (默认值为768 B)
static uint32 i_file_name_max_length = 768;

// Define file handle array.
static i_file_link_type i_file_link[I_FILE_OPENED_COUNT_MAX + 1];
static uint32 i_file_array_count = 0;

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
 * static funciton implementations                    *
 *----------------------------------------------*/

/*****************************************************************************
 Prototype    : i_check_file_handle_state
 Description  : 检测文件句柄状态是否对.
 Input        : file_state  
                open_type   
 Output       : None
 Return Value : boolean     :ture    ok;
                             false   fail
 Calls        : 
 Called By    : 
 Others       : 
 
 History      : 
               1. 2010/2/21		 duangan			Created function

*****************************************************************************/
static boolean i_check_file_link_state(const I_FILE_RW_STATE file_state,const I_FILE_OPEN_TYPE open_type)
{
  if(I_FILE_ERROR_FILE_IS_OPEN == file_state)
  {
    if(I_FILE_RUNNING == open_type)return TRUE;
    else
        return FALSE;
  }
  else if(I_FILE_ERROR_FILE_IS_CLOSE == file_state)
  {
    if(I_FILE_RUNNING == open_type)return FALSE;
    else
        return TRUE;
  }

  return FALSE;
}

/*****************************************************************************
 Prototype    : i_check_file_opened
 Description  : 检测文件是否打开. 如果已打开, 则返回该句柄结构.
 Input        : file_name  
 Output       : None
 Return Value : i_file_handle_type *
 Calls        : 
 Called By    : 
 Others       : 
 
 History      : 
               1. 2010/2/21		 duangan			Created function

*****************************************************************************/
static int32 * i_check_file_opened(char * file_name, I_FILE_RW_STATE * alloc_state)
{
  uint32  ii;

  // loop the file handle array.
  for(ii = 0; ii < I_FILE_OPENED_COUNT_MAX; ii++)
  {
    if(I_CHECK_FILE_HANDLE_VALID(i_file_link[ii]))
    {
      // file name is ok, and that`s state is open.
      if((strnstr(i_file_link[ii].file_route,file_name,i_file_route_max_length)
          &&(i_file_link[ii].file_is_open))
      {
        alloc_state = I_FILE_ERROR_FILE_IS_OPEN;
        return ii;
      }
    }
  }

  // the file handle is full.
  if(ii < I_FILE_OPENED_COUNT_MAX)
  {
    alloc_state = I_FILE_ERROR_FILE_IS_CLOSE;
  }
  else
  {
    alloc_state = I_FILE_ERROR_LINK_FULL;
  }

  return -1;
}


/*****************************************************************************
 Prototype    : i_file_link_alloc
 Description  : 分配文件句柄节点.
 Input        : alloc_state  return state.
 Output       : None
 Return Value : static int32: file link index.
 Calls        : 
 Called By    : 
 Others       : 
 
 History      : 
               1. 2010/2/22		 duangan			Created function

*****************************************************************************/
static int32 i_file_link_alloc(I_FILE_RW_STATE * alloc_state)
{
  uint32  ii;
  uint32  available_node = 0;
  boolean alloc_memory = FALSE;

  for(ii = 0; ii < I_FILE_OPENED_COUNT_MAX; ii++)
  {
    // if node do not alloc, or the handle is free.
    if(!I_CHECK_FILE_HANDLE_VALID(i_file_link[ii])
        ||!i_file_link.file_is_open)
    {
      break;
    }
  }

  if(ii < I_FILE_OPENED_COUNT_MAX)
  {
    memset(i_file_link[ii], 0 ,sizeof(i_file_link_type));
    I_CHECK_FILE_HANDLE_INIT(i_file_link[ii]);

    alloc_state = I_FILE_STATE_OK;
    return ii;
  }
  else
  {
    alloc_state = I_FILE_ERROR_LINK_FULL;
    return -1;
  }
}


/*****************************************************************************
 Prototype    : i_file_handle_free
 Description  : 释放文件句柄
 Input        : file_handle_index  
                free_state         
 Output       : None
 Return Value : static
 Calls        : 
 Called By    : 
 Others       : 
 
 History      : 
               1. 2010/2/23		 duangan			Created function

*****************************************************************************/
static void i_file_link_free(uint32 index, I_FILE_RW_STATE * free_state)
{
  if(index > I_FILE_OPENED_COUNT_MAX)
  {
    free_state = I_FILE_ERROR_LINK_INDEX_ERROR;
    return ;
  }

  if(!I_CHECK_FILE_HANDLE_VALID(i_file_link[index])
  {
    free_state = I_FILE_ERROR_LINK_FREE_ERROR;
    return;
  }

  i_file_link[index].file_is_open = FALSE;

  // free memory.
  if(i_file_link[index].file_route)
  {
    i_free(i_file_link[index].file_route);
  }
  
  if(i_file_link[index].p_file_buffer)
  {
    i_free(i_file_link[index].p_file_buffer);
  }
  
  memset(i_file_link[index], 0 ,sizeof(i_file_link_type));
  
  free_state = I_FILE_STATE_OK;
  return;
}

/*----------------------------------------------*
 * interface funciton implementations            *
 *----------------------------------------------*/

/*****************************************************************************
 Prototype    : i_get_file_handle
 Description  : 获取文件句柄.
 Input        : file_name    
                open_type    
                alloc_state             返回状态.
 Output       : None
 Return Value : I_FILE_HANDLE_TYPE      返回句柄,如果失败,则返回空句柄.
 Calls        : 
 Called By    : 
 Others       : 已定事宜:
                1. 这里有个权衡, 到底要不要把 i_file_handle_type 节点的指针公布给 i_file.c ;
                ==> i_file_handle_type 封装在本地,不需要公布出去.
                2. 要不要把这个函数的功能修改为获取句柄, 这样对调用方很方便.
                但是也有问题, 就是需要在这里调用内存分配和文件的打开关闭了.
                ==> 确定使用该方法.
 History      : 
               1. 2010/2/22		 duangan			Created function

*****************************************************************************/
int32 i_get_file_link(
                      char * file_name,
                      const I_FILE_OPEN_TYPE open_type, 
                      I_FILE_RW_STATE * get_state
                      )
{
  int32 file_link;
  
  file_link = i_check_file_opened(file_name, &get_state);

  // if handle array full
  if(I_FILE_ERROR_LINK_FULL == get_state)
  {
    return -1;
  }

  // if handle state error.
  if(!i_check_file_link_state(get_state,open_type))
  {
    return -1;
  }

  // if file is open
  if(I_FILE_ERROR_FILE_IS_OPEN == get_state)
  {
    return file_link;
  }

  // alloc new handle node
  file_link = i_file_link_alloc(&get_state);
  if(I_FILE_STATE_OK == get_state)
  {
    return file_link;
  }
  else
  {
    return -1;
  }
}

