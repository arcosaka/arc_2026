/*インクルード***********************************************************/
#include "lpc13xx.h"
#include "gpio.h"
#include "vs-wrc103.h"
#include "ixbus.h"

/*マクロ***********************************************************/

/*グローバル変数***********************************************************/
unsigned int cnt;
unsigned int waitingflg;
short gear = 120;


/*プロトタイプ宣言***********************************************************/
void SI(unsigned int msec);
void DO(unsigned int msec);
void DO_(unsigned int msec);
void RE(unsigned int msec);
void RE_(unsigned int msec);
void MI(unsigned int msec);
void FA(unsigned int msec);
void SO(unsigned int msec);
void SO_(unsigned int msec);
void RA(unsigned int msec);
void RA_(unsigned int msec);
void SI2(unsigned int msec);
void DO2(unsigned int msec);

void DOREMI(void);
void FF(void);

void WAITING(void);

/*メイン関数***********************************************************/
void main(void)
{
	//制御周期の設定[単位：Hz　範囲：30.0~]
	const unsigned short MainCycle = 60;
	Init(MainCycle);		//CPUの初期設定

	//LED(3);
	GPIOSetDir( 0, 4, 0 );
	GPIOSetDir( 0, 5, 0 );
	GPIOSetDir( 1, 6, 0 );
	GPIOSetDir( 1, 7, 0 );
	GPIOSetDir( 3, 0, 0 );
	GPIOSetDir( 3, 2, 0 );

	//ループ
	while(1){
		Sync();					//同期
		//updatePAD();			//パッドの情報を更新

/*
		if(ADRead(1) > 600) {                  //前方向落下防止
			//後進
			Mtr_Run_lv(-10000,10000,0,0,0,0);
			Wait(400);
			//停止
			Mtr_Run_lv(0,0,0,0,0,0);

			DO2(50);
			Wait(50);
			DO2(50);
			Wait(50);
			DO2(50);
		}
		else if(ADRead(0) > 600) {             //後方向落下防止
			//前進
			Mtr_Run_lv(10000,-10000,0,0,0,0);
			Wait(400);
			//停止
			Mtr_Run_lv(0,0,0,0,0,0);

			DO2(50);
			Wait(50);
			DO2(50);
			Wait(50);
			DO2(50);
		}
*/
#if 0
		if(getPAD(PAD_B2) & BTN_R1){				//Rが押されたら

			// Mtr_Run_lv(20000,-20000,0,0,0,0);	//前進
			gear = gear + 5;
			// if (160 < gear)
			// {
			//     gear = 160;
			// }

		}
		else if(getPAD(PAD_B2) & BTN_L1){			//Lが押されたら

			// Mtr_Run_lv(-20000,20000,0,0,0,0);	//バック
			gear = gear - 5;
			if (gear < 0)
			{
				gear = 0;
			}
		}
		else if(getPAD(PAD_B1) & BTN_UP){			//上が押されたら

			// Mtr_Run_lv(-20000,-20000,0,0,0,0);	//右旋回
			Mtr_Run_lv(	 32767
						,-32767
						,0,0,0,0);

		}
		else if(getPAD(PAD_B1) & BTN_DOWN){			//下が押されたら

			// Mtr_Run_lv(20000,20000,0,0,0,0);	//左旋回
			Mtr_Run_lv(	 -32767
						,32767
						,0,0,0,0);

		}
		else{									//何も押されていなかったら

			//停止　アナログスティックの値で移動（左スティック前後で前後進、右スティック左右で旋回）
			// Mtr_Run_lv(	 (getPAD(PAD_AN_LY) + getPAD(PAD_AN_RX))*-127
			// 			,(getPAD(PAD_AN_LY) - getPAD(PAD_AN_RX))*127
			// 			,0,0,0,0);

			Mtr_Run_lv(	 -
						,getPAD(PAD_AN_LY)*gear
						,0,0,0,0);
		}



		//停止　アナログスティックの値で移動（左スティック前後で前後進、右スティック左右で旋回）
		// Mtr_Run_lv(	 (getPAD(PAD_AN_LY) + getPAD(PAD_AN_RX))*-127
		// 			,(getPAD(PAD_AN_LY) - getPAD(PAD_AN_RX))*127
		// 			,0,0,0,0);

		Mtr_Run_lv(	 getPAD(PAD_AN_RY)*-gear
					,getPAD(PAD_AN_LY)*gear
					,0,0,0,0);

#endif

#if 0
		if(GPIOGetValueBit(0, 4) == 0)
		{
			LED(1);
		}
		else if(GPIOGetValueBit(0, 5) == 0)
		{
			LED(3);
		}
		else if(GPIOGetValueBit(1, 6) == 1)
		{
			LED(1);
		}
		else if(GPIOGetValueBit(1, 7) == 1)
		{
			LED(3);
		}
		else if(GPIOGetValueBit(0, 4) == (-1) )
		{
			LED(0);
		}
		else
		{
			LED(2);
		}
#endif

#if 0
		/* if(GPIOGetValueBit(3, 0) == 0 ) */
		if(GPIOGetValueBit(1, 6) == 0 )
		{
			LED(1);
		}
		/* else if(GPIOGetValueBit(3, 2) == 0 ) */
		else if(GPIOGetValueBit(1, 7) == 0 )
		{
			LED(2);
		}
		else
		{
			LED(3);
		}
#endif

		
		
		
		if( ( GPIOGetValueBit(1, 6) == 0 ) && ( GPIOGetValueBit(3, 2) == 0 ) ) //下 + 右ボタン
		{
			//Mtr_Run_lv(-20000,20000,0,0,0,0);	//バック
			Mtr_Run_lv(32767,-22936,0,0,0,0);
		}
		else if( ( GPIOGetValueBit(1, 6) == 0 ) && ( GPIOGetValueBit(3, 0) == 0 ) ) //下 + 左ボタン
		{
			//Mtr_Run_lv(-20000,20000,0,0,0,0);	//バック
			Mtr_Run_lv(22936,-32767,0,0,0,0);
		}
		else if( ( GPIOGetValueBit(1, 7) == 0 ) && ( GPIOGetValueBit(3, 2) == 0 )  ) //上 + 右ボタン
		{
			//Mtr_Run_lv(20000,-20000,0,0,0,0);	//前進
			Mtr_Run_lv(-32767,22936,0,0,0,0);
		}
		else if( ( GPIOGetValueBit(1, 7) == 0 ) && ( GPIOGetValueBit(3, 0) == 0 ) ) //上 + 左ボタン
		{
			//Mtr_Run_lv(20000,-20000,0,0,0,0);	//前進
			Mtr_Run_lv(-22936,32767,0,0,0,0);
		}
		else if( GPIOGetValueBit(1, 6) == 0 ) //下ボタン
		{
			//Mtr_Run_lv(-20000,20000,0,0,0,0);	//バック
			Mtr_Run_lv(32767,-32767,0,0,0,0);
		}
		else if( GPIOGetValueBit(1, 7) == 0 ) //上ボタン
		{
			//Mtr_Run_lv(20000,-20000,0,0,0,0);	//前進
			Mtr_Run_lv(-32767,32767,0,0,0,0);
		}
		else if( GPIOGetValueBit(3, 0) == 0 ) //左ボタン
		{
			//Mtr_Run_lv(20000,20000,0,0,0,0);	//左旋回
			Mtr_Run_lv(-32767,-32767,0,0,0,0);
		}
		else if( GPIOGetValueBit(3, 2) == 0 ) //右ボタン
		{
			//Mtr_Run_lv(-20000,-20000,0,0,0,0);	//右旋回
			Mtr_Run_lv(32767,32767,0,0,0,0);
		}
		else
		{
			Mtr_Run_lv(0,0,0,0,0,0);
		}

		//if(getPAD(PAD_B2) & BTN_CIRCLE) {      //音楽
		//	waitingflg = 1;
		//}

		// if(getPAD(PAD_B2) & BTN_TRIANGLE) {

		// }

		// if(getPAD(PAD_B2) & BTN_SQUARE) {

		// }

		//WAITING();

	}

}

