#include "stm8s.h"
#include "milis.h"
#include "stm8_hd44780.h"
#include <stdio.h>
#include "delay.h"
#include "spse_stm8.h"


#define _ISOC99_SOURCE
#define _GNU_SOURCE

void ADC_init(void){

ADC2_SchmittTriggerConfig(ADC2_SCHMITTTRIG_CHANNEL3,DISABLE);
ADC2_PrescalerConfig(ADC2_PRESSEL_FCPU_D4);
ADC2_AlignConfig(ADC2_ALIGN_RIGHT);
ADC2_Select_Channel(ADC2_CHANNEL_3);
ADC2_Cmd(ENABLE);
ADC2_Startup_Wait();
}


void setup(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz
    init_milis();
    
    lcd_init();
    ADC_init();

}


int main(void)
{
    uint32_t time = 0; 
    uint16_t adc_hodnota;
    uint16_t teplota;
    char text[32];
    setup();  

    while (1) {
     if (milis()-time>1000){
        time = milis();
        
        adc_hodnota = ADC_get(ADC2_CHANNEL_3); // do adc_value ulož výsledek převodu vstupu ADC_IN2 (PB2)


        teplota = adc_hodnota * 500;
        teplota = teplota / 1024;


        lcd_gotoxy(0, 0);
        sprintf(text,"Teplota = %u C",teplota);
        lcd_puts(text);
        }
    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
