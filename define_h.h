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
#define beepPin				A1	//蜂鸣器

/*电机定义*/
#define	Left_motor_back		9	//左电机后退(IN1)
#define	Left_motor_go		5	//左电机前进(IN2)
#define	Right_motor_go		6	// 右电机前进(IN3)
#define	Right_motor_back	10	// 右电机后退(IN4)

/*传感器定义*/
#define SensorRight			A2	//右循迹红外传感器(P3.2 OUT1)
#define SensorLeft			A3	//左循迹红外传感器(P3.3 OUT2)
#define	SensorLeft_2		A4	//左红外传感器(P3.4 OUT3)
#define SensorRight_2		A5	//右红外传感器(P3.5 OUT4)

int SL;		//左循迹红外传感器状态
int SR;		//右循迹红外传感器状态
int SL_2;	//左红外传感器状态
int SR_2;	//右红外传感器状态

/*步进电机*/
StepMotor motor1;

void setPinModes() {
	pinMode(LedPin, OUTPUT);	//设置LED
	pinMode(BtnPin, INPUT);		//按键
	pinMode(beepPin, OUTPUT);	//蜂鸣器
	//初始化电机驱动IO为输出方式
	pinMode(Left_motor_go, OUTPUT); // PIN 5 (PWM)
	pinMode(Left_motor_back, OUTPUT); // PIN 9 (PWM)
	pinMode(Right_motor_go, OUTPUT);// PIN 6 (PWM) 
	pinMode(Right_motor_back, OUTPUT);// PIN 10 (PWM)

	//传感器
	pinMode(SensorRight, INPUT); //定义右循迹红外传感器为输入
	pinMode(SensorLeft, INPUT); //定义左循迹红外传感器为输入
	pinMode(SensorRight_2, INPUT); //定义左红外传感器为输入
	pinMode(SensorLeft_2, INPUT); //定义右红外传感器为输入

	//门禁
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

