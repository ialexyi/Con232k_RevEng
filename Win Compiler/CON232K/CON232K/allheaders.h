#ifndef _INCFILES_INCLUDED
#define _INCFILES_INCLUDED

#define F_CPU 8000000UL  // 8 MHz

#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <ctype.h>
#include "USART2.h"
#include "Ps2.h"
#include "IoSupport.h"
#include "Ps2IntSupport.h"
#include "ScanCode.h"

#endif
