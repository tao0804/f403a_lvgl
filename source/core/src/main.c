/**
  **************************************************************************
  * @file     main.c
  * @brief    main program
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

#include "lcd.h"
#include "at32f403a_407_clock.h"
#include "at32f403a_407_board.h"

/** @addtogroup AT32F403A_periph_examples
  * @{
  */

/** @addtogroup 403A_GPIO_io_toggle GPIO_io_toggle
  * @{
  */

/**
  * @brief  pa.01 gpio configuration.
  * @param  none
  * @retval none
  */

const unsigned char  *point;

void gpio_config(void)
{
	gpio_init_type gpio_init_struct_a, gpio_init_struct_b;	
	/* enable the gpioa clock */
	crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);	
	/* set default parameter */
	gpio_default_para_init(&gpio_init_struct_a);	
	/* configure the gpio */
	gpio_init_struct_a.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct_a.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct_a.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct_a.gpio_pins = GPIO_PINS_9 | GPIO_PINS_8;
	gpio_init_struct_a.gpio_pull = GPIO_PULL_NONE;
	gpio_init(GPIOA, &gpio_init_struct_a);
	
	crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
	gpio_default_para_init(&gpio_init_struct_b);

	gpio_init_struct_b.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct_b.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct_b.gpio_mode = GPIO_MODE_OUTPUT;
	gpio_init_struct_b.gpio_pins = GPIO_PINS_12 | GPIO_PINS_13 | GPIO_PINS_15;
	gpio_init_struct_b.gpio_pull = GPIO_PULL_NONE;
	gpio_init(GPIOB, &gpio_init_struct_b);
}

/**
  * @brief  main function.
  * @param  none
  * @retval none
  */
 // tao:超过10s的情况建议使用DWT秒延时函数
int main(void)
{ 
	point= &picture_tab[0];

	system_clock_config();

	gpio_config();
	// SPI_BLK_1;
	SPI_CS_0;	// tao:low enable
	SPI_SCK_0;
	TFT_init();
	while(1)
	{
		
	TFT_full(RED);
	delay_ms(10000);
	TFT_full(GREEN);
	delay_ms(2000);
	TFT_full(BLUE);
	delay_ms(2000);
	TFT_clear();
	Picture_Display(point);
	delay_ms(5000);
    display_char16_16(20,160,BLUE,0);
	display_char16_16(36,160,GREEN,1);
	display_char16_16(60,160,RED,2);
	display_char16_16(76,160,BLUE,3);
	display_char16_16(92,160,GREEN,4);
	display_char16_16(118,160,BLUE,5);
	display_char16_16(134,160,RED,6);
	delay_ms(10000);

	}
}
