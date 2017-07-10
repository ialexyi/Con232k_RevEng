/* Includes */
#include "allheaders.h"
#include "Ps2.h"

#define		IDLE_PERIOD_uSec			60UL
#define		CLOCK_PERIOD_uSec			10UL
#define		DOUBLE_CLOCK_PERIOD_uSec	(CLOCK_PERIOD_uSec * 2UL)
#define		HALF_CLOCK_PERIOD_uSec		(CLOCK_PERIOD_uSec / 2UL)

unsigned char Sniffer_PS2_Byte( volatile uint8_t *PORT_ADDRESS , unsigned char ucClockBitNumber , unsigned char ucDataBitNumber , unsigned char *pucDataByte )
{
	volatile unsigned char			index												=	0;

	volatile unsigned char			ClockBit											=	0,
										DataBit												=	0;

	volatile unsigned char			BitIndex											=	0,
										BitFound											=	0;

	volatile unsigned char			vReceiveBuffer[10]									=	{0},
										ParityBitError										=	0,
										PortReadData										=	0,
										ReceivedByte										=	0;

	for ( BitIndex = 0; BitIndex < 10 ; BitIndex++ )
	{
		BitFound = 0;

		for( index = 0 ; index < 40 ; index++ )
		{
			PortReadData = *PORT_ADDRESS;

			ClockBit = ( PortReadData >> ucClockBitNumber ) & 0x01;
			DataBit = ( PortReadData >> ucDataBitNumber ) & 0x01;

			if ( ClockBit == 1 )
			{
				if ( BitFound == 0 )
					continue;
				else
					break;
			}

			BitFound = 1;
			vReceiveBuffer[BitIndex] = DataBit;
		};
	}

	ParityBitError = 1;

	for( BitIndex = 0 ; BitIndex < 10 ; BitIndex++ )
	{
		if ( vReceiveBuffer[BitIndex] )
			ParityBitError = !ParityBitError;
	}

	for( BitIndex = 0 ; BitIndex < 8 ; BitIndex++ )
		if ( vReceiveBuffer[BitIndex+1] )
			ReceivedByte |= ( 1 << BitIndex );

	*pucDataByte = ReceivedByte;

	return ParityBitError;
}

unsigned char Read_Ps2_Byte( volatile uint8_t *READ_PORT_ADDRESS , volatile uint8_t *WRITE_PORT_ADDRESS ,unsigned char ucClockBitNumber , unsigned char ucDataBitNumber , volatile unsigned char *pucDataByte )
{
	volatile unsigned char			DataBit												=	0;

	volatile unsigned char			BitIndex											=	0;

	volatile unsigned char			vReceiveBuffer[11]									=	{0},
										ParityBitError										=	0,
										ReceivedByte										=	0;

	ParityBitError = 1;

	for( BitIndex = 0 ; BitIndex < 10 ; BitIndex++ )
	{
		DataBit = ( *READ_PORT_ADDRESS >> ucDataBitNumber ) & 0x01;
		vReceiveBuffer[BitIndex] = DataBit;

		if ( DataBit > 0 )
		{
			ParityBitError = !ParityBitError;

			if (( BitIndex > 0 ) && ( BitIndex < 9 ))
				ReceivedByte |= ( 1 << ( BitIndex - 1 ));
		}

		Set_Port_Bit( WRITE_PORT_ADDRESS , ucClockBitNumber , 1 );
		_delay_us(CLOCK_PERIOD_uSec);
		Set_Port_Bit( WRITE_PORT_ADDRESS , ucClockBitNumber , 0 );
		_delay_us(CLOCK_PERIOD_uSec);
	}

	*pucDataByte = ReceivedByte;

	return ParityBitError;
}

void Write_Ps2_ACK( volatile uint8_t *PORT_ADDRESS , unsigned char ucClockBitNumber , unsigned char ucDataBitNumber )
{
	Set_Port_Bit( PORT_ADDRESS , ucClockBitNumber , 1 );
	Set_Port_Bit( PORT_ADDRESS , ucDataBitNumber , 1 );
	_delay_us(CLOCK_PERIOD_uSec);
	Set_Port_Bit( PORT_ADDRESS , ucClockBitNumber , 0 );
	_delay_us(CLOCK_PERIOD_uSec);
	Set_Port_Bit( PORT_ADDRESS , ucClockBitNumber , 1 );
	Set_Port_Bit( PORT_ADDRESS , ucDataBitNumber , 0 );
	_delay_us(CLOCK_PERIOD_uSec);
	Set_Port_Bit( PORT_ADDRESS , ucClockBitNumber , 0 );
	_delay_us(CLOCK_PERIOD_uSec);
	Set_Port_Bit( PORT_ADDRESS , ucClockBitNumber , 1 );
	Set_Port_Bit( PORT_ADDRESS , ucDataBitNumber , 1 );
}

