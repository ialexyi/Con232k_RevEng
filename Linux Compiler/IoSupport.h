#define			HOST_CLOCK_BIT			5
#define			HOST_DATA_BIT			6

#define			DEVICE_CLOCK_BIT		2
#define			DEVICE_DATA_BIT			7

#define			RED_LED_BIT				0
#define			GREEN_LED_BIT			1
#define			YELLOW_LED_BIT			2

#define			LED_ON					0
#define			LED_OFF					1

void Set_Port_Bit( volatile uint8_t *PORT_ADDRESS , unsigned char ucBitNumber , unsigned char ucSingleBit );

void SetDeviceToHostDirection(void);
void ReadingFromHostDirection(void);
void ListeningtDirection(void);
void SetHostToDeviceDirection(void);
void WritingToDeviceDirection(void);
