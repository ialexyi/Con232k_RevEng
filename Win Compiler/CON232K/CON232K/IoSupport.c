/* Includes */
#include "allheaders.h"


void Set_Port_Bit( volatile uint8_t *PORT_ADDRESS , unsigned char ucBitNumber , unsigned char ucSingleBit )
{
	if ( ucSingleBit > 0 )
		*PORT_ADDRESS |= 1 << ucBitNumber;
	else
		*PORT_ADDRESS &= ~( 1 << ucBitNumber );
}

void SetDeviceToHostDirection(void)			// Sending to Host Clock and Data
{
	cli();

	DDRD =  ( 1 << HOST_DATA_BIT ) | ( 1 << HOST_CLOCK_BIT );
	PORTD = ( 1 << HOST_DATA_BIT ) | ( 1 << HOST_CLOCK_BIT );
}

void ReadingFromHostDirection(void)			// Sending to Host Clock and Reading Data
{
	cli();

	DDRD = ( 1 << HOST_CLOCK_BIT );
	PORTD = ( 1 << HOST_CLOCK_BIT );
}

void ListeningtDirection(void)
{
	cli();

	DDRD = 0x00;
	PORTD = 0x00;

	sei();
}

void SetHostToDeviceDirection(void)
{
	cli();

	DDRD = ( 1 << DEVICE_DATA_BIT ) | ( 1 << DEVICE_CLOCK_BIT );
	PORTD = ( 1 << DEVICE_DATA_BIT ) | ( 1 << DEVICE_CLOCK_BIT );
}

void WritingToDeviceDirection(void)			// Writing to Device Data
{
	cli();

	DDRD = ( 1 << DEVICE_DATA_BIT );
	PORTD = ( 1 << DEVICE_DATA_BIT );
}
