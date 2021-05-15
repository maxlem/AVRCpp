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

#ifndef RCServoTest_H_
#define RCServoTest_H_


#include "TestCase.h"
#include "Actuators/RCServos/RCServo.h"
#include "Actuators/RCServos/PPMCapture.h"
#include "Timers/Timer16bits3OCR.h"

using Timers::Timer16bits3OCR;


class RCServoTest : public TestCase<RCServoTest>
{
public:

	RCServoTest(const prog_mem * testMethodName_P, TestCase<RCServoTest>::TestMethod testMethod) :
	TestCase<RCServoTest>(testMethodName_P, testMethod)
	{

		Timer16bits3OCR * timer1 = Timer16bits3OCR::getTimer16bits3OCR(1);
		Timer16bits3OCR * timer4 = Timer16bits3OCR::getTimer16bits3OCR(4);

		timer1->getCapturer()->setICRValue(40000); // roughly 20ms, the standard servo duty cycle, that will be our TOP
		timer1->getComparatorA()->setOCROutputPinMode(Timers::CompareModes::CLEAR_OC_PIN_ON_COMPARE_MATCH); // the pulse start at 0, ends at OCRValue
		timer1->getComparatorA()->setOCRValue(3000);
		timer1->setWaveGenerationMode(1, 1, 1, 0); //Fast PWM, TOP == ICR
		timer1->getCounter()->setPrescaler(Timers::Prescalers::DIV_8); //with a 16Mhz clock, that will give us 8/16000000 = .5us per tick


		servo1A = new RCServo(timer1->getComparatorA(), &DDRB, PINB5, 2000, 4000); // the OCR values for 1ms, 1.5ms, 2ms


		timer4->getCounter()->setPrescaler(Timers::Prescalers::DIV_8); //with a 16Mhz clock, that will give us 8/16000000 = .5us per tick
		timer4->setWaveGenerationMode(0, 0, 0, 0); //Fast PWM, TOP == ICR


		capture3 = new PPMCapture(timer4->getCounter(), timer4->getCapturer(), 2.0, &DDRL, PINL0, 1);
	}

	void setUp()
	{
	}

	void tearDown()
	{
	}

	bool testsetPosition()
	{
		enableInterrupts();

		uint16_t pulseWidth_us = 1000; //1ms
		int8_t increment = 10;
		while(true)
		{
			servo1A->setPulseWidth(pulseWidth_us);
			pulseWidth_us += increment;
			if(pulseWidth_us < 1000 || pulseWidth_us > 2000)
				increment = -increment;

			printf("ch0 = %d\r", capture3->getPulseWidth(0));

		}

		disableInterrupts();
	}

protected :

	RCServo * servo1A;

	PPMCapture * capture3;

};

#endif /* RCServoTest_H_ */
