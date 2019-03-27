#ifndef __HX711_H__
#define __HX711_H__

# include "stm32f10x.h"


void HX711_GPIO_Init(void); 
unsigned long HX711_Read_DATA(void); 
double Get_shiwu_Weight(void);
double get_HX_711(void);
#endif

