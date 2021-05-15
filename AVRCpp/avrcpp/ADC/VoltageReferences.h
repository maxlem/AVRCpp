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

#ifndef VoltageReferencesV3_H_
#define VoltageReferencesV3_H_

#include "../Utils/Utils.h"


namespace ADCs
{


namespace VoltageReferences
{
	/*!
	 * Reference voltage modes
	 */
	enum VoltageReference
	{
		AREF = 0x00u,		//!<!< use the voltage at the AREF pin
		AVCC = 0x01u,		//!<!< use the voltage at the AVCC pin
		INTERNAL = 0x03u	//!<!< internal regulated (often 1.0V or 2.56V) reference, you should decouple AREF with a small capacitor
	};
}

}
#endif /* VoltageReferences_H_ */
