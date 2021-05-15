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

#ifndef TimerOutputCompareModes_H_
#define TimerOutputCompareModes_H_

namespace Timers
{

namespace CompareModes
{
	/*!
	 * Compare modes available
	 */
	enum CompareMode{

		NORMAL_OC_PIN_DISCONNECTED = 0x00,		//!< the timer counts from 0x00 to TOP and overflows to 0x00
		TOGGLE_OC_PIN_ON_COMPARE_MATCH = 0x01,	//!< the timer counts from 0x00 to TOP and overflows to 0x00 @warning use with WaveGenerationMode::NORMAL_COMPARE_MODE_BEHAVIOUR \b only!

		/*!
		 * The behaviour depends on WaveGenerationMode
		 * - WaveGenerationMode::NORMAL_COMPARE_MODE_BEHAVIOUR : Ocn pin is cleared on compare match (not very useful)
		 * - WaveGenerationMode::PWM_PHASE_CORRECT : Ocn pin is cleared on compare match, set at 0x00
		 * 	- 	this mode will generate a PWM signal with frequency \f$ PWM_{freq} =  \frac	{freq_{clockSource}}	{\left(	\mathsf{prescaler} * 256 \right)} \f$
		 * 		and lenght \f$ frac	{\frac	{\mathsf{compareToValue}}	{\mathsf{getTopValue()}}	}	{PWM_{freq}} \f$
		 * - WaveGenerationMode::PWM_FAST : Ocn pin is cleared on compare match when couting up, set on compare match when couting down
		 *	- 	this mode will generate a PWM signal with frequency \f$ PWM_{freq} =  \frac	{freq_{clockSource}}	{\left(	\mathsf{prescaler} * 510 \right)} \f$
		 * 		and lenght \f$ frac	{\frac	{\mathsf{compareToValue}}	{\mathsf{getTopValue()}}	}	{PWM_{freq}} \f$
		 */
		CLEAR_OC_PIN_ON_COMPARE_MATCH = 0x02,

		/*!
		 * The behaviour depends on WaveGenerationMode
		 * - WaveGenerationMode::NORMAL_COMPARE_MODE_BEHAVIOUR : Ocn pin is set on compare match (not very useful)
		 * - WaveGenerationMode::PWM_PHASE_CORRECT : Ocn pin is set on compare match, cleared at 0x00
		 * 	- 	this mode will generate a PWM signal with frequency \f$ PWM_{freq} =  \frac	{freq_{clockSource}}	{\left(	\mathsf{prescaler} * 256 \right)} \f$
		 * 		and lenght \f$ frac	{\frac	{1 - \mathsf{compareToValue}}	{\mathsf{getTopValue()}}	}	{PWM_{freq}} \f$
		 * - WaveGenerationMode::PWM_FAST : Ocn pin is cleared on compare match when couting down, set on compare match when couting up
		 *	- 	this mode will generate a PWM signal with frequency \f$ PWM_{freq} =  \frac	{freq_{clockSource}}	{\left(	\mathsf{prescaler} * 510 \right)} \f$
		 * 		and lenght \f$ frac	{\frac	{1 - \mathsf{compareToValue}}	{\mathsf{getTopValue()}}	}	{PWM_{freq}} \f$
		 *
		 */
		SET_OC_PIN_ON_COMPARE_MATCH = 0x03
	};
}

}
#endif /* TimerOutputCompareModes_H_ */
