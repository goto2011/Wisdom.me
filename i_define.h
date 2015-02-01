/******************************************************************************
            Wisdom.me - Library of functions for C programming.
            Copyright (C), 2010.02-2010.04  duan.gandhi@gmail.com


  File Name     : i_define.h
  Version       : Initial Draft
  Author        : duangan
  Created       : 2010/2/11
  Description   : 基本数据类型定义
  History       :
  				 1. 2010/2/11			duangan			Created file
  				 2. 
  				 3. 

******************************************************************************/

#ifndef I_DEFINE_H
#define I_DEFINE_H
/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

typedef  unsigned int       boolean;     /* Boolean value type */
#define TRUE   1   /* Boolean true value. */
#define FALSE  0   /* Boolean false value. */

#ifndef NULL
    #define NULL 0
#endif

typedef  unsigned long long uint64;      /* Unsigned 64 bit value, only for C99. */
typedef  unsigned long int  uint32;      /* Unsigned 32 bit value */
typedef  unsigned short     uint16;      /* Unsigned 16 bit value */
typedef  unsigned char      uint8;       /* Unsigned 8  bit value */

typedef  long long          int64;       /* Signed 64 bit value, only for C99. */
typedef  signed long int    int32;       /* Signed 32 bit value */
typedef  signed short       int16;       /* Signed 16 bit value */
typedef  signed char        int8;        /* Signed 8  bit value */


// magic number
#define  FILE_LINK_MAGIC_NUMBER_START  0xE47B337D
#define  FILE_LINK_MAGIC_NUMBER_END    0xCE14091A


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

#ifdef __cplusplus
}
#endif

#endif
