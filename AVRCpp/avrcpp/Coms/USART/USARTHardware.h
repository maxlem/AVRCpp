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

#ifndef USARTHardware_H_
#define USARTHardware_H_

#include "../../Utils/CppExtensions.h"
#include "../../CallbackServers/Callback.h"
#include "Compatibility/USARTInterfaceCompatibility.h"

namespace Coms
{

namespace USART
{

namespace ParityModes
{
	/*!
	 * The different parity choices
	 */
	enum ParityMode{ NONE = 0x00, ODD = 0x02, EVEN = 0x03};

}

namespace FrameSizes
{
	/*!
	 * The different FrameSize choices
	 */
	enum FrameSize{ FIVE_BITS = 0x00, SIX_BITS = 0x01, SEVEN_BITS = 0x02, EIGHT_BITS = 0x03, NINE_BITS = 0x07};

}

namespace StopBitsModes
{
	/*!
	 * The different choices for stopbit
	 */
	enum StopBitsMode{ ONE = 0x00, TWO = 0x01};
}


using ParityModes::ParityMode;
using FrameSizes::FrameSize;
using StopBitsModes::StopBitsMode;

#define USART_NINTH_BIT_MASK		0x0100
#define USART_MAX_DATABITS_VALUE 	0x01FF
#define USART_UCSRA_STATUS_MASK		0x1C 	// bitValue(FE) | bitValue(UPE) | bitValue(DOR)

class USARTHardware
{

public:

	static USARTHardware * getUSARTHardware(size_t number);

	inline void configureBitRate(uint16_t finePrescaler = 34u, bool doubleBitRate = true, bool synchroneous = false) FORCE_INLINE;

	uintmax_t getBitRate();

	inline void configureFrameSize(FrameSize dataBits = FrameSizes::EIGHT_BITS) FORCE_INLINE;
	inline void configureStopBitsMode(StopBitsMode stopBits = StopBitsModes::ONE) FORCE_INLINE;
	inline void configureParityMode(ParityMode parity = ParityModes::NONE) FORCE_INLINE;

	inline void enableMPCM() FORCE_INLINE;

	inline void disableMPCM() FORCE_INLINE;

	inline void configureDefaults();

	inline void enableReceiver() FORCE_INLINE;
	inline void disableReceiver() FORCE_INLINE;



	inline uint16_t readFrame() FORCE_INLINE;

	inline bool isFrameReceived() FORCE_INLINE;
	inline void clearFrameReceivedFlag() FORCE_INLINE;
	inline void enableFrameReceivedInterrupts() FORCE_INLINE;
	inline void disableFrameReceivedInterrupts() FORCE_INLINE;
	void connectFrameReceivedCallback(Callback * frameReceivedCallback);
	Callback * disconnectFrameReceivedCallback();

	inline void enableTransmitter() FORCE_INLINE;
	inline void disableTransmitter() FORCE_INLINE;

	inline void writeFrame(uint16_t dataBits) FORCE_INLINE;

	inline bool isTransmitterReady() FORCE_INLINE;
	inline void enableTransmitterReadyInterrupts() FORCE_INLINE;
	inline void disableTransmitterReadyInterrupts() FORCE_INLINE;
	void connectTransmitterReadyCallback(Callback * transmitterReadyCallback);
	Callback * disconnectTransmitterReadyCallback();

	inline bool isFrameTransmitted() FORCE_INLINE;
	inline void clearFrameTransmittedFlag() FORCE_INLINE;
	inline void enableFrameTransmittedInterrupts() FORCE_INLINE;
	inline void disableFrameTransmittedInterrupts() FORCE_INLINE;
	void connectFrameTransmittedCallback(Callback * frameTransmittedCallback);
	Callback * disconnectFrameTransmittedCallback();

	inline uint8_t status() FORCE_INLINE;

protected:

	USARTHardware(uint8_t USART_RX_vect_number, uint8_t USART_UDRE_vect_number, uint8_t USART_TX_vect_number, IOAddress udr, IOAddress ubrrh, IOAddress ubrrl, IOAddress ucsra, IOAddress ucsrb, IOAddress ucsrc);

	uint8_t USART_RX_vect_number;
	uint8_t USART_UDRE_vect_number;
	uint8_t USART_TX_vect_number;

	IOAddress udr;
	IOAddress ubrrh;
	IOAddress ubrrl;
	IOAddress ucsra;
	IOAddress ucsrb;
	IOAddress ucsrc;


};

#include "USARTHardware-definitions.h"


}

}

#endif /*USARTHardware_H_*/
