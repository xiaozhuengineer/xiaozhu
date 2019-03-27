# include "stm32f10x.h"
# include "sys.h"
# include "delay.h"
# include "usart.h"
#include  "hx711.h"
#include  "lcd.h"

double  cm = 0;
extern uint32_t weight_maopi;

void data_dispose(void)
{
	 char aa[10];
	 LCD_ShowString(120,150,210,24,24,"      ");//   
   sprintf(aa,"%4.1f",cm);
	 LCD_ShowString(120,150,210,24,24,aa);  
}

int main(void)
{
   
    uart_init(115200);
    delay_init();
    HX711_GPIO_Init(); 
	  LCD_Init();
	  POINT_COLOR=BLACK;
	  weight_maopi = get_HX_711();
	  delay_ms(3000);
	  weight_maopi = get_HX_711();
	  LCD_Clear(WHITE);	
	  LCD_ShowChinese(0,100 ,1,32);//
	  LCD_ShowChinese(32,100 ,2,32);
	  LCD_ShowChinese(64,100 ,3,32);
	  LCD_ShowChinese(96,100 ,4,32);
	  LCD_ShowChinese(128,100 ,5,32);
	  LCD_ShowString(160,100,210,24,24,":");   //显示字符串
	  LCD_ShowChinese(200,150 ,6,32);
    while(1)
    {
        cm = Get_shiwu_Weight();
        delay_ms(100);
        printf("%.1fg\t", cm);	//输出实物重量并保留两位小数	
        data_dispose();		
    }


}
