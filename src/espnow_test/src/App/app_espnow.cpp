/**
 * @file app_espnow.cpp
 * @version 26081222.160
 */

#include "app_espnow.h"
#include "cmn_setting.h"
#include "../Mid/mid_espnow.h"
#include "../Mid/mid_task.h"

#ifdef USE_ESPNOW
#include <esp_mac.h>  // For the MAC2STR and MACSTR macros
#include "ESP32_NOW_Serial.h"
#include "MacAddress.h"
#include "WiFi.h"
#include "esp_wifi.h"
#endif /* USE_ESPNOW */

//******************************************************
// グローバル変数定義
//******************************************************

U_PAYLOAD payload_rx;
U_PAYLOAD payload_tx;

//******************************************************
// ローカル型定義
//******************************************************

//******************************************************
// ローカル変数定義
//******************************************************

#define ESPNOW_HEADER                   ((u2)0x5A5AU)                           /** 送受信データヘッダー */
#define ESPNOW_FOOTER                   ((u2)0xA5A5U)                           /** 送受信データフッター */

#define ESPNOW_TIMEOUT_MS               ((u8)1000U)                             /** タイムアウト判定値[ms] */
#define ESPNOW_WAIT                     (10U)                                   /** 待機時間[-] */
#define ESPNOW_TIMEOUT                  ((u8)ESPNOW_TIMEOUT_MS / ESPNOW_WAIT)   /** タイムアウト判定値 */

static bool bi_isready = false;
static bool bi_isrun = false;
static u8 u8_txcnt = 0;
static u8 u8_rxcnt_old = 0, u8_rxcnt_now = 0;
static u8 u8_waitrx = 0;

//******************************************************
// ローカル関数宣言
//******************************************************

static void espnow_rx(void* pvParameters);
static void espnow_tx(void* pvParameters);


//******************************************************
// 関数定義
//******************************************************

static void espnow_midsetup(void){
#ifdef USE_ESPNOW
    if(!bi_isready){
        espnow_setup();
        bi_isready = true;
    }
#endif /* USE_ESPNOW */
}

static void espnow_rx(void* pvParameters) {
#ifdef USE_ESPNOW
    U_PAYLOAD payload_tmp;
    while (1) {
        u8_rxcnt_old = u8_rxcnt_now;
        if(!bi_isrun && espnow_getrx(payload_tmp.bytes, sizeof(S_PAYLOAD))){
            bi_isrun = true;
            if((payload_tmp.payload.header == ESPNOW_HEADER) && (payload_tmp.payload.footer == ESPNOW_FOOTER)){
                u8_rxcnt_now = payload_tmp.payload.tm;
                memcpy(payload_rx.bytes, payload_tmp.bytes, sizeof(S_PAYLOAD));
                task_xQueueSend(E_TASK_Q_ESPNOW_RX);
            }
            bi_isrun = false;
        }
        else{
            M5.delay(ESPNOW_WAIT);
        }
        if(u8_rxcnt_old != u8_rxcnt_now){
            u8_waitrx = 0;
        }
        else if(u8_waitrx < 0xFFFFFFFFUL){
            u8_waitrx++;
        }
        //M5.Log.printf("u8_waitrx =%8ld\n",u8_waitrx);
    }
#endif /* USE_ESPNOW */
    vTaskDelete(NULL);
}

static void espnow_tx(void* pvParameters) {
#ifdef USE_ESPNOW
    if(!bi_isrun){
        bi_isrun = true;
        u8_txcnt++;
        u8 u8_tm = u8_txcnt;
        payload_tx.payload.header = ESPNOW_HEADER;
        payload_tx.payload.tm = (u4)(u8_tm & 0xFFFFFFFFU);
        payload_tx.payload.footer = ESPNOW_FOOTER;
        espnow_settx(payload_tx.bytes, sizeof(S_PAYLOAD));
        bi_isrun = false;
    }
#endif /* USE_ESPNOW */
    vTaskDelete(NULL);
}

bi espnow_isrxtimeout(void){
    return (bi)(u8_waitrx >= ESPNOW_TIMEOUT);
}

void espnow_rxAsync(void) {
#ifdef USE_ESPNOW
    espnow_midsetup();
    xTaskCreatePinnedToCore(
        espnow_rx
        , "espnow_rx"
        , COREBUF_ESPNOW
        , NULL
        , COREPRI_ESPNOW
        , NULL
        , CORESEL_ESPNOW
    );
#endif /* USE_ESPNOW */
}

void espnow_txAsync(void) {
#ifdef USE_ESPNOW
    espnow_midsetup();
    xTaskCreatePinnedToCore(
        espnow_tx
        , "espnow_tx"
        , COREBUF_ESPNOW
        , NULL
        , COREPRI_ESPNOW
        , NULL
        , CORESEL_ESPNOW
    );
#endif /* USE_ESPNOW */
}
