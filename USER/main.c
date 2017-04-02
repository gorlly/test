#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"


//LED1-4: PE7,8,9,10

void servoStayCenter(void)
{
        SERVO_CTRL = 0;
        delay_us(5000);   //1ms = 1000us
        SERVO_CTRL = 1;
        delay_us(1500);
        SERVO_CTRL = 0;
        delay_us(13500);
}
void servoTurnLeft(void)
{
        SERVO_CTRL = 0;
        delay_us(5000);   //1ms = 1000us
        SERVO_CTRL = 1;
        delay_us(1000);
        SERVO_CTRL = 0;
        delay_us(14000);
}
void servoTurnRight(void)
{
        SERVO_CTRL = 0;
        delay_us(5000);   //1ms = 1000us
        SERVO_CTRL = 1;
        delay_us(2000);
        SERVO_CTRL = 0;
        delay_us(13000);
}

void Timer3_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
    GPIO_InitTypeDef  GPIO_InitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;


    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

   	    //remap  TIM3_CH2->PB5
//    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);


   //-------------------GPIO-A7 Configure-----------------------------------------------	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz    
    GPIO_Init(GPIOA, &GPIO_InitStructure);					




//    void TIM_TimeBaseInit(TIM_TypeDef *TIMx, 
//    TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
    
    //timer parameters setting;


    TIM_TimeBaseStructure.TIM_Period = arr;
    TIM_TimeBaseStructure.TIM_Prescaler=psc;
//  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);


    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ�� PWM ģʽ 2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //������Ը�
    TIM_OC2Init(TIM3, &TIM_OCInitStructure); //��ʼ�� TIM3 OC2


        //set update-interruption mode
//    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
//
//    NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
//    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//    NVIC_Init(&NVIC_InitStructure);

      TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);//ʹ��Ԥװ�ؼĴ���
      TIM_Cmd(TIM3, ENABLE);

//    TIM_Cmd(TIM3, DISABLE);
    
}

void TIM5_Cap_Init(u16 arr, u16 psc)
{

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM5_ICInitStructure;
    

    //�ڳ�ʼ�� TIM5 ����
    TIM_TimeBaseStructure.TIM_Period = arr;  //�趨�������Զ���װֵ
    TIM_TimeBaseStructure.TIM_Prescaler =psc;  //Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM ���ϼ���ģʽ
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //��ʼ�� TIMx
    //�۳�ʼ�� TIM5 ���벶��ͨ�� 1
    TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //ѡ������� IC1 ӳ�䵽 TI1 ��
    TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;  //�����ز���
    TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽 TI1 ��
    TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;  //���������Ƶ,����Ƶ
    TIM5_ICInitStructure.TIM_ICFilter = 0x00; //IC1F=0000 ���������˲��� ���˲�
    TIM_ICInit(TIM5, &TIM5_ICInitStructure); //��ʼ�� TIM5 ���벶��ͨ�� 1
    //�ݳ�ʼ�� NVIC �ж����ȼ�����
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM5 �ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ� 2 ��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ� 0 ��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //IRQ ͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);   //��ʼ�� NVIC
    TIM_ITConfig( TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//����������жϲ����ж�
    TIM_Cmd(TIM5,ENABLE );  //��ʹ�ܶ�ʱ�� 5
}

u8 TIM5CH1_CAPTURE_STA=0; //���벶��״̬���Զ���Ĵ�����bit-7,Ϊ��־���λ
                         //bit6 Ϊ����ߵ�ƽ��־�� bit5-0:�������
                           
u16 TIM5CH1_CAPTURE_VAL;//���벶��ֵ

void TIM5_IRQHandler(void)     //�ݶ�ʱ�� 5 �жϷ������
{
    if((TIM5CH1_CAPTURE_STA&(1<<7))==0)//��δ�ɹ�����
    { 
        if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//�ж��Ƿ�Ϊ�����ж�
        {
            if(TIM5CH1_CAPTURE_STA&(1<<6)) //�Ѿ����񵽸ߵ�ƽ��
            {
                if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ����
                {            //bit5-0: ȫΪ1���������
                    TIM5CH1_CAPTURE_STA|=(1<<7); //ǿ�Ʊ�ǳɹ�����
                    TIM5CH1_CAPTURE_VAL=0XFFFF;
                }                  
                else 
                    TIM5CH1_CAPTURE_STA++;  // �������+1
             }
        }
        if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET) //���� 1 ���������¼�
        {
            if(TIM5CH1_CAPTURE_STA&0X40)  //����һ���½���
            { 
                TIM5CH1_CAPTURE_STA|=0X80;  //��ǳɹ�����һ��������
                TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
                TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //����Ϊ�����ز���
             }
             else  //��δ��ʼ,��һ�β���������
             {
                TIM5CH1_CAPTURE_STA=0;  //���
                TIM5CH1_CAPTURE_VAL=0;
                TIM_SetCounter(TIM5,0);
                TIM5CH1_CAPTURE_STA|=0X40;  //��ǲ�����������
                TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling); //����Ϊ�½��ز���
             } 
         }   
     }
     TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
}

int main(void)
{	
    u8 len;
    u8 i;
    u16 led0pwmval=0;
    u8 dir = 1;
//    long int distance;
//    u32 temp = 0;

	delay_init();	    //��ʱ������ʼ��
    NVIC_Configuration();	  
	
    LED_Init();	
    Motor_Init();
    Ultrasonic_Init();
    uart_init(9600);

    Timer3_Init(899, 0);  //����Ƶ��PWMƵ��Ϊ72000/900=8KHz
    //(0+1)*(71+1)/72=1us
    //(4999+1)*(7199+1)/72 = 500ms;
    


 //   TIM5_Cap_Init(0xffff, 72-1);   //1MHz

	while(1){          // �����Իس�����β��0x0d, 0x0a;
        if(USART_RX_STA&0x8000){
            len=  USART_RX_STA & 0x3f;
            for(i=0; i<len; i++){
                USART_SendData(USART1, USART_RX_BUF[i]);
                while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);
            }
            USART_RX_STA=0;
        }

        // count_len();

//        distance = count_len();
//        printf("the distance is: %ld\r\n", distance);


//        if(TIM5CH1_CAPTURE_STA & 0x80){
//            temp = TIM5CH1_CAPTURE_STA & 0x3f;
//            temp *= 65536;
//            temp += TIM5CH1_CAPTURE_VAL;
//            printf("High level: %d us \r\n",temp);
//            TIM5CH1_CAPTURE_STA = 0;
//
//        }
//        delay_ms(500);

            delay_ms(500);
            LED1 = !LED1;

//            if(dir)
//                led0pwmval++;
//            else
//                led0pwmval--;
//
//            if(led0pwmval>300)
//                dir = 0;
//            if(led0pwmval == 0)
//                dir = 1;
//            TIM_SetCompare2(TIM3, led0pwmval);
	}
 }