/*サブ関数***********************************************************/

void SI(unsigned int msec)
{
	BuzzerSet(184 , 0);
	BuzzerStart();
	Wait(msec);
	BuzzerStop();
}

void DO(unsigned int msec)
{
	BuzzerSet(179 , 0);
	BuzzerStart();
	Wait(msec);
	BuzzerStop();
}

void DO_(unsigned int msec)
{
	BuzzerSet(169 , 0);
	BuzzerStart();
	Wait(msec);
	BuzzerStop();
}

void RE(unsigned int msec)
{
	BuzzerSet(160 , 0);
	BuzzerStart();
	Wait(msec);
	BuzzerStop();
}

void RE_(unsigned int msec)
{
	BuzzerSet(151 , 0);
	BuzzerStart();
	Wait(msec);
	BuzzerStop();
}

void MI(unsigned int msec)
{
	BuzzerSet(142 , 0);
	BuzzerStart();
	Wait(msec);
	BuzzerStop();
}

void FA(unsigned int msec)
{
	BuzzerSet(134 , 0);
	BuzzerStart();
	Wait(msec);
	BuzzerStop();
}

void SO(unsigned int msec)
{
	BuzzerSet(120 , 0);
	BuzzerStart();
	Wait(msec);
	BuzzerStop();
}

