/**
 * @file app_servo.cpp
 * @version 26081222.160
 */

#include "main.h"
#include "app_servo.h"
#ifdef USE_ESP32SERVO
#include "ESP32Servo.h"
#endif
#ifdef USE_M5ATOMICMOTION
#include "M5AtomicMotion.h"
#endif

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
#if defined USE_ESP32SERVO
static Servo servo;
#elif defined USE_M5ATOMICMOTION
#define SERVO_L         (0)
#define SERVO_R         (1)
static M5AtomicMotion AtomicMotion;
#else
#warning " not define 'USE_ESP32SERVO' and 'USE_M5ATOMICMOTION'"
#define NONE_SERVO
#endif

//******************************************************
// ローカル関数宣言
//******************************************************


//******************************************************
// 関数定義
//******************************************************

void servo_setup() {
#if defined USE_ESP32SERVO
    servo.attach(SERVO_PIN, COUNT_LOW, COUNT_HIGH); // Attach the servo to the specified pin, with defined min (COUNT_LOW) and max (COUNT_HIGH) pulse widths
    servo.writeMicroseconds(COUNT_MIDDLE);
#elif defined USE_M5ATOMICMOTION
    m5::board_t board = M5.getBoard();
    uint8_t u8_sda = 0, u8_scl = 0;
    switch (board) {
        case m5::board_t::board_M5AtomLite:
        case m5::board_t::board_M5AtomMatrix:
        case m5::board_t::board_M5AtomVoice:
            u8_sda = 25;
            u8_scl = 21;
            break;
        case m5::board_t::board_M5AtomS3:
        case m5::board_t::board_M5AtomS3R:
        case m5::board_t::board_M5AtomS3Lite:
        case m5::board_t::board_M5AtomS3RExt:
        case m5::board_t::board_M5AtomS3RCam:
            u8_sda = 38;
            u8_scl = 39;
            break;

        default:
            M5.Display.clear();
            M5.Display.println("Board Fail");
            while (true) {
                M5.Power.lightSleep(1000);
            }
            break;
    }
    while (!AtomicMotion.begin(&Wire, M5_ATOMIC_MOTION_I2C_ADDR, u8_sda, u8_scl, 100000)) {
        M5.Display.clear();
        M5.Display.println("AtomicMotion Init Fail");
        delay(1000);
    }
    M5.Display.clear();
    M5.Display.println("Motion");

#else
#warning "not define 'USE_ESP32SERVO' and 'USE_M5ATOMICMOTION'"
#endif
}

void servo_get_vc(S_SERVO_VOLCUR* p_s_volcur) {
#if defined USE_M5ATOMICMOTION
    p_s_volcur->current = AtomicMotion.ina226.readShuntCurrent();
    p_s_volcur->voltage = AtomicMotion.ina226.readBusVoltage();
#else
    p_s_volcur->current = 0;
    p_s_volcur->voltage = 0;
#endif
}


void servo_joytomotor(u2 joy_x, u2 joy_y) {
    s2 left  = (s2)joy_x + (s2)joy_y;
    s2 right = (s2)joy_x - (s2)joy_y;

    /* 正規化 */
    int maxVal = max(abs(left), abs(right));

    if (maxVal > 511)
    {
        left  = left  * 511 / maxVal;
        right = right * 511 / maxVal;
    }

    servo_setspeed(COUNT_MIDDLE + left  * 1000 / 511, SERVO_L);
    servo_setspeed(COUNT_MIDDLE + right * 1000 / 511, SERVO_R);
}


void servo_setspeed(u2 u2_w, u1 u1_ch) {
#if defined USE_M5ATOMICMOTION
    if(COUNT_LOW <= u2_w && u2_w <= COUNT_HIGH){
        AtomicMotion.setServoPulse(u1_ch, u2_w);
    }
#endif
}

void servo_setspeed(s1 s1_speed) {
    u2 u2_y = (u2)s1_speed * ((COUNT_HIGH - COUNT_MIDDLE) / STEP_MAX) + COUNT_MIDDLE;
    if(COUNT_LOW <= u2_y && u2_y <= COUNT_HIGH){
#if defined USE_ESP32SERVO
        servo.writeMicroseconds(u2_y);
#elif defined USE_M5ATOMICMOTION
        servo_setspeed(u2_y, SERVO_L);
        servo_setspeed((u2)(COUNT_LOW + COUNT_HIGH) - u2_y, SERVO_R);
#endif
    }
}
