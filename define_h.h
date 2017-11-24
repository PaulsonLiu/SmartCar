// define_h.h

#ifndef _DEFINE_H_h
#define _DEFINE_H_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#define LedPin				13	//led
#define BtnPin				A5	//Button
#define ServoPin			2	//Servo

/*�������*/
#define	Left_motor_back		9	//��������(IN1)
#define	Left_motor_go		5	//����ǰ��(IN2)
#define	Right_motor_go		6	// �ҵ��ǰ��(IN3)
#define	Right_motor_back	10	// �ҵ������(IN4)

void setPinModes() {
	pinMode(LedPin, OUTPUT);	//����LED
	pinMode(BtnPin, INPUT);		//����
	//��ʼ���������IOΪ�����ʽ
	pinMode(Left_motor_go, OUTPUT); // PIN 5 (PWM)
	pinMode(Left_motor_back, OUTPUT); // PIN 9 (PWM)
	pinMode(Right_motor_go, OUTPUT);// PIN 6 (PWM) 
	pinMode(Right_motor_back, OUTPUT);// PIN 10 (PWM)
}


#endif

