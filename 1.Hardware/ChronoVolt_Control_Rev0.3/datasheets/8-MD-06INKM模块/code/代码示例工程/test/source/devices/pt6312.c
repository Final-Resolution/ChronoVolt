/**
 * @file pt6312.c
 * @author mangolu (mangolu81@gmail.com)
 * @brief PT6312操作相关实现
 * @version 1.0.0
 * @date 2019-08-05
 * 
 * @copyright Copyright (c) 2019 mangolu All righits reserved
 * 
 */
#include "pt6312.h"
#include "../devices/font_seg13.h"

/**
 * @brief 向PT6312发送数据，内部函数
 * 
 * @param ucData 要发送的数据
 */
void PT6312_Send(unsigned char ucData) {
	unsigned char ucI;

	for(ucI = 0; ucI < 8; ucI ++) {
		PT6312_CLK_L();

		if(ucData & 0x01) {
			PT6312_DIN_H();
		} else {
			PT6312_DIN_L();
		}

		ucData >>= 1;
		PT6312_CLK_H();
	}
}

/**
 * @brief 向PT6312发送锁存信号，内部函数
 * 
 */
void PT6312_Send_STB(void) {
	PT6312_STB_H();
	PT6312_STB_L();
}

/**
 * @brief PT6312初始化
 * 
 */
void PT6312_Initial(void) {
	unsigned char ucI;

	PT6312_Send_STB();

	/* 发送命令2，写数据 */
	PT6312_Send(CMD2_CMD | WR_TO_DISPLAY_MODE_CMD);
	PT6312_Send_STB();

	/* 发送命令3，清空内存数据 */
	PT6312_Send(CMD3_CMD);

	for(ucI = 0; ucI < 8; ucI ++) { /* 清空内存数据 */
		PT6312_Send(0x00);
		PT6312_Send(0x00);
	}

	PT6312_Send_STB();

	/* 发送命令1，设置显示模式 */
	PT6312_Send(CMD1_CMD | PT6312_MODE);
	PT6312_Send_STB();

	/* 设置命令4，开启显示 */
	PT6312_Send(CMD4_CMD | DISPLAY_ON | PT6312_LIGHT);
	PT6312_Send_STB();

}

/**
 * @brief 显示PT6312当前设置模式的所有码段
 * 
 */
void PT6312_Display_All(void) {
	unsigned char ucI;

	/* 发送命令2，写数据 */
	PT6312_Send(CMD2_CMD | WR_TO_DISPLAY_MODE_CMD);
	PT6312_Send_STB();

	/* 发送命令3，写内存数据 */
	PT6312_Send(CMD3_CMD);

	for(ucI = 0; ucI < 8; ucI ++) {
		PT6312_Send(0xFF);
		PT6312_Send(0xFF);
	}

	PT6312_Send_STB();
}

/**
 * @brief 刷新PT6312显示缓存
 * 
 * @param *uiBuffer 要刷新进PT6312缓存的数据源
 * PT6312内部总共有8个16字节的缓存，要根据实际情况选择相应的刷新位数
 */
void PT6312_Update(unsigned int *uiBuffer) {
	unsigned char ucI;

	/* 发送命令2，写数据 */
	PT6312_Send(CMD2_CMD | WR_TO_DISPLAY_MODE_CMD);
	PT6312_Send_STB();

	/* 发送命令3，写内存数据 */
	PT6312_Send(CMD3_CMD);

	for(ucI = 0; ucI < 7; ucI ++) {
		PT6312_Send((unsigned char)((*(uiBuffer + ucI) >> 8) & 0x00FF));
		PT6312_Send((unsigned char)(*(uiBuffer + ucI) & 0x00FF));
	}

	PT6312_Send_STB();
}

/**
 * @brief 左边第一个时钟点操作
 * 这个操作是通过对单片机缓存数据操作实现的
 * 
 * @param *ucBuffer 缓冲
 * @param ucONOFF 开关，当为1时点亮，为0时灭
 */
void VFD_DOT1_ONOFF(unsigned int *ucBuffer,unsigned char ucONOFF) {

	if(ucONOFF == 1) {
		*(ucBuffer + 2) |= SEG13_DP;
	} else {
		*(ucBuffer + 2) &= ~SEG13_DP;
	}
}

/**
 * @brief 左边第二个时钟点操作
 * 这个操作是通过对单片机缓存数据操作实现的
 * 
 * @param *ucBuffer 缓冲
 * @param ucONOFF 开关，当为1时点亮，为0时灭
 */
void VFD_DOT2_ONOFF(unsigned int *ucBuffer,unsigned char ucONOFF) {

	if(ucONOFF == 1) {
		*(ucBuffer + 4) |= SEG13_DP;
	} else {
		*(ucBuffer + 4) &= ~SEG13_DP;
	}
}
