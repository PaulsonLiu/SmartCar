// mySteper.h
//步进电机调用例子
//int timePerPai = -1;                // 每拍延时24ms，设置转速和方向。负值逆时针转。
//StepMotor motor1;
//motor1.multi_steps(4096, timePerPai);     //一圈
//delay(1000);
//motor1.multi_steps(4096,-timePerPai);
//delay(1000);


#ifndef _MYSTEPER_h
#define _MYSTEPER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class StepMotor
{
public:
	int pin1;
	int pin2;
	int pin3;
	int pin4;
	int pai = 0;  //  拍计数，顺时针7-0，逆时针0-7。
	//int timePerPai; //  每拍延时，控制速度，1ms对应最高速。负值为逆时针方向。

	void multi_steps(int step, int time);
	void one_step(int t);

	StepMotor();
	~StepMotor();

private:

};

StepMotor::StepMotor()
{
}

StepMotor::~StepMotor()
{
}

/*步进多步*/
void StepMotor::multi_steps(int step, int time) {
	for (size_t i = 0; i < step; i++)
	{
		one_step(time);
	}
}

/*  此函数驱动一拍，参数控制速度与旋转方向 */
void StepMotor::one_step(int t) {
	switch (pai) {
	case 0:                        //  (0001)  对应8拍不同的输出值。
		digitalWrite(pin1, LOW);
		digitalWrite(pin2, LOW);
		digitalWrite(pin3, LOW);
		digitalWrite(pin4, HIGH);
		break;
	case 1:                       //  (0011)
		digitalWrite(pin1, LOW);
		digitalWrite(pin2, LOW);
		digitalWrite(pin3, HIGH);
		digitalWrite(pin4, HIGH);
		break;
	case 2:                       //  (0010)
		digitalWrite(pin1, LOW);
		digitalWrite(pin2, LOW);
		digitalWrite(pin3, HIGH);
		digitalWrite(pin4, LOW);
		break;
	case 3:                       //  (0110)
		digitalWrite(pin1, LOW);
		digitalWrite(pin2, HIGH);
		digitalWrite(pin3, HIGH);
		digitalWrite(pin4, LOW);
		break;
	case 4:                       //  (0100)
		digitalWrite(pin1, LOW);
		digitalWrite(pin2, HIGH);
		digitalWrite(pin3, LOW);
		digitalWrite(pin4, LOW);
		break;
	case 5:                        //  (1100)
		digitalWrite(pin1, HIGH);
		digitalWrite(pin2, HIGH);
		digitalWrite(pin3, LOW);
		digitalWrite(pin4, LOW);
		break;
	case 6:                       //  (1000)
		digitalWrite(pin1, HIGH);
		digitalWrite(pin2, LOW);
		digitalWrite(pin3, LOW);
		digitalWrite(pin4, LOW);
		break;
	case 7:                       //  (1001)
		digitalWrite(pin1, HIGH);
		digitalWrite(pin2, LOW);
		digitalWrite(pin3, LOW);
		digitalWrite(pin4, HIGH);
		break;
	}
	if (t < 0) {                  // t为负值，正向计数0-7。
		pai++;
		if (pai > 7) {
			pai = 0;                 // 计数到7重新开始。
		}
	}
	else {                    // t为正值，逆向计数7-0。
		pai--;
		if (pai < 0) {          // 计数到零重新开始。
			pai = 7;
		}
	}
	delay(abs(t));            // 延时，短则转速高。
}



/*方法2,批量处理端口方法*/

/* 步进电机8拍驱动，对应28BYJ-48，每圈64步，减速比64，
输出轴每圈4096步。使用二进制掩码直接置位输出口。
*/
//int p = 0;         // 拍计数，顺时针0-7，逆时针7-0。
//int t;                // 每拍延时，控制速度，1ms对应最高速。负值为逆时针方向。
//byte b[] = { B00010000,B00110000,B00100000,B01100000,
//B01000000,B11000000,B10000000,B10010000 };
//// 对应每拍的D4-D7脚输出掩码。高4位有效。
//
//void setup() {
//	//  Serial.begin(9600);  // 初始化串口，作为监视。
//	DDRD = DDRD | B11110000;  // 置D4-D7脚为步进输出，其它脚不变。  
//}
//
//void loop() {
//	//  Serial.println(p);  // 串口输出拍数，调试用。
//	t = -24;                // 每拍延时24ms，设置转速和方向。负值逆时针转。
//	one_step(t);          // 驱动一拍。
//}
//
////  此函数驱动一拍，参数控制速度与旋转方向。
//void one_step(int t) {
//	PORTD = PORTD & B00001111;  // 清除D4-D7脚，D0-D3脚不变。
//	PORTD = PORTD | b[p];                // 置位D4-D7脚，D0-D3脚不变。
//										 //  Serial.println(PORTD,BIN);           //  串口输出掩码，调试用。
//	if (t < 0) {                                     // t为负值，逆向计数0-7。
//		p--;
//		if (p < 0) {
//			p = 7;                                    // 计数到0重新开始。
//		}
//	}
//	else {                                       // t为正值，逆正向计数7-0。
//		p++;
//		if (p > 7) {                              // 计数到7重新开始。
//			p = 0;
//		}
//	}
//	delay(abs(t));                               // 延时，短则转速高。
//}


#endif

