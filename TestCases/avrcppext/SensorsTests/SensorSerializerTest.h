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

#ifndef SensorSerializerTest_H_
#define SensorSerializerTest_H_

#include "TestAssert.h"

#include "Sampling/Serialization/SensorSerializer.h"



#include "Coms/USART/ActiveBuffered/ActiveBufferedUSARTFrameReceivedCallback.h"
#include "Coms/USART/ActiveBuffered/ActiveBufferedUSARTTransmitterReadyCallback.h"
#include "DataStructures/ActiveBuffers/ActiveReceiveBuffers/ReceiveActiveStringBuffer.h"
#include "DataStructures/ActiveBuffers/ActiveReceiveBuffers/ReceiveEOLActiveStringBuffer.h"
#include "CallbackServers/FastCallbackServer.h"


class SensorSerializerTest : public TestCase<SensorSerializerTest>
{


public:

	SensorSerializerTest(const prog_mem * testMethodName_P, TestCase<SensorSerializerTest>::TestMethod testMethod) :
		TestCase<SensorSerializerTest>(testMethodName_P, testMethod),
//		dataPacketHeader(PROG_MEM_STRING("_SensorSerializer_BIN%d.%d.5=cfHB")),
//		synchronizePacketHeader(PROG_MEM_STRING("Synchronize=HH"))
		formatString(PROG_MEM_STRING("_SensorSerializer_BIN%d.%d.5=cfQB")),
		synchronizeFormatString(PROG_MEM_STRING("Synchronize=QQ"))
	{

		TransmitActiveStringBuffer t(1); //linking bug workaround
		ReceiveActiveStringBuffer r(1); //linking bug workaround
		ReceiveEOLActiveStringBuffer reol(1, '\n');

	}

	void setUp()
	{
		enableInterrupts();
	}

	void tearDown()
	{
		disableInterrupts();
	}


//	bool teststart()
//	{
//		SensorSerializer * serializer = buildSensorSerializer();
//
//		while(true)
//		{
//			serializer->synchronize();
//			serializer->receivePattern();
//			serializer->executeCurrentPattern();
//		}
//
//	}

private:


//	SensorSerializer * buildSensorSerializer()
//	{
//		ADCs::ADCHardware * a2d = ADCs::ADCHardware::getInstance();
//		a2d->setVoltageReference(ADCs::VoltageReferences::AREF);
//		a2d->setPrescaler(ADCs::Prescalers::DIV_8);
//		a2d->setChannelMode(ADCs::ChannelModes::ADC0);
//		a2d->rightAdjust();
//		a2d->enableADC();
//		a2d->startConverter();
//
//		Dictionary<char, ChannelMode> * adclabelToChannelMap = new Dictionary<char, ChannelMode>(6);
//
//		adclabelToChannelMap->insertElement('x', ADCs::ChannelModes::ADC0);
//		adclabelToChannelMap->insertElement('y', ADCs::ChannelModes::ADC1);
//		adclabelToChannelMap->insertElement('z', ADCs::ChannelModes::ADC2);
//		adclabelToChannelMap->insertElement('a', ADCs::ChannelModes::ADC3);
//		adclabelToChannelMap->insertElement('b', ADCs::ChannelModes::ADC4);
//		adclabelToChannelMap->insertElement('c', ADCs::ChannelModes::ADC5);
//
//		Timers::Timer16bits3OCR * timer = Timers::Timer16bits3OCR::getTimer16bits3OCR(1);
//		timer->getCounter()->setPrescaler(Timers::Prescalers::DIV_8);
//
//		Coms::USART::USARTHardware * usartHardware = Coms::USART::USARTHardware::getUSARTHardware(1);
//
//		usartHardware->configureBitRate(34, true, false);
//
////		usartHardware->configureBitRate(103, false, false);
//
////		usartHardware->configureBitRate(8, true, false);
//
//		usartHardware->configureStopBitsMode(Coms::USART::StopBitsModes::ONE);
//
//		usartHardware->configureParityMode(Coms::USART::ParityModes::NONE);
//
//		Coms::USART::ActiveBufferedUSART * activeUSART = new Coms::USART::ActiveBufferedUSART(usartHardware);
//
//		Coms::USART::ActiveBufferedUSARTFrameReceivedCallback * rcb = new Coms::USART::ActiveBufferedUSARTFrameReceivedCallback(activeUSART);
//
//		Coms::USART::ActiveBufferedUSARTTransmitterReadyCallback * wcb = new Coms::USART::ActiveBufferedUSARTTransmitterReadyCallback(activeUSART);
//
//		FastCallbackServer::getInstance()->connect(30, rcb); 	//MAKE SURE USART1_RX_vect a.k.a __vector_30 in atmega128 is declared with DECLARE_CALLBACK
//																// and defined by DEFINE_FAST_CALLBACK
//		FastCallbackServer::getInstance()->connect(31, wcb);	//idem for USART1_UDRE_vect
//
//		return  new SensorSerializer(a2d, adclabelToChannelMap, activeUSART, timer);
//	}

	SensorSerializer * serializer;

	Coms::USART::ActiveBufferedUSART * com;
	Coms::USART::USARTHardware * usartHardware;
	Coms::USART::ActiveBufferedUSARTFrameReceivedCallback * rcb;
	Coms::USART::ActiveBufferedUSARTTransmitterReadyCallback * wcb;

	const prog_mem * formatString;
	const prog_mem * synchronizeFormatString;

};

#endif /* SensorSerializerTest_H_ */
