#define SLAVE_ADDRESS_MCP23S08_W 0x46
#define SLAVE_ADDRESS_MCP23S08_R 0x47
#define CS_SET IOSET0 = (1 << 27)
#define CS_CLR IOCLR0 = (1 << 27)
#define ADDR_MCP23S08_GPIO 0x09

//Global table
const unsigned char MCP23S08_settings[] = {
		0x0F, // IODIR (0x00)
		0x00, // IPOL (0x01)
		0x00, // GPINTEN
		0x00, // DEFVAL
		0x00, // INTCON
		0x04, // IOCON
		0xFF  // GPPU
};

void SPIInit(void);
unsigned char WriteSPIByte(unsigned char byte);
unsigned char SPIMCP23S08SendMultipleBytes(const unsigned int SlaveAddress, const unsigned char Address,
		const unsigned char *pData, const unsigned int NumberOfBytes);
unsigned char MCP23S08_Init(void) {
	return SPIMCP23S08SendMultipleBytes(SLAVE_ADDRESS_MCP23S08_W, 0, MCP23S08_settings,
			sizeof(MCP23S08_settings));
}
unsigned char SPIMCP23S08SendByte(const unsigned int SlaveAddress, const unsigned char Address,
		unsigned char DataByte) {
	return SPIMCP23S08SendMultipleBytes(SlaveAddress, Addres, &DataByte, 1);
}
