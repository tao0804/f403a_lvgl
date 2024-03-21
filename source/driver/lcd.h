/********************金逸晨**************************
*****************GMT130 模块 1.3寸   7PIN SPI TFT FOR STM32F103*************
***************************240*240   16/18BIT真彩***********************
*****STM32F103驱动**************************
***** PB5----3  SCK   ,  PB6----4  SDA   ,    PB7---5  RST   ,
      PB8    ---6   DC   ,  PB6----7  BLK
***** BY:GU 
*********ST7789 控制器,本模块第七针BLK为0时，背光关闭，可以不接
由于本模块CS直接接地，默认片选，在所有操作中不应该随意操作SCK 以避免引起错误命令
为顺利完成初始化，在RESET 之前应先将SCK操作为1，以便顺利识别时序中的START，随后每次SCK=1,将完成一位数据发送！！

默认数据格式位RGB565
********************************************************/

#ifndef __LCD_H
#define __LCD_H

#include "at32f403a_407_gpio.h"



#define     RED          0XF800	  //红
#define     GREEN        0X07E0	  //绿
#define     BLUE         0X001F	  //蓝
#define     WHITE        0XFFFF	  //白

#define TFT_COLUMN_NUMBER 240
#define TFT_LINE_NUMBER 240		// tao:列与行的分辨率(pixel)
#define TFT_COLUMN_OFFSET 0		// tao:液晶显示器的列偏移量(pixel)

#define PIC_NUM 28800			// tao:图片数据大小(byte)

extern const unsigned char  picture_tab[PIC_NUM];

// #define SPI_BLK_0   GPIOB->BRR=0X0200    // 设置/WR 或CS接口到PB9
// #define SPI_BLK_1   GPIOB->BSRR=0X0200


/**********SPI引脚分配，连接TFT屏，更具实际情况修改*********/

// tao:可以用odt,也可以用scr
#define SPI_SCK_0  GPIOB->odt &= ~GPIO_PINS_13       // 设置sck接口到PB13   清零
#define SPI_SCK_1  GPIOB->odt |= GPIO_PINS_13       //置位
#define SPI_SDA_0  GPIOB-> odt &= ~GPIO_PINS_15     // 设置SDA接口到PB15
#define SPI_SDA_1  GPIOB-> odt |= GPIO_PINS_15
#define SPI_RST_0  GPIOB-> odt &= ~GPIO_PINS_12      // 设置RST接口到PB12
#define SPI_RST_1  GPIOB-> odt |= GPIO_PINS_12
#define SPI_DC_0   GPIOA-> odt &= ~GPIO_PINS_9		// 设置DC接口到PA9
#define SPI_DC_1   GPIOA-> odt |= GPIO_PINS_9 
#define SPI_CS_0   GPIOA-> odt &= ~GPIO_PINS_8			// 设置/WR 或CS接口到PA8
#define SPI_CS_1   GPIOA-> odt |= GPIO_PINS_8



void TFT_clear(void);
void TFT_full(unsigned int color);
void TFT_init(void);
void display_char16_16(unsigned int x,unsigned int y,unsigned long color,unsigned char word_serial_number);
void Picture_Display(const unsigned char *ptr_pic);

#endif

