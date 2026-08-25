/**
 * @file app_servo.h
 * @version 26081222.160
 */

#ifndef LOAD_APP_SERVO
#define LOAD_APP_SERVO

#include "main.h"

//******************************************************
// グローバル型定義
//******************************************************

typedef struct struct_SERVO_VOLCUR {
    f1 voltage;
    f1 current;
}S_SERVO_VOLCUR;

//******************************************************
// グローバル変数宣言
//******************************************************

//******************************************************
// グローバル関数宣言
//******************************************************

void servo_setup(void);
void servo_get_vc(S_SERVO_VOLCUR* p_s_volcur);
void servo_joytomotor(u2 joy_x, u2 joy_y);
void servo_setspeed(u2 u2_y, u1 u1_ch);
void servo_setspeed(s1 s1_speed);

#endif /* LOAD_APP_SERVO */
