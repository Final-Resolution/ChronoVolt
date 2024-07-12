/**
 * @file key_4.c
 * @author mangolu (mangolu81@gmail.com)
 * @brief 四位独立按键驱动相关函数定义
 * @version 1.0.0
 * @date 2018-11-24
 * 
 * @copyright Copyright (c) 2018
 * 
 */
/** 所需头文件开始>>> */

#include "key_4.h"
#include <intrins.h>
#include "../status.h"

/** 所需头文件结束<<< */



/** 按键缓存区队列存储数组 */
unsigned char Key_Temp_Buffer[KEY_BUFFER_SIZE];

/** 按键缓存区队列 */
KEY_FIFO Key_Buffer;

/**
 * @brief 按键初始化函数
 *
 * @param fifo 按键缓存区队列
 * @param ucBuffer 按键缓存区队列存储数组
 * @param ucSize 按键缓存区队列长度
 */
void Key_Initial(KEY_FIFO *fifo, unsigned char *ucBuffer, unsigned char ucSize) {

    Key_Buffer_Initial(fifo, ucBuffer, ucSize);	/** 初始化按键缓存区队列 */
}

/**
 * @brief 读取按键值
 * 只负责读取按键的值，不负责消抖识别等处理。
 *
 * @return unsigned char 获取的按键值
 */
unsigned char Key_Read(void) {
    unsigned char ucTemp = 0;

    K0 = 1;
    K1 = 1;
    K2 = 1;
    K3 = 1;
    _nop_();

    ucTemp = (unsigned char)K3; /** 读K3 */
    ucTemp <<= 1;
    ucTemp |= (unsigned char)K2; /** 读K2 */
    ucTemp <<= 1;
    ucTemp |= (unsigned char)K1; /** 读K1 */
    ucTemp <<= 1;
    ucTemp |= (unsigned char)K0; /** 读K0 */

    return ucTemp;
}

/**
 * @brief 按键扫描函数
 * 默认10ms调用一次。
 *
 */
void Key_Scan(void) {
    static unsigned int uiCount = 0;				/** 按键按下计数变量 */
#if (DOUBLE_CLICK_ENABLE == ON)	/** 启用按键双击 */
    static unsigned char ucShort_Click_Flag = 0;	/** 按键单击标志位 */
    static unsigned int uiShort_Click_Count = 0;	/** 双击超时计数变量，按键单击后计数判断是否有双击，超时则判断为单击 */
#endif	/** DOUBLE_CLICK_ENABLE == ON */
#if (LONG_CLICK_ENABLE == ON)	/** 启用按键长按 */
    static unsigned char ucLong_Click_Flag = 0;		/** 按键长按标志位，用于防止长按反复返回按键值 */
#endif	/** LONG_CLICK_ENABLE == ON */
    unsigned char ucTemp;	/** 按键值临时存储变量 */
    unsigned char ucKeyTemp;

    /** 读取按键值 */
    ucTemp =  Key_Read();

    /** 处理按键值 */
    if(ucTemp != KEY_VALUE_NULL) {	/** 按键值不等于空值 */
        if(ucTemp == Key_Read()) {
            ucKeyTemp = ucTemp;
#if (LONG_CLICK_ENABLE == ON)	/** 启用按键长按 */
            if(ucLong_Click_Flag != 1) {
                if(uiCount < LONG_CLICK_TIME) {
                    uiCount ++;
                } else {
                    ucLong_Click_Flag = 1;
                    uiCount = 0;
                    Key_Buffer_In(&Key_Buffer, Long_Click | ucKeyTemp);	/** 返回按键长按 */
                }
            }
#elif (LONG_CLICK_ENABLE == OFF)	/** 禁用按键长按 */
            uiCount ++;
#endif	/** LONG_CLICK_ENABLE == ON */
        } else {
            uiCount = 0;
        }
    } else {
#if (DOUBLE_CLICK_ENABLE == ON)	/** 启用按键双击 */
        if(uiCount >= 5) {	/** 按键消抖时间，检测到5次即5*10mS即为一个有效按键 */
            if(ucShort_Click_Flag == 1) {
                ucShort_Click_Flag = 0;
                Key_Buffer_In(&Key_Buffer, Double_Click | ucKeyTemp);	/** 返回按键双击 */
            } else {
                ucShort_Click_Flag = 1;
            }
        }

        if(ucShort_Click_Flag == 1) {
            if((uiShort_Click_Count ++) > DOUBLE_CLICK_TIME) {
                Key_Buffer_In(&Key_Buffer, Short_Click | ucKeyTemp);	/** 返回按键单击 */
                ucShort_Click_Flag = 0;
                uiShort_Click_Count = 0;
            }
        } else {
            uiShort_Click_Count = 0;
        }
#elif (DOUBLE_CLICK_ENABLE == OFF)	/** 禁用按键双击 */
        if(uiCount >= 5) {	/** 按键消抖时间，检测到5次即5*10mS即为一个有效按键 */
            Key_Buffer_In(&Key_Buffer, Short_Click | ucKeyTemp);	/** 返回按键单击 */
        }
#endif	/** DOUBLE_CLICK_ENABLE == ON */

#if (LONG_CLICK_ENABLE == ON)	/** 启用按键长按 */
        ucLong_Click_Flag = 0;
#endif	/** LONG_CLICK_ENABLE == ON */
        uiCount = 0;

    }
}

