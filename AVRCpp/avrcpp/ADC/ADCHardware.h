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

#ifndef ADCHardware_H_
#define ADCHardware_H_

#include "../Utils/CppExtensions.h"
#include "../Utils/BitManipulation.h"
#include "Compatibility/ADCHardwareCompatibilityInterface.h"
#include "../CallbackServers/CallbackConnector.h"
#include "Prescalers.h"
#include "ChannelModes.h"
#include "VoltageReferences.h"

namespace ADCs
{




using Prescalers::Prescaler;
using ChannelModes::ChannelMode;
using VoltageReferences::VoltageReference;

/*! Analog to digital conversion class.
 */
class ADCHardware : public CallbackConnector
{
public:



	static ADCHardware* getInstance();

	inline void enableADC() FORCE_INLINE;

	inline void disableADC() FORCE_INLINE;

	inline void enableAutoTriggering() FORCE_INLINE;

	inline void disableAutoTriggering() FORCE_INLINE;

	inline void enableInterrupts() FORCE_INLINE;

	inline void disableInterrupts() FORCE_INLINE;

	inline bool isConversionComplete() FORCE_INLINE;

	inline void clearConversionCompleteFlag() FORCE_INLINE;

	inline uint16_t read() FORCE_INLINE;

	inline bool isBusy() FORCE_INLINE;

	inline void startConverter() FORCE_INLINE;

	inline void setPrescaler(Prescaler prescaler) FORCE_INLINE;

	inline void setVoltageReference(VoltageReference voltageReference) FORCE_INLINE;

	inline void setChannelMode(ChannelMode channelMode) FORCE_INLINE;

	inline void leftAdjust()  FORCE_INLINE;

	inline void rightAdjust()  FORCE_INLINE;

protected:

	IOAddress adcsra;
	IOAddress admux;
	IOAddress sfior;
	IOAddress16 adc;

	IOAddress triggers;
	uint8_t triggersMask;

	/*! Private Constructor.
	 * This class is a Singleton, access it via \a getInstance()
	 */
	ADCHardware(uint8_t callbackVectorNumber, IOAddress acdsra, IOAddress admux, IOAddress16 adc);

};

#include "ADCHardware-definitions.h"

}

#endif /*ADCHardware_H_*/
