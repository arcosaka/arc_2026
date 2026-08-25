/**
 * @file mid_joyhat.cpp
 * @version 26081222.160
 */

#include "mid_m5stack.h"
#include "mid_joyhat.h"

#include "M5HatMiniJoyC.h"

//******************************************************
// グローバル変数定義
//******************************************************

M5HatMiniJoyC joyc;                             // Joystick object

//******************************************************
// ローカル型定義
//******************************************************

typedef enum enum_JOYHAT_CAL{
    CAL_CENTER = 0,   // State 0: Center calibration
    CAL_CENTER_DONE,  // State 1: Center calibration done
    CAL_XY_RANGE,     // State 2: XY axis range calibration
    CAL_DONE,         // State 3: Calibration complete
    CAL_VERIFY        // State 4: Verify calibration results
}E_JOYHAT_CAL;

//******************************************************
// ローカル変数定義
//******************************************************

static E_JOYHAT_CAL cal_state = CAL_CENTER;     // Current calibration state
static u1 u8_sda = 0;
static u1 u8_scl = 0;
static bi bi_isready = false;

static s2 s2_joyx_min;

//******************************************************
// ローカル関数宣言
//******************************************************

static bool joyhat_begin(void);

//******************************************************
// 関数定義
//******************************************************

static bool joyhat_begin(void) {
    bool bi_ret = bi_isready;
    u1 u1_loop;
    u1 u1_sda_in, u1_scl_in;
    u1 u1_sda_ex, u1_scl_ex;
    if(!bi_isready){
        M5.Log.println("joyhat begining");
        if((u8_sda != 0 || u8_scl != 0)){
            u1_sda_in = M5.getPin(m5::pin_name_t::in_i2c_sda);
            u1_scl_in = M5.getPin(m5::pin_name_t::in_i2c_scl);
            M5.Log.printf("In_I2C sda:%d,scl:%d\n", u1_sda_in, u1_scl_in);
            if((u1_sda_in == u8_sda) && (u1_scl_in == u8_scl)){
                M5.Log.println("In_I2C.release");
                M5.In_I2C.release();
            }

            u1_sda_ex = M5.getPin(m5::pin_name_t::ex_i2c_sda);
            u1_scl_ex = M5.getPin(m5::pin_name_t::ex_i2c_scl);
            M5.Log.printf("Ex_I2C sda:%d,scl:%d\n", u1_sda_ex, u1_scl_ex);
            if((u1_sda_ex == u8_sda) && (u1_scl_ex == u8_scl)){
                M5.Log.println("Ex_I2C.release");
                M5.Ex_I2C.release();
            }

            for (u1_loop = 0; u1_loop < 5; u1_loop++) {
                bi_ret = joyc.begin(&Wire, MiniJoyC_ADDR, u8_sda, u8_scl, 100000UL);
                if(bi_ret) {
                    break;
                }
                M5.delay(50);
            }
        }
        if(bi_ret){
            M5.Log.printf("FirmwareVersion=0x%2X\n", joyc.getFirmwareVersion());
            joyc.setLEDColor(0x00FF00U);
            M5.Log.println("joyhat ready!");
            bi_isready = true;
        }
    }
    return bi_ret;
}

void joyhat_setup(void) {
    switch (s_dev.devtype)
    {
        case E_DEVTYPE_M5_STCP: /** M5Stack Stick CPlus */
            u8_sda = 0;
            u8_scl = 26;
            break;
        default:
            M5.Display.clear();
            M5.Display.drawString("Board Fail", M5.Display.width() / 2, M5.Display.height() / 2);
            while (true) {
                M5.Power.lightSleep(1000);
            }
            break;
    }
    joyhat_begin();
}

void joyhat_set_led(u4 u4_rgb888) {
    joyc.setLEDColor(u4_rgb888);
}

void joyhat_set_led(u4 u4_r8, u4 u4_g8, u4 u4_b8) {
    joyc.setLEDColor(
       ((u4_r8 & 0xFFU) << 16U)
     + ((u4_g8 & 0xFFU) << 8U)
     +  (u4_b8 & 0xFFU)
    );
}

void joyhat_get_xyb(u2* pu2_x, u2* pu2_y, u1* pu1_b){
    u2 u2_tmp;
    if(joyhat_begin()) {
        u2_tmp = joyc.getPOSValue(POS_X, _10bit);
        *pu2_x = u2_tmp;
        u2_tmp = joyc.getPOSValue(POS_Y, _10bit);
        *pu2_y = u2_tmp;
        u2_tmp = joyc.getButtonStatus();
        *pu1_b = (u1)u2_tmp;
        if(((*pu2_x) == 0xFF) && ((*pu2_y) == 0xFF)) {
            bi_isready = false;
        }
    }
    else {
        *pu2_x = 0;
        *pu2_y = 0;
        *pu1_b = 0xFF;
    }
}
