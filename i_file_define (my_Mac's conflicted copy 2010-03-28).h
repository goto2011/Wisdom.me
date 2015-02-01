/******************************************************************************
            Wisdom.me - Library of functions for C programming.
            Copyright (C), 2010.02-2010.04  duan.gandhi@gmail.com


  File Name     : i_file_define.h
  Version       : Initial Draft
  Author        : duangan
  Created       : 2010/2/12
  Description   : �ļ�ϵͳ��ȫ�����Լ�����ʽӿ�
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

// file handle type.
typedef struct
{
  uint32                magic_start;       // first magic number
  boolean               file_is_open;      // true:open ; false:close
  I_FILE_HANDLE_TYPE    file_link;       // file handle for file system
  char  *               file_route;        // file route and name
  int8   **             p_file_buffer;     // file read buffer ptr
  uint32                magic_end;         // end magic number
} i_file_link_type;

/*----------------------------------------------*
 * function declare                             *
 *----------------------------------------------*/
/*****************************************************************************
 Prototype    : i_check_file_handle_state
 Description  : ����ļ����״̬�Ƿ��.
 Input        : file_state  
                open_type   
 Output       : None
 Return Value : boolean     :ture    ok;
                             false   fail
 Calls        : 
 Called By    : 
 Others       : 
 
 History      : 
               1. 2010/2/21      duangan            Created function

*****************************************************************************/
boolean i_check_file_link_state(const I_FILE_RW_STATE file_state,const I_FILE_OPEN_TYPE open_type);


/*****************************************************************************
 Prototype    : i_check_file_opened
 Description  : ����ļ��Ƿ��. ����Ѵ�, �򷵻ظþ���ṹ.
 Input        : file_name  
 Output       : None
 Return Value : i_file_handle_type *
 Calls        : 
 Called By    : 
 Others       : 
 
 History      : 
               1. 2010/2/21		 duangan			Created function

*****************************************************************************/
i_file_link_type * i_check_file_opened(char * file_name, I_FILE_RW_STATE * alloc_state);


/*****************************************************************************
 Prototype    : i_get_file_route_max_length
 Description  : ��ȡ�ļ�ϵͳ·����󳤶�
 Input        : None
 Output       : None
 Return Value : uint32
 Calls        : 
 Called By    : 
 Others       : 
 
 History        :
                1. 2010/2/12         duangan            Created function

*****************************************************************************/
uint32 i_get_file_route_max_length();

/*****************************************************************************
 Prototype    : i_get_file_route_max_length
 Description  : ��ȡ�ļ�ϵͳ·����󳤶�
 Input        : None
 Output       : None
 Return Value : uint32
 Calls        : 
 Called By    : 
 Others       : 
 
 History        :
  				1. 2010/2/12		 duangan			Created function

*****************************************************************************/
uint32 i_get_file_route_max_length();

/*****************************************************************************
 Prototype    : i_get_file_name_max_length
 Description  : ��ȡ�ļ�����󳤶�
 Input        : None
 Output       : None
 Return Value : uint32
 Calls        : 
 Called By    : 
 Others       : 
 
 History      : 
               1. 2010/2/12		 duangan			Created function

*****************************************************************************/
uint32 i_get_file_name_max_length();

/*****************************************************************************
 Prototype    : i_set_file_name_max_length
 Description  : �����ļ�����󳤶�
 Input        : new_max_length  
 Output       : None
 Return Value : void
 Calls        : 
 Called By    : 
 Others       : 
 
 History      : 
               1. 2010/2/12		 duangan			Created function

*****************************************************************************/
void i_set_file_name_max_length(uint32 new_max_length);

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

