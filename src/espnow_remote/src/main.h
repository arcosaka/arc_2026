/**
 * @file main.h
 * @version 26080718.200
 */

#ifndef LOAD_MAIN_H
#define LOAD_MAIN_H

#include <Arduino.h>
#include <M5Unified.h>
#include "build_info.h"
#include "device_info.h"

//******************************************************
// グローバル型定義
//******************************************************

typedef bool        bi;
typedef int8_t      s1;
typedef uint8_t     u1;
typedef int16_t     s2;
typedef uint16_t    u2;
typedef int32_t     s4;
typedef uint32_t    u4;
typedef int64_t     s8;
typedef uint64_t    u8;
typedef float       f1;
typedef double      f2;

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

#endif /* LOAD_MAIN_H */
