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

#ifndef ADCSensorTest_H_
#define ADCSensorTest_H_
#include "TestAssert.h"
#include "TestCase.h"
#include "Sensors/ADCSensor.h"
#include "CallbackServers/Callback.h"

using ADCs::ADCHardware;

class ADCSensorTest : public TestCase<ADCSensorTest>
{


public:

	ADCSensorTest(const prog_mem * testMethodName_P, TestCase<ADCSensorTest>::TestMethod testMethod) :
		TestCase<ADCSensorTest>(testMethodName_P, testMethod)
	{
	//		Callback();
		adcHardware = ADCHardware::getInstance();
		adcHardware->setVoltageReference(ADCs::VoltageReferences::AREF);
		adcHardware->setPrescaler(ADCs::Prescalers::DIV_8);
		adcHardware->setChannelMode(ADCs::ChannelModes::ADC0);
		adcHardware->rightAdjust();

		adcSensor0V = new ADCSensor(ADCHardware::getInstance(), ADCs::ChannelModes::ADC0);
		adcSensor3_33V = new ADCSensor(ADCHardware::getInstance(), ADCs::ChannelModes::ADC1);

	}
	~ADCSensorTest()
	{
		delete adcSensor0V;
		delete adcSensor3_33V;
	}

	void setUp()
	{
		adcHardware->enableADC();
		enableInterrupts();

	}

	void tearDown()
	{
		adcHardware->disableADC();
		disableInterrupts();
	}

	bool testRead()
	{

		//Instructions : Put 5V in AREF, 0V in ADC0 and 3.33V in ADC1

		bool result = AVRUNIT_ASSERT_IN_RANGE_LONG(adcSensor3_33V->read().serialize().buffer, 666, 100);

		result = AVRUNIT_ASSERT_IN_RANGE_LONG(adcSensor0V->read().serialize().buffer, 0, 10);

		return result;

	}

protected :
	ADCSensor * adcSensor3_33V;
	ADCSensor * adcSensor0V;
	ADCHardware * adcHardware;

};

#endif /* ADCSensorTest_H_ */
