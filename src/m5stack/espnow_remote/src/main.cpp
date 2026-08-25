/**
 * @file main.cpp
 * @version 26081222.160
 */

#include "main.h"
#include "Mid/mid_m5stack.h"
#include "Mid/mid_task.h"
#include "Mid/mid_pref.h"
#include "Mid/mid_joyhat.h"
#include "App/app_espnow.h"
#include "App/app_websetup.h"

//******************************************************
// グローバル変数定義
//******************************************************

//******************************************************
// ローカル型定義
//******************************************************

//******************************************************
// ローカル変数定義
//******************************************************

#define STEP    (4)
#define MAX     (100)

static s1 s1_cnt;
static s1 s1_step;
static u1 u1_wait;
static bi bi_isrun;
#ifdef USE_DISP
static f1 f1_txtsize_x, f1_txtsize_y;
#endif  /* USE_DISP */

//******************************************************
// ローカル関数宣言
//******************************************************

//******************************************************
// 関数定義
//******************************************************

void setup() {
    m5stack_setup();
    pref_setup();
    M5.update();
    if((u4_wifi_ch < 1U) || M5.BtnA.isPressed() || M5.BtnB.isPressed()){
        websetup_setup();
        M5.Log.println("rebooting...");
        M5.delay(10 * 1000);
        ESP.restart();
        return;
    }
    joyhat_setup();
    task_setup();
    s1_step = STEP;
    u1_wait = STEP;
    s1_cnt = 0;
    bi_isrun = false;
    espnow_rxAsync();
#ifdef USE_DISP
    f1_txtsize_x = disp_canvas.getTextSizeX();
    f1_txtsize_y = disp_canvas.getTextSizeY();
#endif  /* USE_DISP */
}

void loop() {
    BaseType_t ret;
    E_TASK_Q e_task_q;
    u2 u2_x;
    u2 u2_y;
    u1 u1_b;
    e_task_q = E_TASK_Q_MAX;
    ret = xQueueReceive(xTaskQueue, &e_task_q, 0);
    if (ret == pdTRUE) {
        switch (e_task_q) {
            case E_TASK_Q_BUTTON_A:
                M5.Log.println("BUTTON_A");
                bi_isrun = !bi_isrun;
                m5stack_disp_clear_count();
                break;
            case E_TASK_Q_BUTTON_B:
                //M5.Log.println("BUTTON_B");
                break;
            case E_TASK_Q_BUTTON_C:
                //M5.Log.println("BUTTON_C");
                break;
            case E_TASK_Q_TIMER125MS:
                M5.Log.println("TIMER125MS");
                m5stack_loop();
                joyhat_get_xyb(&u2_x, &u2_y, &u1_b);
                payload_tx.payload.remote.bits.isremote = true;
                payload_tx.payload.remote.bits.isready = bi_isrun;
                payload_tx.payload.joyx = u2_x;
                payload_tx.payload.joyy = u2_y;
                payload_tx.payload.joyb = (u2)u1_b;
                if(bi_isrun){
#ifdef USE_ESPNOW
                    task_xQueueSend(E_TASK_Q_ESPNOW_TX);
#endif  /* USE_ESPNOW */
                    if(espnow_isrxtimeout()){
                        joyhat_set_led(0xFFU, 0xFFU, 0x00U);
                    }
                    else {
                        joyhat_set_led(0x00U, 0x00U, 0xFFU);
                    }
                }
                else {
                    joyhat_set_led(0xFFU, 0x00U, 0x00U);
                }
                break;
#ifdef USE_TIMER_050MS
            case E_TASK_Q_TIMER050MS:
                //M5.Log.println("TIMER050MS");
                break;
#endif /* USE_TIMER_050MS */
#ifdef USE_TIMER_250MS
            case E_TASK_Q_TIMER250MS:
                //M5.Log.println("TIMER250MS");
                break;
#endif /* USE_TIMER_250MS */
#ifdef USE_TIMER_1S
            case E_TASK_Q_TIMER1S:
                //M5.Log.println("TIMER1S");
                break;
#endif /* USE_TIMER_1S */
#ifdef USE_INT_GPIOEX0
            case E_TASK_Q_GPIO_EX0:
                //M5.Log.println("GPIO_EX0");
                break;
#endif /* USE_INT_GPIOEX0 */
#ifdef USE_INT_GPIOEX1
            case E_TASK_Q_GPIO_EX1:
                //M5.Log.println("GPIO_EX1");
                break;
#endif /* USE_INT_GPIOEX1 */
#ifdef USE_INT_GPIOEX2
            case E_TASK_Q_GPIO_EX2:
                //M5.Log.println("GPIO_EX2");
                break;
#endif /* USE_INT_GPIOEX2 */
#ifdef USE_DISP
            case E_TASK_Q_DISP_MAIN:
                M5.Log.printf("DISP_MAIN(%d[ms])\n", s_dev.update);
                DISP_UPDATE_S();
                disp_canvas.setTextWrap(false,false);
                disp_canvas.clearDisplay(TFT_BLACK);
                disp_canvas.setCursor(0, 0);
                disp_canvas.printf(
                    "tm        =%6u\nvoltage =%4u[mV]\ncurrent =%4d[mA]\n"
                  , payload_tx.payload.tm
                  , payload_rx.payload.voltage
                  , payload_rx.payload.current
                );
                disp_canvas.printf(
                    "joyx    =%4d\njoyy    =%4d\njoyb    =%4u\n"
                  , (s2)payload_tx.payload.joyx
                  , (s2)payload_tx.payload.joyy
                  , payload_tx.payload.joyb
                );
                if(bi_isrun) {
                    disp_canvas.println(" RUN! ");
                }
                else{
                    disp_canvas.println(" STOP ");
                }
                disp_canvas.setTextSize(f1_txtsize_x * 4, f1_txtsize_y * 4);
                if(bi_isrun && payload_rx.payload.body.bits.isready) {
                    disp_canvas.setTextColor(TFT_BLACK, TFT_GREEN);
                    disp_canvas.println("      ");
                    disp_canvas.println(" RUN! ");
                    disp_canvas.println("      ");
                }
                else{
                    disp_canvas.setTextColor(TFT_WHITE, TFT_RED);
                    disp_canvas.println("      ");
                    disp_canvas.println(" STOP ");
                    disp_canvas.println("      ");
                }
                disp_canvas.setTextColor(TFT_WHITE, TFT_BLACK);
                disp_canvas.setTextSize(f1_txtsize_x, f1_txtsize_y);
                DISP_UPDATE_E();
                m5stack_disp_update();
                break;
#endif  /* USE_DISP */
#ifdef USE_ESPNOW
            case E_TASK_Q_ESPNOW_RX:
                M5.Log.println("ESPNOW_RX");
                M5.Log.printf("tm\t%6lu\tcur\t%4d[mA]\tvol\t%4d[mV]\n"
                    , payload_rx.payload.tm
                    , payload_rx.payload.current
                    , payload_rx.payload.voltage
                );
                m5stack_disp_clear_count();
                break;
            case E_TASK_Q_ESPNOW_TX:
                M5.Log.println("ESPNOW_TX");
                espnow_txAsync();
                break;
#endif  /* USE_ESPNOW */
            default:
                M5.Power.lightSleep(3000);
                break;
        }
    }
    else {
        M5.Power.lightSleep(2000);
    }
}
