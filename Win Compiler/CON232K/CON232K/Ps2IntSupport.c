#include "allheaders.h"
#include "Ps2IntSupport.h"
#include "IoSupport.h"

static unsigned char DEV_TO_HOST_Ps2Buf[PS2_BUFFER_SIZE];
static volatile unsigned char DEV_TO_HOST_Ps2Head;
static volatile unsigned char DEV_TO_HOST_Ps2Tail;

static unsigned char HOST_TO_DEV_Ps2Buf[PS2_BUFFER_SIZE];
static volatile unsigned char HOST_TO_DEV_Ps2Head;
static volatile unsigned char HOST_TO_DEV_Ps2Tail;


//--------------- Device Side Interrupts --------------------//
void Ps2Init(void)
{
	unsigned char x = 0;

	DEV_TO_HOST_Ps2Head = x;
	DEV_TO_HOST_Ps2Tail = x;

	HOST_TO_DEV_Ps2Head = x;
	HOST_TO_DEV_Ps2Tail = x;

	EnableDeviceInterrupt(1);

    PCICR |= (1 << PCIE2);    // set PCIE2 to enable PCMSK2 scan
    PCMSK2 |= (1 << PCINT22);  // set PCINT22 to trigger an interrupt on state change
}

void EnableDeviceInterrupt( unsigned char Enable )
{
	if ( Enable > 0 )
	{
		EIMSK |= ( 1 << INT0 );  //Enable INT0
	    EICRA |= ( 1 << ISC01 ); //Trigger on falling edge of INT0
	}
	else
	{
		EIMSK = 0;  //Disable INT0
	    EICRA = 0;
	}
}

ISR(INT0_vect)
{
	unsigned char		CurrentReceivedByte		=	0,
						CurrentBufferIndex		=	0;

	unsigned char		Error					=	2;

	cli();

	Error = Sniffer_PS2_Byte( &PIND , DEVICE_CLOCK_BIT , DEVICE_DATA_BIT , &CurrentReceivedByte );

	if ( Error == 0 )
	{
		CurrentBufferIndex = ( DEV_TO_HOST_Ps2Head + 1 ) & PS2_BUFFER_MASK;
		DEV_TO_HOST_Ps2Head = CurrentBufferIndex;      /* Store new index */

		if ( CurrentBufferIndex == DEV_TO_HOST_Ps2Tail )
		{

		}

		DEV_TO_HOST_Ps2Buf[CurrentBufferIndex] = CurrentReceivedByte; /* Store received data in buffer */

		Set_Port_Bit( &PORTC , GREEN_LED_BIT , LED_ON );								// Green LED ON ( Device Sending )
	}

	sei();
}

unsigned char IsDataInPs2SnifferBuffer( void )
{
	return ( DEV_TO_HOST_Ps2Head != DEV_TO_HOST_Ps2Tail ); /* Return 0 (FALSE) if the receive buffer is empty */
}

unsigned char GetDataFromPs2SnifferBuffer( void )
{
	unsigned char CurrentBufferIndex;

	CurrentBufferIndex = ( DEV_TO_HOST_Ps2Tail + 1 ) & PS2_BUFFER_MASK;/* Calculate buffer index */

	DEV_TO_HOST_Ps2Tail = CurrentBufferIndex;

	return DEV_TO_HOST_Ps2Buf[CurrentBufferIndex];  /* Return data */
}

//--------------- Host Side Interrupts --------------------//

ISR (PCINT2_vect)
{
	volatile unsigned char			DataBit												=	0;
	volatile unsigned char			CurrentReceivedByte									=	0,
										CurrentBufferIndex									=	0;

	volatile unsigned char			Error												=	2;

	DataBit = ( PIND >> HOST_DATA_BIT ) & 0x01;

	if ( DataBit == 0 )
	{
		Set_Port_Bit( &PORTC , YELLOW_LED_BIT , LED_OFF );

		ReadingFromHostDirection();

		Error = Read_Ps2_Byte( &PIND, &PORTD , HOST_CLOCK_BIT , HOST_DATA_BIT , &CurrentReceivedByte );

		SetDeviceToHostDirection();

		Write_Ps2_ACK( &PORTD , HOST_CLOCK_BIT , HOST_DATA_BIT );

		if ( Error == 0 )
		{
			CurrentBufferIndex = ( HOST_TO_DEV_Ps2Head + 1 ) & PS2_BUFFER_MASK;
			HOST_TO_DEV_Ps2Head = CurrentBufferIndex;      /* Store new index */

			if ( CurrentBufferIndex == HOST_TO_DEV_Ps2Tail )
			{

			}

			HOST_TO_DEV_Ps2Buf[CurrentBufferIndex] = CurrentReceivedByte; /* Store received data in buffer */
		}

		ListeningtDirection();
	}
}

unsigned char IsDataInPs2HostBuffer( void )
{
	return ( HOST_TO_DEV_Ps2Head != HOST_TO_DEV_Ps2Tail ); /* Return 0 (FALSE) if the receive buffer is empty */
}

unsigned char GetDataFromPs2HostBuffer( void )
{
	unsigned char CurrentBufferIndex;

	CurrentBufferIndex = ( HOST_TO_DEV_Ps2Tail + 1 ) & PS2_BUFFER_MASK;/* Calculate buffer index */

	HOST_TO_DEV_Ps2Tail = CurrentBufferIndex;

	return HOST_TO_DEV_Ps2Buf[CurrentBufferIndex];  /* Return data */
}
