/**
 * @file vfd_8md06inkm.c
 * @author mangolu (mangolu81@gmail.com)
 * @brief VFD 8MD06INKM驱动实现
 * @version 1.0.0
 * @date 2019-10-27
 * 
 * @copyright Copyright (c) 2019 mangolu All righits reserved
 * 
 */

/* 所需头文件 */
#include "vfd_8md06inkm.h"
#include "../common/stdint.h"
#include "../n76e003/sfr_macro.h"
#include "../n76e003/gpio.h"

/**
 * @brief 初始化与8MD06INKM连接的端口
 * 
 */
void VFD_8MD06INKM_Port_Init(void) {
	/** 8MD06INKM接口初始化 */
	SET_P00_PushPull_Mode;  /** 设置P0^0为推挽输出模式 */
	SET_P01_PushPull_Mode;  /** 设置P0^1为推挽输出模式 */
	SET_P03_PushPull_Mode;  /** 设置P0^3为推挽输出模式 */
	SET_P04_PushPull_Mode;  /** 设置P0^4为推挽输出模式 */
	SET_P10_PushPull_Mode;  /** 设置P1^0为推挽输出模式 */
}

/**
 * @brief 向8MD06INKM发送数据
 * 
 * @param u8Data 所要发送的数据
 */
void VFD_8MD06INKM_Send(uint8_t u8Data) {
	uint8_t u8I;

	for(u8I = 0; u8I < 8; u8I ++) {
		PT6312_CP_L();

		if((u8Data & 0x01) == 0x01) {
			PT6312_DA_H();
		} else {
			PT6312_DA_L();
		}

		u8Data >>= 1;
		PT6312_CP_H();
	}
}

/**
 * @brief 8MD06INKM初始化
 * 
 */
void VFD_8MD06INKM_Init(void) {
	/* 取消复位 */
	PT6312_RST_H();

	/* 开启高压和灯丝供电 */
	HV_ON();

	//1.上电(Power On)

	//2.设置显示时序(Set The Diaplay Timing)
	/* 片选 */
	PT6312_CS_L();
	/* 命令第一字节 */
	VFD_8MD06INKM_Send(0xE0);
	/* 命令第二字节 */
	VFD_8MD06INKM_Send(0x07);	/* URAM不启用 */
	/* 取消片选 */
	PT6312_CS_H();
	//3.设置URAM(Set The URAM)	/* 不启用 */

	//4.设置亮度(Set The Dimming Data)
	/* 片选 */
	PT6312_CS_L();
	/* 命令第一字节 */
	VFD_8MD06INKM_Send(0xE4);
	/* 命令第二字节 */
	// VFD_8MD06INKM_Send(0xFF);
	VFD_8MD06INKM_Send(180);
	/* 取消片选 */
	PT6312_CS_H();
	//5.发送数据到CGRAM/DCRAM/ADRAM(Transfer The Display Data(CGRAM/DCRAM/ADRAM))

	//6.释放所有显示关闭(Release The All Display OFF)

	//7.开启VFD灯光(The VFD Lights Up)
	/* 片选 */
	PT6312_CS_L();
	/*  */
	VFD_8MD06INKM_Send(0xE8);	/* 正常操作 */
	// VFD_8MD06INKM_Send(0xE9);	/* 全亮 */
	// VFD_8MD06INKM_Send(0xEA);	/* 全灭 */
	/* 取消片选 */
	PT6312_CS_H();
}

/**
 * @brief 在8MD06INKM指定位置显示一个字符
 * 
 * @param u8Position 位置，为0~7。
 * @param u8Char 要显示的字符，为ASCII编码。
 */
void VFD_8MD06INKM_Display_Char(uint8_t u8Position, uint8_t u8Char) {
	/* 片选 */
	PT6312_CS_L();
	/*  */
	VFD_8MD06INKM_Send(0x20 + u8Position);
	/*  */
	// VFD_8MD06INKM_Send(0x30 + u8Char);
	VFD_8MD06INKM_Send(u8Char);
	/* 取消片选 */
	PT6312_CS_H();
}

/**
 * @brief 从指定位置开始显示字符串
 * 
 * @param u8Position 指定开始显示的位置，为0~7。
 * @param Str 要显示的字符串指针。
 */
void VFD_8MD06INKM_Display_String(uint8_t u8Position, uint8_t *Str) {
	/* 片选 */
	PT6312_CS_L();
	/*  */
	VFD_8MD06INKM_Send(0x20 + u8Position);
	/*  */
	while(*Str) {
		VFD_8MD06INKM_Send(*Str);
		Str++;
	}
	/* 取消片选 */
	PT6312_CS_H();
}

