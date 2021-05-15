#include "Coms/USART/USARTHardware.h"
#include "Coms/USART/stdio/stdioUSART.h"
#include "Utils/Blink.h"
#include "Timers/Timer16bits3OCR.h"
#include "Actuators/RCServos/RCServo.h"
#include "RegularExpressions/RegularExpression.h"
#include "Coms/USART/ActiveBuffered/ActiveBufferedUSART.h"
#include "DataStructures/ActiveBuffers/ActiveReceiveBuffers/ReceiveEOLActiveStringBuffer.h"

using Timers::Timer16bits3OCR;
using RegularExpressions::RegularExpression;


void configureTimerBC(size_t number)
{
    Timer16bits3OCR::getTimer16bits3OCR(number)->getCapturer()->setICRValue(40000); // roughly 20ms, the standard servo duty cycle, that will be our TOP
    Timer16bits3OCR::getTimer16bits3OCR(number)->getComparatorB()->setOCROutputPinMode(Timers::CompareModes::CLEAR_OC_PIN_ON_COMPARE_MATCH); // the pulse start at 0, ends at OCRValue
    Timer16bits3OCR::getTimer16bits3OCR(number)->getComparatorB()->setOCRValue(2000);
    Timer16bits3OCR::getTimer16bits3OCR(number)->getComparatorC()->setOCROutputPinMode(Timers::CompareModes::CLEAR_OC_PIN_ON_COMPARE_MATCH); // the pulse start at 0, ends at OCRValue
    Timer16bits3OCR::getTimer16bits3OCR(number)->getComparatorC()->setOCRValue(2000);
    Timer16bits3OCR::getTimer16bits3OCR(number)->setWaveGenerationMode(1, 1, 1, 0); //Fast PWM, TOP == ICR
    Timer16bits3OCR::getTimer16bits3OCR(number)->getCounter()->setPrescaler(Timers::Prescalers::DIV_8); //with a 16Mhz clock, that will give µs 8/16000000 = .5µs per tick

}

void displayHelp()
{
    printf(PROG_MEM_STRING("***************************************\n\r"
"Usages:  motor [number] [pwm] \'Enter\' \n\r"
"         motors [pwm1] [pwm2] [pwm3] [pwm4] [pwm5] [pwm6] \'Enter\' \n\r"
"         stop 'Enter\' \n\r"
"examples: motor 4 1500 \'Enter\' \n\r"
"          ... will set motor 4 pwm at 1500µs \n\r"
"          motors 1500 1500 1500 1200 1200 1200 \'Enter\' \n\r"
"          ... will set motors 1,2 and 3 pwm at 1500µs, motors 4,5 and 6 at 1200µs \n\r"
"          stop \'Enter\' \n\r"
"          ... will set all motors pwm at 1000µs \n\r"
"***************************************\n\r"));
}

int main()
{
//	Blink led(&PORTE, &DDRE, 1, 2, 500);



	stderr = stdout = Coms::USART::fdevopen(_FDEV_SETUP_WRITE, Coms::USART::USARTHardware::getUSARTHardware(0));

	displayHelp();

	configureTimerBC(5);
	configureTimerBC(1);
	configureTimerBC(3);
	configureTimerBC(4);


	RCServo * servos[8];

	servos[0] = new RCServo( Timer16bits3OCR::getTimer16bits3OCR(5)->getComparatorB(), &DDRL, PIN4, 2000, 4000);
	servos[1] = new RCServo( Timer16bits3OCR::getTimer16bits3OCR(5)->getComparatorC(), &DDRL, PIN5, 2000, 4000);
	servos[2] = new RCServo( Timer16bits3OCR::getTimer16bits3OCR(1)->getComparatorB(), &DDRB, PIN6, 2000, 4000);
	servos[3] = new RCServo( Timer16bits3OCR::getTimer16bits3OCR(1)->getComparatorC(), &DDRB, PIN7, 2000, 4000);
//	servos[4] = new RCServo( Timer16bits3OCR::getTimer16bits3OCR(4)->getComparatorB(), &DDRH, PIN5, 2000, 4000);
//	servos[5] = new RCServo( Timer16bits3OCR::getTimer16bits3OCR(4)->getComparatorC(), &DDRH, PIN4, 2000, 4000);
	servos[4] = new RCServo( Timer16bits3OCR::getTimer16bits3OCR(3)->getComparatorB(), &DDRE, PIN5, 2000, 4000);
	servos[5] = new RCServo( Timer16bits3OCR::getTimer16bits3OCR(3)->getComparatorC(), &DDRE, PIN4, 2000, 4000);




	RegularExpression setMotorRegex(PROG_MEM_STRING("(motor) ([1-6]) ([1-2][0-9][0-9][0-9]).*"));
	RegularExpression setMotorsRegex(PROG_MEM_STRING("(motors) ([1-2][0-9][0-9][0-9]) ([1-2][0-9][0-9][0-9]) ([1-2][0-9][0-9][0-9])"
			" ([1-2][0-9][0-9][0-9]) ([1-2][0-9][0-9][0-9]) ([1-2][0-9][0-9][0-9])"));
	RegularExpression stopRegex(PROG_MEM_STRING("stop"));
	RegularExpression helpRegex(PROG_MEM_STRING("help"));



	Coms::USART::ActiveBufferedUSART * activeUSART = new Coms::USART::ActiveBufferedUSART(Coms::USART::USARTHardware::getUSARTHardware(0));
	ReceiveEOLActiveStringBuffer rbuf(500, '\r');
	activeUSART->setCurrentReceiveBuffer(&rbuf);
	activeUSART->enableReceiver();
	activeUSART->enableFrameReceivedInterrupts();
	enableInterrupts();
	while(true)
	{


		if(!rbuf.isOpen())
		{
			RegularExpressions::Result * setMotorResult = setMotorRegex.parse(rbuf.inspect());
			RegularExpressions::Result * setMotorsResult = setMotorsRegex.parse(rbuf.inspect());
			RegularExpressions::Result * stopResult = stopRegex.parse(rbuf.inspect());
			RegularExpressions::Result * helpResult = helpRegex.parse(rbuf.inspect());
			char buffer[20];
			if(!isNull(setMotorResult))
			{

				size_t motor = atoi(setMotorResult->getGroup(2)->string);
				size_t pwm = atoi(setMotorResult->getGroup(3)->string);
			    servos[motor-1]->setPulseWidth(pwm);

			    printf("\n\rmotor %u was set to %u µs \n\r", motor, servos[motor-1]->getPulseWidth());

			    delete setMotorResult;
			}
			else if(!isNull(setMotorsResult))
			{

				for(size_t i = 2; i < setMotorsResult->numberOfGroups(); i++)
				{
					size_t pwm = atoi(setMotorsResult->getGroup(i)->string);
				    servos[i-2]->setPulseWidth(pwm);

				    printf(PROG_MEM_STRING("\n\rmotor %u was set to %u µs \n\r"), i-1, servos[i-2]->getPulseWidth());
				}
				delete setMotorsResult;
			}
			else if(!isNull(stopResult))
			{
				for(size_t i = 0; i < 6; i++)
				    servos[i]->setPulseWidth(1000);

				printf(PROG_MEM_STRING("\n\rall motors set to 1000 µs \n\r"));
			}
			else if(!isNull(helpResult))
			{
				displayHelp();
			}
			else
			{
				printf(PROG_MEM_STRING("\n\rInvalid command! \n\r"));
			}

			rbuf.reset();
			rbuf.clearMemory();

			activeUSART->enableFrameReceivedInterrupts();

		}
//		printf("pwm is at %u", pwm);
	}
}
