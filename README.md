# ADS131M04-Lib

Library for the ADS131M04 four way ADC, for use with the Arduino framework. Written by Daniele Valentino Bella, for Imperial College London Rocketry.

Click for the [ADS131M04 product page](https://www.ti.com/product/ADS131M04), and the [data sheet](https://www.ti.com/lit/gpn/ads131m04).

## Library Usage

### Initialising the library

#### Class constructor

``` 
ADS131M04(int8_t _csPin, int8_t _clkoutPin, SPIClass* _spi, int8_t _clockCh = 1); 
```

Inputs:

* ```int8_t _csPin```: Chip select pin number

* ```int8_t _clkoutPin```: Pin used to produce the 8.192MHz clock required by the ADC on its CLKIN pin

* ```SPIClass* _spi```: SPIClass object, configured with the appropriate settings and pins

* ```int8_t _clockCh = 1```: LEDC channel used to generate the master clock for the ADC. Defaults to 1.

#### Initialising the ADS131M04

```
void begin(void);
```

Initialises SPI interface, sets the chip select pin to the correct state, and makes the microcontroller output the clock frequency required by the ADS131M04. Must be called in ```void setup()```.

### Reading Channel Data

#### Raw data from multiple channels

```
void rawChannels(int8_t * channelArrPtr, int8_t channelArrLen, int32_t * outputArrPtr);
```

This function sends an empty SPI communication frame, then reads the data from the next communication frame.

Inputs:

* ```int8_t * channelArrPtr```: Pointer to the first element of an array containing the channels desired

* ```int8_t channelArrLen```: Number of elements in the array containing the desired channels

* ```int32_t * outputArrPtr```: Pointer to the first element of an array where the raw data from the channels specified in the channel array will be stored. Note that the order of the channels will be in the order that was specified in the channel array.

#### Raw data from a single channel

```
int32_t rawChannelSingle(int8_t channel);
```

Returns the raw value read from a single channel ```channel```.

It is a wrapper function of the ```rawChannels``` method, thus if multiple channels need to be read, that method will be faster.

### Changing ADC Settings

#### Setting Gain

```
bool setGain(uint8_t log2Gain0 = 0, uint8_t log2Gain1 = 0, uint8_t log2Gain2 = 0, uint8_t log2Gain3 = 0);
```

This function sets the gain of the four channels of the ADC, using its programmable gain amplifier.

```uint8_t log2Gain0 = 0, uint8_t log2Gain1 = 0, uint8_t log2Gain2 = 0, uint8_t log2Gain3 = 0``` are the inputs. These are the log base 2 of the gain to set to each channel.

Function returns true if gain was succesfully set.

Written by Iris Clercq-Roques.

#### Changing Global-Chop mode settings

```
bool globalChop(bool enabled = false, uint8_t log2delay = 4);
```

This function configures the appropriate register such as to set the global-chop settings as defined by the inputs. Other contents of the register remain unchanged.

Inputs:

* ```bool enabled = false```: Whether to enable global-chop mode.

* ```uint8_t log2delay = 4```: logarithm with base 2 of the desired delay in modulator clock periods before measurement begins.  Possible values are between and including 1 and 16, to give delays between 2 and 65536 clock periods respectively. For more information, refer to the datasheet.

Returns true if settings were written succesfully.

### Registers

#### Reading a single register

```
uint16_t readReg(uint8_t reg);
```

Sends a communication frame with the proper command to read the register with address ```reg```, then from the next communication frame returns the value of that register.

#### Writing a single register

```
bool writeReg(uint8_t reg, uint16_t data);
```

Sends a communication frame with the proper command to write ```data``` to the register with address ```reg```. Checks the next communication frame to ensure writing has occurred, and appropriately returns ```true``` or ```false```.
