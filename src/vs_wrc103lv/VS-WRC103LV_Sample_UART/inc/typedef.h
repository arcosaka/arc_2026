/**
 * @file typedef.h
 * @version 26081222.160
 */

#ifndef LOAD_TYPEDEF_H
#define LOAD_TYPEDEF_H

#include "type.h"

//******************************************************
// グローバル型定義
//******************************************************

typedef uint8_t     BI;
typedef int8_t      S1;
typedef uint8_t     U1;
typedef int16_t     S2;
typedef uint16_t    U2;
typedef int32_t     S4;
typedef uint32_t    U4;
typedef int64_t     S8;
typedef uint64_t    U8;

#define ARRSIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define D2STR(d,c) dtostrf( \
    (d)\
  , (((d)>=10000?5:((d)>=1000)?4:((d)>=100)?3:((d)>=10)?2:1)+3)\
  , 2\
  , (c)\
)

//******************************************************
// グローバル変数宣言
//******************************************************

//******************************************************
// グローバル関数宣言
//******************************************************

#endif /* LOAD_TYPEDEF_H */
