/**
 * @file pt6312.h
 * @author mangolu (mangolu81@gmail.com)
 * @brief PT6312操作相关定义
 * @version 1.0.0
 * @date 2019-08-05
 * 
 * @copyright Copyright (c) 2019 mangolu All righits reserved
 * 
 */
#ifndef _PT6312_H_
#define _PT6312_H_

#include "../n76e003/sfr_macro.h"

/* COMMAND 1: DISPLAY MODE SETTING COMMANDS，显示模式设置 */
#define CMD1_CMD 0x00
#define DISPLAY_4GRID_16SEGMENT_MODE 0x00
#define DISPLAY_5GRID_16SEGMENT_MODE 0x01
#define DISPLAY_6GRID_16SEGMENT_MODE 0x02
#define DISPLAY_7GRID_15SEGMENT_MODE 0x03
#define DISPLAY_8GRID_14SEGMENT_MODE 0x04
#define DISPLAY_9GRID_13SEGMENT_MODE 0x05
#define DISPLAY_10GRID_12SEGMENT_MODE 0x06
#define DISPLAY_11GRID_11SEGMENT_MODE 0x07

/* COMMAND 2: DATA SETTING COMMANDS，设置数据从PT6312读或写 */
#define CMD2_CMD 0x40
#define WR_TO_DISPLAY_MODE_CMD 0x00
#define WR_TO_LED_PORT_CMD 0x01
#define RD_KEY_DATA_CMD 0x02
#define RD_SW_DATA_CMD 0x03
#define FIXED_ADDRESS_CMD 0x04  

/* COMMAND 3: ADDRESS SETTING COMMANDS，显示内存地址设置 */
#define CMD3_CMD 0xC0

/* COMMAND 4: DISPLAY CONTROL COMMANDS，显示控制命令 */
#define CMD4_CMD 0x80
#define DISPLAY_ON 0x08
#define DISPLAY_OFF 0x00
#define MIN_BRIGHTNESS 0x00
#define V2_16_BRIGHTNESS 0x01
#define V4_16_BRIGHTNESS 0x02
#define V10_16_BRIGHTNESS 0x03
#define V11_16_BRIGHTNESS 0x04
#define V12_16_BRIGHTNESS 0x05
#define V13_16_BRIGHTNESS 0x06
#define MAX_BRIGHTNESS 0x07

/* 高压操作 */
#define set_HV_ON() set_P10
#define clr_HV_ON() clr_P10
/* PT6312 CLK操作 */
#define PT6312_CLK_H() set_P03
#define PT6312_CLK_L() clr_P03
/* PT6312 DIN操作 */
#define PT6312_DIN_H() set_P01
#define PT6312_DIN_L() clr_P01
/* PT6312 STB操作 */
#define PT6312_STB_H() set_P04
#define PT6312_STB_L() clr_P04

/**
 * @brief PT6312初始化
 * 
 */
void PT6312_Initial(void);

/**
 * @brief 显示PT6312当前设置模式的所有码段
 * 
 */
void PT6312_Display_All(void);

/**
 * @brief 刷新PT6312显示缓存
 * 
 * @param *uiBuffer 要刷新进PT6312缓存的数据源
 * PT6312内部总共有8个16字节的缓存，要根据实际情况选择相应的刷新位数
 */
void PT6312_Update(unsigned int *uiBuffer);

/**
 * @brief 左边第一个时钟点操作
 * 这个操作是通过对单片机缓存数据操作实现的
 * 
 * @param *ucBuffer 缓冲
 * @param ucONOFF 开关，当为1时点亮，为0时灭
 */
void VFD_DOT1_ONOFF(unsigned int *ucBuffer,unsigned char ucONOFF);

/**
 * @brief 左边第二个时钟点操作
 * 这个操作是通过对单片机缓存数据操作实现的
 * 
 * @param *ucBuffer 缓冲
 * @param ucONOFF 开关，当为1时点亮，为0时灭
 */
void VFD_DOT2_ONOFF(unsigned int *ucBuffer,unsigned char ucONOFF);


/* 以下根据实际情况进行修改 >>> */

/* PT6312与单片机引脚连接设置 */
// sbit PT6312_DOUT = P1^0;
// sbit PT6312_DIN  = P1^1;
// sbit PT6312_CLK  = P1^2;
// sbit PT6312_STB  = P1^3;

#define PT6312_MODE  DISPLAY_7GRID_15SEGMENT_MODE  /* 设置显示模式 */ 
// #define PT6312_MODE  DISPLAY_4GRID_16SEGMENT_MODE  /* 设置显示模式 */

/* 设置VFD亮度，这里是设置PT6312扫描占空比，与电压无关 */ 
/* 单选 */
// #define PT6312_LIGHT	MIN_BRIGHTNESS
// #define PT6312_LIGHT	V2_16_BRIGHTNESS
// #define PT6312_LIGHT	V4_16_BRIGHTNESS
// #define PT6312_LIGHT	V10_16_BRIGHTNESS
// #define PT6312_LIGHT	V11_16_BRIGHTNESS
#define PT6312_LIGHT	V12_16_BRIGHTNESS
// #define PT6312_LIGHT	V13_16_BRIGHTNESS
// #define PT6312_LIGHT	MAX_BRIGHTNESS

#endif	/** _PT6312_H_ */