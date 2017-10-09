/*
 * SPI.c
 *
 *  Created on: 2017-10-06
 *      Author: embedded
 */

void SPIInit(void) {
	//P0.4 = SCK0, P0.5 = MISO0, P0.6 = MOSI0
	PINSEL0 &=~ (0x3F << 8);
	PINSEL0 |= (0x15 << 8);

	// Initially CS set
	CS_SET;

	//setbit rate 15MHz/S0SPCR == cca. 1.8M

	S0SPCCR = 0x8;
	//Control register: Master mode
	S0SPCR = (1 << 5);
}

unsigned char WriteSPIByte(unsigned char byte) {
	unsigned char spi_status, dummy;

	//Write byte to SPI Data Register
	S0SPDR = byte;

	//Wait for end of byte transmission
	while ((S0SPSR & (1 << 7)) == 0);

	//read SPI status register
	spi_status = S0SPSR;

	//dummy read of SPI data register to clear SPIF (S0SPSR.7) bit
	dummy = S0SPDR;

	return (spi_status & 0x78);
}

unsigned char SPIMCP23S08SendMultipleBytes(const unsigned int SlaveAddress, const unsigned char Address,
		const unsigned char *pData, const unsigned int NumberOfBytes) {
	unsigned int count;
	unsigned char err;

	//Start
	CS_CLR;

	//Write SLaveAddress to SPI
	if((err = WriteSPIByte(SlaveAddress & 0xFF)) != 0) {
		CS_SET;
		return err;
	}

	//Write Address to SPI
	if ((err = WriteSPIByte(Address)) != 0) {
		CS_SET;
		return err;
	}

	//Transmit all bytes
	for (count = 0; count < NumberofBytes; count++) {
		//Write byte
		if ((err = WriteSPIByte(pdata[count])) != 0) {
			CS_SET;
			return err;
		}
	}

	//END
	CS_SET;

	return 0;
}
