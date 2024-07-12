/**
 * @file initial.c
 * @author mangolu (mangolu81@gmail.com)
 * @brief N76E003系统初始化函数定义
 * @version 1.0.0
 * @date 2019-04-19
 *
 * @copyright Copyright (c) 2018 mangolu All rights reserved
 *
 */

/** 所需头文件开始>>> */

#include "Initial.h"
#include "../common/common.h"
#include "config.h"

#include "../n76e003/gpio.h"
#include "../n76e003/clock.h"

#include "../devices/vfd_8md06inkm.h"

/** 所需头文件结束<<< */

/**
 * @brief 初始化系统
 * 包括初始化MCU和外部设备。
 *
 */
void Initial_System(void) {
	/** 初始化MCU */
	Initial_MCU();
	/** 初始化外部设备 */
	Initial_Devices();
}

/**
 * @brief 初始化MCU
 * 用于初始化MCU系统内部寄存器定时计数器串口等的操作。
 *
 */
void Initial_MCU(void) {
	/** 设置系统频率 */
	System_Clock_Select(High_Speed_Internal_RC);
	// System_Clock_Divid(24);	/**系统分频 */
	System_Clock_Output(ON);	/** P11输出FOSC */
	SET_P11_PushPull_Mode;  /** 设置P1^0为推挽输出模式 *//** P11输出FOSC */


}

/**
 * @brief 初始化外部设备
 * 用于初始化外部设备，如按键、LCM等。
 *
 */
void Initial_Devices(void) {

	/** 8MD06INKM接口初始化 */
	VFD_8MD06INKM_Port_Init();
	/** 初始化8MD06INKM_Init */
	VFD_8MD06INKM_Init();

}
