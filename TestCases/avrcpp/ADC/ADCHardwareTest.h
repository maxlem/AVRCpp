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

#ifndef ADCHardwareTest_H_
#define ADCHardwareTest_H_

#include "TestCase.h"
#include "TestSuite.h"
#include "TestAssert.h"

#include "ADC/ADCHardware.h"
#include <stdlib.h>
#include <math.h>

class ADCHardwareTest : public TestCase<ADCHardwareTest>
{




	void printInstructions()
	{
		char * adcGNDBuffer = new(Allocators::STACK) char[25];
		dtostrf(adcGNDVoltage, 5, 5, adcGNDBuffer);
		char * adcVCCBuffer = new(Allocators::STACK) char[25];
		dtostrf(adcVCCVoltage, 5, 5, adcVCCBuffer);
		char * adcOtherBuffer = new(Allocators::STACK) char[25];
		dtostrf(adcOtherVoltage, 5, 5, adcOtherBuffer);

		printf(PROG_MEM_STRING("\n\rADCHardware test procedure :\n\r"));
		printf(PROG_MEM_STRING("\t1) Connect AD0 to a %sV source\n\r"), adcGNDBuffer);
		printf(PROG_MEM_STRING("\t2) Connect AD1 to a %sV\n\r"), adcVCCBuffer);
		printf(PROG_MEM_STRING("\t3) Connect AD2 to a %sV source\n\r"), adcOtherBuffer);
	}

public:
	ADCHardwareTest(const prog_mem * testMethodName_P, TestCase<ADCHardwareTest>::TestMethod testMethod) :
		TestCase<ADCHardwareTest>(testMethodName_P, testMethod)
	{
		a2d = ADCs::ADCHardware::getInstance();
		adcGNDVoltage = 0.0;
		adcVCCVoltage = 5.0;
		adcOtherVoltage = 3.33;
	}

	~ADCHardwareTest()
	{

	}

	void setUp()
	{

		a2d->setVoltageReference(ADCs::VoltageReferences::AVCC);

	}

	void tearDown()
	{
		a2d->disableADC();
		a2d->disableAutoTriggering();
	}

	bool testgetInstance()
	{
		return AVRUNIT_ASSERT(!isNull(a2d));
	}

	bool testUntriggeredConversions()
	{
		a2d->setPrescaler(ADCs::Prescalers::SLOWEST_128);

		a2d->setChannelMode(ADCs::ChannelModes::ADC0);

		a2d->rightAdjust();

		a2d->enableADC();

		// throw away the first conversion :

		a2d->startConverter();

		while(a2d->isBusy());


		a2d->startConverter();

		while(a2d->isBusy());

		bool result = AVRUNIT_ASSERT_IN_RANGE_LONG(a2d->read(), 0, 1);

		a2d->setChannelMode(ADCs::ChannelModes::ADC1);

		a2d->startConverter();

		while(a2d->isBusy());

		result &= AVRUNIT_ASSERT_IN_RANGE_LONG(a2d->read(), 1023, 1);


		a2d->setChannelMode(ADCs::ChannelModes::ADC2);

		a2d->startConverter();

		while(a2d->isBusy());

		result &= AVRUNIT_ASSERT_IN_RANGE_LONG(a2d->read(), (long long) (adcOtherVoltage/adcVCCVoltage * 1023), 25);

		return result;
	}

	bool testTriggeredConversions()
	{

		a2d->enableAutoTriggering();

		a2d->setPrescaler(ADCs::Prescalers::SLOWEST_128);

		size_t prescaler = 128;

		a2d->setChannelMode(ADCs::ChannelModes::ADC0);

		a2d->rightAdjust();

		a2d->enableADC();

		// This starts the auto-triggered conversions :
		a2d->startConverter();

		// throw away the first conversion :
		wasteCycles(POWER_UP_ADC_CYCLES * prescaler);

		// wait next conversion :
		wasteCycles(CONVERSION_ADC_CYCLES * prescaler);

		bool result = AVRUNIT_ASSERT_IN_RANGE_LONG(a2d->read(), 0, 1);

		a2d->setChannelMode(ADCs::ChannelModes::ADC1);

		// throw away the current conversion because channel changed:
		wasteCycles(CONVERSION_ADC_CYCLES * prescaler);

		// wait next conversion :
		wasteCycles(CONVERSION_ADC_CYCLES * prescaler);

		result &= AVRUNIT_ASSERT_IN_RANGE_LONG(a2d->read(), 1023, 1);


		a2d->setChannelMode(ADCs::ChannelModes::ADC2);

		// throw away the current conversion because channel changed:
		wasteCycles(CONVERSION_ADC_CYCLES * prescaler);

		// wait next conversion :
		wasteCycles(CONVERSION_ADC_CYCLES * prescaler);

		result &= AVRUNIT_ASSERT_IN_RANGE_LONG(a2d->read(), (long long) (adcOtherVoltage/adcVCCVoltage * 1023), 25);

		return result;
	}


	bool testDifferentialModes()
	{
		// quite frankly, this test case doesn't test much

		a2d->setPrescaler(ADCs::Prescalers::SLOWEST_128);

		a2d->setChannelMode(ADCs::ChannelModes::ADC0_ADC0_X10);

		a2d->rightAdjust();

		a2d->enableADC();

		// throw away the first conversion :

		a2d->startConverter();

		while(a2d->isBusy());


		a2d->startConverter();

		while(a2d->isBusy());

		uint16_t adc0adc0x10twosComplement = a2d->read();

		intmax_t adc0adc0x10 = fromTwosCompletement(adc0adc0x10twosComplement, 9);

		bool result = AVRUNIT_ASSERT_IN_RANGE_LONG(adc0adc0x10, 0, 1);

		a2d->setChannelMode(ADCs::ChannelModes::ADC0_ADC0_X200);

		a2d->startConverter();

		while(a2d->isBusy());

		uint16_t adc0adc0x200twosComplement = a2d->read();

		intmax_t adc0adc0x200 = fromTwosCompletement(adc0adc0x200twosComplement, 9);

		result &= AVRUNIT_ASSERT_IN_RANGE_LONG(adc0adc0x200, 0, 1);

		return result;
	}

private:

	ADCs::ADCHardware * a2d;

	double adcGNDVoltage;
	double adcVCCVoltage;
	double adcOtherVoltage;

};


#endif /* ADCHardwareTest_H_ */
