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
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz    
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


    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择 PWM 模式 2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性高
    TIM_OC2Init(TIM3, &TIM_OCInitStructure); //初始化 TIM3 OC2


        //set update-interruption mode
//    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
//
//    NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
//    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//    NVIC_Init(&NVIC_InitStructure);

      TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);//使能预装载寄存器
      TIM_Cmd(TIM3, ENABLE);

//    TIM_Cmd(TIM3, DISABLE);
    
}

void TIM5_Cap_Init(u16 arr, u16 psc)
{

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM5_ICInitStructure;
    

    //②初始化 TIM5 参数
    TIM_TimeBaseStructure.TIM_Period = arr;  //设定计数器自动重装值
    TIM_TimeBaseStructure.TIM_Prescaler =psc;  //预分频器
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM 向上计数模式
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //初始化 TIMx
    //③初始化 TIM5 输入捕获通道 1
    TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //选择输入端 IC1 映射到 TI1 上
    TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;  //上升沿捕获
    TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到 TI1 上
    TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;  //配置输入分频,不分频
    TIM5_ICInitStructure.TIM_ICFilter = 0x00; //IC1F=0000 配置输入滤波器 不滤波
    TIM_ICInit(TIM5, &TIM5_ICInitStructure); //初始化 TIM5 输入捕获通道 1
    //⑤初始化 NVIC 中断优先级分组
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM5 中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //先占优先级 2 级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级 0 级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //IRQ 通道被使能
    NVIC_Init(&NVIC_InitStructure);   //初始化 NVIC
    TIM_ITConfig( TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//④允许更新中断捕获中断
    TIM_Cmd(TIM5,ENABLE );  //⑥使能定时器 5
}

u8 TIM5CH1_CAPTURE_STA=0; //输入捕获状态，自定义寄存器：bit-7,为标志完成位
                         //bit6 为捕获高电平标志， bit5-0:溢出次数
                           
u16 TIM5CH1_CAPTURE_VAL;//输入捕获值

void TIM5_IRQHandler(void)     //⑤定时器 5 中断服务程序
{
    if((TIM5CH1_CAPTURE_STA&(1<<7))==0)//还未成功捕获
    { 
        if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//判断是否为更新中断
        {
            if(TIM5CH1_CAPTURE_STA&(1<<6)) //已经捕获到高电平了
            {
                if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平过长
                {            //bit5-0: 全为1；溢出过多
                    TIM5CH1_CAPTURE_STA|=(1<<7); //强制标记成功捕获
                    TIM5CH1_CAPTURE_VAL=0XFFFF;
                }                  
                else 
                    TIM5CH1_CAPTURE_STA++;  // 溢出次数+1
             }
        }
        if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET) //捕获 1 发生捕获事件
        {
            if(TIM5CH1_CAPTURE_STA&0X40)  //捕获到一个下降沿
            { 
                TIM5CH1_CAPTURE_STA|=0X80;  //标记成功捕获到一次上升沿
                TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
                TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //设置为上升沿捕获
             }
             else  //还未开始,第一次捕获上升沿
             {
                TIM5CH1_CAPTURE_STA=0;  //清空
                TIM5CH1_CAPTURE_VAL=0;
                TIM_SetCounter(TIM5,0);
                TIM5CH1_CAPTURE_STA|=0X40;  //标记捕获到了上升沿
                TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling); //设置为下降沿捕获
             } 
         }   
     }
     TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
}

int main(void)
{	
    u8 len;
    u8 i;
    u16 led0pwmval=0;
    u8 dir = 1;
//    long int distance;
//    u32 temp = 0;

	delay_init();	    //延时函数初始化
    NVIC_Configuration();	  
	
    LED_Init();	
    Motor_Init();
    Ultrasonic_Init();
    uart_init(9600);

    Timer3_Init(899, 0);  //不分频，PWM频率为72000/900=8KHz
    //(0+1)*(71+1)/72=1us
    //(4999+1)*(7199+1)/72 = 500ms;
    


 //   TIM5_Cap_Init(0xffff, 72-1);   //1MHz

	while(1){          // 数据以回车符结尾：0x0d, 0x0a;
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



