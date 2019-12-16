/* This is a library for the ADS131M04 4-channel ADC
   
   Product information:
   https://www.ti.com/product/ADS131M04

   Datasheet: 
   https://www.ti.com/lit/gpn/ads131m04

   This library was made for Imperial College London Rocketry
   Created by Daniele Valentino Bella

   */

#ifndef ADS131M04_H
#define ADS131M04_H

#include <Arduino.h>
#include <SPI.h>
#include "registerDefinitions.h"

class ADS131M04 {
  public:
    ADS131M04(int8_t _csPin, SPIClass* _spi);

  private:
    int8_t csPin;
    SPIClass* spi;
};

#endif
