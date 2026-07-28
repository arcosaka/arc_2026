/**
 * @file mid_m5stack.cpp
 * @version 26053112.280
 */

#include "mid_m5stack.h"
#include "mid_task.h"

//******************************************************
// グローバル変数定義
//******************************************************

S_DEVINFO s_dev;
S_BTNPINS s_btn;
m5::Touch_Class::touch_detail_t td;

//******************************************************
// ローカル型定義
//******************************************************


//******************************************************
// ローカル変数定義
//******************************************************

#define SERIAL_BAUD     (115200)
S_BTNPIN& btna = s_btn.a;
S_BTNPIN& btnb = s_btn.b;
S_BTNPIN& btnc = s_btn.c;

//******************************************************
// ローカル関数宣言
//******************************************************


//******************************************************
// 関数定義
//******************************************************

void m5stack_setup(void){
    auto cfg = M5.config();

    cfg.serial_baudrate = SERIAL_BAUD;
    M5.begin(cfg);
    M5.delay(1000);

    M5.Display.setTextScroll(true);


    auto board = M5.getBoard();
    switch (board) {
#if defined (CONFIG_IDF_TARGET_ESP32S3)
        case m5gfx::board_t::board_M5StackCoreS3SE:
            s_dev.devtype = E_DEVTYPE_M5_CS3S;
            s_dev.update = 50;
            s_dev.dispoff = 60 * 60 * 1000L;
            s_dev.scale = 2U;
            s_btn.t.mode = E_BTNMODE_POLLING;

            break;
        case m5gfx::board_t::board_M5StickS3:
            s_dev.devtype = E_DEVTYPE_M5_STS3;
            s_dev.update = 50;
            s_dev.dispoff = 60 * 1000L;
            s_dev.scale = 2U;
            btna.pin = gpio_num_t::GPIO_NUM_11;
            btna.mode = E_BTNMODE_FALLING;
            btnb.pin = gpio_num_t::GPIO_NUM_12;
            btnb.mode = E_BTNMODE_FALLING;
            break;
        case m5gfx::board_t::board_M5AtomS3:
            s_dev.devtype = E_DEVTYPE_M5_AT3N;
            s_dev.update = 50;
            s_dev.dispoff = 30 * 60 * 1000L;
            s_dev.scale = 1U;
            btna.pin = gpio_num_t::GPIO_NUM_41;
            btna.mode = E_BTNMODE_FALLING;
            break;
        case m5gfx::board_t::board_M5AtomS3Lite:
            s_dev.devtype = E_DEVTYPE_M5_AT3L;
            s_dev.update = 0;
            s_dev.dispoff = 0;
            s_dev.scale = 0U;
            btna.pin = gpio_num_t::GPIO_NUM_41;
            btna.mode = E_BTNMODE_FALLING;
            break;
        case m5gfx::board_t::board_M5AtomS3R:
            s_dev.devtype = E_DEVTYPE_M5_AT3R;
            s_dev.update = 50;
            s_dev.dispoff = 30 * 60 * 1000L;
            s_dev.scale = 1U;
            btna.pin = gpio_num_t::GPIO_NUM_41;
            btna.mode = E_BTNMODE_FALLING;
            break;
        case m5gfx::board_t::board_M5AtomVoiceS3R:   /* 判定ミスの暫定対応 */
        case m5gfx::board_t::board_M5AtomS3RCam:
            s_dev.devtype = E_DEVTYPE_M5_AT3C;
            s_dev.update = 0;
            s_dev.dispoff = 0;
            s_dev.scale = 0U;
            btna.pin = gpio_num_t::GPIO_NUM_41;
            btna.mode = E_BTNMODE_FALLING;
            break;
#else
        case m5gfx::board_t::board_M5Stack:
            s_dev.devtype = E_DEVTYPE_M5_CRBS;
            s_dev.update = 250;
            s_dev.dispoff = 60 * 60 * 1000L;
            s_dev.scale = 2U;
            btna.pin = gpio_num_t::GPIO_NUM_39;
            btna.mode = E_BTNMODE_FALLING_P;

            btnb.pin = gpio_num_t::GPIO_NUM_38;
            btnb.mode = E_BTNMODE_FALLING;

            btnc.pin = gpio_num_t::GPIO_NUM_37;
            btnc.mode = E_BTNMODE_FALLING;

            break;
        case m5gfx::board_t::board_M5StickCPlus:
            s_dev.devtype = E_DEVTYPE_M5_STCP;
            s_dev.update = 50;
            s_dev.dispoff = 60 * 1000L;
            s_dev.scale = 2U;
            btna.pin = gpio_num_t::GPIO_NUM_37;
            btna.mode = E_BTNMODE_FALLING;
            btnb.pin = gpio_num_t::GPIO_NUM_39;
            btnb.mode = E_BTNMODE_FALLING_P;
            break;
#endif /* defined (CONFIG_IDF_TARGET_*) */
        default:
            M5.Log.println("Undefined board.");
            M5.Log.printf("board = %d\n", board);
            M5.delay(10000U);
            while (1) {
                M5.Power.deepSleep();
            }
    }

    if (s_dev.scale > 0U) {
        s_dev.w = M5.Display.width();
        s_dev.h = M5.Display.height();
        s_dev.landscape = (bi)(s_dev.w >= s_dev.h);
    }
    else {
        s_dev.w = 0;
        s_dev.h = 0;
        s_dev.landscape = false;
    }

    if (CORE_BTNPOLL(s_btn.t.mode)) {
        td = M5.Touch.getDetail();
    }

}

void m5stack_loop(void){
    M5.update();
    if(CORE_BTNPOLL(s_btn.a.mode)){
        if(M5.BtnA.pressedFor(10)){
            task_xQueueSend(E_TASK_Q_BUTTON_A);
        }
    }

    if(CORE_BTNPOLL(s_btn.b.mode)){
        if(M5.BtnB.pressedFor(10)){
            task_xQueueSend(E_TASK_Q_BUTTON_B);
        }
    }

    if(CORE_BTNPOLL(s_btn.c.mode)){
        if(M5.BtnC.pressedFor(10)){
            task_xQueueSend(E_TASK_Q_BUTTON_C);
        }
    }
}


