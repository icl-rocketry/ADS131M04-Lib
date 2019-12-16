#ifndef REGISTERDEFINITIONS_H
#define REGISTERDEFINITIONS_H

/* Definitions of all the addresses of the registers of the ADS131M04
   Chip. For the content of the registers, please refer to the datasheet:

   https://www.ti.com/lit/gpn/ads131m04

   Written by Imperial College London Rocketry
   Electronics subteam
*/

#define ID 0x00
#define STATUS 0x01
#define MODE 0x02
#define CLOCK 0x03
#define GAIN1 0x04
#define CFG 0x06
#define THRSHLD_MSB 0x07
#define THRSHLD_LSB 0x08
#define CH0_CFG 0x09
#define CH0_OCAL_MSB 0x0A
#define CH0_OCAL_LSB 0x0B
#define CH0_GCAL_MSB 0x0C
#define CH0_GCAL_LSB 0x0D
#define CH1_CFG 0x0E
#define CH1_OCAL_MSB 0x0F
#define CH1_OCAL_LSB 0x10
#define CH1_GCAL_MSB 0x11
#define CH1_GCAL_LSB 0x12
#define CH2_CFG 0x13
#define CH2_OCAL_MSB 0x14
#define CH2_OCAL_LSB 0x15
#define CH2_GCAL_MSB 0x16
#define CH2_GCAL_LSB 0x17
#define CH3_CFG 0x18
#define CH3_OCAL_MSB 0x19
#define CH3_OCAL_LSB 0x1A
#define CH3_GCAL_MSB 0x1B
#define CH3_GCAL_LSB 0x1C
#define REGMAP_CRC 0x3E
#define RESERVED 0x3F

#endif
