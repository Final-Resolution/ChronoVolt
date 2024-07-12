/**
 * @file initial.h
 * @author mangolu (mangolu81@gmail.com)
 * @brief N76E003系统初始化函数声明
 * @version 1.0.0
 * @date 2019-04-19
 *
 * @copyright Copyright (c) 2018 mangolu All rights reserved
 *
 */
#ifndef _INITIAL_H_
#define _INITIAL_H_

/**
 * @brief 初始化系统
 * 包括初始化MCU和外部设备。
 *
 */
void Initial_System(void);

/**
 * @brief 初始化MCU
 * 用于初始化MCU系统内部寄存器定时计数器串口等的操作。
 *
 */
void Initial_MCU(void);

/**
 * @brief 初始化外部设备
 * 用于初始化外部设备，如按键、LCM等。
 *
 */
void Initial_Devices(void);

#endif	/** _INITIAL_H_ */
