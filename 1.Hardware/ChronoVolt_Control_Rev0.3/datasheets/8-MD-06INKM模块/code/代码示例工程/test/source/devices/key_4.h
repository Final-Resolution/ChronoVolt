/**
 * @file key_4.h
 * @author mangolu (mangolu81@gmail.com)
 * @brief 四位独立按键驱动相关函数声明
 * @version 1.0.0
 * @date 2018-11-24
 * 
 * @copyright Copyright (c) 2018
 * 
 */
/**
 * ----------------- 独立按键连接 -----------------
 *
 * P05 ---- K0 ---- GND
 *      
 * P06 ---- K1 ---- GND
 * 
 * P07 ---- K2 ---- GND
 * 
 * P30 ---- K3 ---- GND
 *
 * ---------------------- 键码 ----------------------
 * K0: 0x0E
 * K1: 0x0D
 * K2: 0x0B
 * K3: 0x07
 * --------------------------------------------------
 */

#ifndef _KEY_4_H_
#define _KEY_4_H_

/** 所需头文件开始>>> */

#include <REGX52.H>
#include "../status.h"

/** 所需头文件结束<<< */


/** 需要自行定义部分开始>>> */


/** 定义按键连接 */
sbit K0 = P1 ^ 0;
sbit K1 = P1 ^ 1;
sbit K2 = P1 ^ 2;
sbit K3 = P1 ^ 3;

/** 定义按键空值，即按键未按下读取获得的值 */
#define KEY_VALUE_NULL 0x0F

/** 定义键盘缓冲区长度 */
#define KEY_BUFFER_SIZE 8

/** 双击和长按检测 */
#define DOUBLE_CLICK_ENABLE ON		/** 启用按键双击 */
// #define DOUBLE_CLICK_ENABLE OFF		/** 禁用按键双击 */
#define LONG_CLICK_ENABLE ON		/** 启用按键长按 */
// #define LONG_CLICK_ENABLE OFF		/** 禁用按键长按 */

/** 定义按键超时判断时间 */
/** 默认按键扫描程序放在10ms中断一次的定时中断中，所以下面的时间值要乘以10mS */
#define DOUBLE_CLICK_TIME   50     /** 双击超时值，按键单击后计数判断是否有双击，超时则判断为单击 */
#define LONG_CLICK_TIME     150    /** 长按时间间隔 */


/** 需要自行定义部分结束<<< */



/** 定义键值 */
#define KEY_VALUE_K0 0x0E
#define KEY_VALUE_K1 0x0D
#define KEY_VALUE_K2 0x0B
#define KEY_VALUE_K3 0x07

/** 定义按键状态枚举 */
typedef enum {
	No_Click = 0x10,
	Short_Click = 0x20,
	Double_Click =0x40,
	Long_Click =0x80,
} Button;

/** 按键缓冲区队列数据结构原型 */
typedef struct {
	unsigned char size;		/** 队列长度 */
	unsigned char count;	/** 队列数据数量 */
	unsigned char front;	/** 队列头 */
	unsigned char rear;		/** 队列尾 */
	unsigned char *buffer;	/** 队列缓冲区 */
} KEY_FIFO;

/** 按键缓存区队列存储数组 */
extern unsigned char Key_Temp_Buffer[KEY_BUFFER_SIZE];

/** 按键缓存区队列 */
extern KEY_FIFO Key_Buffer;

/**
 * @brief 按键初始化函数
 *
 * @param fifo 按键缓存区队列
 * @param ucBuffer 按键缓存区队列存储数组
 * @param ucSize 按键缓存区队列长度
 */
void Key_Initial(KEY_FIFO *fifo, unsigned char *ucBuffer, unsigned char ucSize);

/**
 * @brief 读取按键值
 * 只负责读取按键的值，不负责消抖识别等处理。
 * 
 * @return unsigned char 获取的按键值
 */
unsigned char Key_Read(void);

/**
 * @brief 按键扫描函数
 * 默认10ms调用一次。
 * 
 */
void Key_Scan(void);

/**
 * @brief 按键缓冲区队列初始化
 *
 * @param fifo 要初始化的按键缓冲区队列
 * @param ucBuffer 按键缓冲区队列缓存数组
 * @param ucSize 按键缓冲区队列长度
 */
void Key_Buffer_Initial(KEY_FIFO *fifo, unsigned char *ucBuffer, unsigned char ucSize);

/**
 * @brief 存一个数据到按键缓冲区队列中
 *
 * @param fifo 要操作的按键缓冲区队列
 * @param ucData 要存入按键缓冲区队列的数据
 */
void Key_Buffer_In(KEY_FIFO *fifo, unsigned char ucData);

/**
 * @brief 从按键缓冲区队列中读出一个数据
 * 当读取的次数超过队列长度时，会循环从队列头开始读取。
 * @param fifo 要操作的按键缓冲区队列
 * @return unsigned char ucTemp 取出的数据
 */
unsigned char Key_Buffer_Out(KEY_FIFO *fifo);

/**
 * @brief 获取按键缓冲区队列中数据个数
 *
 * @param fifo 要操作的按键缓冲区队列
 * @return unsigned char 按键缓冲区队列中数据个数
 */
unsigned char Key_Buffer_Get_Count(KEY_FIFO *fifo);

/**
 * @brief 按键服务函数
 * 获取按键缓冲区队列的键值，并进行处理。需自行编写。
 *
 * @param fifo 按键缓冲区队列。
 */
void Key_Services(KEY_FIFO *fifo);


#endif	/** _KEY_4_H_ */
