/**
 * @file app_espnow.h
 * @version 26053112.280
 */

#ifndef LOAD_APP_ESPNOW
#define LOAD_APP_ESPNOW

#include "main.h"

//******************************************************
// グローバル型定義
//******************************************************

typedef struct struct_PAYLOAD {
    u4 timestamp;
    u2 randdata;
    s2 gx;
    s2 gy;
    s2 gz;
} S_PAYLOAD;

typedef union union_PAYLOAD {
    u1 bytes[sizeof(S_PAYLOAD)];
    S_PAYLOAD s_payload;
} U_PAYLOAD;

//******************************************************
// グローバル変数宣言
//******************************************************

extern volatile U_PAYLOAD u_payload;

//******************************************************
// グローバル関数宣言
//******************************************************

void espnow_setup(void);

#endif /* LOAD_APP_ESPNOW */
