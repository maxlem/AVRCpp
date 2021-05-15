/*
 * ComI2CtestsDongle.h
 *
 *  Created on: 2009-09-14
 *      Author: malem303
 */


#ifndef CallbackComI2CMasterTest_H_
#define CallbackComI2CMasterTest_H_
#include "TestCase.h"
#include "Synchronization/NormallyHighSynchronizer.h"
#include "Communication/Com.h"
#include "Communication/I2C/ComI2C.h"
#include "Communication/I2C/Modes/Callback/Master.h"
#include "DataStructures/ActiveBuffers/ReceiveBuffers/EOLCallBackReceiveBuffer.h"
#include "DataStructures/ActiveBuffers/TransmitBuffers/CallbackTransmitBuffer.h"

#include "Utils/Delay.h"

#define MANUAL

using Coms::I2C::ComI2C;
using Coms::I2C::Callback::Master;

#define READ_MARGIN 10

class CallbackComI2CMasterTest : public TestCase<CallbackComI2CMasterTest>, public NormallyHighSynchronizer
{
public:


	CallbackComI2CMasterTest(const prog_mem * testMethodName_P, TestCase<CallbackComI2CMasterTest>::TestMethod testMethod) :
	TestCase<CallbackComI2CMasterTest>(testMethodName_P, testMethod), NormallyHighSynchronizer(&DDRE, &PORTE, &PINE, PINE6, PINE7),
	message(PROG_MEM_STRING("CallbackI2C_TEST123"))
	{
		comUnderTest = ComI2C::getInstance(0);
		comUnderTest->setSlaveAddress(13);
		comUnderTest->setDestinationAddress(12);
		comUnderTest->setMode(Master::getInstance());

	}

	~CallbackComI2CMasterTest()
	{
	}
	static void bufferFullCallback()
	{
		bufferFull = true;
		calledBack = true;
		comUnderTest->abortRead();
	}
	static void eolCallback()
	{
		eolFound = true;
		calledBack = true;
		comUnderTest->abortRead();
	}

	static void writeCompleteCallback()
	{
		writeComplete = true;
		calledBack = true;
		comUnderTest->abortWrite();
	}

	void setUp()
	{
		calledBack = false;

		bufferFull = false;
		eolFound = false;

		writeComplete = false;


	}

	void tearDown()
	{

	}

	bool testwrite()
	{



		TransmitBuffer * tbuf = new CallbackTransmitBuffer(50, CallbackComI2CMasterTest::writeCompleteCallback);

		*tbuf << message << '\n';

		sendSignal();

		enableInterrupts();

		bool result = comUnderTest->write(tbuf);

		while(!writeComplete);

		disableInterrupts();

		result &= AVRUNIT_ASSERT(result);

		delete tbuf;

		return result;
	}

	bool testread()
	{

		CallbackReceiveBuffer * rbuf = new EOLCallBackReceiveBuffer(50, CallbackComI2CMasterTest::bufferFullCallback, '\0', CallbackComI2CMasterTest::eolCallback);

		sendSignal();

		enableInterrupts();

		comUnderTest->read(rbuf);


		while(!calledBack);


		disableInterrupts();


		char * string = rbuf->unload();

		const char * found = strstr(string, message);

		bool result = AVRUNIT_ASSERT(!isNull(found));

		if(!result && !isNull(string))
			printf("Received : %s\n\r", string);

		delete rbuf;


		return result;
	}



private:

	static volatile bool calledBack;

	static volatile bool bufferFull;
	static volatile bool eolFound;


	static volatile bool writeComplete;

	const prog_mem * message;
	const prog_mem * toWrite;

	static ComI2C * comUnderTest;
};

volatile bool CallbackComI2CMasterTest::calledBack = false;

volatile bool CallbackComI2CMasterTest::bufferFull = false;
volatile bool CallbackComI2CMasterTest::eolFound = false;

volatile bool CallbackComI2CMasterTest::writeComplete = false;

ComI2C * CallbackComI2CMasterTest::comUnderTest;

#endif /* CallbackComI2CMasterTest_H_ */