void Write_Ps2_Byte( volatile uint8_t *PORT_ADDRESS , unsigned char ucClockBitNumber , unsigned char ucDataBitNumber , unsigned char ucDataByte )
{
	volatile unsigned char			BitIndex											=	0,
										ByteIndex											=	0;

	volatile unsigned char			vSendBuffer[11]										=	{0},
										ParityOddBit										=	0,
										PrepareData											=	0;

	ParityOddBit = 1;

	for( BitIndex = 0 ; BitIndex < 8 ; BitIndex++ )
	{
		PrepareData = ( ucDataByte >> BitIndex ) & 0x01;

		if ( PrepareData )
			ParityOddBit = !ParityOddBit;

		vSendBuffer[BitIndex+1] = PrepareData;
	}

	vSendBuffer[0] = 0;
	vSendBuffer[9] = ParityOddBit;
	vSendBuffer[10] = 1;

	for( ByteIndex = 0 ; ByteIndex < 11 ; ByteIndex++ )
	{
		if ( ByteIndex )
			_delay_us(HALF_CLOCK_PERIOD_uSec);

		Set_Port_Bit( PORT_ADDRESS , ucDataBitNumber , vSendBuffer[ByteIndex] );
		_delay_us(HALF_CLOCK_PERIOD_uSec);
		Set_Port_Bit( PORT_ADDRESS , ucClockBitNumber , 0 );
		_delay_us(CLOCK_PERIOD_uSec);
		Set_Port_Bit( PORT_ADDRESS , ucClockBitNumber , 1 );
	}
}


void Push_PS2_Byte( volatile uint8_t *READ_PORT_ADDRESS , volatile uint8_t *WRITE_PORT_ADDRESS , unsigned char ucClockBitNumber , unsigned char ucDataBitNumber , unsigned char ucDataByte )
{
	volatile unsigned char			index												=	0;

	volatile unsigned char			ClockBit											=	0;

	volatile unsigned char			BitIndex											=	0,
										BitFound											=	0;

	volatile unsigned char			vSendBuffer[11]										=	{0},
										PortReadData										=	0;

	unsigned char						ParityOddBit										=	0;

	ParityOddBit = 1;

	for( BitIndex = 0 ; BitIndex < 8 ; BitIndex++ )
	{
		vSendBuffer[BitIndex+1] = ( ucDataByte >> BitIndex ) & 0x01;

		if ( vSendBuffer[BitIndex+1] )
			ParityOddBit = !ParityOddBit;
	}

	vSendBuffer[9] = ParityOddBit;
	vSendBuffer[10] = 1;

	for ( BitIndex = 0; BitIndex < 11 ; BitIndex++ )
	{
		BitFound = 0;

		for( index = 0 ; index < 100 ; index++ )
		{
			PortReadData = *READ_PORT_ADDRESS;

			ClockBit = ( PortReadData >> ucClockBitNumber ) & 0x01;

			if ( ClockBit == 1 )
			{
				if ( BitFound == 0 )
				{
					Set_Port_Bit( WRITE_PORT_ADDRESS , ucDataBitNumber , vSendBuffer[BitIndex] );
					continue;
				}
				else
					break;
			}

			BitFound = 1;
		};
	}

	return;
}

void Write_Ps2_HOST_REQUEST( volatile uint8_t *PORT_ADDRESS , unsigned char ucClockBitNumber , unsigned char ucDataBitNumber )
{
	Set_Port_Bit( PORT_ADDRESS , ucDataBitNumber , 1 );
	Set_Port_Bit( PORT_ADDRESS , ucClockBitNumber , 0 );
	_delay_us(IDLE_PERIOD_uSec);
	Set_Port_Bit( PORT_ADDRESS , ucDataBitNumber , 0 );
	_delay_us(CLOCK_PERIOD_uSec);
	Set_Port_Bit( PORT_ADDRESS , ucClockBitNumber , 1 );
}
