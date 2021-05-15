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

#include "BitManipulation.h"
#include "../Utils/Utils.h"
uint8_t maskToConfig(uint8_t mask)
{
	uint8_t config = 0;

	for(size_t i = 0; i < 8; i++)
		if(bitIsSet(mask, i))
			config++;

	return config;
}

void setConfig(const IOAddress & reg, uint8_t configBitMask, uint8_t config)
{

	if (configBitMask == 0)
		return;

	*reg &= (uint8_t)~configBitMask; // clears all bits in the mask


	uint8_t shiftedConfig = 0x00;

	size_t configIndex = 0;
	for(size_t configBitMaskIndex = 0; configBitMaskIndex < 8; configBitMaskIndex++)
		if( bitIsSet(configBitMask, configBitMaskIndex))
			{
				changeBitValueTo(shiftedConfig, configBitMaskIndex, bitIsSet(config, configIndex)); // sets is a bit in position configBitMaskIndex if the responding bit in config is one
				configIndex++;
			}

	*reg |= shiftedConfig; // write the setting

}


uint8_t getConfig(IOAddress & reg, uint8_t configBitMask)
{

	if (configBitMask == 0)
		return 0;

	uint8_t maskLSB = 0;

	while ((configBitMask >> maskLSB) % 2 == 0) // we shift until we find the mask LSB
		maskLSB++;

	return (*reg & configBitMask) >> maskLSB;
}
