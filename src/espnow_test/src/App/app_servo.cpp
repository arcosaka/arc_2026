/**
 * @file app_servo.cpp
 * @version 26060619.530
 */

#include "main.h"
#include "ESP32Servo.h"

//******************************************************
// グローバル変数定義
//******************************************************

//******************************************************
// ローカル型定義
//******************************************************

//******************************************************
// ローカル変数定義
//******************************************************

#define COUNT_LOW       (500)
#define COUNT_HIGH      (2500)
#define COUNT_MIDDLE    ((COUNT_LOW + COUNT_HIGH) / 2)
#define STEP_MAX        (100)
#define SERVO_PIN       (2)    // Digital pin connected to the servo motor's signal wire

Servo servo;

//******************************************************
// ローカル関数宣言
//******************************************************


//******************************************************
// 関数定義
//******************************************************

void servo_setup() {
    servo.attach(SERVO_PIN, COUNT_LOW, COUNT_HIGH); // Attach the servo to the specified pin, with defined min (COUNT_LOW) and max (COUNT_HIGH) pulse widths
    servo.writeMicroseconds(COUNT_MIDDLE);

}

void servo_setspeed(s1 s1_speed) {
    u2 u2_y = (u2)s1_speed * ((COUNT_HIGH - COUNT_MIDDLE) / STEP_MAX) + COUNT_MIDDLE;
    if(COUNT_LOW <= u2_y && u2_y <= COUNT_HIGH){
        M5.Log.printf("s1_cnt=%u\n",u2_y);
        servo.writeMicroseconds(u2_y);
    }
}
