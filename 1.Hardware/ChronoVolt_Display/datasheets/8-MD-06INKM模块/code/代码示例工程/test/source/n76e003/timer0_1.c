/**
 * @file timer0_1.c
 * @author mangolu (mangolu81@gmail.com)
 * @brief 定时器0和1操作实现
 * @version 1.0.0
 * @date 2019-05-07
 *
 * @copyright Copyright (c) 2019 mangolu All righits reserved
 *
 */
/** 所需头文件开始>>> */

#include "N76E003.h"	/** N76E003寄存器定义头文件 */
#include "sfr_macro.h"	/** N76E003特殊功能寄存器操作宏定义头文件 */
#include "../common/stdint.h"	/** 标准数据类型定义头文件 */
#include "../common/common.h"	/** 通用操作设置定义头文件 */
#include "../user/config.h"	/** 系统配置相关定义 */
#include "clock.h"	/** 系统时钟设置及切换函数定义头文件 */
#include "timer0_1.h"	/** 定时器0和1操作定义头文件 */

/** 所需头文件结束<<< */

/** 需要自行定义部分开始>>> */



/** 需要自行定义部分结束<<< */

/**
 * @brief 定时器0和1初始化函数
 * 
 * @param TIMER0_1 timer，要初始化的定时器。
 * 为TIMER0_1_TIMER0和TIMER0_1_TIMER1两个值对应定时器0和1。 
 * @param TIMER0_1_MODE mode，要初始化成的模式。
 * 为TIMER0_1_MODE0, TIMER0_1_MODE1,TIMER0_1_MODE2和TIMER0_1_MODE3对应4种模式。
 */
void Timer0_1_Initial(TIMER0_1 timer, TIMER0_1_MODE mode) {
	switch (timer) {
		case TIMER0_1_TIMER0:	/** 初始化定时器0 */
			switch (mode) {
				case TIMER0_1_MODE0:
					/* code */
					break;

				case TIMER0_1_MODE1:
					/* code */
					break;

				case TIMER0_1_MODE2:
					/* code */
					break;

				case TIMER0_1_MODE3:
					/* code */
					break;

				default:
					break;
			}

			break;

		case TIMER0_1_TIMER1:	/** 初始化定时器1 */
			/* code */
			break;

		default:
			break;
	}
}