/**
 * @brief 按键缓冲区队列初始化
 *
 * @param fifo 要初始化的按键缓冲区队列
 * @param ucBuffer 按键缓冲区队列缓存数组
 * @param ucSize 按键缓冲区队列长度
 */
void Key_Buffer_Initial(KEY_FIFO *fifo, unsigned char *ucBuffer, unsigned char ucSize) {
	fifo -> buffer = ucBuffer;
	fifo -> size = ucSize;
	fifo -> count = 0;
	fifo -> front = 0;
	fifo -> rear = 0;
}

/**
 * @brief 存一个数据到按键缓冲区队列中
 *
 * @param fifo 要操作的按键缓冲区队列
 * @param ucData 要存入按键缓冲区队列的数据
 */
void Key_Buffer_In(KEY_FIFO *fifo, unsigned char ucData) {

	/** 循环写入，即写满从头开如写 */
	fifo -> buffer[fifo -> front] = ucData;
	fifo -> front = (fifo -> front + 1) % (fifo -> size);

	if(fifo -> count < fifo -> size) {
		fifo -> count ++;	/** 当队列元素个数小于指定队列长度时自加 */
	}
}

/**
 * @brief 从按键缓冲区队列中读出一个数据
 * 当读取的次数超过队列长度时，会循环从队列头开始读取。
 * @param fifo 要操作的按键缓冲区队列
 * @return unsigned char ucTemp 取出的数据
 */
unsigned char Key_Buffer_Out(KEY_FIFO *fifo) {
	unsigned char ucTemp;

	/** 循环读取，即读完从头开如读 */
	ucTemp = fifo -> buffer[fifo -> rear];
	fifo -> rear = (fifo -> rear + 1) % (fifo -> size);

	if(fifo -> count > 0) {
		fifo -> count --;	/** 当队列元素个数为0时不自减 */
	}

	return ucTemp;
}

/**
 * @brief 获取按键缓冲区队列中数据个数
 *
 * @param fifo 要操作的按键缓冲区队列
 * @return unsigned char 按键缓冲区队列中数据个数
 */
unsigned char Key_Buffer_Get_Count(KEY_FIFO *fifo) {
	return (fifo -> count);
}


// /**
//  * @brief 按键服务函数
//  * 获取按键缓冲区队列的键值，并进行处理。需自行编写。
//  *
//  * @param fifo 按键缓冲区队列。
//  */
// void Key_Services(KEY_FIFO *fifo) {
// 	unsigned char ucTemp;
// 	static unsigned char ucI;

// 	if(fifo ->count > 0) {	/** 判断缓冲区队列内是否有未处理按键 */

// 		ucTemp = Key_Buffer_Out(fifo);	/** 读取缓冲区队列 */

// 		switch(ucTemp) {
// 			case No_Click | KEY_VALUE_K0:	/** K0无效 */
// 				break;

// 			case  Short_Click | KEY_VALUE_K0:	/** K0单击 */
// 				ucI ++;
// 				break;

// 			case Double_Click | KEY_VALUE_K0:	/** K0双击 */
// 				ucI --;
// 				break;

// 			case Long_Click | KEY_VALUE_K0:	/** K0长按 */
// 				ucI += 10;
// 				break;

// 			case No_Click | KEY_VALUE_K1:	/** K1无效 */
// 				break;

// 			case  Short_Click | KEY_VALUE_K1:	/** K1单击 */
// 				ucI += 2;
// 				break;

// 			case Double_Click | KEY_VALUE_K1:	/** K1双击 */
// 				ucI -= 2;
// 				break;

// 			case Long_Click | KEY_VALUE_K1:	/** K1长按 */
// 				ucI += 20;
// 				break;

// 			case No_Click | KEY_VALUE_K2:	/** K2无效 */
// 				break;

// 			case  Short_Click | KEY_VALUE_K2:	/** K2单击 */
// 				ucI += 3;
// 				break;

// 			case Double_Click | KEY_VALUE_K2:	/** K2双击 */
// 				ucI -= 3;
// 				break;

// 			case Long_Click | KEY_VALUE_K2:	/** K2长按 */
// 				ucI += 30;
// 				break;

// 			case No_Click | KEY_VALUE_K3:	/** K3无效 */
// 				break;

// 			case  Short_Click | KEY_VALUE_K3:	/** K3单击 */
// 				ucI += 4;
// 				break;

// 			case Double_Click | KEY_VALUE_K3:	/** K3双击 */
// 				ucI -= 4;
// 				break;

// 			case Long_Click | KEY_VALUE_K3:	/** K3长按 */
// 				ucI += 40;
// 				break;

// 			default:
// 				break;
// 		}
// 	} else {
// 		HD44780_Display_Hex(1, 0, ucI / 100);
// 		HD44780_Display_Hex(1, 1, ucI % 100 / 10);
// 		HD44780_Display_Hex(1, 2, ucI % 100 % 10);
// 	}

// }




