/**
 * @file mid_task.cpp
 * @version 26081222.160
 */

#include "mid_task.h"
#ifdef LOAD_MID_TASK_H
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mid_m5stack.h"

//******************************************************
// グローバル変数定義
//******************************************************

//******************************************************
// ローカル型定義
//******************************************************

#define TASK_QUEUE_LENGTH           (16U)
#define TASK_BTNCNT_JDG             (16U)

//******************************************************
// ローカル変数定義
//******************************************************

volatile QueueHandle_t xTaskQueue;
static hw_timer_t* hwtimer[E_TASK_TIMER_MAX];

//******************************************************
// ローカル関数宣言
//******************************************************


//******************************************************
// 関数定義
//******************************************************

#ifdef USE_TIMER_050MS
void IRAM_ATTR task_onTimer_0050ms() {
    xQueueSendFromISR(xTaskQueue, &es_task_q[E_TASK_Q_TIMER050MS], 0U);
}
#endif /* USE_TIMER_050MS */

void IRAM_ATTR task_onTimer_0125ms() {
    xQueueSendFromISR(xTaskQueue, &es_task_q[E_TASK_Q_TIMER125MS], 0U);
}

#ifdef USE_TIMER_250MS
void IRAM_ATTR task_onTimer_0250ms() {
    xQueueSendFromISR(xTaskQueue, &es_task_q[E_TASK_Q_TIMER250MS], 0U);
}
#endif /* USE_TIMER_250MS */

#ifdef USE_TIMER_1S
void IRAM_ATTR task_onTimer_1000ms() {
    xQueueSendFromISR(xTaskQueue, &es_task_q[E_TASK_Q_TIMER1S], 0U);
}
#endif /* USE_TIMER_1S */

void task_onEnable(E_TASK_TIMER e_timer){
    timerStart(hwtimer[e_timer]);
}

void task_onDisable(E_TASK_TIMER e_timer){
    timerStop(hwtimer[e_timer]);
}

#ifdef USE_DISP
void IRAM_ATTR task_onTimer_disp() {
    xQueueSendFromISR(xTaskQueue, &es_task_q[E_TASK_Q_DISP_MAIN], 0U);
}

void task_onEnable_disp(void) {
    timerStart(hwtimer[E_TASK_TIMER_DISPMAIN]);
}

void task_onDisable_disp(void) {
    timerStop(hwtimer[E_TASK_TIMER_DISPMAIN]);
}

#endif  /* USE_DISP */

void IRAM_ATTR task_onButton_A() {
    xQueueSendToFrontFromISR(xTaskQueue, &es_task_q[E_TASK_Q_BUTTON_A], 0U);
}

void IRAM_ATTR task_onButton_B() {
    xQueueSendToFrontFromISR(xTaskQueue, &es_task_q[E_TASK_Q_BUTTON_B], 0U);
}

void IRAM_ATTR task_onButton_C() {
    xQueueSendToFrontFromISR(xTaskQueue, &es_task_q[E_TASK_Q_BUTTON_C], 0U);
}

#ifdef USE_INT_GPIOEX0
void IRAM_ATTR task_onGPIO_EX0() {
    xQueueSendToFrontFromISR(xTaskQueue, &es_task_q[E_TASK_Q_GPIO_EX0], 0U);
}
#endif  /* USE_INT_GPIOEX0 */

#ifdef USE_INT_GPIOEX1
void IRAM_ATTR task_onGPIO_EX1() {
    xQueueSendToFrontFromISR(xTaskQueue, &es_task_q[E_TASK_Q_GPIO_EX1], 0U);
}
#endif  /* USE_INT_GPIOEX1 */

#ifdef USE_INT_GPIOEX2
void IRAM_ATTR task_onGPIO_EX2() {
    xQueueSendToFrontFromISR(xTaskQueue, &es_task_q[E_TASK_Q_GPIO_EX2], 0U);
}
#endif  /* USE_INT_GPIOEX2 */

