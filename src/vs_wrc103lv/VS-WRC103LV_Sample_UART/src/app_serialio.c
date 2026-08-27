/**
 * @file app_serialio.c
 * @version 26081222.160
 */

#include "app_serialio.h"
#include "vs-wrc103.h"

//******************************************************
// グローバル変数定義
//******************************************************

U_DATA_BODY serialio_data_b;  /** 本体→コントローラ制御データ(TX) */
U_DATA_CONT serialio_data_c;  /** コントローラ→本体制御データ(RX) */

//******************************************************
// ローカル型定義
//******************************************************

//******************************************************
// ローカル変数定義
//******************************************************

//******************************************************
// 関数定義
//******************************************************

/**
 * @brief   あらかじめ設定しているデータを相手に送信します
 */
void SerialIO_TxData(void){

}

/**
 * @brief   受信したデータを解析し、グローバル変数に保存します
 */
void SerialIO_RxData(void){

}

U2 SerialIO_CalcChkSum(U1* pu1_data, U1 u1_size){
    U2 u2_data = 0;
    for (U1 u1_i = 0; u1_i < u1_size; u1_i++)
    {
        u2_data += (U2)pu1_data[u1_i];
    }
    u2_data = (U2)((U4)0x10000U - (U4)u2_data);
    return u2_data;
}

BI SerialIO_ValidateChkSum(U1* pu1_data, U1 u1_size, U2 u2_cs){
    U2 u2_data = 0;
    for (U1 u1_i = 0; u1_i < u1_size; u1_i++)
    {
        u2_data += (U2)pu1_data[u1_i];
    }
    return (BI)(((u2_data + u2_cs) == 0) ? TRUE : FALSE);
}
