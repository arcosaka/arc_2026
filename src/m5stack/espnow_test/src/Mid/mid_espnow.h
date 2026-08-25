/**
 * @file mid_espnow.h
 * @version 26081222.160
 */

#ifndef LOAD_MID_ESPNOW
#define LOAD_MID_ESPNOW

#include "main.h"
#ifdef USE_ESPNOW
#endif /* USE_ESPNOW */

//******************************************************
// グローバル型定義
//******************************************************

//******************************************************
// グローバル変数宣言
//******************************************************

#define ESPNOW_BUFFSIZE                 (1024U)

#define ESPNOW_TASKWAIT_MS              (100)
#define ESPNOW_UPDATE_S()               if(xSemaphoreTake(smh_espnow, ESPNOW_TASKWAIT_MS-1) == pdTRUE){
#define ESPNOW_UPDATE_E()               xSemaphoreGive(smh_espnow);}
extern volatile SemaphoreHandle_t smh_espnow;

//******************************************************
// グローバル関数宣言
//******************************************************

void espnow_setup(void);
bool espnow_getrx(u1* pu1_rxdata, u2 u2_size);
bool espnow_settx(u1* pu1_txdata, u2 u2_size);

#endif /* LOAD_MID_ESPNOW */