void task_setup(void) {
    xTaskQueue = xQueueCreate(TASK_QUEUE_LENGTH, sizeof(E_TASK_Q));

    M5.Log.println("SRT E_TASK_TIMER_125MS");
    hwtimer[E_TASK_TIMER_125MS] = timerBegin(1000000);
    timerAttachInterrupt(hwtimer[E_TASK_TIMER_125MS], &task_onTimer_0125ms);
    timerAlarm(hwtimer[E_TASK_TIMER_125MS], 125 * 1000, true, 0);
    timerRestart(hwtimer[E_TASK_TIMER_125MS]);
    M5.Log.println("END E_TASK_TIMER_125MS");

#ifdef USE_TIMER_050MS
    M5.Log.println("SRT E_TASK_TIMER_050MS");
    hwtimer[E_TASK_TIMER_050MS] = timerBegin(1000000);
    timerAttachInterrupt(hwtimer[E_TASK_TIMER_050MS], &task_onTimer_0050ms);
    timerAlarm(hwtimer[E_TASK_TIMER_050MS], 50 * 1000, true, 0);
    timerRestart(hwtimer[E_TASK_TIMER_050MS]);
    M5.Log.println("END E_TASK_TIMER_050MS");
#endif /* USE_TIMER_050MS */

#ifdef USE_TIMER_250MS
    M5.Log.println("SRT E_TASK_TIMER_250MS");
    hwtimer[E_TASK_TIMER_250MS] = timerBegin(1000000);
    timerAttachInterrupt(hwtimer[E_TASK_TIMER_250MS], &task_onTimer_0250ms);
    timerAlarm(hwtimer[E_TASK_TIMER_250MS], 250 * 1000, true, 0);
    timerRestart(hwtimer[E_TASK_TIMER_250MS]);
    M5.Log.println("END E_TASK_TIMER_250MS");
#endif /* USE_TIMER_250MS */

#ifdef USE_TIMER_1S
    M5.Log.println("SRT E_TASK_TIMER_1S");
    hwtimer[E_TASK_TIMER_1S] = timerBegin(1000000);
    timerAttachInterrupt(hwtimer[E_TASK_TIMER_1S], &task_onTimer_1000ms);
    timerAlarm(hwtimer[E_TASK_TIMER_1S], 1000 * 1000, true, 0);
    timerRestart(hwtimer[E_TASK_TIMER_1S]);
    M5.Log.println("END E_TASK_TIMER_1S");
#endif /* USE_TIMER_1S */

#ifdef USE_DISP
    M5.Log.println("SRT E_TASK_TIMER_DISPMAIN");
    if (s_dev.update > 0) {
        hwtimer[E_TASK_TIMER_DISPMAIN] = timerBegin(1000000);
        timerAttachInterrupt(hwtimer[E_TASK_TIMER_DISPMAIN], &task_onTimer_disp);
        timerAlarm(hwtimer[E_TASK_TIMER_DISPMAIN], s_dev.update * 1000, true, 0);
        timerRestart(hwtimer[E_TASK_TIMER_DISPMAIN]);
    }
    M5.Log.println("END E_TASK_TIMER_DISPMAIN");
#endif  /* USE_DISP */

    if (s_btn.a.pin != gpio_num_t::GPIO_NUM_NC) {
        M5.Log.printf("s_btn.a = %d\n", s_btn.a.pin);
        if (!CORE_BTNPOLL(s_btn.a.mode)) {
            attachInterrupt(s_btn.a.pin, task_onButton_A, CORE_BTNMODE(s_btn.a.mode));
        }
    }
    if (s_btn.b.pin != gpio_num_t::GPIO_NUM_NC) {
        M5.Log.printf("s_btn.b = %d\n", s_btn.b.pin);
        if (!CORE_BTNPOLL(s_btn.b.mode)) {
            attachInterrupt(s_btn.b.pin, task_onButton_B, CORE_BTNMODE(s_btn.b.mode));
        }
    }
    if (s_btn.c.pin != gpio_num_t::GPIO_NUM_NC) {
        M5.Log.printf("s_btn.c = %d\n", s_btn.c.pin);
        if (!CORE_BTNPOLL(s_btn.c.mode)) {
            attachInterrupt(s_btn.c.pin, task_onButton_C, CORE_BTNMODE(s_btn.c.mode));
        }
    }

#ifdef USE_INT_GPIOEX0
    if (s_btn.ex0.pin != gpio_num_t::GPIO_NUM_NC) {
        M5.Log.printf("s_btn.ex0 = %d\n", s_btn.ex0.pin);
        if (!CORE_BTNPOLL(s_btn.ex0.mode)) {
            attachInterrupt(s_btn.ex0.pin, task_onGPIO_EX0, CORE_BTNMODE(s_btn.ex0.mode));
        }
    }
#endif  /* USE_INT_GPIOEX0 */

#ifdef USE_INT_GPIOEX1
    if (s_btn.ex1.pin != gpio_num_t::GPIO_NUM_NC) {
        M5.Log.printf("s_btn.ex1 = %d\n", s_btn.ex1.pin);
        if (!CORE_BTNPOLL(s_btn.ex1.mode)) {
            attachInterrupt(s_btn.ex1.pin, task_onGPIO_ex1, CORE_BTNMODE(s_btn.ex1.mode));
        }
    }
#endif  /* USE_INT_GPIOEX1 */

#ifdef USE_INT_GPIOEX2
    if (s_btn.ex2.pin != gpio_num_t::GPIO_NUM_NC) {
        M5.Log.printf("s_btn.ex2 = %d\n", s_btn.ex2.pin);
        if (!CORE_BTNPOLL(s_btn.ex2.mode)) {
            attachInterrupt(s_btn.ex2.pin, task_onGPIO_EX2, CORE_BTNMODE(s_btn.ex2.mode));
        }
    }
#endif  /* USE_INT_GPIOEX2 */

}

bool task_xQueueSend(E_TASK_Q e_taskq) {
    BaseType_t ret = pdFAIL;
    if ((u4)e_taskq < (u4)E_TASK_Q_MAX) {
        ret = xQueueSend(xTaskQueue, &es_task_q[(u4)e_taskq], 0U);
    }
    return ret == pdPASS;
}

bool task_xQueueSendToFront(E_TASK_Q e_taskq) {
    BaseType_t ret = pdFAIL;
    if ((u4)e_taskq < (u4)E_TASK_Q_MAX) {
        ret = xQueueSendToFront(xTaskQueue, &es_task_q[(u4)e_taskq], 0U);
    }
    return ret == pdPASS;
}

#endif  /* LOAD_MID_TASK_H */
