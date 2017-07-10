#include "allheaders.h"

#define UBRR_VALUE_19200 	(((F_CPU / (19200UL * 16UL))) - 1)
#define UBRR_VALUE_9600 	(((F_CPU / (9600UL * 16UL))) - 1)
#define UBRR_VALUE_4800 	(((F_CPU / (4800UL * 16UL))) - 1)
#define UBRR_VALUE_2400 	(((F_CPU / (2400UL * 16UL))) - 1)

void SystemInit(void)
{
	DDRC = 0x0F;
}

int main( void )
{
	volatile unsigned short					BoudRateArray[4]						=	{UBRR_VALUE_19200,UBRR_VALUE_9600,UBRR_VALUE_4800,UBRR_VALUE_2400};
	volatile unsigned char					BoudrateModeIndex						=	0;
	volatile unsigned char					CurrentReceivedByte						=	0,
												CommandReceivedByte						=	0,
												PreviousCommandByte						=	0,
												KeyCodeQuantity							=	0,
												RepeatLastSend							=	0,
												LastSentByte							=	0,
												iKeyCodeIndex							=	0,
												DeviceAlive								=	0;

	volatile unsigned char					StoreLedsState							=	0,
												StoreLedsStateUpdated					=	0,
												StoreScanCodeState						=	0,
												StoreScanCodeStateUpdated				=	0,
												StoreAutoRateState 						= 	0,
												StoreAutoRateStateUpdated 				=	0,
												StoreEnableStateUpdated 				=	0,
												StoreDisableStateUpdated 				=	0;

	volatile unsigned char 					CodeArray[MAX_NUMBER_OF_CODE_KEYS]		=	{0};

	SystemInit();

	BoudrateModeIndex = ( PORTB >> 6 ) & 0x03;					// Read Baud Rate configuration from Port B (4,5)

	USART_Init( BoudRateArray[BoudrateModeIndex] );

	Ps2Init();

	PORTC = 0x00;												// Set All LEDs

	//Send Reset Command to Device
	SetHostToDeviceDirection();
	Write_Ps2_HOST_REQUEST( &PORTD , DEVICE_CLOCK_BIT  , DEVICE_DATA_BIT );
	WritingToDeviceDirection();
	Push_PS2_Byte( &PIND , &PORTD , DEVICE_CLOCK_BIT  , DEVICE_DATA_BIT , DEVICE_RESET_COMMAND );
	LastSentByte = DEVICE_RESET_COMMAND;

	_delay_ms(1000);

	//Send trigger to Host
	SetDeviceToHostDirection();
	Write_Ps2_Byte( &PORTD , HOST_CLOCK_BIT , HOST_DATA_BIT , ACKNOWLEDGEMENT );

	PORTC = 0x07;												// Clear All LEDs

	//Enable global interrupts
	sei();

	Set_Port_Bit( &PORTC , YELLOW_LED_BIT , LED_ON );								// Yellow LED ON ( Ready )

	ListeningtDirection();

	while (1) 													// Loop forever
	{
		if ( iKeyCodeIndex >= KeyCodeQuantity ) // Disable Device for Sending to host
		{
			/* If Led data change send to device first command byte */
			if ( StoreLedsStateUpdated == 1 )
			{
				SetHostToDeviceDirection();
				Write_Ps2_HOST_REQUEST( &PORTD , DEVICE_CLOCK_BIT  , DEVICE_DATA_BIT );
				WritingToDeviceDirection();
				Push_PS2_Byte( &PIND , &PORTD , DEVICE_CLOCK_BIT  , DEVICE_DATA_BIT , DEVICE_LED_SET );
				ListeningtDirection();

				LastSentByte = DEVICE_LED_SET;
				StoreLedsStateUpdated++;
			}

			/* Process data received from Device */
			if ( IsDataInPs2SnifferBuffer())
			{
				DeviceAlive = 1;
				CurrentReceivedByte = GetDataFromPs2SnifferBuffer();

				switch(CurrentReceivedByte)
				{
					case ACKNOWLEDGEMENT:

							if ( StoreLedsStateUpdated == 2 )
							{ // Send second Led Data contain byte
								SetHostToDeviceDirection();
								Write_Ps2_HOST_REQUEST( &PORTD , DEVICE_CLOCK_BIT  , DEVICE_DATA_BIT );
								WritingToDeviceDirection();
								Push_PS2_Byte( &PIND , &PORTD , DEVICE_CLOCK_BIT  , DEVICE_DATA_BIT , StoreLedsState );
								LastSentByte = StoreLedsState;
								StoreLedsStateUpdated++;
							}

							if ( StoreLedsStateUpdated == 3 )
								StoreLedsStateUpdated = 0;

							break;

					case DEVICE_REPEAT_REQ:

							SetHostToDeviceDirection();
							Write_Ps2_HOST_REQUEST( &PORTD , DEVICE_CLOCK_BIT  , DEVICE_DATA_BIT );
							WritingToDeviceDirection();
							Push_PS2_Byte( &PIND , &PORTD , DEVICE_CLOCK_BIT  , DEVICE_DATA_BIT , LastSentByte );

							break;

					case DEVICE_FEEDBACK_ERROR:
					case BAT_PASS:
					case BAT_FAIL:
					case 0:
							if ( StoreLedsStateUpdated == 3 )
								StoreLedsStateUpdated = 2;

							break;
					default:
							SetDeviceToHostDirection();
							Write_Ps2_Byte( &PORTD , HOST_CLOCK_BIT , HOST_DATA_BIT , CurrentReceivedByte );
							RepeatLastSend = CurrentReceivedByte;
							break;
				}

				ListeningtDirection();

				Set_Port_Bit( &PORTC , GREEN_LED_BIT , LED_OFF );								// Green LED OFF ( Device Sending )
			}

			/* Pop Single Byte from RS232 and code it to Scan code*/
			if ( DataInReceiveBuffer())
			{
				CurrentReceivedByte = GetDataFromReceiveBuffer();

				KeyCodeQuantity = GetScanCode( CurrentReceivedByte , CodeArray );

				iKeyCodeIndex = 0;

				Set_Port_Bit( &PORTC , RED_LED_BIT , LED_OFF );								// Red LED OFF ( Rs232 Sending )
			}
		}
		/* If is not received request from host send scan code to host*/
		if (( iKeyCodeIndex < KeyCodeQuantity ) && ( IsDataInPs2HostBuffer() == 0 ))
		{
			//if (( RepeatLastSend == 0xF0 ) || ( RepeatLastSend == 0xE0 ))
			//	_delay_ms(200);
			//else
				_delay_ms(50);

			SetDeviceToHostDirection();

			Write_Ps2_Byte( &PORTD , HOST_CLOCK_BIT , HOST_DATA_BIT , CodeArray[iKeyCodeIndex] );

			RepeatLastSend = CodeArray[iKeyCodeIndex];

			//DirectSendData(RepeatLastSend);

			iKeyCodeIndex++;

			ListeningtDirection();
		}

		/* Process data received from Host */
		while ( IsDataInPs2HostBuffer() )
		{
			CommandReceivedByte = GetDataFromPs2HostBuffer();

			SetDeviceToHostDirection();

			if ( CommandReceivedByte > 0x7F )
			{
				switch(CommandReceivedByte)
				{
					case 0xF2:// This command is used to read the keyboard ID. Upon receipt, the keyboard responds with the acknowledge response code (FAh), followed by two bytes that constitute the keyboard's ID – ABh and 83h.
								_delay_ms(50);
								Write_Ps2_Byte( &PORTD , HOST_CLOCK_BIT , HOST_DATA_BIT , ACKNOWLEDGEMENT );
								_delay_ms(50);
								Write_Ps2_Byte( &PORTD , HOST_CLOCK_BIT , HOST_DATA_BIT , KEYBOARD_ID_FIRST );
								_delay_ms(50);
								Write_Ps2_Byte( &PORTD , HOST_CLOCK_BIT , HOST_DATA_BIT , KEYBOARD_ID_SECOND );
								break;
					case 0xEE://This is the echo command. Upon receipt, the keyboard transmits the echo response code (EEh).
								_delay_ms(50);
								Write_Ps2_Byte( &PORTD , HOST_CLOCK_BIT , HOST_DATA_BIT , ECHO_RESPONSE );
								break;
					case 0xED://This command is used to turn the keyboard's LED indicators ON or OFF
								_delay_ms(50);
								Write_Ps2_Byte( &PORTD , HOST_CLOCK_BIT , HOST_DATA_BIT , ACKNOWLEDGEMENT );
								break;
					case 0xF0://This command is used to select the scan code set to be used for the keyboard. Every key on the keyboard has a scan code associated with it and it is this code that is sent to the host CPU when the key is pressed. The keyboard sends an acknowledgement (response code FAh) and then waits for another byte of data from the host, that specifies the particular scan code set to be used.
								_delay_ms(50);
								Write_Ps2_Byte( &PORTD , HOST_CLOCK_BIT , HOST_DATA_BIT , ACKNOWLEDGEMENT );
								break;
					case 0xF3://This command is used to set the auto-repeat rate. This is the rate at which the scan code for a depressed key is sent when that key has been held depressed for a length of time exceeding a specified delay. Upon receipt of the command, the keyboard issues the acknowledge response code (FAh) and then waits for another byte of data from the host, that specifies the auto-repeat rate and also the delay before auto-repeat comes into effect,
								_delay_ms(50);
								Write_Ps2_Byte( &PORTD , HOST_CLOCK_BIT , HOST_DATA_BIT , ACKNOWLEDGEMENT );
								break;
					case 0xF4:// This command is used to enable the keyboard. Upon receipt of the command, the keyboard's output buffer is flushed and keyboard scanning (of the PSDATA and PSCLK lines) is enabled. The keyboard responds by sending the acknowledgement code (FAh).
								StoreEnableStateUpdated = 1;
								break;
					case 0xF5://This command is used to disable the keyboard. Upon receipt of the command, the keyboard is reset. The keyboard issues the acknowledgement code (FAh) and then keyboard scanning (of the PSDATA and PSCLK lines) is disabled. The keyboard remains in this state, waiting for another command from the host CPU.
								StoreDisableStateUpdated = 1;
								break;
					case 0xFE://This is the resend command and is used when the host requires the keyboard to retransmit the last byte of data sent. Upon receipt, the keyboard responds with the acknowledge response code (FAh), then proceeds to transmit the previously sent byte of data.
								_delay_ms(50);
								Write_Ps2_Byte( &PORTD , HOST_CLOCK_BIT , HOST_DATA_BIT , RepeatLastSend );
								break;
					case 0xFF://This command is used to reset the mouse. Upon receipt of the command, the mouse sends the acknowledge response code (FAh). The mouse is reset and subsequently performs its power-on Basic Assurance Test (BAT). During this test, default values are loaded for the sampling rate, resolution and scaling, and data reporting is disabled. Depending on the result of the test, the mouse will either send the 'Passed' code (AAh) or the 'Failed' code (FCh).
					default:
								break;
				}
			}
			else
			{
				switch(PreviousCommandByte)
				{
					case 0xF2:// This command is used to read the keyboard ID. Upon receipt, the keyboard responds with the acknowledge response code (FAh), followed by two bytes that constitute the keyboard's ID – ABh and 83h.
								_delay_ms(50);
								Write_Ps2_Byte( &PORTD , HOST_CLOCK_BIT , HOST_DATA_BIT , DEVICE_FEEDBACK_ERROR );
								break;
					case 0xEE://This is the echo command. Upon receipt, the keyboard transmits the echo response code (EEh).
								_delay_ms(50);
								Write_Ps2_Byte( &PORTD , HOST_CLOCK_BIT , HOST_DATA_BIT , DEVICE_FEEDBACK_ERROR );
								break;
					case 0xED://This command is used to turn the keyboard's LED indicators ON or OFF
								StoreLedsState = CommandReceivedByte;
								StoreLedsStateUpdated = 1;
								break;
					case 0xF0://This command is used to select the scan code set to be used for the keyboard. Every key on the keyboard has a scan code associated with it and it is this code that is sent to the host CPU when the key is pressed. The keyboard sends an acknowledgement (response code FAh) and then waits for another byte of data from the host, that specifies the particular scan code set to be used.
								if ( CommandReceivedByte & 0x03 )
								{
									StoreScanCodeState = CommandReceivedByte;
									StoreScanCodeStateUpdated = 1;
								}
								else
								{
									_delay_ms(50);
									Write_Ps2_Byte( &PORTD , HOST_CLOCK_BIT , HOST_DATA_BIT , StoreScanCodeState );
								}
								break;
					case 0xF3://This command is used to set the auto-repeat rate. This is the rate at which the scan code for a depressed key is sent when that key has been held depressed for a length of time exceeding a specified delay. Upon receipt of the command, the keyboard issues the acknowledge response code (FAh) and then waits for another byte of data from the host, that specifies the auto-repeat rate and also the delay before auto-repeat comes into effect,
								StoreAutoRateState = CommandReceivedByte;
								StoreAutoRateStateUpdated = 1;
								break;
					case 0xF4:// This command is used to enable the keyboard. Upon receipt of the command, the keyboard's output buffer is flushed and keyboard scanning (of the PSDATA and PSCLK lines) is enabled. The keyboard responds by sending the acknowledgement code (FAh).
								_delay_ms(50);
								Write_Ps2_Byte( &PORTD , HOST_CLOCK_BIT , HOST_DATA_BIT , DEVICE_FEEDBACK_ERROR );
								break;
					case 0xF5://This command is used to disable the keyboard. Upon receipt of the command, the keyboard is reset. The keyboard issues the acknowledgement code (FAh) and then keyboard scanning (of the PSDATA and PSCLK lines) is disabled. The keyboard remains in this state, waiting for another command from the host CPU.
								_delay_ms(50);
								Write_Ps2_Byte( &PORTD , HOST_CLOCK_BIT , HOST_DATA_BIT , DEVICE_FEEDBACK_ERROR );
								break;
					case 0xFE://This is the resend command and is used when the host requires the keyboard to retransmit the last byte of data sent. Upon receipt, the keyboard responds with the acknowledge response code (FAh), then proceeds to transmit the previously sent byte of data.
								_delay_ms(50);
								Write_Ps2_Byte( &PORTD , HOST_CLOCK_BIT , HOST_DATA_BIT , DEVICE_FEEDBACK_ERROR );
								break;
					case 0xFF://This command is used to reset the mouse. Upon receipt of the command, the mouse sends the acknowledge response code (FAh). The mouse is reset and subsequently performs its power-on Basic Assurance Test (BAT). During this test, default values are loaded for the sampling rate, resolution and scaling, and data reporting is disabled. Depending on the result of the test, the mouse will either send the 'Passed' code (AAh) or the 'Failed' code (FCh).
								_delay_ms(50);
								Write_Ps2_Byte( &PORTD , HOST_CLOCK_BIT , HOST_DATA_BIT , DEVICE_FEEDBACK_ERROR );
								break;
					default:
								Write_Ps2_Byte( &PORTD , HOST_CLOCK_BIT , HOST_DATA_BIT , DEVICE_FEEDBACK_ERROR );
								break;
				}
			}

			ListeningtDirection();

			PreviousCommandByte = CommandReceivedByte;

			Set_Port_Bit( &PORTC , YELLOW_LED_BIT , LED_ON );							// Yellow LED ON ( Rs232 Sending )
		}
	}

	return 0;
}

