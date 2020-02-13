// 
// 
// 

#include "SPIdev.h"


SPIdev::SPIdev()
{
	spi.begin();
	setDataMode(MSBFIRST);
	setClockDivider(SPI_CLOCK_DIV64);
	setBitOrder(SPI_MODE0);
	setChipSelectPin(SS);
}

SPIdev::SPIdev(uint8_t dataMode, uint8_t clockDivider, uint8_t bitOrder, uint8_t chipSelectPin)
{
	spi.begin();
	setDataMode(dataMode);
	setClockDivider(clockDivider);
	setBitOrder(bitOrder);
	setChipSelectPin(chipSelectPin);
}

void SPIdev::write(uint8_t* data, uint8_t size)
{
	chipSelectEnable();
	for (uint8_t i = 0; i < size; i++)
	{
		spi.transfer(data[i]);
	}
	chipSelectDisable();
}

uint8_t SPIdev::read(uint8_t data)
{
	chipSelectEnable();
	uint8_t dataOut = spi.transfer(data);
	chipSelectDisable();
	return dataOut;
}

uint8_t* SPIdev::read(uint8_t* data, uint8_t size)
{
	chipSelectEnable();
	for (int i = 0; i < size; i++)
	{
		data[i] = spi.transfer(data[i]);
	}
	chipSelectDisable();
	return data;
}

uint8_t* SPIdev::read(uint8_t* data,uint8_t*dataBuffer, uint8_t size)
{
	chipSelectEnable();
	for (int i = 0; i < size; i++)
	{
		dataBuffer[i] = spi.transfer(data[i]);
	}
	chipSelectDisable();
	return dataBuffer;
}

void SPIdev::chipSelectEnable()
{
	digitalWrite(chipSelectPin, LOW);
}

void SPIdev::chipSelectDisable()
{
	digitalWrite(chipSelectPin, HIGH);
}


uint8_t SPIdev::getDataMode()
{
	return dataMode;
}

void SPIdev::setDataMode(uint8_t dataMode)
{
	spi.setDataMode(dataMode);
	this->dataMode = dataMode;
}

uint8_t SPIdev::getClockDivider()
{
	return clockDivider;
}

void SPIdev::setClockDivider(uint8_t clockDivider)
{
	spi.setClockDivider(clockDivider);
	this->clockDivider = clockDivider;
}

uint8_t SPIdev::getBitOrder()
{
	return bitOrder;
}

void SPIdev::setBitOrder(uint8_t bitOrder)
{
	if (bitOrder == 1)
	{
		spi.setBitOrder(MSBFIRST);
	}
	else
	{
		spi.setBitOrder(LSBFIRST);
	}
	this->bitOrder = bitOrder;
}

uint8_t SPIdev::getChipSelectPin()
{
	return chipSelectPin;
}

void SPIdev::setChipSelectPin(uint8_t chipSelectPin)
{
	pinMode(chipSelectPin, OUTPUT);
	this->chipSelectPin = chipSelectPin;
}

SPIdev::~SPIdev()
{
}
