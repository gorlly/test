#include "led.h"
#include "delay.h"
   
//��ʼ��LED-I/O�����.��ʹ���������ڵ�ʱ��		    

//LED1-4: PE7,8,9,10

//servo control signal PB7;

void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;

//ʹ��PB,PE,PC�˿�ʱ�� 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);	 

//-------------------GPIO-E7 Configure-----------------------------------------------	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //LED1-->PE.7 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz

 GPIO_Init(GPIOE, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOE.7
 GPIO_SetBits(GPIOE,GPIO_Pin_7);						 //PE.7 �����

//-------------------GPIO-E8 Configure-------------------------------------------------
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED2-->PE.8 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz

 GPIO_Init(GPIOE, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOE.8
 GPIO_SetBits(GPIOE,GPIO_Pin_8);						 //PE.8 �����

 //-------------------GPIO-E9 Configure-------------------------------------------------
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 //LED3-->PE.9 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz

 GPIO_Init(GPIOE, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOE.9
 GPIO_SetBits(GPIOE,GPIO_Pin_9);						 //PE.9 �����

 //-------------------GPIO-E10 Configure-------------------------------------------------
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				 //LED4-->PE.10 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz

 GPIO_Init(GPIOE, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOE.10
 GPIO_SetBits(GPIOE,GPIO_Pin_10);						 //PE.10 �����

 //-------------------GPIO-B7 Configure-------------------------------------------------
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //Servo�˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz

 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.7
 GPIO_ResetBits(GPIOB,GPIO_Pin_7);						 //PB.7 output as low level

}


void Motor_Init(void)
{

 GPIO_InitTypeDef  GPIO_InitStructure;

    //ʹ��PB,PE,PC�˿�ʱ�� 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);	 

 //-------------------//#define ENB  PBout(4)-------------------------------------------------
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 //LED0-->PB.4 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz

 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.4
 GPIO_SetBits(GPIOB,GPIO_Pin_4);						 //PB.4 output as high level

 //-----------------------#define IN4  PDout(6)---------------------------------------------
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				 //LED0-->PD.6 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz

 GPIO_Init(GPIOD, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOD.6
 GPIO_SetBits(GPIOD,GPIO_Pin_6);						 //PD.6 output as high level
 //-----------------------//#define IN3  PDout(4)---------------------------------------------
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 //LED0-->PD.4 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz

 GPIO_Init(GPIOD, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOD.4
 GPIO_SetBits(GPIOD,GPIO_Pin_4);						 //PD.4 output as high level
 //-----------------------//#define IN2  PDout(2)---------------------------------------------
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //LED0-->PD.2 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz

 GPIO_Init(GPIOD, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOD.2
 GPIO_SetBits(GPIOD,GPIO_Pin_2);						 //PD.2 output as high level

 //-----------------------//#define IN1  PDout(0)---------------------------------------------
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //LED0-->PD.0 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz

 GPIO_Init(GPIOD, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOD.0
 GPIO_SetBits(GPIOD,GPIO_Pin_0);						 //PD.0 output as high level

 //-----------------------//#define ENA  PCout(11)---------------------------------------------
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				 //LED0-->PC.11 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz

 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC.11
 GPIO_SetBits(GPIOC,GPIO_Pin_11);						 //PC.11 output as high level
}

void Ultrasonic_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
   	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);//ʹ�� TIM5 ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOA, ENABLE);//ʹ��PE�˿�ʱ�� 	 

   //-------------------GPIO-E2 Configure-----------------------------------------------	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //LED0-->PE.2 �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
    
    GPIO_Init(GPIOE, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOE.2
    GPIO_SetBits(GPIOE,GPIO_Pin_2);						 //PE.2 �����

    //-------------------GPIO-A0 Configure-----------------------------------------------	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //LED0-->PA.0 �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		     //��������,��׽�ߵ�ƽ����
  
    
    GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.0
    GPIO_ResetBits(GPIOA,GPIO_Pin_0);  //PA0 ����

}


long int time_count=0;

void TIM3_IRQHandler(void)  
{
    if(TIM_GetITStatus(TIM3, TIM_IT_Update)!=RESET){
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
        //LED1 = !LED1;
        time_count ++ ; 
    }

} 


long int count_len(void)
{
	long int time = 0;
	//��trlg��10us���ϵĸߵ�ƽ
	trlg = 0;
	trlg = 1;
	delay_us(20);
	trlg = 0;

	//�ȴ�echo��״̬��Ϊ�ߵ�ƽ
	//while(!echo);//GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
 
//    while(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3));
	
    //��ʼ����ʱ��0����ʼ��ʱ
    //time0_start(); 
//    time_count = 0;          
//    TIM_Cmd(TIM3, ENABLE);
	
    //�ȴ�echo��Ϊ�͵�ƽ;
	//while(echo);
  
  //  while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3));
	
    //ֹͣ��ʱ0���������
//	TR0 = 0;ET0 = 0;
 
//    TIM_Cmd(TIM3, DISABLE);

//	time = count*256+TL0;
//	return (long float)(time*1.87)/100;

    time = time_count;
    return time;

	//���Ծ���=���ߵ�ƽʱ��*340m/s��/2
	/*
	���ü��������Echo�ߵ�ƽʱ�䡣
	��ʱ������Ƶ��Ϊ�����1/12��
	�辧��Ƶ��XMHz������ֵt����ʽ1��t=TH0*256+TL0����
	����L=(t*12/(X*10^6))*340000/2  (mm)

     =0.17*t             (X=12)
	 =(2.04/11.0592)*t     (X=11.0592)
	*/
}


void Left_moto_go()     {IN4=1;IN3=0;}
void Left_moto_back()   {IN4=0;IN3=1;}
void Left_moto_stop()   {IN4=0;IN3=0;}

void Right_moto_go()    {IN1=0;IN2=1;}
void Right_moto_back()  {IN1=1;IN2=0;}
void Right_moto_stop()  {IN1=0;IN2=0;}

void car_go(void)
{
	Left_moto_go();
	Right_moto_go();
}

void car_back(void)
{
	Left_moto_back();
	Right_moto_back();
}

void car_stop(void)
{
	Left_moto_stop();
	Right_moto_stop();
}

void car_right(void)
{
	Right_moto_go();
	Left_moto_back();
}

void car_left(void)
{
	Right_moto_back();
	Left_moto_go();
}

