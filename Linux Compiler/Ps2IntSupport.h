
#define PS2_BUFFER_SIZE 	32     /* 2,4,8,16,32,64,128 or 256 bytes */
#define PS2_BUFFER_MASK 	( PS2_BUFFER_SIZE - 1 )

void Ps2Init(void);

unsigned char IsDataInPs2SnifferBuffer( void );
unsigned char GetDataFromPs2SnifferBuffer( void );

unsigned char IsDataInPs2HostBuffer( void );
unsigned char GetDataFromPs2HostBuffer( void );

void EnableDeviceInterrupt( unsigned char Enable );
