/**
 * @file app_serialio.c
 * @version 26081222.160
 */

#include "app_serialio.h"
#include "vs-wrc103.h"

#include "app_event.h"

//******************************************************
// グローバル変数定義
//******************************************************

U_DATA_CONT serialio_data_b;  /** 本体→コントローラ制御データ(TX) */
U_DATA_CONT serialio_data_c;  /** コントローラ→本体制御データ(RX) */

//******************************************************
// ローカル型定義
//******************************************************

//******************************************************
// ローカル変数定義
//******************************************************

#define SERIALIO_DATASIZE               (sizeof(S_DATA_CONT))
#define SERIALIO_CHKSUMSIZE(pu_cont)    (SERIALIO_DATASIZE - sizeof(pu_cont->data.chksum) - sizeof(pu_cont->data.footer))

U_DATA_CONT* pu_cont_tx = &serialio_data_b;
U_DATA_CONT* pu_cont_rx = &serialio_data_c;

//******************************************************
// 関数定義
//******************************************************

/**
 * @brief   あらかじめ設定しているデータを相手に送信します
 */
void SerialIO_TxData(void){
    pu_cont_tx->data.header = SERIALIO_HEADER;
    pu_cont_tx->data.chksum
        = SerialIO_CalcChkSum(pu_cont_tx->bytes, SERIALIO_CHKSUMSIZE(pu_cont_tx));
    pu_cont_tx->data.footer = SERIALIO_FOOTER;
    SciTx(pu_cont_tx->bytes, SERIALIO_DATASIZE);
}

/**
 * @brief   受信したデータを解析し、グローバル変数に保存します
 */
void SerialIO_RxData(void){
    uint8_t u1_tmp;
    U4 u4_read;
    BI bi_iscsok;
    u4_read = SciRx(pu_cont_rx->bytes, SERIALIO_DATASIZE);
    if(
        (u4_read == SERIALIO_DATASIZE)
     && (pu_cont_rx->data.header == SERIALIO_HEADER)
     && (pu_cont_rx->data.footer == SERIALIO_FOOTER)
    ){
        bi_iscsok = SerialIO_ValidateChkSum(pu_cont_rx->bytes, SERIALIO_CHKSUMSIZE(pu_cont_rx), pu_cont_rx->data.chksum);
        if(bi_iscsok){
            Event_SetEvent(E_EVE_MAIN);
        }
    }

    /* 不要な受信データをバッファから削除 */
    DI();
    while (SciByteRx(&u1_tmp)){}
    RI();
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
