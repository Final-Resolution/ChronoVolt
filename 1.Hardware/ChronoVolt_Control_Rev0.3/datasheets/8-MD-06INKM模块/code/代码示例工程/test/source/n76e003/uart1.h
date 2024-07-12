/**
 * @file uart.h
 * @author mangolu (mangolu81@gmail.com)
 * @brief N76E003串口相关操作定义
 * @version 1.0.0
 * @date 2019-05-04
 * 
 * @copyright Copyright (c) 2019 mangolu All righits reserved
 * 
 */
/********************************************************************************************************************************************************************************************************/
/*************************  *************************/


/********************************************************************************************************************************************************************************************************/
#ifndef _UART_H_
#define _UART_H_

/** 所需头文件开始>>> */

#include "N76E003.h"
#include "common.h"
#include "uart.h"

/** 所需头文件结束<<< */

/** 需要自行定义部分开始>>> */



/** 需要自行定义部分结束<<< */

/********************************************************************************************************************************************************************************************************/
/*************************  *************************/


/********************************************************************************************************************************************************************************************************/

//**** T3CON		C4H	PAGE0 ****                     
#define set_SMOD_1  T3CON   |= SET_BIT7
#define set_SMOD0_1 T3CON   |= SET_BIT6
#define set_BRCK    T3CON   |= SET_BIT5
#define set_TF3     T3CON   |= SET_BIT4
#define set_TR3     T3CON   |= SET_BIT3
#define set_T3PS2   T3CON   |= SET_BIT2
#define set_T3PS1   T3CON   |= SET_BIT1
#define set_T3PS0   T3CON   |= SET_BIT0
                            
#define clr_SMOD_1  T3CON   &= ~SET_BIT7
#define clr_SMOD0_1 T3CON   &= ~SET_BIT6
#define clr_BRCK    T3CON   &= ~SET_BIT5
#define clr_TF3     T3CON   &= ~SET_BIT4
#define clr_TR3     T3CON   &= ~SET_BIT3
#define clr_T3PS2   T3CON   &= ~SET_BIT2
#define clr_T3PS1   T3CON   &= ~SET_BIT1
#define clr_T3PS0   T3CON   &= ~SET_BIT0

//**** EIE1		9CH ****                      
#define set_EWKT    EIE1    |= SET_BIT2
#define set_ET3     EIE1    |= SET_BIT1
#define set_ES_1    EIE1    |= SET_BIT0
                            
#define clr_EWKT    EIE1    &= ~SET_BIT2
#define clr_ET3     EIE1    &= ~SET_BIT1
#define clr_ES_1    EIE1    &= ~SET_BIT0

//**** IE			A8H ****
#define set_EA      EA       = 1
#define set_EADC    EADC     = 1
#define set_EBOD    EBOD     = 1
#define set_ES      ES       = 1
#define set_ET1     ET1      = 1
#define set_EX1     EX1      = 1
#define set_ET0     ET0      = 1
#define set_EX0     EX0      = 1

#define clr_EA      EA       = 0
#define clr_EADC    EADC     = 0
#define clr_EBOD    EBOD     = 0
#define clr_ES      ES       = 0
#define clr_ET1     ET1      = 0
#define clr_EX1     EX1      = 0
#define clr_ET0     ET0      = 0
#define clr_EX0     EX0      = 0

/**** SCON_1		F8H ****/
#define set_FE_1    FE_1  = 1
#define set_SM1_1   SM1_1 = 1
#define set_SM2_1   SM2_1 = 1
#define set_REN_1   REN_1 = 1
#define set_TB8_1   TB8_1 = 1
#define set_RB8_1   RB8_1 = 1
#define set_TI_1    TI_1  = 1
#define set_RI_1    RI_1  = 1

#define clr_FE_1    FE_1  = 0
#define clr_SM1_1   SM1_1 = 0
#define clr_SM2_1   SM2_1 = 0
#define clr_REN_1   REN_1 = 0
#define clr_TB8_1   TB8_1 = 0
#define clr_RB8_1   RB8_1 = 0
#define clr_TI_1    TI_1  = 0
#define clr_RI_1    RI_1  = 0

void InitialUART1_Timer3(unsigned long u32Baudrate);

unsigned char Receive_Data_From_UART1(void);

void Send_Data_To_UART1 (unsigned char c);

#endif	/** _UART_H_ */