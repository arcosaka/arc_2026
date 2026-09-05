/**
 * @file app_event.h
 * @version 26081222.160
 */

#ifndef LOAD_APP_EVENT_H
#define LOAD_APP_EVENT_H

#include "typedef.h"

//******************************************************
// グローバル型定義
//******************************************************

typedef enum enum_EVE{
    E_EVE_NONE
  , E_EVE_MAIN
  , E_EVE_TX
  , E_EVE_RX
  , E_EVE_MAX
} E_EVE;

//******************************************************
// グローバル変数宣言
//******************************************************

//******************************************************
// グローバル関数宣言
//******************************************************

void Event_Init(void);
BI Event_SetEvent(E_EVE e_eve);
E_EVE Event_GetEvent(void);
U1 Event_GetQueueCount(void);

#endif /* LOAD_APP_EVENT_H */
