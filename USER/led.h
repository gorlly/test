#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

//LED1-4: PE7,8,9,10
#define LED1 PEout(7)
#define LED2 PEout(8)	
#define LED3 PEout(9)
#define LED4 PEout(10)

//servo control signal(servo pwm)
#define SERVO_CTRL PBout(7)

/*
sbit RightPlus=P0^0; //N4����
sbit RightMinus=P0^1;	//N3�Ҹ�
sbit LeftMinus=P0^2; //N2��
sbit LeftPlus=P0^3; //N1����	  
sbit RightEna=P0^4;//ENB��ʹ��
sbit LeftEna=P0^5;	//ENA��ʹ��


sbit ENB = P1^2;
sbit IN4 = P1^3;
sbit IN3 = P1^4;
sbit IN2 = P1^5;
sbit IN1 = P1^6;
sbit ENA = P1^7;


sbit trlg = P1^0;  //��������ഥ��λ
sbit echo = P1^1;  //������������λ

*/

#define ENB  PBout(4)  
#define IN4  PDout(6)
#define IN3  PDout(4)
#define IN2  PDout(2)
#define IN1  PDout(0)
#define ENA  PCout(11)


#define trlg PEout(2)     //��������ഥ��λ
#define echo PAin(0)     //������������λ


void LED_Init(void);//��ʼ��
void Ultrasonic_Init(void);
long int count_len(void);
void Motor_Init(void);

void car_left(void);
void car_go(void);
void car_back(void);
void car_stop(void);
void car_right(void);

		 				    
#endif
