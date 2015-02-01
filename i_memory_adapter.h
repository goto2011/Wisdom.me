/******************************************************************************
            Wisdom.me - Library of functions for C programming.
            Copyright (C), 2010.02-2010.04  duan.gandhi@gmail.com


  File Name     : i_memory.h
  Version       : Initial Draft
  Author        : duangan
  Created       : 2010/2/21
  Description   : 内存管理
  History       :
  				 1. 2010/2/21			duangan			Created file
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
  Prototype    : i_malloc
  Description  : 分配内存.
  Input        : size  
  Output       : None
  Return Value : void
  Calls        : 
  Called By    : 
  Others       : 
  
  History      : 
                1. 2010/2/21      duangan            Created function
 
 *****************************************************************************/
 void * i_malloc(uint32 size);

 /*****************************************************************************
  Prototype    : i_free
  Description  : 释放内存.
  Input        : p  
  Output       : None
  Return Value : void
  Calls        : 
  Called By    : 
  Others       : 
  
  History      : 
                1. 2010/2/21      duangan            Created function
 
 *****************************************************************************/
 void * i_free(void * p);

 /*****************************************************************************
  Prototype    : i_re_malloc
  Description  : 重新分配内存
  Input        : p     
                 size  
  Output       : None
  Return Value : void
  Calls        : 
  Called By    : 
  Others       : 
  
  History      : 
                1. 2010/2/21      duangan            Created function
 
 *****************************************************************************/
 void * i_re_malloc(void *p, uint32 size);

