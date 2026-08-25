/**
 * @file mid_task.h
 * @version 26081222.160
 */

#ifndef LOAD_MID_TASK_H
#define LOAD_MID_TASK_H

#include "main.h"
#include "cmn_setting.h"

//******************************************************
// グローバル型定義
//******************************************************

//******************************************************
// グローバル変数宣言
//******************************************************

extern volatile QueueHandle_t xTaskQueue;

//******************************************************
// グローバル関数宣言
//******************************************************

void task_setup(void);
void task_onEnable(E_TASK_TIMER e_timer);
void task_onDisable(E_TASK_TIMER e_timer);
void task_onEnable_disp(void);
void task_onDisable_disp(void);
bool task_xQueueSend(E_TASK_Q e_taskq);
bool task_xQueueSendToFront(E_TASK_Q e_taskq);
#endif /* LOAD_MID_TASK_H */
