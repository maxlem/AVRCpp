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
#include <stdlib.h>
#include "Utils/Utils.h"
#include "Utils/Delay.h"
#include "Sampling/Serialization/SensorSerializer.h"
//#include "Sensors/SCA3000.h"
#include "Sensors/TimeSensor.h"
#include "Sensors/TimerOverflowSensor.h"
#include "Sensors/TimestampSensor.h"
//#include "Sensors/DummySensor.h"
#include "Sampling/Patterns/RotationalSamplingPattern.h"
#include "Coms/USART/ActiveBuffered/ActiveBufferedUSART.h"
#include "Coms/USART/ActiveBuffered/ActiveBufferedUSARTFrameReceivedCallback.h"
#include "Coms/USART/ActiveBuffered/ActiveBufferedUSARTTransmitterReadyCallback.h"
#include "Coms/USART/stdio/stdioUSART.h"
#include "DataStructures/ActiveBuffers/ActiveReceiveBuffers/ReceiveActiveStringBuffer.h"
#include "DataStructures/ActiveBuffers/ActiveReceiveBuffers/ReceiveEOLActiveStringBuffer.h"
#include "CallbackServers/FastCallbackServer.h"




SensorSerializer * buildSensorSerializer()
{
	ADCs::ADCHardware * adc = ADCs::ADCHardware::getInstance();
	adc->setVoltageReference(ADCs::VoltageReferences::AREF);
	adc->setPrescaler(ADCs::Prescalers::DIV_32);
	adc->setChannelMode(ADCs::ChannelModes::ADC0);
	adc->rightAdjust();
	adc->enableADC();
	adc->startConverter();

//	Coms::SPI::SPIHardware * spiHardware = Coms::SPI::SPIHardware::getSPIHardware(0);
//	spiHardware->setPrescaler(Coms::SPI::Prescalers::DIV_16, false);
//	spiHardware->setSPIPinsDirections(OUTPUT, OUTPUT, OUTPUT, OUTPUT);
//	spiHardware->setMaster();
//	spiHardware->transmitMSBFirst();
//	spiHardware->enable();
//
//
//	Coms::SPI::SPIMaster * spiMaster = new Coms::SPI::SPIMaster(spiHardware, &PORTC, &DDRC, PINC0);

	Timers::Timer16bits3OCR * timer = Timers::Timer16bits3OCR::getTimer16bits3OCR(1);
	timer->getCounter()->setPrescaler(Timers::Prescalers::DIV_TIMER16_64);

	Dictionary<char, Sensor* > * label2Sensor = new Dictionary<char, Sensor*>(15);

//	label2Sensor->insertElement('x', new SCA3000(spiMaster, 0x05));
//	label2Sensor->insertElement('y', new SCA3000(spiMaster, 0x07));
//	label2Sensor->insertElement('z', new SCA3000(spiMaster, 0x09));
//	label2Sensor->insertElement('x', new DummySensor());
//	label2Sensor->insertElement('y', new DummySensor());
//	label2Sensor->insertElement('z', new DummySensor());
//	label2Sensor->insertElement('a', new DummySensor());
//	label2Sensor->insertElement('b', new DummySensor());
//	label2Sensor->insertElement('c', new DummySensor());
	label2Sensor->insertElement('x', new ADCSensor(adc, ADCs::ChannelModes::ADC4));
	label2Sensor->insertElement('y', new ADCSensor(adc, ADCs::ChannelModes::ADC3));
	label2Sensor->insertElement('z', new ADCSensor(adc, ADCs::ChannelModes::ADC2));
	label2Sensor->insertElement('a', new ADCSensor(adc, ADCs::ChannelModes::ADC6));
	label2Sensor->insertElement('b', new ADCSensor(adc, ADCs::ChannelModes::ADC5));
	label2Sensor->insertElement('c', new ADCSensor(adc, ADCs::ChannelModes::ADC7));
	label2Sensor->insertElement('t', new TimeSensor(timer->getCounter()));
//	label2Sensor->insertElement('T', new TimerOverflowSensor(timer->getCounter()));
	label2Sensor->insertElement('s', new TimestampSensor(timer->getCounter()));


	Coms::USART::USARTHardware * usartHardware = Coms::USART::USARTHardware::getUSARTHardware(1);

//	usartHardware->configureBitRate(832, true, false); // 2400

//	usartHardware->configureBitRate(103, false, false); // 9600

	usartHardware->configureBitRate(34, true, false);	// 56700

//	usartHardware->configureBitRate(16, false, false);



//		usartHardware->configureBitRate(8, true, false);

	usartHardware->configureStopBitsMode(Coms::USART::StopBitsModes::ONE);

	usartHardware->configureParityMode(Coms::USART::ParityModes::NONE);

	Coms::USART::ActiveBufferedUSART * activeUSART = new Coms::USART::ActiveBufferedUSART(usartHardware);

	return  new SensorSerializer(label2Sensor, activeUSART);
}

int main()
{
	TransmitActiveStringBuffer t(1); //linking bug workaround
	ReceiveActiveStringBuffer r(1); //linking bug workaround
	ReceiveEOLActiveStringBuffer reol(1, '\n');

	stderr = Coms::USART::fdevopen(_FDEV_SETUP_RW, Coms::USART::USARTHardware::getUSARTHardware(0));

	stdin = stdout = Coms::USART::fdevopen(_FDEV_SETUP_RW, Coms::USART::USARTHardware::getUSARTHardware(0));

//	printf("IMUCalibration \n\r-----------------------\n\r");

	SensorSerializer * serializer = buildSensorSerializer();

	serializer->setCurrentPattern(new RotationalSamplingPattern("pkt", PROG_MEM_STRING("xyzabcs"), 100));

	enableInterrupts();

	while(true)
	{
//		serializer->synchronize();
		serializer->receivePattern();
		serializer->executeCurrentPattern();
	}

}
