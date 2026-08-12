/**
 * @file cmn_setting.h
 * @version 26081222.160
 */

#ifndef LOAD_CMN_SETTING_H
#define LOAD_CMN_SETTING_H

#include "main.h"

#ifndef APP_CPU_NUM
#define APP_CPU_NUM     PRO_CPU_NUM     /** Select SOC is single core */
#endif  /* APP_CPU_NUM */

// Async Task
//  COREBUF
#define COREBUF_DISP    (8192)
#define COREBUF_ESPNOW  (16384)

//  COREPRI
#define COREPRI_DISP    (7)
#define COREPRI_ESPNOW  (4)

//  CORESEL
#define CORESEL_DISP    (APP_CPU_NUM)
#define CORESEL_ESPNOW  (APP_CPU_NUM)

//#define USE_TIMER_050MS
//#define USE_TIMER_250MS
#define USE_TIMER_1S

//******************************************************
// グローバル型定義
//******************************************************

typedef enum enum_TASK_Q {
      E_TASK_Q_BUTTON_A
    , E_TASK_Q_BUTTON_B
    , E_TASK_Q_BUTTON_C
    , E_TASK_Q_TIMER125MS
#ifdef USE_TIMER_050MS
    , E_TASK_Q_TIMER050MS
#endif /* USE_TIMER_050MS */
#ifdef USE_TIMER_250MS
    , E_TASK_Q_TIMER250MS
#endif /* USE_TIMER_250MS */
#ifdef USE_TIMER_1S
    , E_TASK_Q_TIMER1S
#endif /* USE_TIMER_1S */
#ifdef USE_INT_GPIOEX0
    , E_TASK_Q_GPIO_EX0
#endif /* USE_INT_GPIOEX0 */
#ifdef USE_INT_GPIOEX1
    , E_TASK_Q_GPIO_EX1
#endif /* USE_INT_GPIOEX1 */
#ifdef USE_INT_GPIOEX2
    , E_TASK_Q_GPIO_EX2
#endif /* USE_INT_GPIOEX2 */
#ifdef USE_DISP
    , E_TASK_Q_DISP_MAIN
#endif  /* USE_DISP */
#ifdef USE_ESPNOW
    , E_TASK_Q_ESPNOW_TX
    , E_TASK_Q_ESPNOW_RX
#endif
    , E_TASK_Q_MAX
} E_TASK_Q;

typedef enum enum_TASK_TIMER{
      E_TASK_TIMER_125MS
    #ifdef USE_TIMER_050MS
    , E_TASK_TIMER_050MS
    #endif /* USE_TIMER_050MS */
    #ifdef USE_TIMER_250MS
    , E_TASK_TIMER_250MS
    #endif /* USE_TIMER_250MS */
    #ifdef USE_TIMER_1S
    , E_TASK_TIMER_1S
    #endif /* USE_TIMER_1S */
#ifdef USE_DISP
    , E_TASK_TIMER_DISPMAIN
#endif  /* USE_DISP */
    , E_TASK_TIMER_MAX
} E_TASK_TIMER;

//******************************************************
// グローバル変数宣言
//******************************************************

const E_TASK_Q es_task_q[E_TASK_Q_MAX] = {
      E_TASK_Q_BUTTON_A
    , E_TASK_Q_BUTTON_B
    , E_TASK_Q_BUTTON_C
    , E_TASK_Q_TIMER125MS
    #ifdef USE_TIMER_050MS
    , E_TASK_Q_TIMER050MS
    #endif /* USE_TIMER_050MS */
    #ifdef USE_TIMER_250MS
    , E_TASK_Q_TIMER250MS
    #endif /* USE_TIMER_250MS */
    #ifdef USE_TIMER_1S
    , E_TASK_Q_TIMER1S
    #endif /* USE_TIMER_1S */
    #ifdef USE_TIMER_2S
    , E_TASK_Q_TIMER2S
    #endif /* USE_TIMER_2S */
    #ifdef USE_INT_GPIOEX0
    , E_TASK_Q_GPIO_EX0
    #endif /* USE_INT_GPIOEX0 */
    #ifdef USE_INT_GPIOEX1
    , E_TASK_Q_GPIO_EX1
    #endif /* USE_INT_GPIOEX1 */
    #ifdef USE_INT_GPIOEX2
    , E_TASK_Q_GPIO_EX2
    #endif /* USE_INT_GPIOEX2 */
#ifdef USE_DISP
    , E_TASK_Q_DISP_MAIN
#endif  /* USE_DISP */
#ifdef USE_ESPNOW
    , E_TASK_Q_ESPNOW_TX
    , E_TASK_Q_ESPNOW_RX
#endif
};

#endif /* LOAD_CMN_SETTING_H */
