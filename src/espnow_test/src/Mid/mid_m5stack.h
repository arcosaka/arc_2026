/**
 * @file mid_m5stack.h
 * @version 26053112.280
 */

#ifndef LOAD_MID_M5STACK_H
#define LOAD_MID_M5STACK_H

#include "main.h"

#define CORE_BTNMODE(arg_mode)          ((int)((u1)(arg_mode) & (u1)E_BTNMODE_INTMODEMASK))
#define CORE_BTNPOLL(arg_mode)          (((u1)(arg_mode) & (u1)E_BTNMODE_POLLING) == (u1)E_BTNMODE_POLLING)


//******************************************************
// グローバル型定義
//******************************************************

typedef enum enum_DEVTYPE {
      E_DEVTYPE_M5_CRBS /** M5Stack Core Basic */
    , E_DEVTYPE_M5_CS3S /** M5Stack Core S3-SE */
    , E_DEVTYPE_M5_CRT5 /** M5Stack Core Tab5 */
    , E_DEVTYPE_M5_STCP /** M5Stack Stick CPlus */
    , E_DEVTYPE_M5_STS3 /** M5Stack Stick S3 */
    , E_DEVTYPE_M5_AT3N /** M5Stack Atom S3 */
    , E_DEVTYPE_M5_AT3L /** M5Stack Atom S3 Lite */
    , E_DEVTYPE_M5_AT3R /** M5Stack Atom S3R */
    , E_DEVTYPE_M5_AT3C /** M5Stack Atom S3R Cam */
    , E_DEVTYPE_ENUMMAX
} E_DEVTYPE;

/**
 * @brief ボタン判定モード
 */
typedef enum enum_BTNMODE{
      E_BTNMODE_NONE        = 0x0U                          /** 判定無効 */
    , E_BTNMODE_RISING      = RISING                        /** 割り込み 立ち上がり */
    , E_BTNMODE_FALLING     = FALLING                       /** 割り込み 立ち下がり */
    , E_BTNMODE_CHANGE      = CHANGE                        /** 割り込み 変化時 */
    , E_BTNMODE_ONLOW       = ONLOW                         /** 割り込み LOW時 */
    , E_BTNMODE_ONHIGH      = ONHIGH                        /** 割り込み HIGH時 */
    , E_BTNMODE_ONLOW_WE    = ONLOW_WE                      /** 割り込み LOW時スリープ復帰 */
    , E_BTNMODE_ONHIGH_WE   = ONHIGH_WE                     /** 割り込み HIGH時スリープ復帰 */
    , E_BTNMODE_INTMODEMASK = 0x0FU                         /** 割り込み判定マスク値 */
    , E_BTNMODE_POLLING     = 0x10U                         /** ポーリング判定マスク値 */
    , E_BTNMODE_RISING_P    = E_BTNMODE_POLLING | RISING    /** ポーリング 立ち上がり */
    , E_BTNMODE_FALLING_P   = E_BTNMODE_POLLING | FALLING   /** ポーリング 立ち下がり */
    , E_BTNMODE_CHANGE_P    = E_BTNMODE_POLLING | CHANGE    /** ポーリング 変化時 */
    , E_BTNMODE_ONLOW_P     = E_BTNMODE_POLLING | ONLOW     /** ポーリング LOW時 */
    , E_BTNMODE_ONHIGH_P    = E_BTNMODE_POLLING | ONHIGH    /** ポーリング HIGH時 */
    , E_BTNMODE_ONLOW_WE_P  = E_BTNMODE_POLLING | ONLOW_WE  /** ポーリング LOW時スリープ復帰 */
    , E_BTNMODE_ONHIGH_WE_P = E_BTNMODE_POLLING | ONHIGH_WE /** ポーリング HIGH時スリープ復帰 */
} E_BTNMODE;

typedef struct struct_BTNPIN {
    gpio_num_t pin = gpio_num_t::GPIO_NUM_NC;   /** ピン番号 */
    E_BTNMODE mode = E_BTNMODE_NONE;            /** ボタン判定モード */
} S_BTNPIN;

typedef struct struct_DEVINFO {
    E_DEVTYPE devtype;      /** デバイス種類 */
    u2 w;                   /** 画面幅[px] */
    u2 h;                   /** 画面高さ[px] */
    u1 scale;               /** 拡大率[倍] */
    bi landscape;           /** 横向き[-] */
    u4 update;              /** 描写更新間隔[ms] */
    u4 dispoff;             /** 画面OFF時間[ms] */
    bi psram;               /** 外部PSRAM使用[-] */
} S_DEVINFO;

typedef struct struct_BTNPINS {
    S_BTNPIN a;             /** BtnA */
    S_BTNPIN b;             /** BtnB */
    S_BTNPIN c;             /** BtnC */
    S_BTNPIN e;             /** BtnEXT */
    S_BTNPIN p;             /** BtnPWR */
    S_BTNPIN t;             /** TOUCH */
    S_BTNPIN ex0;           /** EX0 */
    S_BTNPIN ex1;           /** EX1 */
    S_BTNPIN ex2;           /** EX2 */
} S_BTNPINS;


//******************************************************
// グローバル変数宣言
//******************************************************

extern S_DEVINFO s_dev;
extern S_BTNPINS s_btn;

//******************************************************
// グローバル関数宣言
//******************************************************

void m5stack_setup(void);
void m5stack_loop(void);

#endif /* LOAD_MID_M5STACK_H */
