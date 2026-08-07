/**
 * @file app_espnow.h
 * @version 26080718.200
 */

#ifndef LOAD_APP_ESPNOW
#define LOAD_APP_ESPNOW

#include "main.h"
#include "cmn_setting.h"

//******************************************************
// グローバル型定義
//******************************************************

typedef struct struct_PAYLOAD {
                    /**  sz  x  y  */
    u2 header;      /** [ 2: 0: 0] */
    u2 tm_h;        /** [ 2: 0: 2] */
    u4 tm_l;        /** [ 4: 1: 0] */
    s2 current;     /** [ 4: 2: 0] */
    u2 voltage;     /** [ 4: 2: 2] */
    s2 joyx;        /** [ 2: 3: 0] */
    s2 joyy;        /** [ 2: 3: 2] */
    u2 joyb;        /** [ 2: 4: 0] */
    u2 footer;      /** [ 2: 4: 2] */
} S_PAYLOAD;

typedef union union_PAYLOAD {
    u1 bytes[sizeof(S_PAYLOAD)];
    S_PAYLOAD payload;
} U_PAYLOAD;

//******************************************************
// グローバル変数宣言
//******************************************************

extern U_PAYLOAD payload_rx;
extern U_PAYLOAD payload_tx;

//******************************************************
// グローバル関数宣言
//******************************************************

void espnow_rxAsync(void);
void espnow_txAsync(void);

#endif /* LOAD_APP_ESPNOW */
