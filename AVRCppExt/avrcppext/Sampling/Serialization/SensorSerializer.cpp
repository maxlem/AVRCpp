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

#include "SensorSerializer.h"
#include "../Patterns/RotationalSamplingPattern.h"
#include "DataStructures/ActiveBuffers/ActiveReceiveBuffers/ReceiveEOLActiveStringBuffer.h"

#include "../../Sensors/Sample.h"

#include "Utils/Utils.h"
#include <avr/sleep.h>


SensorSerializer::SensorSerializer(Dictionary<char, Sensor *> * label2Sensors, ActiveBufferedUSART * activeUSART) :
label2Sensors(label2Sensors), activeUSART(activeUSART), currentPattern(NULL),
tbuf(BUFFERS_SIZE), rbuf(BUFFERS_SIZE, '\n'),
packetHeaderFormatString(PROG_MEM_STRING(":%s:%d:")), padding(PROG_MEM_STRING("_____")),
patternRegex(PROG_MEM_STRING("(Pattern):([^:]+):([0-9]+):([0-9]+):([a-zA-Z]+)"))
{
	activeUSART->setCurrentReceiveBuffer(&rbuf);
	activeUSART->enableReceiver();
	activeUSART->enableFrameReceivedInterrupts();

	activeUSART->setCurrentTransmitBuffer(&tbuf);
	activeUSART->enableTransmitter();


//	currentPattern = new RotationalSamplingPattern(PROG_MEM_STRING("xyzabcxyzabc"), 10);
}

SensorSerializer::~SensorSerializer()
{
}

void SensorSerializer::setCurrentPattern(SamplingPattern * currentPattern)
{
	this->currentPattern = currentPattern;
}


void SensorSerializer::receivePattern()
{
    if(rbuf.isOpen())
    	return;

    RegularExpressions::Result * regexResult = patternRegex.parse(rbuf.inspect());

	if(!isNull(regexResult))
	{
	    RegularExpressions::Group * patternNameGroup = regexResult->getGroup(2);
	    patternNameGroup->string[patternNameGroup->lenght] = '\0';

	    RegularExpressions::Group * patternRepetitionsGroup = regexResult->getGroup(3);

	    size_t patternRepetitions = atol(patternRepetitionsGroup->string);

	    RegularExpressions::Group * patternSizeGroup = regexResult->getGroup(4);

	    size_t patternSize = atol(patternSizeGroup->string);

	    RegularExpressions::Group * patternGroup = regexResult->getGroup(5);
	    patternGroup->string[patternGroup->lenght] = '\0';

	    if(patternSize == patternGroup->lenght)
	    {

			delete currentPattern;



			currentPattern = new RotationalSamplingPattern(patternNameGroup->string, patternGroup->string, patternRepetitions);

			printf("New pattern : %s \n\r %d rep. \n\r %d samples per packets\n\r Pattern : %s\n\r", patternNameGroup->string, patternRepetitions, patternSize, patternGroup->string);

	    }

	    delete regexResult;
	}

	rbuf.reset();
	rbuf.clearMemory();

	activeUSART->enableFrameReceivedInterrupts();

}


void SensorSerializer::executeCurrentPattern()
{
	if(isNull(currentPattern))
		return;

	currentPattern->reset();

	while(!currentPattern->isExhausted())
	{
		serializePacket();
		activeUSART->enableFrameReceivedInterrupts();
	}
}

void SensorSerializer::serializePacketHeader()
{
	char * header = new(Allocators::STACK) char[PACKET_HEADER_SIZE];
    sprintf(header, packetHeaderFormatString, currentPattern->getName(), currentPattern->getRepetitions() - currentPattern->getRepetitionsLeft());

//    tbuf << padding;
    tbuf << header;
    activeUSART->enableTransmitterReadyInterrupts();
}

void SensorSerializer::serializePacket()
{
    serializePacketHeader();

    uint8_t sum = 0;

    for(size_t index = 0; index < currentPattern->getSize(); index++)
    {

        prepareTransmitterForSleep();

        char label = currentPattern->currentLabel();

    	Sensor ** sensor = label2Sensors->find(label);

    	if(!isNull(sensor))
    	{
    		AbstractSample sample = (*sensor)->read();

    		sum += sample.computeSum();

			Buffer<char> buffer = sample.serialize();

		    tbuf << buffer;
    	}


    	activeUSART->enableTransmitterReadyInterrupts();

        currentPattern->nextLabel();
    }

    tbuf << checksum<uint8_t>(sum);

    tbuf << ":\n\r";

//    tbuf << padding;
    activeUSART->flushCurrentTransmitBuffer();
    activeUSART->enableTransmitterReadyInterrupts();
}


void SensorSerializer::prepareTransmitterForSleep()
{
    activeUSART->disableTransmitterReadyInterrupts();
    activeUSART->writeBaudSleepSafe();
}






