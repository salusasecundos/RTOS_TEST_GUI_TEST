#include "stm32f4xx.h"
#include "bmp180.h"
#include "i2c.h"

/* Calibration parameters from E2PROM of BMP180 */
//BMP180_Calibration_TypeDef BMP180_Calibration;			//for KEIL
extern BMP180_Calibration_TypeDef BMP180_Calibration;
//-----------------------------------------------------------------------------------------------
void BMP180_Reset()
{
	BMP180_WriteReg(BMP180_SOFT_RESET_REG,0xb6); // Do software reset
}
//-----------------------------------------------------------------------------------------------
void BMP180_WriteReg(uint8_t Reg, uint8_t Value)
{
	I2Cx_WriteData(BMP180_ADDR, Reg, Value);
}
//-----------------------------------------------------------------------------------------------
uint8_t BMP180_ReadReg(uint8_t Reg)
{
	return I2Cx_ReadData(BMP180_ADDR, Reg);
}
//-----------------------------------------------------------------------------------------------
void BMP180_ReadCalibration(void)
{
//	uint8_t i=0;
	uint8_t buffer[BMP180_PROM_DATA_LEN];
	I2Cx_ReadBuffer(BMP180_ADDR, BMP180_PROM_START_ADDR, buffer, BMP180_PROM_DATA_LEN);

	BMP180_Calibration.AC1 = (buffer[0]  << 8) | buffer[1];
	BMP180_Calibration.AC2 = (buffer[2]  << 8) | buffer[3];
	BMP180_Calibration.AC3 = (buffer[4]  << 8) | buffer[5];
	BMP180_Calibration.AC4 = (buffer[6]  << 8) | buffer[7];
	BMP180_Calibration.AC5 = (buffer[8]  << 8) | buffer[9];
	BMP180_Calibration.AC6 = (buffer[10] << 8) | buffer[11];
	BMP180_Calibration.B1  = (buffer[12] << 8) | buffer[13];
	BMP180_Calibration.B2  = (buffer[14] << 8) | buffer[15];
	BMP180_Calibration.MB  = (buffer[16] << 8) | buffer[17];
	BMP180_Calibration.MC  = (buffer[18] << 8) | buffer[19];
	BMP180_Calibration.MD  = (buffer[20] << 8) | buffer[21];
}
//-----------------------------------------------------------------------------------------------
uint16_t BMP180_Read_UT(void)
{
	uint16_t UT;
	uint8_t buffer[BUFFER_UT_LENGTH];

	BMP180_WriteReg(BMP180_CTRL_MEAS_REG, BMP180_T_MEASURE);
	HAL_Delay(10);
	I2Cx_ReadBuffer(BMP180_ADDR, BMP180_ADC_OUT_MSB_REG, buffer, BUFFER_UT_LENGTH);
	UT = (buffer[0]  << 8) | buffer[1]; // Receive MSB
	return UT;
}

//-----------------------------------------------------------------------------------------------
uint32_t BMP180_Read_PT(uint8_t oss)
{
	uint32_t PT;
	uint8_t cmd = 0, delay = 0;
	uint8_t buffer[BUFFER_PT_LENGTH];

	switch(oss)
	{
	case 0:
		cmd = BMP180_P0_MEASURE;
		delay   = 6;
		break;
	case 1:
		cmd = BMP180_P1_MEASURE;
		delay   = 9;
		break;
	case 2:
		cmd = BMP180_P2_MEASURE;
		delay   = 15;
		break;
	case 3:
		cmd = BMP180_P3_MEASURE;
		delay   = 27;
		break;
	}

	BMP180_WriteReg(BMP180_CTRL_MEAS_REG, cmd);
	HAL_Delay(delay);
	I2Cx_ReadBuffer(BMP180_ADDR, BMP180_ADC_OUT_MSB_REG, buffer, BUFFER_PT_LENGTH);
	PT = (buffer[0]  << 16) | buffer[1] << 8 | buffer[2]; // Receive MSB
	return PT >> (8 - oss);
}
//-----------------------------------------------------------------------------------------------
int16_t BMP180_Calc_RT(uint16_t UT) {
	BMP180_Calibration.B5  = (((int32_t)UT - (int32_t)BMP180_Calibration.AC6) * (int32_t)BMP180_Calibration.AC5) >> 15;
	BMP180_Calibration.B5 += ((int32_t)BMP180_Calibration.MC << 11) / (BMP180_Calibration.B5 + BMP180_Calibration.MD);

	return (BMP180_Calibration.B5 + 8) >> 4;
}
//-----------------------------------------------------------------------------------------------
int32_t BMP180_Calc_RP(uint32_t UP, uint8_t oss)
{
	int32_t B3,B6,X3,p;
	uint32_t B4,B7;

	B6 = BMP180_Calibration.B5 - 4000;
	X3 = ((BMP180_Calibration.B2 * ((B6 * B6) >> 12)) >> 11) + ((BMP180_Calibration.AC2 * B6) >> 11);
	B3 = (((((int32_t)BMP180_Calibration.AC1) * 4 + X3) << oss) + 2) >> 2;
	X3 = (((BMP180_Calibration.AC3 * B6) >> 13) + ((BMP180_Calibration.B1 * ((B6 * B6) >> 12)) >> 16) + 2) >> 2;
	B4 = (BMP180_Calibration.AC4 * (uint32_t)(X3 + 32768)) >> 15;
	B7 = ((uint32_t)UP - B3) * (50000 >> oss);
	if (B7 < 0x80000000) p = (B7 << 1) / B4; else p = (B7 / B4) << 1;
	p += ((((p >> 8) * (p >> 8) * BMP180_PARAM_MG) >> 16) + ((BMP180_PARAM_MH * p) >> 16) + BMP180_PARAM_MI) >> 4;

	return p;
}
//-----------------------------------------------------------------------------------------------
int32_t BMP180_kpa_to_mmhg1(int32_t Pa)
{
	uint32_t p_mmHg = Pa * BME_MMHG_Q0_20;   //98488*7865 = 774 608 120
	return (((p_mmHg >> 20) * 1000) + ((((p_mmHg << 12) >> 18) * 61039) / 1000000));
}
//-----------------------------------------------------------------------------------------------
int32_t BMP180_kpa_to_mmhg2(int32_t Pa)
{
	return (Pa / 1000.000) * 75006.375 ; // equal to (Pa * 75.006375419)
}
