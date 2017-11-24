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

/*电机定义*/
#define	Left_motor_back		9	//左电机后退(IN1)
#define	Left_motor_go		5	//左电机前进(IN2)
#define	Right_motor_go		6	// 右电机前进(IN3)
#define	Right_motor_back	10	// 右电机后退(IN4)

void setPinModes() {
	pinMode(LedPin, OUTPUT);	//设置LED
	pinMode(BtnPin, INPUT);		//按键
	//初始化电机驱动IO为输出方式
	pinMode(Left_motor_go, OUTPUT); // PIN 5 (PWM)
	pinMode(Left_motor_back, OUTPUT); // PIN 9 (PWM)
	pinMode(Right_motor_go, OUTPUT);// PIN 6 (PWM) 
	pinMode(Right_motor_back, OUTPUT);// PIN 10 (PWM)
}


#endif

