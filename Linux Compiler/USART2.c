/* Includes */
#include "allheaders.h"

/* Static Variables */
static unsigned char USART_RxBuf[USART_RX_BUFFER_SIZE];
static volatile unsigned char USART_RxHead;
static volatile unsigned char USART_RxTail;
static unsigned char USART_TxBuf[USART_TX_BUFFER_SIZE];
static volatile unsigned char USART_TxHead;
static volatile unsigned char USART_TxTail;

/* Initialize USART */
void USART_Init( unsigned int baudrate )
{
	unsigned char x;

	/* Set the baud rate */
	UBRR0H = (unsigned char) (baudrate>>8);
	UBRR0L = (unsigned char) baudrate;

	UCSR0B |= (1 << RXEN0) | (1 << TXEN0); 						// Turn on the transmission and reception circuitry
    UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)|(0<<UPM01)|(0<<UPM00)|(0<<USBS0)|(0<<UCSZ02)|(1<<UCSZ01)|(1<<UCSZ00);

    UCSR0B |= ( 1 << RXCIE0 );									// Enable UART receiver Interrupt

    //UCSR0A |= ( 1 << U2X0 );
	/* Flush receive buffer */
	x = 0; 			    

	USART_RxTail = x;
	USART_RxHead = x;
	USART_TxTail = x;
	USART_TxHead = x;
}

/* Interrupt handlers */
ISR( USART_RX_vect )
{
	unsigned char data;
	unsigned char tmphead;

	Set_Port_Bit( &PORTC , RED_LED_BIT , LED_ON );			// Red LED ON ( Rs232 Sending )

	/* Read the received data */
	data = UDR0;
	/* Calculate buffer index */
	tmphead = ( USART_RxHead + 1 ) & USART_RX_BUFFER_MASK;
	USART_RxHead = tmphead;      /* Store new index */

	if ( tmphead == USART_RxTail )
	{
		/* ERROR! Receive buffer overflow */
	}

	USART_RxBuf[tmphead] = data; /* Store received data in buffer */
}

ISR( USART_UDRE_vect )
{
	unsigned char tmptail;

	/* Check if all data is transmitted */
	if ( USART_TxHead != USART_TxTail )
	{
		/* Calculate buffer index */
		tmptail = ( USART_TxTail + 1 ) & USART_TX_BUFFER_MASK;
		USART_TxTail = tmptail;      /* Store new index */
	
		UDR0 = USART_TxBuf[tmptail];  /* Start transmition */
	}
	else
	{
		UCSR0B &= ~(1<<UDRIE0);         /* Disable UDRE interrupt */
	}
}

/* Read and write functions */
unsigned char USART_Receive( void )
{
	unsigned char tmptail;
	
	while ( USART_RxHead == USART_RxTail );  /* Wait for incomming data */
		
	tmptail = ( USART_RxTail + 1 ) & USART_RX_BUFFER_MASK;/* Calculate buffer index */
	
	USART_RxTail = tmptail;                /* Store new index */
	
	return USART_RxBuf[tmptail];  /* Return data */
}

void USART_Transmit( unsigned char data )
{
	unsigned char tmphead;
	/* Calculate buffer index */
	tmphead = ( USART_TxHead + 1 ) & USART_TX_BUFFER_MASK; /* Wait for free space in buffer */
	while ( tmphead == USART_TxTail );

	USART_TxBuf[tmphead] = data;           /* Store data in buffer */
	USART_TxHead = tmphead;                /* Store new index */

	UCSR0B |= (1<<UDRIE0);                    /* Enable UDRE interrupt */
}

unsigned char DataInReceiveBuffer( void )
{
	return ( USART_RxHead != USART_RxTail ); /* Return 0 (FALSE) if the receive buffer is empty */
}

unsigned char GetDataFromReceiveBuffer( void )
{
	unsigned char tmptail;

	tmptail = ( USART_RxTail + 1 ) & USART_RX_BUFFER_MASK;/* Calculate buffer index */

	USART_RxTail = tmptail;

	return USART_RxBuf[tmptail];  /* Return data */
}

unsigned char	DirectReceiveData()
{
	unsigned char ReceivedByte;

	UCSR0B &= ~( 1 << RXCIE0 );       							// Disable UART receiver interrupt

	while ((UCSR0A & (1 << RXC0)) == 0) {};

	ReceivedByte = UDR0;

	UCSR0B |= ( 1 << RXCIE0 );									// Enable UART receiver Interrupt

	return ReceivedByte;
}

void DirectSendData( unsigned char ByteToSend )
{
	while ((UCSR0A & (1 << UDRE0)) == 0) {};

	UDR0 = ByteToSend;
}

void DirectSendString( char *pStringData )
{
	int		iCurrentIndex		=	0;

	while ( pStringData[iCurrentIndex] )
	{
		DirectSendData( pStringData[iCurrentIndex] );

		iCurrentIndex++;
	};
}
