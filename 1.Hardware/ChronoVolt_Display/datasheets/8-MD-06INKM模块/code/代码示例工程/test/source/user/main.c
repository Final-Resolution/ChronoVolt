/**
 * @file main.c
 * @author mangolu (mangolu81@gmail.com)
 * @brief N76E003系统入口函数
 * @version 1.0.0
 * @date 2019-04-19
 *
 * @copyright Copyright (c) 2019 mangolu All righits reserved
 *
 */

/** 所需头文件开始>>> */

#include "../n76e003/N76E003.h"
#include "../common/common.h"
#include "../user/config.h"
#include "../user/initial.h"
#include "../n76e003/gpio.h"
#include "../n76e003/clock.h"
// #include "uart.h"

#include "intrins.h"

#include "../devices/vfd_8md06inkm.h"

/** 所需头文件结束<<< */

/** 需要自行定义部分开始>>> */



uint8_t test[] = "VFD-TEST";
uint8_t time[] = "12:30:30";
uint8_t sec,min,hour;

void Delay1000ms();
/** 需要自行定义部分结束<<< */

void main(void) {

	Initial_System();	/** 初始化系统 */

	// VFD_8MD06INKM_Display_Char(0,'0');
	// VFD_8MD06INKM_Display_Char(1,'1');
	// VFD_8MD06INKM_Display_Char(2,'2');
	// VFD_8MD06INKM_Display_Char(3,'3');
	// VFD_8MD06INKM_Display_Char(4,'4');
	// VFD_8MD06INKM_Display_Char(5,'5');
	// VFD_8MD06INKM_Display_Char(6,'6');
	// VFD_8MD06INKM_Display_Char(7,'7');

	// VFD_8MD06INKM_Display_Char(0,'A');
	// VFD_8MD06INKM_Display_Char(1,'B');
	// VFD_8MD06INKM_Display_Char(2,'C');
	// VFD_8MD06INKM_Display_Char(3,'D');
	// VFD_8MD06INKM_Display_Char(4,'E');
	// VFD_8MD06INKM_Display_Char(5,'F');
	// VFD_8MD06INKM_Display_Char(6,'G');
	// VFD_8MD06INKM_Display_Char(7,'H');

	// VFD_8MD06INKM_Display_String(0,test);
	// VFD_8MD06INKM_Display_String(0,time);
	PT6312_CS_L();
	VFD_8MD06INKM_Send(0xE9);	/** 全亮 */
	PT6312_CS_H();
	Delay1000ms();
	Delay1000ms();
	PT6312_CS_L();
	VFD_8MD06INKM_Send(0xEA);	/** 全灭 */
	PT6312_CS_H();
	Delay1000ms();
	PT6312_CS_L();
	VFD_8MD06INKM_Send(0xE9);	/** 全亮 */
	PT6312_CS_H();
	Delay1000ms();
	Delay1000ms();
	PT6312_CS_L();
	VFD_8MD06INKM_Send(0xEA);	/** 全灭 */
	PT6312_CS_H();
	Delay1000ms();
	PT6312_CS_L();
	VFD_8MD06INKM_Send(0xE9);	/** 全亮 */
	PT6312_CS_H();
	Delay1000ms();
	Delay1000ms();
	PT6312_CS_L();
	VFD_8MD06INKM_Send(0xEA);	/** 全灭 */
	PT6312_CS_H();
	Delay1000ms();
	PT6312_CS_L();
	VFD_8MD06INKM_Send(0xE8);	/** 正常操作 */
	PT6312_CS_H();
	Delay1000ms();
	VFD_8MD06INKM_Display_String(0,test);
	Delay1000ms();
	Delay1000ms();
	Delay1000ms();
	VFD_8MD06INKM_Display_String(0,time);
	Delay1000ms();
	Delay1000ms();
	Delay1000ms();

	while(1) {
		time[0] = hour / 10 + 0x30;
		time[1] = hour % 10 + 0x30;
		time[3] = min / 10 + 0x30;
		time[4] = min % 10 + 0x30;
		time[6] = sec / 10 + 0x30;
		time[7] = sec % 10 + 0x30;
		VFD_8MD06INKM_Display_String(0,time);
		Delay1000ms();
		sec += 1;
		if(sec == 60) {
			sec = 0;
			min += 1;
			if(min == 60) {
				min = 0;
				hour += 1;
				if(hour == 24) {
					hour = 0;
				}
			}
		}

		

	}
}


void Delay1000ms()		//@16MHz
{
	unsigned char i, j, k;

	i = 61;
	j = 204;
	k = 243;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
