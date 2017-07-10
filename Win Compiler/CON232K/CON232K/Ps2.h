#define		ACKNOWLEDGEMENT			0xFA
#define		KEYBOARD_ID_FIRST		0xAB
#define		KEYBOARD_ID_SECOND		0x83
#define		ECHO_RESPONSE			0xEE
#define		BAT_PASS				0xAA
#define		BAT_FAIL				0xFC

#define		DEVICE_RESET_COMMAND	0xFF
#define		DEVICE_FEEDBACK_ERROR	0xFF
#define		DEVICE_RELEASE_KEY		0xF0

#define		DEVICE_CAPS_LOCK		0x58

#define		DEVICE_LED_SET			0xED
#define		DEVICE_REPEAT_REQ		0xFE

unsigned char Sniffer_PS2_Byte( volatile uint8_t *PORT_ADDRESS , unsigned char ucClockBitNumber , unsigned char ucDataBitNumber , unsigned char *pucDataByte );
void Write_Ps2_Byte( volatile uint8_t *PORT_ADDRESS , unsigned char ucClockBitNumber , unsigned char ucDataBitNumber , unsigned char ucDataByte );

unsigned char Read_Ps2_Byte( volatile uint8_t *READ_PORT_ADDRESS , volatile uint8_t *WRITE_PORT_ADDRESS ,unsigned char ucClockBitNumber , unsigned char ucDataBitNumber , volatile unsigned char *pucDataByte );
void Push_PS2_Byte( volatile uint8_t *READ_PORT_ADDRESS , volatile uint8_t *WRITE_PORT_ADDRESS , unsigned char ucClockBitNumber , unsigned char ucDataBitNumber , unsigned char ucDataByte );

void Write_Ps2_ACK( volatile uint8_t *PORT_ADDRESS , unsigned char ucClockBitNumber , unsigned char ucDataBitNumber );
void Write_Ps2_HOST_REQUEST( volatile uint8_t *PORT_ADDRESS , unsigned char ucClockBitNumber , unsigned char ucDataBitNumber );
