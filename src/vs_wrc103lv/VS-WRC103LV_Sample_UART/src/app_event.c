/**
 * @file app_event.c
 * @version 26081222.160
 */

#include "app_event.h"

//******************************************************
// グローバル変数定義
//******************************************************

//******************************************************
// ローカル型定義
//******************************************************

//******************************************************
// ローカル変数定義
//******************************************************

#define EVENT_QUEUE_MAX   (E_EVE_MAX)

static E_EVE event_queue[EVENT_QUEUE_MAX];
static S1 s1_event_index;

//******************************************************
// 関数定義
//******************************************************

void Event_Init(void){
    s1_event_index = 0;
    for (U1 u1_loop = 0; u1_loop < EVENT_QUEUE_MAX; u1_loop++)
    {
        event_queue[u1_loop] = E_EVE_NONE;
    }
}

BI Event_SetEvent(E_EVE e_eve){
    if(
        (s1_event_index < EVENT_QUEUE_MAX)
     && (e_eve < E_EVE_MAX)
    ){
        DI();
        event_queue[s1_event_index] = e_eve;
        s1_event_index++;
        RI();
    }
}

E_EVE Event_GetEvent(void){
    E_EVE e_eve = E_EVE_NONE;
    if(s1_event_index > 0){
        DI();
        s1_event_index--;
        e_eve = event_queue[s1_event_index] = e_eve;
        RI();
    }
}
