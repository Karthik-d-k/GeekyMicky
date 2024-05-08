#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

const uint32_t BAUDRATE = 115200;

/******************************************************************************
 * FAST IO for ATMEGA328 ONLY
 *
 * There are places in the code (ADC and ENCODERS) where it is important that
 * you are able to access IO pins as quickly as possible. Some processor are fast
 * enough that this is not a problem. The ATMega328 using the Arduino framework
 * is not one of those cases so the macros below translate simple pin IO
 * functions into single machine code instructions.
 *
 * Extracted from digitalWriteFast:
 *      Optimized digital functions for AVR microcontrollers
 *      by Watterott electronic (www.watterott.com)
 *      based on https://code.google.com/p/digitalwritefast
 *
 * If you are using a different processor, you will either need to reimplement
 * these functions or use a suitable built-in function if it is fast enough
 */
#if defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
#define __digitalPinToPortReg(P) (((P) <= 7) ? &PORTD : (((P) >= 8 && (P) <= 13) ? &PORTB : &PORTC))
#define __digitalPinToDDRReg(P) (((P) <= 7) ? &DDRD : (((P) >= 8 && (P) <= 13) ? &DDRB : &DDRC))
#define __digitalPinToPINReg(P) (((P) <= 7) ? &PIND : (((P) >= 8 && (P) <= 13) ? &PINB : &PINC))
#define __digitalPinToBit(P) (((P) <= 7) ? (P) : (((P) >= 8 && (P) <= 13) ? (P)-8 : (P)-14))

// general macros/defines
#if !defined(BIT_READ)
#define BIT_READ(value, bit) ((value) & (1UL << (bit)))
#endif
#if !defined(BIT_SET)
#define BIT_SET(value, bit) ((value) |= (1UL << (bit)))
#endif
#if !defined(BIT_CLEAR)
#define BIT_CLEAR(value, bit) ((value) &= ~(1UL << (bit)))
#endif
#if !defined(BIT_WRITE)
#define BIT_WRITE(value, bit, bitvalue) (bitvalue ? BIT_SET(value, bit) : BIT_CLEAR(value, bit))
#endif

#define fast_write_pin(P, V) BIT_WRITE(*__digitalPinToPortReg(P), __digitalPinToBit(P), (V));
#define fast_read_pin(P) ((int)(((BIT_READ(*__digitalPinToPINReg(P), __digitalPinToBit(P))) ? HIGH : LOW)))

#else
#define fast_write_pin(P, V) digitalWrite(P, V)
#define fast_read_pin(P) digitalRead(P)
#endif

/******************************************************************************
 * ATOMIC OPERATIONS for ATMEGA328 ONLY
 * Since the ATMega328 is an 8 bit processor it is possible that you will end
 * up trying to read a multi-byte quantity that is modified in an interrupt while
 * you are doing the read or write. The result is a corrupt value. 32 bit processors
 * are unlikely to suffer from this since quantities are read in a single operation.
 *
 * The AVR compiler provides a method for you to disable interrupts for the
 * duration of a block of code and then restore the state at the end of the block.
 *
 * It is not enough to simply turn off interrupts and then turn them back on because
 * you need to remember the state of the interrupt enable flag at the start of the
 * block.
 *
 * These macros do this for you and should be either modified for different processors
 * or bypassed if needed.
 *
 * Use like this:
 * ATOMIC {
 * // code to protect
 * }
 *
 */
#if defined(__AVR__)
#include <util/atomic.h>
#define ATOMIC ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
#else
#define ATOMIC
#endif

#endif
