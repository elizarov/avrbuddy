#ifndef AVRBUDDY_IO_IO_BITS_H_
#define AVRBUDDY_IO_IO_BITS_H_

/*
   Defines cbi(port,bit) and sbi(port,bit) macros to manupulate AVR ports.
   Also includes avr/io and stdint types.
*/

#include <stdint.h>
#include <avr/io.h>

#ifndef sbi
#define sbi(port, pin)   ((port) |= (uint8_t)(1 << pin))
#endif

#ifndef cbi
#define cbi(port, pin)   ((port) &= (uint8_t)~(1 << pin))
#endif

#endif
