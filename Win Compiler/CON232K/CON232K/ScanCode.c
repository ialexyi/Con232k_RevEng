#include "allheaders.h"
#include "ScanCode.h"

typedef struct
{
	unsigned char		num_of_items,
						CodeArray[MAX_NUMBER_OF_CODE_KEYS];

} tsScanCodeItem;


const tsScanCodeItem ScanCodeList[] PROGMEM =
{{
	//-- ASCII value  0   --//
	.num_of_items = 0,
	.CodeArray = {0,0,0,0,0}
},
{
	//-- ASCII value  1 ( CTRL + A )  --//
	.num_of_items = 6,
	.CodeArray = {0x14,0x1C,0xF0,0x1C,0xF0,0x14}
},
{
	//-- ASCII value  2 ( WIN )  --//
	.num_of_items = 5,
	.CodeArray = {0xE0,0x1F,0xE0,0xF0,0x1F}
},
{
	//-- ASCII value  3 ( MENU )  --//
	.num_of_items = 5,
	.CodeArray = {0xE0,0x2F,0xE0,0xF0,0x2F}
},
{
	//-- ASCII value  4 ( PAGE UP )  --//
	.num_of_items = 5,
	.CodeArray = {0xE0,0x7D,0xE0,0xF0,0x7D}
},
{
	//-- ASCII value  5 ( PAGE DOWN )  --//
	.num_of_items = 5,
	.CodeArray = {0xE0,0x7A,0xE0,0xF0,0x7A}
},
{
	//-- ASCII value  6 ( HOME )  --//
	.num_of_items = 5,
	.CodeArray = {0xE0,0x6C,0xE0,0xF0,0x6C}
},
{
	//-- ASCII value  7 ( END )  --//
	.num_of_items = 5,
	.CodeArray = {0xE0,0x69,0xE0,0xF0,0x69}
},
{
	//-- ASCII value  8 ( BACKSPACE )  --//
	.num_of_items = 3,
	.CodeArray = {0x66,0xF0,0x66,0,0}
},
{
	//-- ASCII value  9 ( TAB )   --//
	.num_of_items = 3,
	.CodeArray = {0x0D,0xF0,0x0D,0,0}
},
{
	//-- ASCII value  10 ( ENTER )  --//
	.num_of_items = 3,
	.CodeArray = {0x5A,0xF0,0x5A,0,0}
},
{
	//-- ASCII value  11 ( Caps Lock ) --//
	.num_of_items = 3,
	.CodeArray = {0x58,0xF0,0x58,0,0}
},
{
	//-- ASCII value  12 ( CTRL + SHIFT ) --//
	.num_of_items = 6,
	.CodeArray = {0x14,0x12,0xF0,0x12,0xF0,0x14}
},
{
	//-- ASCII value  13 ( CTRL + ENTER ) --//
	.num_of_items = 6,
	.CodeArray = {0x14,0x5A,0xF0,0x5A,0xF0,0x14}
},
{
	//-- ASCII value  14 ( DELETE ) --//
	.num_of_items = 5,
	.CodeArray = {0xE0,0x71,0xE0,0xF0,0x71}
},
{
	//-- ASCII value  15 ( F1 ) --//
	.num_of_items = 3,
	.CodeArray = {0x05,0xF0,0x05,0,0}
},
{
	//-- ASCII value  16 ( F2 ) --//
	.num_of_items = 3,
	.CodeArray = {0x06,0xF0,0x06,0,0}
},
{
	//-- ASCII value  17 ( F3 ) --//
	.num_of_items = 3,
	.CodeArray = {0x04,0xF0,0x04,0,0}
},
{
	//-- ASCII value  18 ( F4 ) --//
	.num_of_items = 3,
	.CodeArray = {0x0C,0xF0,0x0C,0,0}
},
{
	//-- ASCII value  19 ( F5 ) --//
	.num_of_items = 3,
	.CodeArray = {0x03,0xF0,0x03,0,0}
},
{
	//-- ASCII value  20 ( F6 ) --//
	.num_of_items = 3,
	.CodeArray = {0x0B,0xF0,0x0B,0,0}
},
{
	//-- ASCII value  21 ( F7 ) --//
	.num_of_items = 3,
	.CodeArray = {0x83,0xF0,0x83,0,0}
},
{
	//-- ASCII value  22 ( F8 ) --//
	.num_of_items = 3,
	.CodeArray = {0x0A,0xF0,0x0A,0,0}
},
{
	//-- ASCII value  23 ( F9 ) --//
	.num_of_items = 3,
	.CodeArray = {0x01,0xF0,0x01,0,0}
},
{
	//-- ASCII value  24 ( F10 ) --//
	.num_of_items = 3,
	.CodeArray = {0x09,0xF0,0x09,0,0}
},
{
	//-- ASCII value  25 ( F11 ) --//
	.num_of_items = 3,
	.CodeArray = {0x78,0xF0,0x78,0,0}
},
{
	//-- ASCII value  26 ( F12 ) --//
	.num_of_items = 3,
	.CodeArray = {0x07,0xF0,0x07,0,0}
},
{
	//-- ASCII value  27 ( ESC ) --//
	.num_of_items = 3,
	.CodeArray = {0x76,0xF0,0x76,0,0}
},
{
	//-- ASCII value  28 ( CTRL PRESS )  --//
	.num_of_items = 3,
	.CodeArray = {0x14,0,0,0,0}
},
{
	//-- ASCII value  29 ( CTRL RELEASE ) --//
	.num_of_items = 3,
	.CodeArray = {0xF0,0x14,0,0,0}
},
{
	//-- ASCII value  30 ( ALT PRESS ) --//
	.num_of_items = 1,
	.CodeArray = {0x11,0,0,0,0}
},
{
	//-- ASCII value  31 ( ALT RELEASE ) --//
	.num_of_items = 3,
	.CodeArray = {0xF0,0x11,0,0,0}
},
{
	//-- ASCII value  32 ( SPACE )  --//
	.num_of_items = 3,
	.CodeArray = {0x29,0xF0,0x29,0,0}
},
{
	//-- ASCII value  33 (!)  --//
	.num_of_items = 6,
	.CodeArray = {0x59,0x16,0xF0,0x16,0xF0,0x59}
},
{
	//-- ASCII value  34 (")  --//
	.num_of_items = 6,
	.CodeArray = {0x59,0x52,0xF0,0x52,0xF0,0x59}
},
{
	//-- ASCII value  35 (#) --//
	.num_of_items = 6,
	.CodeArray = {0x59,0x26,0xF0,0x26,0xF0,0x59}
},
{
	//-- ASCII value  36 ($)  --//
	.num_of_items = 6,
	.CodeArray = {0x59,0x25,0xF0,0x25,0xF0,0x59}
},
{
	//-- ASCII value  37 (%)  --//
	.num_of_items = 6,
	.CodeArray = {0x59,0x2E,0xF0,0x2E,0xF0,0x59}
},
{
	//-- ASCII value  38 (&)  --//
	.num_of_items = 6,
	.CodeArray = {0x59,0x3D,0xF0,0x3D,0xF0,0x59}
},
{
	//-- ASCII value  39 (')  --//
	.num_of_items = 3,
	.CodeArray = {0x52,0xF0,0x52,0,0}
},
{
	//-- ASCII value  40 ('(')  --//
	.num_of_items = 6,
	.CodeArray = {0x59,0x46,0xF0,0x46,0xF0,0x59}
},
{
	//-- ASCII value  41 (')')  --//
	.num_of_items = 6,
	.CodeArray = {0x59,0x45,0xF0,0x45,0xF0,0x59}
},
{
	//-- ASCII value  42 (*)  --//
	.num_of_items = 6,
	.CodeArray = {0x59,0x3E,0xF0,0x3E,0xF0,0x59}
},
{
	//-- ASCII value  43 (+)  --//
	.num_of_items = 6,
	.CodeArray = {0x59,0x55,0xF0,0x55,0xF0,0x59}
},
{
	//-- ASCII value  44 (,)  --//
	.num_of_items = 3,
	.CodeArray = {0x41,0xF0,0x41,0,0}
},
{
	//-- ASCII value  45 (-)  --//
	.num_of_items = 3,
	.CodeArray = {0x4E,0xF0,0x4E,0,0}
},
{
	//-- ASCII value  46 (.) --//
	.num_of_items = 3,
	.CodeArray = {0x49,0xF0,0x49,0,0}
},
{
	//-- ASCII value  47 (/) --//
	.num_of_items = 3,
	.CodeArray = {0x4A,0xF0,0x4A,0,0}
},
{
	//-- ASCII value  48 (0) --//
	.num_of_items = 3,
	.CodeArray = {0x45,0xF0,0x45,0,0}
},
{
	//-- ASCII value  49 (1) --//
	.num_of_items = 3,
	.CodeArray = {0x16,0xF0,0x16,0,0}
},
{
	//-- ASCII value  50 (2) --//
	.num_of_items = 3,
	.CodeArray = {0x1E,0xF0,0x1E,0,0}
},
{
	//-- ASCII value  51 (3) --//
	.num_of_items = 3,
	.CodeArray = {0x26,0xF0,0x26,0,0}
},
{
	//-- ASCII value  52 (4) --//
	.num_of_items = 3,
	.CodeArray = {0x25,0xF0,0x25,0,0}
},
{
	//-- ASCII value  53 (5) --//
	.num_of_items = 3,
	.CodeArray = {0x2E,0xF0,0x2E,0,0}
},
{
	//-- ASCII value  54 (6) --//
	.num_of_items = 3,
	.CodeArray = {0x36,0xF0,0x36,0,0}
},
{
	//-- ASCII value  55 (7) --//
	.num_of_items = 3,
	.CodeArray = {0x3D,0xF0,0x3D,0,0}
},
{
	//-- ASCII value  56 (8) --//
	.num_of_items = 3,
	.CodeArray = {0x3E,0xF0,0x3E,0,0}
},
{
	//-- ASCII value  57 (9) --//
	.num_of_items = 3,
	.CodeArray = {0x46,0xF0,0x46,0,0}
},
{
	//-- ASCII value  58 (:) --//
	.num_of_items = 6,
	.CodeArray = {0x59,0x4C,0xF0,0x4C,0xF0,0x59}
},
{
	//-- ASCII value  59 (;) --//
	.num_of_items = 3,
	.CodeArray = {0x4C,0xF0,0x4C,0,0}
},
{
	//-- ASCII value  60 (<)  --//
	.num_of_items = 6,
	.CodeArray = {0x59,0x41,0xF0,0x41,0xF0,0x59}
},
{
	//-- ASCII value  61 (=)  --//
	.num_of_items = 3,
	.CodeArray = {0x55,0xF0,0x55,0,0}
},
{
	//-- ASCII value  62 (>) --//
	.num_of_items = 6,
	.CodeArray = {0x59,0x49,0xF0,0x49,0xF0,0x59}
},
{
	//-- ASCII value  63 (?)  --//
	.num_of_items = 6,
	.CodeArray = {0x59,0x4A,0xF0,0x4A,0xF0,0x59}
},
{
	//-- ASCII value  64 (@)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x1E,0xF0,0x1E,0xF0,0x12}
},
{
	//-- ASCII value  65 (A)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x1C,0xF0,0x1C,0xF0,0x12}
},
{
	//-- ASCII value  66 (B)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x32,0xF0,0x32,0xF0,0x12}
},
{
	//-- ASCII value  67 (C)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x21,0xF0,0x21,0xF0,0x12}
},
{
	//-- ASCII value  68 (D)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x23,0xF0,0x23,0xF0,0x12}
},
{
	//-- ASCII value  69 (E)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x24,0xF0,0x24,0xF0,0x12}
},
{
	//-- ASCII value  70 (F)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x2B,0xF0,0x2B,0xF0,0x12}
},
{
	//-- ASCII value  71 (G)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x34,0xF0,0x34,0xF0,0x12}
},
{
	//-- ASCII value  72 (H)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x33,0xF0,0x33,0xF0,0x12}
},
{
	//-- ASCII value  73 (I)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x43,0xF0,0x43,0xF0,0x12}
},
{
	//-- ASCII value  74 (J)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x3B,0xF0,0x3B,0xF0,0x12}
},
{
	//-- ASCII value  75 (K)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x42,0xF0,0x42,0xF0,0x12}
},
{
	//-- ASCII value  76 (L)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x4B,0xF0,0x4B,0xF0,0x12}
},
{
	//-- ASCII value  77 (M)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x3A,0xF0,0x3A,0xF0,0x12}
},
{
	//-- ASCII value  78 (N)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x31,0xF0,0x31,0xF0,0x12}
},
{
	//-- ASCII value  79 (O)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x44,0xF0,0x44,0xF0,0x12}
},
{
	//-- ASCII value  80 (P)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x4D,0xF0,0x4D,0xF0,0x12}
},
{
	//-- ASCII value  81 (Q)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x15,0xF0,0x15,0xF0,0x12}
},
{
	//-- ASCII value  82 (R)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x2D,0xF0,0x2D,0xF0,0x12}
},
{
	//-- ASCII value  83 (S)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x1B,0xF0,0x1B,0xF0,0x12}
},
{
	//-- ASCII value  84 (T)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x2C,0xF0,0x2C,0xF0,0x12}
},
{
	//-- ASCII value  85 (U)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x3C,0xF0,0x3C,0xF0,0x12}
},
{
	//-- ASCII value  86 (V)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x2A,0xF0,0x2A,0xF0,0x12}
},
{
	//-- ASCII value  87 (W)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x1D,0xF0,0x1D,0xF0,0x12}
},
{
	//-- ASCII value  88 (X)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x22,0xF0,0x22,0xF0,0x12}
},
{
	//-- ASCII value  89 (Y)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x35,0xF0,0x35,0xF0,0x12}
},
{
	//-- ASCII value  90 (Z)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x1A,0xF0,0x1A,0xF0,0x12}
},
{
	//-- ASCII value  91 ([)  --//
	.num_of_items = 3,
	.CodeArray = {0x54,0xF0,0x54,0,0}
},
{
	//-- ASCII value  92 (\)  --//
	.num_of_items = 3,
	.CodeArray = {0x5D,0xF0,0x5D,0,0}
},
{
	//-- ASCII value  93 (])  --//
	.num_of_items = 3,
	.CodeArray = {0x5B,0xF0,0x5B,0,0}
},
{
	//-- ASCII value  94 (^)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x36,0xF0,0x36,0xF0,0x12}
},
{
	//-- ASCII value  95 (_)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x4E,0xF0,0x4E,0xF0,0x12}
},
{
	//-- ASCII value  96 (`)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x0E,0xF0,0x0E,0xF0,0x12}
},
{
	//-- ASCII value  97 (a)  --//
	.num_of_items = 3,
	.CodeArray = {0x1C,0xF0,0x1C,0,0}
},
{
	//-- ASCII value  98 (b)  --//
	.num_of_items = 3,
	.CodeArray = {0x32,0xF0,0x32,0,0}
},
{
	//-- ASCII value  99 (c)  --//
	.num_of_items = 3,
	.CodeArray = {0x21,0xF0,0x21,0,0}
},
{
	//-- ASCII value  100 (d)  --//
	.num_of_items = 3,
	.CodeArray = {0x23,0xF0,0x23,0,0}
},
{
	//-- ASCII value  101 (e)  --//
	.num_of_items = 3,
	.CodeArray = {0x24,0xF0,0x24,0,0}
},
{
	//-- ASCII value  102 (f)  --//
	.num_of_items = 3,
	.CodeArray = {0x2B,0xF0,0x2B,0,0}
},
{
	//-- ASCII value  103 (g)  --//
	.num_of_items = 3,
	.CodeArray = {0x34,0xF0,0x34,0,0}
},
{
	//-- ASCII value  104 (h)  --//
	.num_of_items = 3,
	.CodeArray = {0x33,0xF0,0x33,0,0}
},
{
	//-- ASCII value  105 (i)  --//
	.num_of_items = 3,
	.CodeArray = {0x43,0xF0,0x43,0,0}
},
{
	//-- ASCII value  106 (j)  --//
	.num_of_items = 3,
	.CodeArray = {0x3B,0xF0,0x3B,0,0}
},
{
	//-- ASCII value  107 (k)  --//
	.num_of_items = 3,
	.CodeArray = {0x42,0xF0,0x42,0,0}
},
{
	//-- ASCII value  108 (l)  --//
	.num_of_items = 3,
	.CodeArray = {0x4B,0xF0,0x4B,0,0}
},
{
	//-- ASCII value  109 (m)  --//
	.num_of_items = 3,
	.CodeArray = {0x3A,0xF0,0x3A,0,0}
},
{
	//-- ASCII value  110 (n)  --//
	.num_of_items = 3,
	.CodeArray = {0x31,0xF0,0x31,0,0}
},
{
	//-- ASCII value  111 (o)  --//
	.num_of_items = 3,
	.CodeArray = {0x44,0xF0,0x44,0,0}
},
{
	//-- ASCII value  112 (p)  --//
	.num_of_items = 3,
	.CodeArray = {0x4D,0xF0,0x4D,0,0}
},
{
	//-- ASCII value  113 (q)  --//
	.num_of_items = 3,
	.CodeArray = {0x15,0xF0,0x15,0,0}
},
{
	//-- ASCII value  114 (r)  --//
	.num_of_items = 3,
	.CodeArray = {0x2D,0xF0,0x2D,0,0}
},
{
	//-- ASCII value  115 (s)  --//
	.num_of_items = 3,
	.CodeArray = {0x1B,0xF0,0x1B,0,0}
},
{
	//-- ASCII value  116 (t)  --//
	.num_of_items = 3,
	.CodeArray = {0x2C,0xF0,0x2C,0,0}
},
{
	//-- ASCII value  117 (u)  --//
	.num_of_items = 3,
	.CodeArray = {0x3C,0xF0,0x3C,0,0}
},
{
	//-- ASCII value  118 (v)  --//
	.num_of_items = 3,
	.CodeArray = {0x2A,0xF0,0x2A,0,0}
},
{
	//-- ASCII value  119 (w)  --//
	.num_of_items = 3,
	.CodeArray = {0x1D,0xF0,0x1D,0,0}
},
{
	//-- ASCII value  120 (x)  --//
	.num_of_items = 3,
	.CodeArray = {0x22,0xF0,0x22,0,0}
},
{
	//-- ASCII value  121 (y)  --//
	.num_of_items = 3,
	.CodeArray = {0x35,0xF0,0x35,0,0}
},
{
	//-- ASCII value  122 (z)  --//
	.num_of_items = 3,
	.CodeArray = {0x1A,0xF0,0x1A,0,0}
},
{
	//-- ASCII value  123 ({)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x54,0xF0,0x54,0xF0,0x12}
},
{
	//-- ASCII value  124 (|)  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x5D,0xF0,0x5D,0xF0,0x12}
},
{
	//-- ASCII value  125 (})  --//
	.num_of_items = 6,
	.CodeArray = {0x12,0x5B,0xF0,0x5B,0xF0,0x12}
},
{
	//-- ASCII value  126 (~)  --//
	.num_of_items = 3,
	.CodeArray = {0x0E,0xF0,0x0E,0,0}
},
{
	//-- ASCII value  127 ( DELETE ) --//
	.num_of_items = 5,
	.CodeArray = {0xE0,0x71,0xE0,0xF0,0x71}
}};

int		GetScanCode( volatile unsigned char ASCII_key, volatile unsigned char *CodeArray )
{
	volatile unsigned char 	iIndex			=	0,
								SizeOfList		=	0,
								NumberOfItems	=	0;

	SizeOfList = sizeof(ScanCodeList) / sizeof(tsScanCodeItem);

	if ( ASCII_key >= SizeOfList )
		return 0;

	NumberOfItems = pgm_read_byte(&(ScanCodeList[ASCII_key].num_of_items));

	for ( iIndex = 0; iIndex < NumberOfItems; iIndex++)
		CodeArray[iIndex] = pgm_read_byte(&(ScanCodeList[ASCII_key].CodeArray[iIndex]));

	return NumberOfItems;
}
