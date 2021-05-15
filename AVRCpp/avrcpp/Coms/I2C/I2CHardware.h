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

#ifndef I2CHardware_H_
#define I2CHardware_H_

#include "../../Utils/CppExtensions.h"
#include "../../Utils/BitManipulation.h"
#include "../../CallbackServers/CallbackConnector.h"
#include "Compatibility/I2CHardwareCompatibilityInterface.h"
#include <util/twi.h>

namespace Coms
{

namespace I2C
{

namespace Prescalers
{

	/*! I2C prescaler enum
	* The I2C's bitrate will be \f$ \frac{freq_{CPU}}{16 + 2 \cdot twbr \cdot prescaler} \f$
	*/
	enum Prescaler {
		DIV_1 = 0x00,					//!<!< divide clock source by 1
		DIV_4 = 0x01,					//!<!< divide clock source by 4
		DIV_16 = 0x02,					//!<!< divide clock source by 16
		DIV_64 = 0x03,					//!<!< divide clock source by 64
		FASTEST_1 = DIV_1,				//!<!< same as DIV_1
		SLOWEST_64 = DIV_64				//!<!< same as DIV_64
	};
}

namespace TransmitDirections
{
	enum TransmitDirection {
		READ = TW_READ,
		WRITE = TW_WRITE
	};

}

namespace TransmitActions
{
	enum TransmitAction
	{
		SHUTDOWN = 0x00,
		READY = bitValue(TWEN) | bitValue(TWINT),
		START_SIGNAL = READY | bitValue(TWSTA),
		STOP_SIGNAL = READY | bitValue(TWSTO),
		ACKNOWLEDGE = READY | bitValue(TWEA),
		NOT_ACKNOWLEDGE = READY,
		READY_IE = READY | bitValue(TWIE),
		START_SIGNAL_IE = START_SIGNAL | bitValue(TWIE),
		STOP_SIGNAL_IE = STOP_SIGNAL | bitValue(TWIE),
		ACKNOWLEDGE_IE = ACKNOWLEDGE | bitValue(TWIE),
		NOT_ACKNOWLEDGE_IE = READY_IE
	};
}

using Prescalers::Prescaler;
using TransmitDirections::TransmitDirection;
using TransmitActions::TransmitAction;

#define DEFAULT_ADDRESS 12u

#define GENERAL_I2C_CALL 0x00

class Mode;

class I2CMode;

class I2CHardware : public CallbackConnector
{
public:

	static I2CHardware * getInstance(size_t number);

	virtual ~I2CHardware();

	/*!
	 * Sets the bitrate for master transfers according to the following formula :
	 * \f$ \frac{freq_{CPU}}{16 + 2 \cdot twbrPrescaler \cdot twsrPrescaler} \f$
	 * @param finePrescaler the fine resolution prescaler (TWBR)
	 * @param coarsePrescaler the coarse resolution prescaler (TWSR)
	 * @see \a Prescaler
	 * @return the bitrate in Hz
	 */
	size_t setBitRate(uint8_t finePrescaler = 0xFF, Prescaler coarsePrescaler = Prescalers::SLOWEST_64);

	/*! Sets the device's address (only used in slave mode, of course).
	 * @param address7bit the \e 7-bits address of this device (0b000 0000 is reserved)
	 * @param answerGeneralCalls will answer to general calls (address 0b000 0000) if true
	 */
	void setSlaveAddress(uint8_t address7bit = DEFAULT_ADDRESS, bool answerGeneralCalls = false);

	inline void writeDestinationAddress(uint8_t destinationAddress, TransmitDirection currentMode) FORCE_INLINE;

	inline void command(TransmitAction action) FORCE_INLINE;

	inline uint8_t getStatus() FORCE_INLINE;

	inline bool readInterruptFlag() FORCE_INLINE;

	inline char readByte() FORCE_INLINE;

	inline bool writeByte(char byte) FORCE_INLINE;

protected:

	I2CHardware(uint8_t callbackVectorNumber, IOAddress twdr, IOAddress twbr, IOAddress twcr, IOAddress twsr, IOAddress twar);

	IOAddress twdr;
	IOAddress twbr;
	IOAddress twcr;
	IOAddress twsr;
	IOAddress twar;

};

#include "I2CHardware-definitions.h"

}

}

#endif /* I2CHardware_H_ */
