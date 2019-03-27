#include "hx711.h"
#include "delay.h"

#define HX711 GPIOB        
#define DATA GPIO_Pin_11	  
#define CLK  GPIO_Pin_10	  
#define ADCLK RCC_APB2Periph_GPIOB 
uint32_t weight_maopi = 82204;

void HX711_GPIO_Init(void) //管脚初始化
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(ADCLK, ENABLE); 
    GPIO_InitStructure.GPIO_Pin = CLK;				 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
    GPIO_Init(HX711, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = DATA; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(HX711, &GPIO_InitStructure);
}

unsigned long HX711_Read_DATA(void) //读取HX711数据 
{
    unsigned long val = 0;
    unsigned char i = 0;
    float data;
    GPIO_SetBits(HX711, DATA);
    GPIO_ResetBits(HX711, CLK); 
    while(GPIO_ReadInputDataBit(HX711, DATA)); 
    delay_us(1);
    for(i = 0; i < 24; i++)     //25脉冲128增益
    {
        GPIO_SetBits(HX711, CLK); 
        val = val << 1; 
        delay_us(1);
        GPIO_ResetBits(HX711, CLK); 
        if(GPIO_ReadInputDataBit(HX711, DATA))
            val++;
        delay_us(1);
    }
    GPIO_SetBits(HX711, CLK);
    val = val ^ 0x800000; 
    delay_us(1);
    GPIO_ResetBits(HX711, CLK);
    delay_us(1);
    data = val;
    return data;
}

double get_HX_711(void)
{
    return HX711_Read_DATA() / 100;//得到整形数据
}

double  sum = 0;
double Get_shiwu_Weight(void)
{
    sum = get_HX_711() - weight_maopi;//去除皮毛
    return sum / 4.14; //4.14校准值，根据传感器自行校准
}
