// define_h.h

#ifndef _DEFINE_H_h
#define _DEFINE_H_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#define LedPin				13	//led
#define BtnPin				A0	//Button
#define ServoPin			2	//Servo
#define beepPin				A1	//������

/*�������*/
#define	Left_motor_back		9	//��������(IN1)
#define	Left_motor_go		5	//����ǰ��(IN2)
#define	Right_motor_go		6	// �ҵ��ǰ��(IN3)
#define	Right_motor_back	10	// �ҵ������(IN4)

/*����������*/
#define SensorRight			A2	//��ѭ�����⴫����(P3.2 OUT1)
#define SensorLeft			A3	//��ѭ�����⴫����(P3.3 OUT2)
#define	SensorLeft_2		A4	//����⴫����(P3.4 OUT3)
#define SensorRight_2		A5	//�Һ��⴫����(P3.5 OUT4)

int SL;		//��ѭ�����⴫����״̬
int SR;		//��ѭ�����⴫����״̬
int SL_2;	//����⴫����״̬
int SR_2;	//�Һ��⴫����״̬

/*�������*/
StepMotor motor1;

void setPinModes() {
	pinMode(LedPin, OUTPUT);	//����LED
	pinMode(BtnPin, INPUT);		//����
	pinMode(beepPin, OUTPUT);	//������
	//��ʼ���������IOΪ�����ʽ
	pinMode(Left_motor_go, OUTPUT); // PIN 5 (PWM)
	pinMode(Left_motor_back, OUTPUT); // PIN 9 (PWM)
	pinMode(Right_motor_go, OUTPUT);// PIN 6 (PWM) 
	pinMode(Right_motor_back, OUTPUT);// PIN 10 (PWM)

	//������
	pinMode(SensorRight, INPUT); //������ѭ�����⴫����Ϊ����
	pinMode(SensorLeft, INPUT); //������ѭ�����⴫����Ϊ����
	pinMode(SensorRight_2, INPUT); //��������⴫����Ϊ����
	pinMode(SensorLeft_2, INPUT); //�����Һ��⴫����Ϊ����

	//�Ž�
	//motor1.pin1 = 2;
	//motor1.pin2 = 3;
	//motor1.pin3 = 4;
	//motor1.pin4 = 7;

	//pinMode(motor1.pin1, OUTPUT);
	//pinMode(motor1.pin2, OUTPUT);
	//pinMode(motor1.pin3, OUTPUT);
	//pinMode(motor1.pin4, OUTPUT);

}


#endif

