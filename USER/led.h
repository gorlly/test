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
sbit RightPlus=P0^0; //N4右正
sbit RightMinus=P0^1;	//N3右负
sbit LeftMinus=P0^2; //N2左负
sbit LeftPlus=P0^3; //N1左正	  
sbit RightEna=P0^4;//ENB右使能
sbit LeftEna=P0^5;	//ENA左使能


sbit ENB = P1^2;
sbit IN4 = P1^3;
sbit IN3 = P1^4;
sbit IN2 = P1^5;
sbit IN1 = P1^6;
sbit ENA = P1^7;


sbit trlg = P1^0;  //超声波测距触发位
sbit echo = P1^1;  //超声波测距输出位

*/

#define ENB  PBout(4)  
#define IN4  PDout(6)
#define IN3  PDout(4)
#define IN2  PDout(2)
#define IN1  PDout(0)
#define ENA  PCout(11)


#define trlg PEout(2)     //超声波测距触发位
#define echo PAin(0)     //超声波测距输出位


void LED_Init(void);//初始化
void Ultrasonic_Init(void);
long int count_len(void);
void Motor_Init(void);

void car_left(void);
void car_go(void);
void car_back(void);
void car_stop(void);
void car_right(void);

		 				    
#endif
