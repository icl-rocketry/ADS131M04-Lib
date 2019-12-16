/* This is a library for the ADS131M04 4-channel ADC
   
   Product information:
   https://www.ti.com/product/ADS131M04

   Datasheet: 
   https://www.ti.com/lit/gpn/ads131m04

   This library was made for Imperial College London Rocketry
   Created by Daniele Valentino Bella
*/

#include <Arduino.h>
#include <SPI.h>
#include "registerDefinitions.h"
#include "ADS131M04.h"

ADS131M04::ADS131M04(int8_t _csPin, SPIClass* _spi) {
  csPin = _csPin;
  spi = _spi;

  initialised=false;
}

void ADS131M04::begin(void) {
  pinMode(csPin, OUTPUT);
  digitalWrite(csPin, HIGH);

  spi->begin();

  initialised=true;
}
