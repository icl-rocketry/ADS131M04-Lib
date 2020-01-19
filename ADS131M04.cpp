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
  ledcSetup(clockCh, CLKIN_SPD, 2);
  ledcAttachPin(clkoutPin, clockCh);
  ledcWrite(clockCh, 2);

  initialised=true;
}

void ADS131M04::rawChannels(int8_t * channelArrPtr, int8_t channelArrLen, int32_t * outputArrPtr) {
  /* Writes data from the channels specified in channelArr, to outputArr,
     in the correct order.

     channelArr should have values from 0-3, and channelArrLen should be the
     length of that array, starting from 1.
  */
  
  uint32_t rawDataArr[6];

  // Get data
  spiCommFrame(&rawDataArr[0]);
  
  // Save the decoded data for each of the channels
  for (int8_t i = 0; i<channelArrLen; i++) {
    *outputArrPtr = twoCompDeco(rawDataArr[*channelArrPtr+1]);
    outputArrPtr++;
    channelArrPtr++;
  }
}

int32_t ADS131M04::rawChannelSingle(int8_t channel) {
  /* Returns raw value from a single channel
     channel input from 0-3
  */
  
  int32_t outputArr[1];
  int8_t channelArr[1] = {channel};

  rawChannels(&channelArr[0], 1, &outputArr[0]);

  return outputArr[0];
}

bool ADS131M04::writeReg(uint8_t reg, uint16_t data) {
  /* Writes the content of data to the register reg
     Returns true if successful
  */
  
  uint8_t commandPref = 0x06;

  // Make command word using syntax found in data sheet
  uint16_t commandWord = (commandPref<<12) + (reg<<7);

  digitalWrite(csPin, LOW);
  spi->beginTransaction(SPISettings(SCLK_SPD, MSBFIRST, SPI_MODE1));

  spiTransferWord(commandWord);
  
  spiTransferWord(data);

  // Send 4 empty words
  for (uint8_t i=0; i<4; i++) {
    spiTransferWord();
  }

  spi->endTransaction();
  digitalWrite(csPin, HIGH);

  // Get response
  uint32_t responseArr[6];
  spiCommFrame(&responseArr[0]);

  if ( ( (0x04<<12) + (reg<<7) ) == responseArr[0]) {
    return true;
  } else {
    return false;
  }
}

uint16_t ADS131M04::readReg(uint8_t reg) {
  /* Reads the content of single register found at address reg
     Returns register value
  */
  
  uint8_t commandPref = 0x0A;

  // Make command word using syntax found in data sheet
  uint16_t commandWord = (commandPref << 12) + (reg << 7);

  uint32_t responseArr[6];

  // Use first frame to send command
  spiCommFrame(&responseArr[0], commandWord);

  // Read response
  spiCommFrame(&responseArr[0]);

  return responseArr[0] >> 16;
}

uint32_t ADS131M04::spiTransferWord(uint16_t inputData) {
  /* Transfer a 24 bit word
     Data returned is MSB aligned
  */ 

  uint32_t data = spi->transfer(inputData >> 8);
  data <<= 8;
  data |= spi->transfer((inputData<<8) >> 8);
  data <<= 8;
  data |= spi->transfer(0x00);

  return data << 8;
}

void ADS131M04::spiCommFrame(uint32_t * outPtr, uint16_t command) {
  // Saves all the data of a communication frame to an array with pointer outPtr

  digitalWrite(csPin, LOW);

  spi->beginTransaction(SPISettings(SCLK_SPD, MSBFIRST, SPI_MODE1));

  // Send the command in the first word
  *outPtr = spiTransferWord(command);

  // For the next 4 words, just read the data
  for (uint8_t i=1; i < 5; i++) {
    outPtr++;
    *outPtr = spiTransferWord() >> 8;
  }

  // Save CRC bits
  outPtr++;
  *outPtr = spiTransferWord();

  spi->endTransaction();

  digitalWrite(csPin, HIGH);
}

int32_t ADS131M04::twoCompDeco(uint32_t data) {
  // Take the two's complement of the data

  data <<= 8;
  int32_t dataInt = (int)data;

  return dataInt/pow(2,8);
}
