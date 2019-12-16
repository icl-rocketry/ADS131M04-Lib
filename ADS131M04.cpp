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

ADS131M04::ADS131M04(int8_t _csPin, int8_t _clkoutPin, SPIClass* _spi, int8_t _clockCh) {
  csPin = _csPin;
  clkoutPin = _clkoutPin;
  spi = _spi;
  clockCh = _clockCh;
  initialised = false;
}

void ADS131M04::begin(void) {
  pinMode(csPin, OUTPUT);
  digitalWrite(csPin, HIGH);

  spi->begin();

  // Set CLKOUT on the ESP32 to give the correct frequency for CLKIN on the DAC
  ledcAttachPin(clkoutPin, clockCh);
  ledcSetup(clockCh, CLKIN_SPD, 8);
  ledcWrite(clockCh, 127);

  initialised=true;
}

uint32_t ADS131M04::spiTransferWord(uint16_t inputData) {
  // Transfer a 24 bit word

  uint32_t data = spi->transfer(inputData>>8);
  data <<= 8;
  data |= spi->transfer(inputData<<8);
  data <<= 8;
  data |= spi->transfer(0x00);

  return data;
}

void ADS131M04::spiCommFrame(uint32_t * outPtr, uint16_t command) {
  // Saves all the data of a communication frame to an array with pointer outPtr

  digitalWrite(csPin, LOW);

  spi->beginTransaction(SPISettings(SCLK_SPD, MSBFIRST, SPI_MODE0));

  // Send the command in the first word
  *outPtr = spiTransferWord(command);
  // For the next 5 words, just read the data
  for (uint8_t i=1; i < 6; i++) {
    outPtr++;
    *outPtr = spiTransferWord();
  }

  spi->endTransaction();

  digitalWrite(csPin, HIGH);
}
