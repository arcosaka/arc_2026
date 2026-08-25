/**
 * @file mid_joyhat.h
 * @version 26081222.160
 */

#ifndef LOAD_MID_JOYHAT_H
#define LOAD_MID_JOYHAT_H

#include "main.h"
#include "cmn_setting.h"

//******************************************************
// グローバル型定義
//******************************************************

//******************************************************
// グローバル変数宣言
//******************************************************

//******************************************************
// グローバル関数宣言
//******************************************************

void joyhat_setup(void);
void joyhat_set_led(u4 u4_rgb888);
void joyhat_set_led(u4 u4_r8, u4 u4_g8, u4 u4_b8);
void joyhat_get_xyb(u2* pu2_x, u2* pu2_y, u1* pu1_b);

#endif /* LOAD_MID_JOYHAT_H */
