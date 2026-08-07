/**
 * @file main.cpp
 * @version 26080722.220
 */

#include "main.h"
#include "Mid/mid_m5stack.h"
#include "Mid/mid_task.h"
#include "App/app_espnow.h"
#include "Mid/mid_joyhat.h"

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

//******************************************************
// ローカル関数宣言
//******************************************************

//******************************************************
// 関数定義
//******************************************************

void setup() {
    m5stack_setup();
    joyhat_setup();
    task_setup();
    s1_step = STEP;
    u1_wait = STEP;
    s1_cnt = 0;
    bi_isrun = false;
    espnow_rxAsync();
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
                //M5.Log.println("BUTTON_A");
                bi_isrun = !bi_isrun;
#ifdef USE_DISP
                m5stack_disp_clear_count();
#endif  /* USE_DISP */
                break;
            case E_TASK_Q_BUTTON_B:
                //M5.Log.println("BUTTON_B");
                break;
            case E_TASK_Q_BUTTON_C:
                //M5.Log.println("BUTTON_C");
                break;
            case E_TASK_Q_TIMER125MS:
                //M5.Log.println("TIMER125MS");
                m5stack_loop();
                break;
#ifdef USE_TIMER_050MS
            case E_TASK_Q_TIMER050MS:
                //M5.Log.println("TIMER050MS");
                break;
#endif /* USE_TIMER_050MS */
#ifdef USE_TIMER_250MS
            case E_TASK_Q_TIMER250MS:
                //M5.Log.println("TIMER250MS");
                joyhat_get_xyb(&u2_x, &u2_y, &u1_b);
                payload_tx.payload.joyx = u2_x;
                payload_tx.payload.joyy = u2_y;
                payload_tx.payload.joyb = (u2)u1_b;
                if(bi_isrun) {
#ifdef USE_ESPNOW
                    task_xQueueSend(E_TASK_Q_ESPNOW_TX);
#endif  /* USE_ESPNOW */
                }
#ifdef USE_DISP
                DISP_UPDATE_S();
                disp_canvas.clearDisplay(TFT_BLACK);
                disp_canvas.setCursor(0, 0);
                disp_canvas.printf(
                    "tm_l    =%6u\nvoltage =%4u[mV]\ncurrent =%4d[mA]\n"
                  , payload_tx.payload.tm_l
                  , payload_rx.payload.voltage
                  , payload_rx.payload.current
                );
                disp_canvas.printf(
                    "joyx=%4d\njoyy=%4d\njoyb=%4u\n"
                  , (s2)payload_tx.payload.joyx
                  , (s2)payload_tx.payload.joyy
                  , payload_tx.payload.joyb
                );
                if(bi_isrun) {
                    disp_canvas.println("run!");
                }
                else{
                    disp_canvas.println("not run");
                }
                DISP_UPDATE_E();
#endif  /* USE_DISP */

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
                //M5.Log.printf("DISP_MAIN(%d[ms])\n", s_dev.update);
                m5stack_disp_update();
                break;
#endif  /* USE_DISP */
#ifdef USE_ESPNOW
            case E_TASK_Q_ESPNOW_RX:
                M5.Log.println("ESPNOW_RX");
                M5.Log.printf("tm_l\t%6lu\tcur\t%4d[mA]\tvol\t%4d[mV]\n"
                    , payload_rx.payload.tm_l
                    , payload_rx.payload.current
                    , payload_rx.payload.voltage
                );
#ifdef USE_DISP
                m5stack_disp_clear_count();
#endif  /* USE_DISP */
                break;
            case E_TASK_Q_ESPNOW_TX:
                M5.Log.println("ESPNOW_TX");
                espnow_txAsync();
                break;
#endif  /* USE_ESPNOW */
            default:
                M5.Power.lightSleep(2000);
                break;
        }
    }
    else {
        M5.Power.lightSleep(2000);
    }
}
