/******************************************************************************
            Wisdom.me - Library of functions for C programming.
            Copyright (C), 2010.02-2010.04  duan.gandhi@gmail.com


  File Name     : i_string.h
  Version       : Initial Draft
  Author        : duangan
  Created       : 2010/3/9
  Description   : string函数库头文件
  History       :
  				 1. 2010/3/9			duangan			Created file
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
 Prototype    : i_string_reversal
 Description  : 字符数组翻转(由于指定了字节数，所以字符数组中间可以包含\0)
 Input        : des            
              count_by_byte  : 要翻转的字节数.
 Output       : des
 Return Value : void
 Calls        : 
 Called By    : 
 Others       : 
 
 History      : 
             1. 2010/3/9       duangan            Created function

*****************************************************************************/
void i_string_reversal(char * des, uint32 count_by_byte);

