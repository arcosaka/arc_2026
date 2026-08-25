/**
 * @file mid_espnow.cpp
 * @version 26081222.160
 */

#include "mid_espnow.h"
#include "mid_m5stack.h"
#include "Mid/mid_pref.h"

#ifdef USE_ESPNOW
#include <esp_mac.h>  // For the MAC2STR and MACSTR macros
#include "Network.h"
#include "ESP32_NOW_Serial.h"
#include "MacAddress.h"
#include "WiFi.h"
#include "esp_wifi.h"
#endif /* USE_ESPNOW */


//******************************************************
// グローバル変数定義
//******************************************************

volatile SemaphoreHandle_t smh_espnow;

//******************************************************
// ローカル型定義
//******************************************************

//******************************************************
// ローカル変数定義
//******************************************************

#ifdef USE_ESPNOW
// 0: AP mode, 1: Station mode
// platformio.iniで指定
// #define ESPNOW_WIFI_MODE_STATION 1

// Channel to be used by the ESP-NOW protocol
#define ESPNOW_WIFI_CHANNEL 1

#if ESPNOW_WIFI_MODE_STATION            // ESP-NOW using WiFi Station mode
#define ESPNOW_WIFI_MODE WIFI_STA       // WiFi Mode
#define ESPNOW_WIFI_IF   WIFI_IF_STA    // WiFi Interface
#else                                   // ESP-NOW using WiFi AP mode
#define ESPNOW_WIFI_MODE WIFI_AP        // WiFi Mode
#define ESPNOW_WIFI_IF   WIFI_IF_AP     // WiFi Interface
#endif

ESP_NOW_Serial_Class* NowSerial = nullptr;
bi bi_isready = false;

#endif /* USE_ESPNOW */

//******************************************************
// ローカル関数宣言
//******************************************************

//******************************************************
// 関数定義
//******************************************************

void espnow_setup(void) {
#ifdef USE_ESPNOW
    u1 u1_ch = ESPNOW_WIFI_CHANNEL;
    if(u4_wifi_ch > 0){
        u1_ch = (u1)u4_wifi_ch;
    }

    int int_semaphore;
    smh_espnow = xSemaphoreCreateBinary();
    xSemaphoreGiveFromISR(smh_espnow, &int_semaphore);
    WiFi.mode(ESPNOW_WIFI_MODE);
    WiFi.setChannel(u1_ch, WIFI_SECOND_CHAN_NONE);

    while (!(WiFi.STA.started() || WiFi.AP.started())) {
        delay(10);
    }

    ESPNOW_UPDATE_S();

    M5.Log.print("MAC Address: ");
    M5.Log.println(
        (ESPNOW_WIFI_MODE == WIFI_AP)
        ? WiFi.softAPmacAddress().c_str()
        : WiFi.macAddress().c_str()
    );

    const MacAddress peer_mac(chr_wifi_peer);
    NowSerial = new ESP_NOW_Serial_Class(
        peer_mac,
        u1_ch,
        ESPNOW_WIFI_IF
    );
    NowSerial->setChannel(u1_ch);
    M5.Log.printf("NowSerial.peer=`%s`\n", chr_wifi_peer);
    M5.Log.printf("NowSerial.ch=%d\n", u1_ch);
    bi_isready = NowSerial->begin(115200);
    M5.Log.printf("NowSerial bi_isready=%s\n", bi_isready ? "TRUE " : "FALSE");

    NowSerial->setTxBufferSize(ESPNOW_BUFFSIZE);
    NowSerial->setRxBufferSize(ESPNOW_BUFFSIZE);
    M5.Log.printf(
        "ESP-NOW version: %d, max data length: %d\n"
      , ESP_NOW.getVersion()
      , ESP_NOW.getMaxDataLen()
    );
    ESPNOW_UPDATE_E();
#endif /* USE_ESPNOW */
}

bool espnow_getrx(u1* pu1_rxdata, u2 u2_size) {
    bool bi_ret = false;
#ifdef USE_ESPNOW
    ESPNOW_UPDATE_S();
    if(NowSerial->read(pu1_rxdata, u2_size) == u2_size){
        bi_ret = true;
    }
    ESPNOW_UPDATE_E();
#endif /* USE_ESPNOW */
    return bi_ret;
}

bool espnow_settx(u1* pu1_txdata, u2 u2_size) {
    bool bi_ret = false;
#ifdef USE_ESPNOW
    ESPNOW_UPDATE_S();
    if(NowSerial->write(pu1_txdata, u2_size) == u2_size){
        bi_ret = true;
    }
    ESPNOW_UPDATE_E();
#endif /* USE_ESPNOW */
    return bi_ret;
}
