// Test code for the ADS131M04 library
// Daniele Valentino Bella

#include "ADS131M04.h"
#include <Arduino.h>
#include "daq_pins.h"
#include <SPI.h>

SPIClass ADCSPI=SPIClass(VSPI);

ADS131M04 ADC=ADS131M04(DAQ_ADC_CS, DAQ_CLKOUT, &ADCSPI);

void printData() {

  int32_t outputArray[4];
  
  int8_t channelArr[4] = {0, 1, 2, 3};

  ADC.rawChannels(&channelArr[0], 4, &outputArray[0]);

  for (int8_t i = 0; i<4; i++) {
    Serial.print(outputArray[i]);
    Serial.print(" ");

  }
  Serial.println(" ");
}
  /*
  uint32_t outputArray[6];
  ADC.spiCommFrame(&outputArray[0]);


  //Serial.println(outputArray[3]);

  //Serial.print(" ");

  Serial.print(outputArray[0]);
  Serial.print(" ");

  for (uint8_t i=1; i<5; i++) {
    Serial.print(ADC.twoCompDeco(outputArray[i]));
    Serial.print(" ");
  }
  Serial.print(outputArray[5]);
  Serial.print(" ");
  Serial.println();
}
*/

void setup() {
  Serial.begin(115200);

  //Initialise hardware SPI
  ADCSPI.begin(-1, -1, -1, -1);

  ADC.begin();
  Serial.println("Initialised!");

  // Set chip select pins to high
  pinMode(DAQ_TC_CS1, OUTPUT);
  pinMode(DAQ_TC_CS2, OUTPUT);
  pinMode(DAQ_TC_CS3, OUTPUT);
  pinMode(DAQ_TC_CS4, OUTPUT);

  digitalWrite(DAQ_TC_CS1, HIGH);
  digitalWrite(DAQ_TC_CS2, HIGH);
  digitalWrite(DAQ_TC_CS3, HIGH);
  digitalWrite(DAQ_TC_CS4, HIGH);

  /*

  // Try to read every single register
  for (uint8_t i=0x00; i<=0x3F; i++) {
    Serial.print("Result for: ");
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(ADC.readReg(i));
  }
  
  // Try putting to sleep and waking it up
  printData();
  printData();
  printData();
  
  Serial.println("Putting to sleep...");
  ADC.sendCommand(0x0022);

  printData();
  printData();
  printData();

  Serial.println("Waking up... ");
  ADC.sendCommand(0x0033);
  printData();
  printData();
  printData();
  */
}

void loop() {
  /*
  printData();

  delay(100);
*/
//  printData();
  // Try writing the gain; and then reading that register
  printData();
  printData();
  printData();
/*
  Serial.print("Writing: ");
  Serial.println(ADC.setGain(3,3,3,3));
  /*
  Serial.println(ADC.writeReg(0x04,0x3333));
  Serial.print("Reading: ");
  Serial.println(ADC.readReg(0x04));
  Serial.println("#######################");

  delay(1000);

  printData();
  printData();
  printData();

  Serial.print("Writing: ");
  Serial.println(ADC.setGain());
  */
  /*
  Serial.println(ADC.writeReg(0x04,0x0000));
  Serial.print("Reading: ");
  Serial.println(ADC.readReg(0x04));
  Serial.println("#######################");
*/
  //delay(1000);
  // Try putting to sleep and waking it up
  /*
  printData();
  printData();
  printData();
  Serial.println("Putting to sleep...");
  ADC.sendCommand(0x0022);
  printData();
  printData();
  printData();

  Serial.println("Waking up... ");
  ADC.sendCommand(0x0033);
  printData();
  printData();
  printData();
  */
}
