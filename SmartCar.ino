/***********************************************************
Project: Smart Car
Arthor:  Paulson Liu
Compay:  Huamintek
Create:  2017-11-24
Modify:  2017-11-24
***********************************************************/
#include "define_h.h"

boolean isMotorRunning = false; //����Ƿ�������

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

/*��������*/
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

/*��������*/
void moveTest() {
	back(10); //����1s
	brake(5);//ֹͣ0.5s
	run(10);//ǰ��1s
	brake(5);//ֹͣ0.5s
	left(10);//����ת1s
	right(10);//����ת1s
	spin_right(20); //������ת2s
	spin_left(20);//������ת2s
	brake(5);//ͣ��
}

/*�������*/
void servoHandler() {
	int val = Serial.read();//��ȡ�����յ�������
	if (val>'0'&&val <= '400')//�ж��յ�����ֵ�Ƿ���Ϸ�Χ
	{
		val = val - '0';//��ASCII��ת������ֵ����'9'-'0'=0x39-0x30=9
		val = val*(180 / 9);//������ת��Ϊ�Ƕȣ���9*��180/9��=180
		Serial.print("moving servo to ");
		Serial.print(val, DEC);
		Serial.println();
		for (int i = 0; i <= 50; i++) //����PWM��������Ч��ʱ�Ա�֤��ת����Ӧ�Ƕ�
		{
			servopulse(ServoPin, val);//ģ�����PWM
		}
	}
}

/*����Ƕȿ���,ģ��PWM�źŷ���*/
void servopulse(int servopin, int myangle)/*����һ�����庯��������ģ�ⷽʽ����PWMֵ*/
{
	int pulsewidth = (myangle * 11) + 500;//���Ƕ�ת��Ϊ500-2480 ������ֵ
	digitalWrite(servopin, HIGH);//������ӿڵ�ƽ�ø�
	delayMicroseconds(pulsewidth);//��ʱ����ֵ��΢����
	digitalWrite(servopin, LOW);//������ӿڵ�ƽ�õ�
	delay(20 - pulsewidth / 1000);//��ʱ������ʣ��ʱ��
}

/*����˶�*/
void run(int time)     // ǰ��
{
	digitalWrite(Right_motor_go, HIGH);  // �ҵ��ǰ��
	digitalWrite(Right_motor_back, LOW);
	analogWrite(Right_motor_go, 200);//PWM����0~255���٣������ֲ���������
	analogWrite(Right_motor_back, 0);
	digitalWrite(Left_motor_go, HIGH);  // ����ǰ��
	digitalWrite(Left_motor_back, LOW);
	analogWrite(Left_motor_go, 200);//PWM����0~255���٣������ֲ���������
	analogWrite(Left_motor_back, 0);
	delay(time * 100);   //ִ��ʱ�䣬���Ե���  
}

/*���ɲ��*/
void brake(int time)         //ɲ����ͣ��
{
	digitalWrite(Right_motor_go, LOW);
	digitalWrite(Right_motor_back, LOW);
	digitalWrite(Left_motor_go, LOW);
	digitalWrite(Left_motor_back, LOW);
	delay(time * 100);//ִ��ʱ�䣬���Ե���  
}

/*��ת(���ֲ���������ǰ��)*/
void left(int time)
{
	digitalWrite(Right_motor_go, HIGH);	// �ҵ��ǰ��
	digitalWrite(Right_motor_back, LOW);
	analogWrite(Right_motor_go, 200);
	analogWrite(Right_motor_back, 0);//PWM����0~255����
	digitalWrite(Left_motor_go, LOW);   //���ֲ���
	digitalWrite(Left_motor_back, LOW);
	analogWrite(Left_motor_go, 0);
	analogWrite(Left_motor_back, 0);//PWM����0~255����
	delay(time * 100);	//ִ��ʱ�䣬���Ե���  
}

/*��ת(���ֺ��ˣ�����ǰ��)*/
void spin_left(int time) 
{
	digitalWrite(Right_motor_go, HIGH);	// �ҵ��ǰ��
	digitalWrite(Right_motor_back, LOW);
	analogWrite(Right_motor_go, 200);
	analogWrite(Right_motor_back, 0);//PWM����0~255����
	digitalWrite(Left_motor_go, LOW);   //���ֺ���
	digitalWrite(Left_motor_back, HIGH);
	analogWrite(Left_motor_go, 0);
	analogWrite(Left_motor_back, 200);//PWM����0~255����
	delay(time * 100);	//ִ��ʱ�䣬���Ե���  
}

/*��ת(���ֲ���������ǰ��)*/
void right(int time)        
{
	digitalWrite(Right_motor_go, LOW);   //�ҵ������
	digitalWrite(Right_motor_back, LOW);
	analogWrite(Right_motor_go, 0);
	analogWrite(Right_motor_back, 0);//PWM����0~255����
	digitalWrite(Left_motor_go, HIGH);//����ǰ��
	digitalWrite(Left_motor_back, LOW);
	analogWrite(Left_motor_go, 200);
	analogWrite(Left_motor_back, 0);//PWM����0~255����
	delay(time * 100);	//ִ��ʱ�䣬���Ե���  
}

/*��ת(���ֺ��ˣ�����ǰ��)*/
void spin_right(int time)
{
	digitalWrite(Right_motor_go, LOW);   //�ҵ������
	digitalWrite(Right_motor_back, HIGH);
	analogWrite(Right_motor_go, 0);
	analogWrite(Right_motor_back, 200);//PWM����0~255����
	digitalWrite(Left_motor_go, HIGH);//����ǰ��
	digitalWrite(Left_motor_back, LOW);
	analogWrite(Left_motor_go, 200);
	analogWrite(Left_motor_back, 0);//PWM����0~255����
	delay(time * 100);	//ִ��ʱ�䣬���Ե���  
}

/*����*/
void back(int time)          
{
	digitalWrite(Right_motor_go, LOW);  //���ֺ���
	digitalWrite(Right_motor_back, HIGH);
	analogWrite(Right_motor_go, 0);
	analogWrite(Right_motor_back, 150);//PWM����0~255����
	digitalWrite(Left_motor_go, LOW);  //���ֺ���
	digitalWrite(Left_motor_back, HIGH);
	analogWrite(Left_motor_go, 0);
	analogWrite(Left_motor_back, 150);//PWM����0~255����
	delay(time * 100);     //ִ��ʱ�䣬���Ե���  
}