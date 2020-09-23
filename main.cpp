#include "mbed.h"
#include "adrobo.h"
/* DCモータを使う場合は Motor.h を
   読み込む必要があります． */
#include "Motor.h"

BusOut led(LED1,LED2,LED3,LED4,LED5,LED);
/* 下記のように変数motor1を宣言することで，
   CN1に接続したDCモータを制御することが
   可能になります． */
Motor motor1(MOTOR11, MOTOR12);
/* DCモータは計2個同時に制御できます．
   CN2に接続したDCモータも制御したい場合は
   以下の様にします */
/* Motor motor2(MOTOR21, MOTOR22); */
PwmOut servo1(SERVO1);
PwmOut servo3(SERVO3);
AnalogIn ad[] = {A0};
BusIn sw(SW1);

int main() {
  /* valueがモータに与える値（速度に相当）．
     deltaがvalueを時間に応じてどれだけ変化
     させるかを表した値 */
	servo1.period_ms(20);
	servo3.period_ms(20);
	sw.mode(PullUp);
  int i;
	int n;
  float value = 0.0f, delta = 0.1f;
		  float val;
				


  /* value に n を足しこむ */	
  
	    /* valueの絶対値（fabs(value)が
       1.0以上になったら delta の符号を
       反転させる．こうすることで，
       valueは -1 ～ 1 の間をいったり
       きたりする． */
	while(1) {
		    val = ad[0].read();
	  val = (val - 0.5) * 2; 
		val += delta;
    if (fabs(val) >= 1.0f) {
      delta *= -1.0f;
    }
    printf("%f\r\n", val);
		motor1 = val;
		  wait(0.2);
	if ((sw & 0x01) == 0) {

		for(i = 800; i <= 1800; i += 100) {
  
 			/* 実際にサーボモータに位置を指令する際には，
         パルス幅というものを設定する必要があります．
         次の命令はそれを行うためのものです．
         iの値に応じて400マイクロ秒～2000マイクロ秒に
         設定しています．
			初期位置は個体差があるので注意してください．*/
		servo1.pulsewidth_us(i);
			
		}
		wait(0.2);

		for(n = 500; n <= 2500; n += 100) {
	  servo3.pulsewidth_us(n);
		}
		val = 0;
		motor1 = val;
	}

	if ((sw & 0x01) == 1) {
			
		for(i = 1800; i >= 800; i -= 100) {
		servo1.pulsewidth_us(i);
		}	
		for(n = 2500; n >= 500; n -= 50) {
    /* motor1 に数値を代入するとその値に
       応じた速度で回転する．
       -1～1の値を与える必要がある．
       絶対値が大きいほど速く回転する．
       符号は回転の方向を表す．
     */
	  servo3.pulsewidth_us(n);
		}

	}

   }
	 
  
 }
	