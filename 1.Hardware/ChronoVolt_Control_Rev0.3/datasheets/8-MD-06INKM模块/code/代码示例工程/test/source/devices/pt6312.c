/**
 * @file pt6312.c
 * @author mangolu (mangolu81@gmail.com)
 * @brief PT6312�������ʵ��
 * @version 1.0.0
 * @date 2019-08-05
 * 
 * @copyright Copyright (c) 2019 mangolu All righits reserved
 * 
 */
#include "pt6312.h"
#include "../devices/font_seg13.h"

/**
 * @brief ��PT6312�������ݣ��ڲ�����
 * 
 * @param ucData Ҫ���͵�����
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
 * @brief ��PT6312���������źţ��ڲ�����
 * 
 */
void PT6312_Send_STB(void) {
	PT6312_STB_H();
	PT6312_STB_L();
}

/**
 * @brief PT6312��ʼ��
 * 
 */
void PT6312_Initial(void) {
	unsigned char ucI;

	PT6312_Send_STB();

	/* ��������2��д���� */
	PT6312_Send(CMD2_CMD | WR_TO_DISPLAY_MODE_CMD);
	PT6312_Send_STB();

	/* ��������3������ڴ����� */
	PT6312_Send(CMD3_CMD);

	for(ucI = 0; ucI < 8; ucI ++) { /* ����ڴ����� */
		PT6312_Send(0x00);
		PT6312_Send(0x00);
	}

	PT6312_Send_STB();

	/* ��������1��������ʾģʽ */
	PT6312_Send(CMD1_CMD | PT6312_MODE);
	PT6312_Send_STB();

	/* ��������4��������ʾ */
	PT6312_Send(CMD4_CMD | DISPLAY_ON | PT6312_LIGHT);
	PT6312_Send_STB();

}

/**
 * @brief ��ʾPT6312��ǰ����ģʽ���������
 * 
 */
void PT6312_Display_All(void) {
	unsigned char ucI;

	/* ��������2��д���� */
	PT6312_Send(CMD2_CMD | WR_TO_DISPLAY_MODE_CMD);
	PT6312_Send_STB();

	/* ��������3��д�ڴ����� */
	PT6312_Send(CMD3_CMD);

	for(ucI = 0; ucI < 8; ucI ++) {
		PT6312_Send(0xFF);
		PT6312_Send(0xFF);
	}

	PT6312_Send_STB();
}

/**
 * @brief ˢ��PT6312��ʾ����
 * 
 * @param *uiBuffer Ҫˢ�½�PT6312���������Դ
 * PT6312�ڲ��ܹ���8��16�ֽڵĻ��棬Ҫ����ʵ�����ѡ����Ӧ��ˢ��λ��
 */
void PT6312_Update(unsigned int *uiBuffer) {
	unsigned char ucI;

	/* ��������2��д���� */
	PT6312_Send(CMD2_CMD | WR_TO_DISPLAY_MODE_CMD);
	PT6312_Send_STB();

	/* ��������3��д�ڴ����� */
	PT6312_Send(CMD3_CMD);

	for(ucI = 0; ucI < 7; ucI ++) {
		PT6312_Send((unsigned char)((*(uiBuffer + ucI) >> 8) & 0x00FF));
		PT6312_Send((unsigned char)(*(uiBuffer + ucI) & 0x00FF));
	}

	PT6312_Send_STB();
}

/**
 * @brief ��ߵ�һ��ʱ�ӵ����
 * ���������ͨ���Ե�Ƭ���������ݲ���ʵ�ֵ�
 * 
 * @param *ucBuffer ����
 * @param ucONOFF ���أ���Ϊ1ʱ������Ϊ0ʱ��
 */
void VFD_DOT1_ONOFF(unsigned int *ucBuffer,unsigned char ucONOFF) {

	if(ucONOFF == 1) {
		*(ucBuffer + 2) |= SEG13_DP;
	} else {
		*(ucBuffer + 2) &= ~SEG13_DP;
	}
}

/**
 * @brief ��ߵڶ���ʱ�ӵ����
 * ���������ͨ���Ե�Ƭ���������ݲ���ʵ�ֵ�
 * 
 * @param *ucBuffer ����
 * @param ucONOFF ���أ���Ϊ1ʱ������Ϊ0ʱ��
 */
void VFD_DOT2_ONOFF(unsigned int *ucBuffer,unsigned char ucONOFF) {

	if(ucONOFF == 1) {
		*(ucBuffer + 4) |= SEG13_DP;
	} else {
		*(ucBuffer + 4) &= ~SEG13_DP;
	}
}
