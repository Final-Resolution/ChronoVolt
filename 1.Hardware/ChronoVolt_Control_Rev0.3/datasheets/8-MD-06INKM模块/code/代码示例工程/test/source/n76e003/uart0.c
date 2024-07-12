/**
 * @file uart.c
 * @author mangolu (mangolu81@gmail.com)
 * @brief N76E003串口相关操作实现
 * @version 1.0.0
 * @date 2019-05-04
 *
 * @copyright Copyright (c) 2019 mangolu All righits reserved
 *
 */
/** 所需头文件开始>>> */

#include "uart.h"
#include "gpio.h"

/** 所需头文件结束<<< */


#define BUFFER_SIZE		16
unsigned char  UART_BUFFER[BUFFER_SIZE],temp;
unsigned int u16CNT=0,u16CNT1=0;
bit riflag;

void InitialUART1_Timer3(unsigned long u32Baudrate) { //use timer3 as Baudrate generator
	SET_P02_Quasi_Mode;		//Setting UART pin as Quasi mode for transmit
	SET_P16_Quasi_Mode;		//Setting UART pin as Quasi mode for transmit

	SCON_1 = 0x50;   	//UART1 Mode1,REN_1=1,TI_1=1
	T3CON = 0x08;   	//T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1), UART1 in MODE 1
	clr_BRCK;

#ifdef FOSC_160000
	RH3    = HIBYTE(65536 - (1000000 / u32Baudrate) - 1);  		/*16 MHz */
	RL3    = LOBYTE(65536 - (1000000 / u32Baudrate) - 1);			/*16 MHz */
#endif
#ifdef FOSC_166000
	RH3    = HIBYTE(65536 - (1037500 / u32Baudrate));  			/*16.6 MHz */
	RL3    = LOBYTE(65536 - (1037500 / u32Baudrate));				/*16.6 MHz */
#endif
	set_TR3;         //Trigger Timer3
}

unsigned char Receive_Data_From_UART1(void) {
	unsigned char c;

	while (!RI_1);

	c = SBUF_1;
	RI_1 = 0;
	return (c);
}

void Send_Data_To_UART1 (unsigned char c) {
	TI_1 = 0;
	SBUF_1 = c;

	while(TI_1 == 0);
}

void SerialPort1_ISR(void) interrupt 15 
{
    if (RI_1==1) 
    {                                       /* if reception occur */
        clr_RI_1;                             /* clear reception flag for next reception */
        UART_BUFFER[u16CNT] = SBUF_1;
        u16CNT ++;
				riflag =1;
    }
    if(TI_1==1)
    {
        clr_TI_1;                             /* if emission occur */
    }
}

