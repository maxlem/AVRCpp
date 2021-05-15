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

#ifndef SensorSerializer_H_
#define SensorSerializer_H_

#include "ADC/ADCHardware.h"
#include "DataStructures/Dictionary.h"
#include "Coms/USART/ActiveBuffered/ActiveBufferedUSART.h"
#include "DataStructures/ActiveBuffers/ActiveTransmitBuffers/TransmitActiveStringBuffer.h"
#include "DataStructures/ActiveBuffers/ActiveReceiveBuffers/ReceiveEOLActiveStringBuffer.h"
#include "../../RegularExpressions/RegularExpression.h"
#include "Timers/Timer16bits3OCR.h"
#include "../Patterns/SamplingPattern.h"
#include "../../Sensors/ADCSensor.h"
#include "SerializableSample.h"

using ADCs::ADCHardware;
using ADCs::ChannelMode;
using Coms::USART::ActiveBufferedUSART;
using Timers::Timer16bits3OCR;
using RegularExpressions::RegularExpression;

#define BUFFERS_SIZE 2000
#define PACKET_HEADER_SIZE 25
#define OVERSAMPLING_COUNT 8

class SensorSerializer
{
public:
	SensorSerializer(Dictionary<char, Sensor *> * label2Sensors, ActiveBufferedUSART * activeUSART);
	virtual ~SensorSerializer();


	void receivePattern();
	void setCurrentPattern(SamplingPattern * currentPattern);
	void executeCurrentPattern();

protected:

	Dictionary<char, Sensor *> * label2Sensors;
	ActiveBufferedUSART * activeUSART;
	SamplingPattern * currentPattern;
	TransmitActiveStringBuffer tbuf;
	ReceiveEOLActiveStringBuffer rbuf;


	char * packetHeader;
	const prog_mem * packetHeaderFormatString;
	const prog_mem * padding;
	RegularExpression patternRegex;

private:

    void serializePacket();

	void serializePacketHeader();

    void prepareTransmitterForSleep();




    void conversionComplete();
    volatile bool isConversionComplete;

    friend class SensorSerializerCallback;
};

#endif /* SensorSerializer_H_ */
