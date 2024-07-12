/**
 * @file clock.c
 * @author mangolu (mangolu81@gmail.com)
 * @brief 系统时钟设置及切换函数实现
 * @version 1.0.0
 * @date 2019-04-21
 *
 * @copyright Copyright (c) 2019 mangolu All righits reserved
 *
 */
/** 所需头文件开始>>> */

#include "N76E003.h"	/** N76E003寄存器定义头文件 */
#include "sfr_macro.h"	/** N76E003特殊功能寄存器操作宏定义头文件 */
#include "../common/stdint.h"	/** 标准数据类型定义头文件 */
#include "../common/common.h"	/** 通用操作设置定义头文件 */
#include "clock.h"	/** 系统时钟设置及切换函数定义头文件 */

/** 所需头文件结束<<< */

/** 需要自行定义部分开始>>> */

/** 需要自行定义部分结束<<< */

/**
 * @brief 系统时钟选择设置函数
 * 内部16MHz RC振荡器，上电默认开启，是默认的系统时钟源
 * 内部10KHz RC振荡器，上电默认开启
 *
 * @param SYSTEM_CLOCK clock 系统时钟类型
 */
void System_Clock_Select(SYSTEM_CLOCK clock) {
	switch (clock) {
		/** 内部16MHz RC振荡器，上电默认开启，默认的系统时钟源 */
		case High_Speed_Internal_RC:
			/** 1、使能内部16MHz RC振荡器 */
			set_HIRCEN;

			/** 2、检查时钟源开启并稳定 */
			while((CKSWT & SET_BIT5) == 0);

			/** 3、切换时钟源 */
			clr_OSC1;
			clr_OSC0;
			break;

		/** 内部10KHz RC振荡器，上电默认开启 */
		case Low_Speed_Internal_RC:
			/** 1、使能内部10KHz RC振荡器 */
			// set_LIRCEN;

			/** 2、检查时钟源开启并稳定 */
			while((CKSWT & SET_BIT4) == 0);

			/** 3、切换时钟源 */
			set_OSC1;
			clr_OSC0;
			break;

		/** 外部时钟输入 */
		case External_OSC:
			/** 1、使能外部时钟源 */
			set_EXTEN1;
			set_EXTEN0;

			/** 2、检查时钟源开启并稳定 */
			while((CKSWT & SET_BIT3) == 0);

			/** 3、切换时钟源 */
			clr_OSC1;
			set_OSC0;
			break;

		default:
			break;
	}

	/** 4、等待时钟源切换成功 */
	while((CKEN & SET_BIT0) == 1);
}

/**
 * @brief 系统时钟分频
 * 系统时钟分频除了不能在中断中改变，可以在任何时刻改变。
 *
 * @param uint8_t u8Div，系统时钟分频值，为0x00~0xFF大小的数值
 * 当u8Div = 0x00时，FSYS = FOSC，即不分频。
 * 当u8Div = 0x01~0xFF时，FSYS = FOSC / (2 * u8Div)，最大为 2* 0xFF即510分频值。
 */
void System_Clock_Divid(uint8_t u8Div) {
	CKDIV = u8Div;
}

/**
 * @brief 从P1.1(Pin14)输出系统时钟
 *
 * @param uint8_t u8On_Off，从P1.1输出或关闭输出系统时钟。
 * ON(即1)为输出，OFF(即0)为不输出。
 */
void System_Clock_Output(uint8_t u8On_Off) {
	switch (u8On_Off) {
		/** 从P1.1输出系统时钟 */
		case ON:
			set_CLOEN;
			break;

		/** 不从P1.1输出系统时钟 */
		case OFF:
			clr_CLOEN;
			break;

		default:
			break;
	}
}

/**
 * @brief 修改高速内部RC振荡器频率为16.6MHz
 * 使串口通讯波特率误差率更低
 *
 */
void MODIFY_HIRC_166(void) {
	unsigned char hircmap0, hircmap1;
	unsigned int trimvalue16bit;

	/* Since only power on will  reload RCTRIM0 and RCTRIM1 value, check power on flag*/
	if ((PCON & SET_BIT4) == SET_BIT4) {
		hircmap0 = RCTRIM0;
		hircmap1 = RCTRIM1;
		trimvalue16bit = ((hircmap0 << 1) + (hircmap1 & 0x01));
		trimvalue16bit = trimvalue16bit - 15;
		hircmap1 = trimvalue16bit & 0x01;
		hircmap0 = trimvalue16bit >> 1;
		TA = 0XAA;
		TA = 0X55;
		RCTRIM0 = hircmap0;
		TA = 0XAA;
		TA = 0X55;
		RCTRIM1 = hircmap1;
		/* After modify HIRC value, clear power on flag */
		PCON &= CLR_BIT4;
	}
}