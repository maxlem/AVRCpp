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

#ifndef TimerWaveGenerationModes_H_
#define TimerWaveGenerationModes_H_


namespace Timers {

namespace WaveGenerationModes
{
	/*!
	 * Wave generation modes
	 * @see \a CompareMode
	 */
	enum WaveGenerationMode2bits{
		NORMAL_COMPARE_MODE_BEHAVIOUR = 0x00, 	//!< @see \a CompareMode
		PWM_PHASE_CORRECT = 0x01,				//!< @see \a CompareMode
		CLEAR_TIMER_ON_COMPARE_MATCH = 0x02,	//!< @deprecated same as NORMAL_COMPARE_MODE_BEHAVIOUR
		PWM_FAST = 0x03                        	//!< @see \a CompareMode
	};

	enum WaveGenerationMode3bits{
//TODO
	};

	enum WaveGenerationMode4bits{
//TODO
	};

}

}  // namespace TimerV3
#endif /* TimerWaveGenerationModes_H_ */
