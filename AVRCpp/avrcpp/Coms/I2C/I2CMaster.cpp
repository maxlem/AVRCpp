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

#include "I2CMaster.h"
#include <stdio.h>
#include "../../Utils/Utils.h"
#include "../../Utils/Delay.h"

namespace Coms
{

namespace I2C
{

#define WAIT_TIME 8000
#define VERBOSE 1

I2CMaster::I2CMaster(I2CHardware * i2cHardware) :
i2cHardware(i2cHardware)
{
	// TODO Auto-generated constructor stub

}

I2CMaster::~I2CMaster()
{
	// TODO Auto-generated destructor stub
}

void I2CMaster::setDestinationAddress(uint8_t destinationAddress)
{
	this->destinationAddress = destinationAddress;
}

bool I2CMaster::selectRegister(uint8_t registerAddress)
{
	i2cHardware->command(TransmitActions::STOP_SIGNAL);
	wasteCycles(WAIT_TIME);

//	if(VERBOSE) fprintf(stderr, PROG_MEM_STRING("sending STOP_SIGNAL\n\r"));

	i2cHardware->command(TransmitActions::START_SIGNAL);
	while(!i2cHardware->readInterruptFlag());
//		if(VERBOSE) fprintf(stderr, PROG_MEM_STRING("waiting START_SIGNAL\n\r"));

	if(i2cHardware->getStatus() != TW_START)
	{
		if(VERBOSE) fprintf(stderr, PROG_MEM_STRING("i2cHardware->getStatus() != TW_START\n\r"));
		return false;
	}

	i2cHardware->writeDestinationAddress(destinationAddress, TransmitDirections::WRITE);
	i2cHardware->command(TransmitActions::READY);
	while(!i2cHardware->readInterruptFlag());

	if(i2cHardware->getStatus() != TW_MT_SLA_ACK)
	{
		if(VERBOSE) fprintf(stderr, PROG_MEM_STRING("i2cHardware->getStatus() != TW_MT_SLA_ACK\n\r"));
		return false;
	}

	i2cHardware->writeByte(registerAddress);
	i2cHardware->command(TransmitActions::READY);
	while(!i2cHardware->readInterruptFlag());

	if(i2cHardware->getStatus() != TW_MT_DATA_ACK)
	{
		if(VERBOSE) fprintf(stderr, PROG_MEM_STRING("i2cHardware->getStatus() != TW_MT_DATA_ACK\n\r"));
		return false;
	}

	return true;
}

uint8_t I2CMaster::readRegister(uint8_t registerAddress)
{
	uint8_t registerContent;

	if(!selectRegister(registerAddress))
	{
		if(VERBOSE) fprintf(stderr, PROG_MEM_STRING("selectRegister() failed, could not contact slave\n\r"));
		return 0;
	}

	i2cHardware->command(TransmitActions::START_SIGNAL);
	while(!i2cHardware->readInterruptFlag());

	if(i2cHardware->getStatus() != TW_REP_START)
	{
		if(VERBOSE) fprintf(stderr, PROG_MEM_STRING("i2cHardware->getStatus() != TW_REP_START\n\r"));
		return 0;
	}

	i2cHardware->writeDestinationAddress(destinationAddress, TransmitDirections::READ);
	i2cHardware->command(TransmitActions::READY);
	while(!i2cHardware->readInterruptFlag());

	if(i2cHardware->getStatus() != TW_MR_SLA_ACK)
	{
		if(VERBOSE) fprintf(stderr, PROG_MEM_STRING("i2cHardware->getStatus() != TW_MR_SLA_ACK\n\r"));
		return 0;
	}

	// SLA+R ACK'ed : here we do nothing

	i2cHardware->command(TransmitActions::READY); // DATA_NACK will be returned after the first (and last byte have been received)
	while(!i2cHardware->readInterruptFlag());

	if(i2cHardware->getStatus() != TW_MR_DATA_NACK)
	{
		if(VERBOSE) fprintf(stderr, PROG_MEM_STRING("i2cHardware->getStatus() != TW_MR_DATA_NACK\n\r"));
		return 0;
	}

	registerContent = i2cHardware->readByte();

	i2cHardware->command(TransmitActions::STOP_SIGNAL);
	wasteCycles(WAIT_TIME);


	return registerContent;

}

void I2CMaster::writeRegister(uint8_t registerAddress, uint8_t registerContent)
{

	while(!selectRegister(registerAddress))
	{
		if(VERBOSE) fprintf(stderr, PROG_MEM_STRING("selectRegister() failed, could not contact slave\n\r"));
		return;
	}

	i2cHardware->writeByte(registerContent);

	i2cHardware->command(TransmitActions::READY);
	while(!i2cHardware->readInterruptFlag());

	i2cHardware->command(TransmitActions::STOP_SIGNAL);
	wasteCycles(WAIT_TIME);

}

void I2CMaster::writeRegistersAM(uint8_t registerAddress, uint8_t *RegisterBuf, uint32_t BufSizeByte){

	while(!selectRegister(registerAddress))
	{
		if(VERBOSE) fprintf(stderr, PROG_MEM_STRING("selectRegister() failed, could not contact slave\n\r"));
		return;
	}

	for(unsigned int i = 0; i < BufSizeByte; i++){
		i2cHardware->writeByte(RegisterBuf[i]);
		i2cHardware->command(TransmitActions::READY);
		while(!i2cHardware->readInterruptFlag());
	}

	i2cHardware->command(TransmitActions::STOP_SIGNAL);
	wasteCycles(WAIT_TIME);


}

void I2CMaster::readRegisters(uint8_t startRegisterAddress, ActiveReceiveBuffer * receiveBuffer)
{
	if(!selectRegister(startRegisterAddress))
	{
		if(VERBOSE) fprintf(stderr, PROG_MEM_STRING("selectRegister() failed, could not contact slave\n\r"));
		return;
	}

	i2cHardware->command(TransmitActions::START_SIGNAL);
	while(!i2cHardware->readInterruptFlag());

	i2cHardware->writeDestinationAddress(destinationAddress, TransmitDirections::READ);

	i2cHardware->command(TransmitActions::READY);
	while(!i2cHardware->readInterruptFlag());

	while(receiveBuffer->isOpen())
	{

		i2cHardware->command(TransmitActions::ACKNOWLEDGE); // DATA_ACK will be returned

		while(!i2cHardware->readInterruptFlag());

		receiveBuffer->receiveByte(i2cHardware->readByte());
	}

	i2cHardware->command(TransmitActions::STOP_SIGNAL);
	wasteCycles(WAIT_TIME);

}

void I2CMaster::writeRegisters(uint8_t startRegisterAddress, ActiveTransmitBuffer * transmitBuffer)
{

	if(!selectRegister(startRegisterAddress))
	{
		if(VERBOSE) fprintf(stderr, PROG_MEM_STRING("selectRegister() failed, could not contact slave\n\r"));
		return;
	}

	while(transmitBuffer->isOpen())
	{
		i2cHardware->writeByte(transmitBuffer->transmitByte());

		i2cHardware->command(TransmitActions::READY);
		while(!i2cHardware->readInterruptFlag());
	}

	i2cHardware->command(TransmitActions::STOP_SIGNAL);
	wasteCycles(WAIT_TIME);

}

}

}
