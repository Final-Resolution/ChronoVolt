/**
 * @file timer3.h
 * @author mangolu (mangolu81@gmail.com)
 * @brief 
 * @version 1.0.0
 * @date 2019-05-07
 * 
 * @copyright Copyright (c) 2019 mangolu All righits reserved
 * 
 */
/********************************************************************************************************************************************************************************************************/
/************************* 定时器3相关寄存器 *************************/

/************************* T3CON – 定时器3控制寄存器 *************************/
// ------------------------------------------------------------------------------
// |   7      |    6      |   5    |   4    |   3    |   2    |   1    |   0    |
// |----------|-----------|--------|--------|--------|--------------------------|
// |  SMOD_1  |  SMOD0_1  |  BRCK  |  TF3   |  TR3   |        T3PS[2:0]         |
// |----------|-----------|--------|--------|--------|----------------- --------|
// |  R/W     |   R/W     |  R/W   |  R/W   |  R/W   |           R/W            |
// ------------------------------------------------------------------------------
// 地址：C4H, 页:0    复位值：0000 0000b
// 
// -------------------------------------------------------------------------
//   Bit  |   Name    |  Description
// -------|-----------|-----------------------------------------------------
//    7   |  SMOD_1   |  串行口1波特率加倍使能
//        |           |  当串口1在模式2下，时钟溢出波特率加倍使能。
// -------|-----------|-----------------------------------------------------
//    6   |  SMOD0_1  |  串口1帧错误使能位
//        |           |  0 =关闭帧错误检测功能，作为SM0_1用
//        |           |  1 =使能帧错误检测，用作帧错误 (FE) 状态标志FE_1
// -------|-----------|-----------------------------------------------------
//    5   |   BRCK    |  串口0波特率时钟源选择
//        |           |  该位用于设置串口0 在模式1或模式3下，所使用的定时器
//        |           |  0 = 定时器 1
//        |           |  1 = 定时器 3
// -------|-----------|-----------------------------------------------------
//    4   |   TF3     |  定时器 3 溢出标志
//        |           |  当定时器3溢出，该位置位。当程序执行定时器3的中断服务程序，
//        |           |  该位由硬件自动清零。该位可以通过软件置位或清零。
// -------|-----------|-----------------------------------------------------
//    3   |   TR3     |  定时器 3 运行控制
//        |           |  0 = 定时器 3 停止
//        |           |  1 = 定时器 3 开始计数
//        |           |  注意重载寄存器R3H 和 R3L仅在定时器3停止(TR3 为 0)的时候
//        |           |  才可以被写。如果TR3 位为1写入RH3或RL3，结果是不可预知的。
// -------|-----------|-----------------------------------------------------
//   2:0  | T3PS[2:0] |  定时器 3 预分频
//        |           |  这些位决定定时器3的时钟分频。
//        |           |  000 = 1/1
//        |           |  001 = 1/2
//        |           |  010 = 1/4
//        |           |  011 = 1/8
//        |           |  100 = 1/16
//        |           |  101 = 1/32
//        |           |  110 = 1/64
//        |           |  111 = 1/128
// -------------------------------------------------------------------------

/************************* RL3 – 定时器3自动重装载寄存器低字节 *************************/
// -------------------------------------------------------------------------
// |   7    |   6    |   5    |   4    |   3    |   2    |   1    |   0    |
// |-----------------------------------------------------------------------|
// |                            RL3[7:0]                                   |
// |-----------------------------------------------------------------------|
// |                                R/W                                    |
// -------------------------------------------------------------------------
// 地址：C5H, 页:0     复位值：0000 0000b
// 
// -------------------------------------------------------------------------
//   Bit  |   Name    |  Description
// -------|-----------|-----------------------------------------------------
//   7:0  |  RL3[7:0] |  定时器 3 重载低字节
//        |           |  它保持着定时器3重载值的低字节
// -------------------------------------------------------------------------

/************************* RH3 – 定时器3自动重装载寄存器高字节 *************************/
// -------------------------------------------------------------------------
// |   7    |   6    |   5    |   4    |   3    |   2    |   1    |   0    |
// |-----------------------------------------------------------------------|
// |                            RH3[7:0]                                   |
// |-----------------------------------------------------------------------|
// |                                R/W                                    |
// -------------------------------------------------------------------------
// 地址：C6H, 页:0    复位值：0000 0000b
// 
// --------------------------------------------------------------------------
//   Bit  |   Name     |  Description
// -------|------------|-----------------------------------------------------
//   7:0  |  RH3[7:0]  |  定时器 3 重载高字节
//        |            |  它保持着定时器3重载值的高字节
// --------------------------------------------------------------------------

/********************************************************************************************************************************************************************************************************/
#ifndef _TIMER3_H_
#define _TIMER3_H_

/** 所需头文件开始>>> */

#include "N76E003.h"	/** N76E003寄存器定义头文件 */
#include "sfr_macro.h"	/** N76E003特殊功能寄存器操作宏定义头文件 */
#include "stdint.h"	/** 标准数据类型定义头文件 */
#include "common.h"	/** 通用操作设置定义头文件 */
#include "clock.h"	/** 系统时钟设置及切换函数定义头文件 */

/** 所需头文件结束<<< */

/** 需要自行定义部分开始>>> */



/** 需要自行定义部分结束<<< */



#endif	/** _TIMER3_H_ */