void SO_(unsigned int msec)
{
	BuzzerSet(113 , 0);
	BuzzerStart();
	Wait(msec);
	BuzzerStop();
}

void RA(unsigned int msec)
{
	BuzzerSet(107 , 0);
	BuzzerStart();
	Wait(msec);
	BuzzerStop();
}

void RA_(unsigned int msec)
{
	BuzzerSet(101 , 0);
	BuzzerStart();
	Wait(msec);
	BuzzerStop();
}

void SI2(unsigned int msec)
{
	BuzzerSet(95 , 0);
	BuzzerStart();
	Wait(msec);
	BuzzerStop();
}

void DO2(unsigned int msec)
{
	BuzzerSet(90 , 0);
	BuzzerStart();
	Wait(msec);
	BuzzerStop();
}

void DOREMI(void)
{
	DO(200);
	RE(200);
	MI(200);
	/* FA(200);
	SO(200);
	RA(200);
	SI2(200);
	DO2(200); */

}

void FF(void)
{
	RA(100);
	Wait(100);
	RA(100);
	Wait(100);
	RA(100);
	Wait(100);
	RA(500);
	Wait(100);
	FA(500);
	Wait(100);
	SO(500);
	Wait(100);
	RA(100);
	Wait(250);
	SO(100);
	Wait(100);
	RA(1000);
}

void WAITING(void)
{
	if(waitingflg == 1) {

		if (cnt == 0) {
			BuzzerSet(107 , 0);
			BuzzerStart();
		}
		if (cnt == 6) {
			BuzzerStop();
		}
		if (cnt == 12) {
			BuzzerSet(107 , 0);
			BuzzerStart();
		}
		if (cnt == 18) {
			BuzzerStop();
		}
		if (cnt == 24) {
			BuzzerSet(107 , 0);
			BuzzerStart();
		}
		if (cnt == 30) {
			BuzzerStop();
		}
		if (cnt == 36) {
			BuzzerSet(107 , 0);
			BuzzerStart();
		}
		if (cnt == 66) {
			BuzzerStop();
		}
		if (cnt == 72) {
			BuzzerSet(134 , 0);
			BuzzerStart();
		}
		if (cnt == 102) {
			BuzzerStop();
		}
		if (cnt == 108) {
			BuzzerSet(120 , 0);
			BuzzerStart();
		}
		if (cnt == 138) {
			BuzzerStop();
		}
		if (cnt == 144) {
			BuzzerSet(107 , 0);
			BuzzerStart();
		}
		if (cnt == 150) {
			BuzzerStop();
		}
		if (cnt == 165) {
			BuzzerSet(120 , 0);
			BuzzerStart();
		}
		if (cnt == 171) {
			BuzzerStop();
		}
		if (cnt == 177) {
			BuzzerSet(107 , 0);
			BuzzerStart();
		}
		if (cnt == 237) {
			BuzzerStop();
			waitingflg = 0;
		}

		cnt++;

		if (waitingflg == 0) {
		    cnt = 0;
		}
	}
}
