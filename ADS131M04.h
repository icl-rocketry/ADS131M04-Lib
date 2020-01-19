/* This is a library for the ADS131M04 4-channel ADC
   
   Product information:
   https://www.ti.com/product/ADS131M04

   Datasheet: 
   https://www.ti.com/lit/gpn/ads131m04

   This library was made for Imperial College London Rocketry
   Created by Daniele Valentino Bella
*/

#define CLKIN_SPD 8192000 // Clock speed for the CLKIN pin on the DAC
#define SCLK_SPD 25000000 // SPI frequency of DAC

#ifndef ADS131M04_H
#define ADS131M04_H

#include <Arduino.h>
#include <SPI.h>
#include "registerDefinitions.h"

class ADS131M04 {
  public:
    ADS131M04(int8_t _csPin, int8_t _clkoutPin, SPIClass* _spi, int8_t _clockCh = 1);
    void begin(void);
    void rawChannels(int8_t * channelArrPtr, int8_t channelArrLen, int32_t * outputArrPtr);
    int32_t rawChannelSingle(int8_t channel);
    uint16_t readReg(uint8_t reg);
    bool writeReg(uint8_t reg, uint16_t data);

  private:
    int8_t csPin, clkoutPin, clockCh;
    SPIClass* spi;
    bool initialised;
    
    void spiCommFrame(uint32_t * outputArray, uint16_t command = 0x0000);
    uint32_t spiTransferWord(uint16_t inputData = 0x0000);
    int32_t twoCompDeco(uint32_t data);
};

#endif
