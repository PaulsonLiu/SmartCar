// mySteper.h
//���������������
//int timePerPai = -1;                // ÿ����ʱ24ms������ת�ٺͷ��򡣸�ֵ��ʱ��ת��
//StepMotor motor1;
//motor1.multi_steps(4096, timePerPai);     //һȦ
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
	int pai = 0;  //  �ļ�����˳ʱ��7-0����ʱ��0-7��
	//int timePerPai; //  ÿ����ʱ�������ٶȣ�1ms��Ӧ����١���ֵΪ��ʱ�뷽��

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

/*�����ಽ*/
void StepMotor::multi_steps(int step, int time) {
	for (size_t i = 0; i < step; i++)
	{
		one_step(time);
	}
}

/*  �˺�������һ�ģ����������ٶ�����ת���� */
void StepMotor::one_step(int t) {
	switch (pai) {
	case 0:                        //  (0001)  ��Ӧ8�Ĳ�ͬ�����ֵ��
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
	if (t < 0) {                  // tΪ��ֵ���������0-7��
		pai++;
		if (pai > 7) {
			pai = 0;                 // ������7���¿�ʼ��
		}
	}
	else {                    // tΪ��ֵ���������7-0��
		pai--;
		if (pai < 0) {          // �����������¿�ʼ��
			pai = 7;
		}
	}
	delay(abs(t));            // ��ʱ������ת�ٸߡ�
}



/*����2,��������˿ڷ���*/

/* �������8����������Ӧ28BYJ-48��ÿȦ64�������ٱ�64��
�����ÿȦ4096����ʹ�ö���������ֱ����λ����ڡ�
*/
//int p = 0;         // �ļ�����˳ʱ��0-7����ʱ��7-0��
//int t;                // ÿ����ʱ�������ٶȣ�1ms��Ӧ����١���ֵΪ��ʱ�뷽��
//byte b[] = { B00010000,B00110000,B00100000,B01100000,
//B01000000,B11000000,B10000000,B10010000 };
//// ��Ӧÿ�ĵ�D4-D7��������롣��4λ��Ч��
//
//void setup() {
//	//  Serial.begin(9600);  // ��ʼ�����ڣ���Ϊ���ӡ�
//	DDRD = DDRD | B11110000;  // ��D4-D7��Ϊ��������������Ų��䡣  
//}
//
//void loop() {
//	//  Serial.println(p);  // ������������������á�
//	t = -24;                // ÿ����ʱ24ms������ת�ٺͷ��򡣸�ֵ��ʱ��ת��
//	one_step(t);          // ����һ�ġ�
//}
//
////  �˺�������һ�ģ����������ٶ�����ת����
//void one_step(int t) {
//	PORTD = PORTD & B00001111;  // ���D4-D7�ţ�D0-D3�Ų��䡣
//	PORTD = PORTD | b[p];                // ��λD4-D7�ţ�D0-D3�Ų��䡣
//										 //  Serial.println(PORTD,BIN);           //  ����������룬�����á�
//	if (t < 0) {                                     // tΪ��ֵ���������0-7��
//		p--;
//		if (p < 0) {
//			p = 7;                                    // ������0���¿�ʼ��
//		}
//	}
//	else {                                       // tΪ��ֵ�����������7-0��
//		p++;
//		if (p > 7) {                              // ������7���¿�ʼ��
//			p = 0;
//		}
//	}
//	delay(abs(t));                               // ��ʱ������ת�ٸߡ�
//}


#endif

