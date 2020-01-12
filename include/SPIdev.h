// SPIdev.h

#ifndef _SPI_h
#define _SPI_h

#include <arduino.h>
#include <SPI.h>

class SPIdev
{
public:
	SPIdev();

	SPIdev(uint8_t dataMode, uint8_t clockDivider, uint8_t bitOrder, uint8_t chipSelectPin);

	void write(uint8_t* data, uint8_t size);
	uint8_t read(uint8_t data);
	uint8_t* read(uint8_t* data, uint8_t size);
	uint8_t* read(uint8_t* data, uint8_t*dataBuffer, uint8_t size);

	uint8_t getDataMode();
	void setDataMode(uint8_t dataMode);

	uint8_t getClockDivider();
	void setClockDivider(uint8_t clockDivider);

	uint8_t getBitOrder();
	void setBitOrder(uint8_t bitOrder);

	uint8_t getChipSelectPin();
	void setChipSelectPin(uint8_t chipSelectPin);

	virtual ~SPIdev();

private:
	SPIClass spi;
	void chipSelectEnable();
	void chipSelectDisable();
	uint8_t dataMode;
	uint8_t clockDivider;
	uint8_t bitOrder;
	uint8_t chipSelectPin;
};

#endif
