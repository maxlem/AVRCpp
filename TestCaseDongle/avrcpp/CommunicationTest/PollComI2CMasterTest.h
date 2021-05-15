/*
 * ComI2CtestsDongle.h
 *
 *  Created on: 2009-09-14
 *      Author: malem303
 */


#ifndef PollComI2CMasterTest_H_
#define PollComI2CMasterTest_H_
#include "TestCase.h"
#include "Synchronization/NormallyHighSynchronizer.h"
#include "Communication/Com.h"
#include "Communication/I2C/ComI2C.h"
#include "Communication/I2C/Modes/Poll/Master.h"
#include "DataStructures/ActiveBuffers/ReceiveBuffers/EOLReceiveBuffer.h"
#include "DataStructures/ActiveBuffers/TransmitBuffers/TransmitBuffer.h"

#include "Utils/Delay.h"

#define MANUAL

using Coms::I2C::ComI2C;
//using Coms::I2C::Poll::Master;

class PollComI2CMasterTest : public TestCase<PollComI2CMasterTest>, public NormallyHighSynchronizer
{
public:


	PollComI2CMasterTest(const prog_mem * testMethodName_P, TestCase<PollComI2CMasterTest>::TestMethod testMethod) :
	TestCase<PollComI2CMasterTest>(testMethodName_P, testMethod), NormallyHighSynchronizer(&DDRE, &PORTE, &PINE, PINE6, PINE7),
	message(PROG_MEM_STRING("CallbackI2C_TEST123"))
	{
		comUnderTest = ComI2C::getInstance(0);
		comUnderTest->setSlaveAddress(13);
		comUnderTest->setDestinationAddress(12);
		comUnderTest->setMode(Coms::I2C::Poll::Master::getInstance());
	}

	void tearDown()
	{
	}

	bool testwrite()
	{

		TransmitBuffer * tbuf = new TransmitBuffer(25);

		*tbuf << message << '\n';

		sendSignal();

		comUnderTest->write(tbuf);

		bool result = AVRUNIT_ASSERT_AUTONAME(tbuf->isEmpty());

		delete tbuf;

		return result;
	}

	bool testread()
	{
		ReceiveBuffer * rbuf = new EOLReceiveBuffer(25, '\0');

		sendSignal();

		comUnderTest->read(rbuf);

		char * string = rbuf->unload();

		const char * found = strstr(string, message);

		bool result = AVRUNIT_ASSERT_AUTONAME(!isNull(found));

		if(isNull(found))
			printf("Received : %s\n\r", string);

		delete rbuf;

		return result;
	}



private:

	const prog_mem * message;
	const prog_mem * toWrite;

	ComI2C * comUnderTest;
};

#endif /* PollComI2CMasterTest_H_ */
