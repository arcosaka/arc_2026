/**
 * @file app_espnow.h
 * @version 26081222.160
 */

#ifndef LOAD_APP_ESPNOW
#define LOAD_APP_ESPNOW

#include "main.h"

//******************************************************
// グローバル型定義
//******************************************************

typedef struct struct_BITFLAG_BODY {
    u1 isbody   : 1;
    u1 isready  : 1;
    u1 dummy_02 : 1;
    u1 dummy_03 : 1;
    u1 dummy_04 : 1;
    u1 dummy_05 : 1;
    u1 dummy_06 : 1;
    u1 dummy_07 : 1;
} S_BITFLAG_BODY;

typedef struct struct_BITFLAG_REMOTE {
    u1 isremote : 1;
    u1 isready  : 1;
    u1 dummy_02 : 1;
    u1 dummy_03 : 1;
    u1 dummy_04 : 1;
    u1 dummy_05 : 1;
    u1 dummy_06 : 1;
    u1 dummy_07 : 1;
} S_BITFLAG_REMOTE;

typedef struct struct_PAYLOAD {
                    /**  sz  x  y  */
    u2 header;      /** [ 2: 0: 0] */
    union {
        S_BITFLAG_BODY bits;
        u1 b;
    } body;         /** [ 1: 0: 2] */
    union {
        S_BITFLAG_REMOTE bits;
        u1 b;
    } remote;       /** [ 1: 0: 3] */
    u4 tm;          /** [ 4: 1: 0] */
    s2 current;     /** [ 4: 2: 0] */
    u2 voltage;     /** [ 4: 2: 2] */
    u2 joyx;        /** [ 2: 3: 0] */
    u2 joyy;        /** [ 2: 3: 2] */
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

bi espnow_isrxtimeout(void);
void espnow_rxAsync(void);
void espnow_txAsync(void);

#endif /* LOAD_APP_ESPNOW */
