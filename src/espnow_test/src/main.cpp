/**
 * @file main.cpp
 * @version 26060619.530
 */

#include "main.h"
#include "Mid/mid_m5stack.h"
#include "Mid/mid_task.h"
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

#define STEP    (2)
#define MAX     (100)

static s1 s1_cnt;
static s1 s1_step;
static u1 u1_wait;

//******************************************************
// ローカル関数宣言
//******************************************************

//******************************************************
// 関数定義
//******************************************************

void setup() {
    m5stack_setup();
    task_setup();
    servo_setup();
    s1_step = STEP;
    s1_cnt = 0;
    u1_wait = STEP;
}

void loop() {
    BaseType_t ret;
    E_TASK_Q e_task_q;
    e_task_q = E_TASK_Q_MAX;
    M5.Power.lightSleep(2000);
    ret = xQueueReceive(xTaskQueue, &e_task_q, 0);
    if (ret == pdTRUE) {
        switch (e_task_q) {
            case E_TASK_Q_BUTTON_A:
                //M5.Log.println("BUTTON_A");
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
                u1_wait--;
                if(u1_wait < 1){
                    u1_wait = STEP;
                    M5.Log.printf("s1_cnt=%d\n",s1_cnt);
                    servo_setspeed(s1_cnt);
                    s1_cnt += s1_step;
                    if(s1_cnt <= -MAX || MAX <= s1_cnt){
                        s1_step *= -1;
                    }
                }
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
                //M5.Log.println("DISP_MAIN");
                break;
#endif  /* USE_DISP */
        }
    }
    else {
        M5.delay(1);
    }
}
