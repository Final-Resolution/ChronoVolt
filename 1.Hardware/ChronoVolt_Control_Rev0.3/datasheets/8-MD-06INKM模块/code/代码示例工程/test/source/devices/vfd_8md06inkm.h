/**
 * @file vfd_8md06inkm.h
 * @author mangolu (mangolu81@gmail.com)
 * @brief VFD 8MD06INKM驱动定义
 * @version 1.0.0
 * @date 2019-10-27
 * 
 * @copyright Copyright (c) 2019 mangolu All righits reserved
 * 
 */
#ifndef _VFD_8MD06INKM_H_
#define _VFD_8MD06INKM_H_

/* 所需头文件 */
#include "../common/stdint.h"
#include "../n76e003/sfr_macro.h"

/* 引脚定义，根据实际连接设置 */
/* 高压开关操作 */
#define HV_ON() set_P10
#define HV_OFF() clr_P10
/* DA操作 */
#define PT6312_DA_H() set_P00
#define PT6312_DA_L() clr_P00
/* CP操作 */
#define PT6312_CP_H() set_P01
#define PT6312_CP_L() clr_P01
/* #CS操作 */
#define PT6312_CS_H() set_P03
#define PT6312_CS_L() clr_P03
/* #RST操作 */
#define PT6312_RST_H() set_P04
#define PT6312_RST_L() clr_P04

/**
 * @brief 初始化与8MD06INKM连接的端口
 * 
 */
void VFD_8MD06INKM_Port_Init(void);

/**
 * @brief 向8MD06INKM发送数据
 * 
 * @param u8Data 所要发送的数据
 */
void VFD_8MD06INKM_Send(uint8_t u8Data);

/**
 * @brief 8MD06INKM初始化
 * 
 */
void VFD_8MD06INKM_Init(void);

/**
 * @brief 在8MD06INKM指定位置显示一个字符
 * 
 * @param u8Position 位置，为0~8。
 * @param u8Char 要显示的字符，为ASCII编码。
 */
void VFD_8MD06INKM_Display_Char(uint8_t u8Position, uint8_t u8Char);

/**
 * @brief 从指定位置开始显示字符串
 * 
 * @param u8Position 指定开始显示的位置，为0~7。
 * @param Str 要显示的字符串指针。
 */
void VFD_8MD06INKM_Display_String(uint8_t u8Position, uint8_t *Str);


#endif	/** _VFD_8MD06INKM_H_ */
