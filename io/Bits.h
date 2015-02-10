/*
   Defines cbi(port,bit) and sbi(port,bit) macros to manupulate AVR ports.
*/

#ifndef BITS_H_
#define BITS_H_

#ifndef sbi
#define sbi(port, pin)   ((port) |= (uint8_t)(1 << pin))
#endif

#ifndef cbi
#define cbi(port, pin)   ((port) &= (uint8_t)~(1 << pin))
#endif

#endif
