/**
 * @file main.cpp
 * @version 26081222.160
 */

#include "main.h"
#include "Mid/mid_m5stack.h"
#include "Mid/mid_task.h"
#include "Mid/mid_pref.h"
#include "App/app_espnow.h"
#include "App/app_websetup.h"
#include "App/app_servo.h"

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

static bi bi_isrun;
static bi bi_isrun_old;
static bi bi_isexbtn0;
static S_SERVO_VOLCUR s_volcur;
#ifdef USE_DISP
static f1 f1_txtsize_x, f1_txtsize_y;
#endif  /* USE_DISP */

//******************************************************
// ローカル関数宣言
//******************************************************

static void main_getvc(void);

//******************************************************
// 関数定義
//******************************************************

static void main_getvc(void){
    servo_get_vc(&s_volcur);
    payload_tx.payload.body.bits.isbody = true;
    payload_tx.payload.body.bits.isready = bi_isrun;
    payload_tx.payload.current = (s2)(s_volcur.current * 1000.0);
    payload_tx.payload.voltage = (u2)(s_volcur.voltage * 1000.0);
    M5.Log.printf(
        "voltage =%4u[mV], current =%4d[mA]\n"
        , payload_tx.payload.voltage
        , payload_tx.payload.current
    );

    if(bi_isrun && espnow_isrxtimeout()){
        bi_isrun = false;
        servo_setspeed(0);
    }
}

void setup() {
    m5stack_setup();
    pref_setup();
    M5.update();
    if((u4_wifi_ch < 1U) || M5.BtnA.isPressed()){
        websetup_setup();
        M5.Log.println("rebooting...");
        M5.delay(10 * 1000);
        ESP.restart();
        return;
    }
    task_setup();
    servo_setup();
    servo_setspeed(0);
    bi_isrun = false;
    bi_isexbtn0 = false;
    espnow_rxAsync();
#ifdef USE_DISP
    f1_txtsize_x = disp_canvas.getTextSizeX();
    f1_txtsize_y = disp_canvas.getTextSizeY();
#endif  /* USE_DISP */
}

void loop() {
    BaseType_t ret;
    E_TASK_Q e_task_q;
    e_task_q = E_TASK_Q_MAX;
    ret = xQueueReceive(xTaskQueue, &e_task_q, 0);
    if (ret == pdTRUE) {
        switch (e_task_q) {
            case E_TASK_Q_BUTTON_A:
                //M5.Log.println("BUTTON_A");
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
                //M5.Log.println("TIMER125MS");
                m5stack_loop();
#ifndef USE_DISP
                if(bi_isrun){
                    if(payload_tx.payload.voltage > 3600){
                        M5.Led.setAllColor(TFT_GREEN);
                    }
                    else if(payload_tx.payload.voltage > 3400){
                        M5.Led.setAllColor(TFT_ORANGE);
                    }
                    else{
                        M5.Led.setAllColor(TFT_YELLOW);
                    }
                }
                else if(!espnow_isrxtimeout()){
                    M5.Led.setAllColor(TFT_RED);
                }
                else{
                    M5.Led.setAllColor(TFT_BLACK);
                }
#endif  /* USE_DISP */
                break;
#ifdef USE_TIMER_050MS
            case E_TASK_Q_TIMER050MS:
                //M5.Log.println("TIMER050MS");
                break;
#endif /* USE_TIMER_050MS */
#ifdef USE_TIMER_250MS
            case E_TASK_Q_TIMER250MS:
                //M5.Log.println("TIMER250MS");
                main_getvc();
                break;
#endif /* USE_TIMER_250MS */
#ifdef USE_TIMER_1S
            case E_TASK_Q_TIMER1S:
                //M5.Log.println("TIMER1S");
                main_getvc();
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
                DISP_UPDATE_S();
                disp_canvas.setTextWrap(false,false);
                disp_canvas.clearDisplay(TFT_BLACK);
                disp_canvas.setCursor(0, 0);
                disp_canvas.printf(
                    "tm      =%6u\nvoltage =%4u[mV]\ncurrent =%4d[mA]\n"
                  , payload_rx.payload.tm
                  , payload_tx.payload.voltage
                  , payload_tx.payload.current
                );
                disp_canvas.printf(
                    "joyx    =%4d\njoyy    =%4d\njoyb    =%4u\n"
                  , (s2)payload_rx.payload.joyx
                  , (s2)payload_rx.payload.joyy
                  , payload_rx.payload.joyb
                );
                disp_canvas.setTextSize(f1_txtsize_x * 4, f1_txtsize_y * 4);
                if(bi_isrun) {
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
                // M5.Log.printf("tm\t%6lu\tjoyx\t%4d\tjoyy\t%4d\tjoyb\t%4d\n"
                //     , payload_rx.payload.tm
                //     , (s2)payload_rx.payload.joyx
                //     , (s2)payload_rx.payload.joyy
                //     , payload_rx.payload.joyb
                // );
                if(bi_isexbtn0 && !(bi)payload_rx.payload.joyb){
                    bi_isrun = !bi_isrun;
                }
                bi_isexbtn0 = (bi)payload_rx.payload.joyb;

                if(bi_isrun){
                    servo_joytomotor(
                        payload_rx.payload.joyx
                      , payload_rx.payload.joyy
                    );
                }
                task_xQueueSend(E_TASK_Q_ESPNOW_TX);
                m5stack_disp_clear_count();
                break;
            case E_TASK_Q_ESPNOW_TX:
                M5.Log.println("ESPNOW_TX");
                payload_tx.payload.body.bits.isready = bi_isrun;
                espnow_txAsync();
                break;
#endif  /* USE_ESPNOW */
            default:
                M5.Power.lightSleep(3000);
                break;
        }
    }
    else {
        M5.Power.lightSleep(5000);
        NOP();
        M5.Power.lightSleep(5000);
        NOP();
        M5.Power.lightSleep(5000);
        NOP();
        M5.Power.lightSleep(5000);
    }

    if(bi_isrun_old && !bi_isrun){
        servo_setspeed(0);
    }
    bi_isrun_old = bi_isrun;
}
