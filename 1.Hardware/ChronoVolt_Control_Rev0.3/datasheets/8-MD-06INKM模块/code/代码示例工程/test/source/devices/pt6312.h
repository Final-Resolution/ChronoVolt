/**
 * @file pt6312.h
 * @author mangolu (mangolu81@gmail.com)
 * @brief PT6312������ض���
 * @version 1.0.0
 * @date 2019-08-05
 * 
 * @copyright Copyright (c) 2019 mangolu All righits reserved
 * 
 */
#ifndef _PT6312_H_
#define _PT6312_H_

#include "../n76e003/sfr_macro.h"

/* COMMAND 1: DISPLAY MODE SETTING COMMANDS����ʾģʽ���� */
#define CMD1_CMD 0x00
#define DISPLAY_4GRID_16SEGMENT_MODE 0x00
#define DISPLAY_5GRID_16SEGMENT_MODE 0x01
#define DISPLAY_6GRID_16SEGMENT_MODE 0x02
#define DISPLAY_7GRID_15SEGMENT_MODE 0x03
#define DISPLAY_8GRID_14SEGMENT_MODE 0x04
#define DISPLAY_9GRID_13SEGMENT_MODE 0x05
#define DISPLAY_10GRID_12SEGMENT_MODE 0x06
#define DISPLAY_11GRID_11SEGMENT_MODE 0x07

/* COMMAND 2: DATA SETTING COMMANDS���������ݴ�PT6312����д */
#define CMD2_CMD 0x40
#define WR_TO_DISPLAY_MODE_CMD 0x00
#define WR_TO_LED_PORT_CMD 0x01
#define RD_KEY_DATA_CMD 0x02
#define RD_SW_DATA_CMD 0x03
#define FIXED_ADDRESS_CMD 0x04  

/* COMMAND 3: ADDRESS SETTING COMMANDS����ʾ�ڴ��ַ���� */
#define CMD3_CMD 0xC0

/* COMMAND 4: DISPLAY CONTROL COMMANDS����ʾ�������� */
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

/* ��ѹ���� */
#define set_HV_ON() set_P10
#define clr_HV_ON() clr_P10
/* PT6312 CLK���� */
#define PT6312_CLK_H() set_P03
#define PT6312_CLK_L() clr_P03
/* PT6312 DIN���� */
#define PT6312_DIN_H() set_P01
#define PT6312_DIN_L() clr_P01
/* PT6312 STB���� */
#define PT6312_STB_H() set_P04
#define PT6312_STB_L() clr_P04

/**
 * @brief PT6312��ʼ��
 * 
 */
void PT6312_Initial(void);

/**
 * @brief ��ʾPT6312��ǰ����ģʽ���������
 * 
 */
void PT6312_Display_All(void);

/**
 * @brief ˢ��PT6312��ʾ����
 * 
 * @param *uiBuffer Ҫˢ�½�PT6312���������Դ
 * PT6312�ڲ��ܹ���8��16�ֽڵĻ��棬Ҫ����ʵ�����ѡ����Ӧ��ˢ��λ��
 */
void PT6312_Update(unsigned int *uiBuffer);

/**
 * @brief ��ߵ�һ��ʱ�ӵ����
 * ���������ͨ���Ե�Ƭ���������ݲ���ʵ�ֵ�
 * 
 * @param *ucBuffer ����
 * @param ucONOFF ���أ���Ϊ1ʱ������Ϊ0ʱ��
 */
void VFD_DOT1_ONOFF(unsigned int *ucBuffer,unsigned char ucONOFF);

/**
 * @brief ��ߵڶ���ʱ�ӵ����
 * ���������ͨ���Ե�Ƭ���������ݲ���ʵ�ֵ�
 * 
 * @param *ucBuffer ����
 * @param ucONOFF ���أ���Ϊ1ʱ������Ϊ0ʱ��
 */
void VFD_DOT2_ONOFF(unsigned int *ucBuffer,unsigned char ucONOFF);


/* ���¸���ʵ����������޸� >>> */

/* PT6312�뵥Ƭ�������������� */
// sbit PT6312_DOUT = P1^0;
// sbit PT6312_DIN  = P1^1;
// sbit PT6312_CLK  = P1^2;
// sbit PT6312_STB  = P1^3;

#define PT6312_MODE  DISPLAY_7GRID_15SEGMENT_MODE  /* ������ʾģʽ */ 
// #define PT6312_MODE  DISPLAY_4GRID_16SEGMENT_MODE  /* ������ʾģʽ */

/* ����VFD���ȣ�����������PT6312ɨ��ռ�ձȣ����ѹ�޹� */ 
/* ��ѡ */
// #define PT6312_LIGHT	MIN_BRIGHTNESS
// #define PT6312_LIGHT	V2_16_BRIGHTNESS
// #define PT6312_LIGHT	V4_16_BRIGHTNESS
// #define PT6312_LIGHT	V10_16_BRIGHTNESS
// #define PT6312_LIGHT	V11_16_BRIGHTNESS
#define PT6312_LIGHT	V12_16_BRIGHTNESS
// #define PT6312_LIGHT	V13_16_BRIGHTNESS
// #define PT6312_LIGHT	MAX_BRIGHTNESS

#endif	/** _PT6312_H_ */