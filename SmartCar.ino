/***********************************************************
Project: Smart Car
Arthor:  Paulson Liu
Compay:  Huamintek
Create:  2017-11-24
Modify:  2017-11-24
***********************************************************/
#include "define_h.h"

boolean isMotorRunning = false; //电机是否运行中

void setup()
{

  /* add setup code here */
	setPinModes();

}

void loop()
{
  /* add main program code here */
	keyPressHandler();

}

/*按键处理*/
void keyPressHandler() {
	static long systick_ms_bak = 0;
	static int time_diff = 10;

	int val = digitalRead(BtnPin);
	if (val == HIGH)
	{
		if (millis() - systick_ms_bak > time_diff) {
			systick_ms_bak = millis();
			val = digitalRead(BtnPin);
			if (val == HIGH)
			{
				while (val)
				{
					val = digitalRead(BtnPin);
				}
				isMotorRunning = !isMotorRunning;
				if (isMotorRunning)
				{
					digitalWrite(LedPin, HIGH);
					//run(10);
					moveTest();
				}
				else
				{
					digitalWrite(LedPin, LOW);
					brake(5);
				}
			}
		}
	}
}

/*动作调试*/
void moveTest() {
	back(10); //后退1s
	brake(5);//停止0.5s
	run(10);//前进1s
	brake(5);//停止0.5s
	left(10);//向左转1s
	right(10);//向右转1s
	spin_right(20); //向右旋转2s
	spin_left(20);//向左旋转2s
	brake(5);//停车
}

/*舵机操作*/
void servoHandler() {
	int val = Serial.read();//读取串口收到的数据
	if (val>'0'&&val <= '400')//判断收到数据值是否符合范围
	{
		val = val - '0';//将ASCII码转换成数值，例'9'-'0'=0x39-0x30=9
		val = val*(180 / 9);//将数字转化为角度，例9*（180/9）=180
		Serial.print("moving servo to ");
		Serial.print(val, DEC);
		Serial.println();
		for (int i = 0; i <= 50; i++) //产生PWM个数，等效延时以保证能转到响应角度
		{
			servopulse(ServoPin, val);//模拟产生PWM
		}
	}
}

/*舵机角度控制,模拟PWM信号发送*/
void servopulse(int servopin, int myangle)/*定义一个脉冲函数，用来模拟方式产生PWM值*/
{
	int pulsewidth = (myangle * 11) + 500;//将角度转化为500-2480 的脉宽值
	digitalWrite(servopin, HIGH);//将舵机接口电平置高
	delayMicroseconds(pulsewidth);//延时脉宽值的微秒数
	digitalWrite(servopin, LOW);//将舵机接口电平置低
	delay(20 - pulsewidth / 1000);//延时周期内剩余时间
}

/*电机运动*/
void run(int time)     // 前进
{
	digitalWrite(Right_motor_go, HIGH);  // 右电机前进
	digitalWrite(Right_motor_back, LOW);
	analogWrite(Right_motor_go, 200);//PWM比例0~255调速，左右轮差异略增减
	analogWrite(Right_motor_back, 0);
	digitalWrite(Left_motor_go, HIGH);  // 左电机前进
	digitalWrite(Left_motor_back, LOW);
	analogWrite(Left_motor_go, 200);//PWM比例0~255调速，左右轮差异略增减
	analogWrite(Left_motor_back, 0);
	delay(time * 100);   //执行时间，可以调整  
}

/*电机刹车*/
void brake(int time)         //刹车，停车
{
	digitalWrite(Right_motor_go, LOW);
	digitalWrite(Right_motor_back, LOW);
	digitalWrite(Left_motor_go, LOW);
	digitalWrite(Left_motor_back, LOW);
	delay(time * 100);//执行时间，可以调整  
}

/*左转(左轮不动，右轮前进)*/
void left(int time)
{
	digitalWrite(Right_motor_go, HIGH);	// 右电机前进
	digitalWrite(Right_motor_back, LOW);
	analogWrite(Right_motor_go, 200);
	analogWrite(Right_motor_back, 0);//PWM比例0~255调速
	digitalWrite(Left_motor_go, LOW);   //左轮不动
	digitalWrite(Left_motor_back, LOW);
	analogWrite(Left_motor_go, 0);
	analogWrite(Left_motor_back, 0);//PWM比例0~255调速
	delay(time * 100);	//执行时间，可以调整  
}

/*左转(左轮后退，右轮前进)*/
void spin_left(int time) 
{
	digitalWrite(Right_motor_go, HIGH);	// 右电机前进
	digitalWrite(Right_motor_back, LOW);
	analogWrite(Right_motor_go, 200);
	analogWrite(Right_motor_back, 0);//PWM比例0~255调速
	digitalWrite(Left_motor_go, LOW);   //左轮后退
	digitalWrite(Left_motor_back, HIGH);
	analogWrite(Left_motor_go, 0);
	analogWrite(Left_motor_back, 200);//PWM比例0~255调速
	delay(time * 100);	//执行时间，可以调整  
}

/*右转(右轮不动，左轮前进)*/
void right(int time)        
{
	digitalWrite(Right_motor_go, LOW);   //右电机不动
	digitalWrite(Right_motor_back, LOW);
	analogWrite(Right_motor_go, 0);
	analogWrite(Right_motor_back, 0);//PWM比例0~255调速
	digitalWrite(Left_motor_go, HIGH);//左电机前进
	digitalWrite(Left_motor_back, LOW);
	analogWrite(Left_motor_go, 200);
	analogWrite(Left_motor_back, 0);//PWM比例0~255调速
	delay(time * 100);	//执行时间，可以调整  
}

/*右转(右轮后退，左轮前进)*/
void spin_right(int time)
{
	digitalWrite(Right_motor_go, LOW);   //右电机后退
	digitalWrite(Right_motor_back, HIGH);
	analogWrite(Right_motor_go, 0);
	analogWrite(Right_motor_back, 200);//PWM比例0~255调速
	digitalWrite(Left_motor_go, HIGH);//左电机前进
	digitalWrite(Left_motor_back, LOW);
	analogWrite(Left_motor_go, 200);
	analogWrite(Left_motor_back, 0);//PWM比例0~255调速
	delay(time * 100);	//执行时间，可以调整  
}

/*后退*/
void back(int time)          
{
	digitalWrite(Right_motor_go, LOW);  //右轮后退
	digitalWrite(Right_motor_back, HIGH);
	analogWrite(Right_motor_go, 0);
	analogWrite(Right_motor_back, 150);//PWM比例0~255调速
	digitalWrite(Left_motor_go, LOW);  //左轮后退
	digitalWrite(Left_motor_back, HIGH);
	analogWrite(Left_motor_go, 0);
	analogWrite(Left_motor_back, 150);//PWM比例0~255调速
	delay(time * 100);     //执行时间，可以调整  
}