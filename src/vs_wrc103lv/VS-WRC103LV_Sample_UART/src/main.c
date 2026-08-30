/*インクルード***********************************************************/
#include "lpc13xx.h"
#include "gpio.h"
#include "vs-wrc103.h"
#include "ixbus.h"

#include "app_event.h"
#include "app_serialio.h"

//******************************************************
// グローバル変数定義
//******************************************************

//******************************************************
// ローカル型定義
//******************************************************

//******************************************************
// ローカル変数定義
//******************************************************

#define MORTOR_L_FW (-32767)
#define MORTOR_L_BW (+32767)
#define MORTOR_R_FW (+32767)
#define MORTOR_R_BW (-32767)
#define MORTOR_X (9831)

static U2 u2_stamp_old = 0xFFFF;

//******************************************************
// 関数定義
//******************************************************

static void main_task(void)
{
    S2 s2_l = 0, s2_r = 0;
    const S_BUTTON* ps_btn = &serialio_data_c.data.btns.bits;
    if(u2_stamp_old != serialio_data_c.data.stamp)
    {   /* 値が更新された場合のみモーターの指示値を変更する */
        u2_stamp_old = serialio_data_c.data.stamp;
        if (ps_btn->isfull)
        {   /* BTコントローラー */

        }
        else
        {   /* 予備コントローラー */
            if(ps_btn->x_down)
            {   /* 下ボタン */
                s2_l = MORTOR_L_BW;
                s2_r = MORTOR_R_BW;
                if (ps_btn->x_right)
                {
                    s2_r += MORTOR_X;
                }
                else if(ps_btn->x_left)
                {
                    s2_l -= MORTOR_X;
                }
                else
                {
                    /* 何もしない */
                }
            }
            else if(ps_btn->x_up)
            {   /* 上ボタン */
                s2_l = MORTOR_L_FW;
                s2_r = MORTOR_R_FW;
                if (ps_btn->x_right)
                {
                    s2_r -= MORTOR_X;
                }
                else if(ps_btn->x_left)
                {
                    s2_l += MORTOR_X;
                }
                else
                {
                    /* 何もしない */
                }
            }
            else if(ps_btn->x_left)
            {   /* 左ボタン */
                s2_l = MORTOR_L_FW;
                s2_r = MORTOR_R_BW;
            }
            else if(ps_btn->x_right)
            {   /* 右ボタン */
                s2_l = MORTOR_L_BW;
                s2_r = MORTOR_R_FW;
            }
            else
            {
                /* 何もしない */
            }
        }
        Mtr_Run_lv(s2_l, s2_r, 0, 0, 0, 0);
    }
}

/*メイン関数***********************************************************/
int main(void)
{
    E_EVE e_eve_tmp;
    //制御周期の設定[単位：Hz　範囲：30.0~]
    const unsigned short MainCycle = 60;
    Init(MainCycle);		//CPUの初期設定

    //シリアル通信初期化
    InitSci3(CBR_115200, non, 1);

    Event_Init();

    //ループ
    while (1) {
        e_eve_tmp = Event_GetEvent();
        switch (e_eve_tmp)
        {
            case E_EVE_RX:
                LED(1); //緑のLED点灯
                SerialIO_RxData();
                break;

            case E_EVE_MAIN:
                main_task();
                break;

            case E_EVE_TX:
                LED(2); //オレンジのLED点灯
                serialio_data_b.data.stamp = serialio_data_c.data.stamp;
                serialio_data_b.data.btns = serialio_data_c.data.btns;
                SerialIO_TxData();
                break;

            default:
                Sync();
                LED(0);
                break;
        }

        //LED(1);		//緑のLED点灯
        //if(SciByteRx(&data) > 0){
        //	LED(2);		//オレンジのLED点灯
        //	SciByteTx(data);
        //}

    }
}
