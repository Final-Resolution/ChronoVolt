/**
 * @file common.h
 * @author mangolu (mangolu81@gmail.com)
 * @brief 通用操作设置定义
 * @version 1.0.0
 * @date 2019-04-21
 *
 * @copyright Copyright (c) 2019 mangolu All righits reserved
 *
 */
#ifndef _COMMON_H_
#define _COMMON_H_

/** 所需头文件开始>>> */

#include "stdint.h"

/** 所需头文件结束<<< */

/** 需要自行定义部分开始>>> */

/** 需要自行定义部分结束<<< */

/************************* 定义真假及布尔值 *************************/
#ifndef FALSE
	#define FALSE (0)
#endif	/** FALSE */
#ifndef TRUE
	#define TRUE (!FALSE)
#endif	/** TRUE */
#ifndef BOOL
	#define BOOL uint8_t
#endif	/** BOOL */

/************************* 定义一些状态信息 *************************/
#ifndef ON
	#define ON		1
#endif	/** ON */
#ifndef OFF
	#define OFF		0
#endif	/** OFF */

#ifndef YES
	#define YES		1
#endif	/** YES */
#ifndef NO
	#define NO		0
#endif	/** NO */

#ifndef START
	#define START	1
#endif	/** START */
#ifndef STOP
	#define STOP	0
#endif	/** STOP */

#ifndef HIGH
	#define HIGH	1
#endif	/** HIGH */
#ifndef LOW
	#define LOW	0
#endif	/** LOW */

/************************* 置位位 *************************/
#define SET_BIT0        0x01
#define SET_BIT1        0x02
#define SET_BIT2        0x04
#define SET_BIT3        0x08
#define SET_BIT4        0x10
#define SET_BIT5        0x20
#define SET_BIT6        0x40
#define SET_BIT7        0x80
#define SET_BIT8        0x0100
#define SET_BIT9        0x0200
#define SET_BIT10       0x0400
#define SET_BIT11       0x0800
#define SET_BIT12       0x1000
#define SET_BIT13       0x2000
#define SET_BIT14       0x4000
#define SET_BIT15       0x8000

/************************* 复位位 *************************/
#define CLR_BIT0        0xFE
#define CLR_BIT1        0xFD
#define CLR_BIT2        0xFB
#define CLR_BIT3        0xF7
#define CLR_BIT4        0xEF
#define CLR_BIT5        0xDF
#define CLR_BIT6        0xBF
#define CLR_BIT7        0x7F
#define CLR_BIT8        0xFEFF
#define CLR_BIT9        0xFDFF
#define CLR_BIT10       0xFBFF
#define CLR_BIT11       0xF7FF
#define CLR_BIT12       0xEFFF
#define CLR_BIT13       0xDFFF
#define CLR_BIT14       0xBFFF
#define CLR_BIT15       0x7FFF

//16 --> 8 x 2
#define HIBYTE(v1)              ((uint8_t)((v1)>>8))                      //v1 is uint16_t
#define LOBYTE(v1)              ((uint8_t)((v1)&0xFF))
//8 x 2 --> 16
#define MAKEWORD(v1,v2)         ((((uint16_t)(v1))<<8)+(uint16_t)(v2))      //v1,v2 is uint8_t
//8 x 4 --> 32
#define MAKELONG(v1,v2,v3,v4)   (UINT32)((v1<<32)+(v2<<16)+(v3<<8)+v4)  //v1,v2,v3,v4 is uint8_t
//32 --> 16 x 2
#define YBYTE1(v1)              ((uint16_t)((v1)>>16))                    //v1 is uint32_t
#define YBYTE0(v1)              ((uint16_t)((v1)&0xFFFF))
//32 --> 8 x 4
#define TBYTE3(v1)              ((uint8_t)((v1)>>24))                     //v1 is uint32_t
#define TBYTE2(v1)              ((uint8_t)((v1)>>16))
#define TBYTE1(v1)              ((uint8_t)((v1)>>8)) 
#define TBYTE0(v1)              ((uint8_t)((v1)&0xFF))

#endif	/** _COMMON_H_ */
