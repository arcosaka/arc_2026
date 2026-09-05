/**
 * @file app_serialio.h
 * @version 26081222.160
 */

#ifndef LOAD_APP_SERIALIO_H
#define LOAD_APP_SERIALIO_H

#include "typedef.h"

//******************************************************
// グローバル型定義
//******************************************************

typedef struct struct_BUTTON{
    U2 isfull   : 1;    /* 00:00 */
    U2 x_up     : 1;    /* 01:01 */
    U2 x_right  : 1;    /* 02:02 */
    U2 x_down   : 1;    /* 03:03 */
    U2 x_left   : 1;    /* 04:04 */
    U2 btnx     : 1;    /* 05:05 */
    U2 btna     : 1;    /* 06:06 */
    U2 btnb     : 1;    /* 07:07 */
    U2 btny     : 1;    /* 08:08 */
    U2 l1       : 1;    /* 09:09 */
    U2 r1       : 1;    /* 10:10 */
    U2 l2       : 1;    /* 11:11 */
    U2 r2       : 1;    /* 12:12 */
    U2 l3       : 1;    /* 13:13 */
    U2 r3       : 1;    /* 14:14 */
    U2 dummy    : 1;    /* 15:15 */
}S_BUTTON;

typedef union union_BUTTON
{
    S_BUTTON bits;
    U2 word;
} U_BUTTON;

typedef struct struct_DATA_CONT {
                    /**  sz  x  y  */
    U2 header;      /** [ 2: 0: 0] */
    U2 stamp;       /** [ 2: 1: 0] */
    U_BUTTON btns;  /** [ 2: 2: 0] */
    U2 chksum;      /** [ 2: 3: 0] */
    U2 footer;      /** [ 2: 4: 0] */
} S_DATA_CONT;      /** コントローラ→本体制御データ */

typedef union union_DATA_CONT {
    U1 bytes[sizeof(S_DATA_CONT)];
    S_DATA_CONT data;
} U_DATA_CONT;

//******************************************************
// グローバル変数宣言
//******************************************************

#define SERIALIO_HEADER ((U2)0x5A5AU)   /** 送受信データヘッダー */
#define SERIALIO_FOOTER ((U2)0x0A0DU)   /** 送受信データフッター */

extern U_DATA_CONT serialio_data_b;
extern U_DATA_CONT serialio_data_c;

//******************************************************
// グローバル関数宣言
//******************************************************

void SerialIO_TxData(void);
void SerialIO_RxData(void);
U2 SerialIO_CalcChkSum(U1* pu1_data, U1 u1_size);
BI SerialIO_ValidateChkSum(U1* pu1_data, U1 u1_size, U2 u2_cs);

#endif /* LOAD_APP_SERIALIO_H */
