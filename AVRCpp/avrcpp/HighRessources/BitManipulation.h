/*
Copyright (c) 2007-2021 Maxime Lemonnier

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef BITMANIPULATION_H_
#define BITMANIPULATION_H_
#include <stdint.h>
#include <stddef.h>
#include <avr/io.h>
/*!
 * Registers and bits manipulation macros
 */

// bit status
#define HIGH 1
#define LOW 0

enum DataDirection {INPUT = 0, OUTPUT = 1};

enum Direction {LEFT = false, RIGHT = true};

#define bitValue( bitNumber ) 													(1 << bitNumber)

#define changeBitValueTo(reg, bitNumber, value_MACRO) 							(value_MACRO)?(setBit(reg, bitNumber)):(clearBit(reg, bitNumber))

#define applyMaskedConfig(reg, bitMask, config)									reg &= ~bitMask; \
																				reg |= config & bitMask

#define mask8(bit7, bit6, bit5, bit4, bit3, bit2, bit1, bit0)					((bit7 << 7) | (bit6 << 6) | (bit5 << 5) | (bit4 << 4) | (bit3 << 3) | (bit2 << 2) | (bit1 << 1) | (bit0))
#define mask16(bit15, bit14, bit13, bit12, bit11, bit10, bit9, it8, bit7, bit6, bit5, bit4, bit3, bit2, bit1, bit0)		( mask8(bit15, bit14, bit13, bit12, bit11, bit10, bit9) | mask8(bit7, bit6, bit5, bit4, bit3, bit2, bit1, bit0)	)

#define clearBit(reg, bitNumber)   												reg &= (uint8_t)~(bitValue(bitNumber))
#define clear2Bits(reg, firstBitName, secondBitName)   							reg &= ((uint8_t)~(bitValue(firstBitName)) & (uint8_t)~(bitValue(secondBitName)))
#define clear3Bits(reg, firstBitName, secondBitName, thirdBitName)   			reg &= ((uint8_t)~(bitValue(firstBitName)) & (uint8_t)~(bitValue(secondBitName)) & (uint8_t)~(bitValue(thirdBitName)))
#define clear4Bits(reg, firstBitName, secondBitName, thirdBitName, fourthBitName)   			reg &= ((uint8_t)~(bitValue(firstBitName)) & (uint8_t)~(bitValue(secondBitName)) & (uint8_t)~(bitValue(thirdBitName)) & (uint8_t)~(bitValue(fourthBitName)))
#define clearReg(reg)															reg = 0x00

#define setBit(reg, bitNumber)   												reg |= (bitValue(bitNumber))
#define set2Bits(reg, firstBitName, secondBitName) 								reg |= ((bitValue(firstBitName)) | (bitValue(secondBitName)))
#define set3Bits(reg, firstBitName, secondBitName, thirdBitName) 				reg |= ((bitValue(firstBitName)) | (bitValue(secondBitName)) | (bitValue(thirdBitName)))
#define set4Bits(reg, firstBitName, secondBitName, thirdBitName, fourthBitName) reg |= ((bitValue(firstBitName)) | (bitValue(secondBitName)) | (bitValue(thirdBitName)) | (bitValue(fourthBitName)))
#define setRegisterBits(reg, bit7, bit6, bit5, bit4, bit3, bit2, bit1, bit0) 	reg = mask8(bit7, bit6, bit5, bit4, bit3, bit2, bit1, bit0)

#define bitIsSetInRegister(reg, bitNumber)										bit_is_set(reg, bitNumber)

inline void enableInterrupts() __attribute__((always_inline));
inline void disableInterrupts() __attribute__((always_inline));
inline bool interruptsEnabled() __attribute__((always_inline));


#define LOCK_INTERRUPTS 	volatile bool interruptStatus = interruptsEnabled();\
							disableInterrupts()

#define UNLOCK_INTERRUPTS 	if(interruptStatus)\
								enableInterrupts();

// This is a hack for JTAG debugging
#define isNull(pointer) ( ( (pointer) == ((void*)NULL)) || ( (pointer) == ((void*)0x8000000)) )

// IO address as arguments
typedef volatile uint8_t * IOAddress;

// IO address as arguments (16 bits)
typedef volatile uint16_t * IOAddress16;


inline uint8_t buildMask(uint8_t bitName1, uint8_t bitName2 = 16, uint8_t bitName3 = 16, uint8_t bitName4 = 16, uint8_t bitName5 = 16, uint8_t bitName6 = 16, uint8_t bitName7 = 16, uint8_t bitName8 = 16) __attribute__((always_inline));


inline bool bitIsSet(uint8_t mask, uint8_t bit) __attribute__((always_inline));

uint8_t maskToConfig(uint8_t mask);

/*!
 * Sets a config in a register
 * @param reg the register's \b address (ex : &DDRA)
 * @param configBitMask 	the affected bits in the register (ex. 0x0F if the config affects the last four bits,
 * 							0xF0 for the first four bits)
 * @param config 	the config data \b unshifted! (i.e. to set the bits 3 and 4 to one, config must be 0x03,
 * 					the bits will be properly placed according to configBitMask)
 */
void setConfig(const IOAddress & reg, uint8_t configBitMask, uint8_t config);

/*!
 * Gets a config in a register
 * @param reg the register's \b address (ex : &DDRA)
 * @param configBitMask the affected bits in the register (ex. 0x0F if the config affects the last four bits, 0xF0 for the first four bits)
 * @return the config, with LSB at bit 0 (shifted according to configBitMask's LSB position)
 */
uint8_t getConfig(IOAddress & reg, uint8_t configBitMask);




#include "BitManipulation-definitions.h"
#endif /* BITMANIPULATION_H_ */
