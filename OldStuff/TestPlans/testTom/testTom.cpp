//#include "testTom.h"
//#include "AVRHardware/AnalogToDigital/AnalogToDigital.h"
//
//
//
//void testTom::testTomLcd() {
//	Blink* testB = new Blink(&PORTD, &DDRD, 7);
//	testB->blink(2, 100);
//
//	HD44780 lcd(&PORTD, &DDRD, 0, 4, 5, 6);
//
//	DDRA = 0x00;	//pour mettre le port en input!!!
//	AnalogToDigital* a2d = AnalogToDigital::getInstance();
//	a2d->powerOn();
//	a2d->configure(128, 0x01);	//AVCCpin, AVREFpin, Internal2dot56Volts
//
//	uint8_t ad0;
//	float pulseWidth = 0;
//
//	lcd.initDisplay();
//	lcd.displaySetup(1, 0, 0);
//	lcd.clearDisplay();
//	lcd.printLineAt(0, 0, "ADC:");
//
//	DDRB = 0x08;
//	Timer8SingleOCR * timer0 = Timer8SingleOCR::getTimer0();
//	PWM8bits pwm( timer0, FastPWM, 0);
//
//	afficherValeur8(1, 5, pwm.setCycleLenght(20), &lcd);
//	pwm.startPWM();
//
//	while(true) {
//
//		ad0 = a2d->eightBitsRead(0);
//
//
//		afficherValeur8(0, 5, ad0, &lcd);
//
//		//pulseWidth = (((float)ad0/(float)255) + 1);
//		pulseWidth = ad0;
//		//for(uint8_t i = 0 ; i <= 255 ; i++){
//
//		//	pulseWidth = i;
//			timer0->startWaveGeneration(1024, (((float)ad0/(float)255)*16)+15);
//		//}
//	}
//}
//
//void testTom::afficherValeur8(uint8_t lineNumber, uint8_t rowNumber, uint8_t data, HD44780 *lcd){
//		lcd->printLineAt(lineNumber, rowNumber, "   ");
//
//		if(data > 99){
//			lcd->printNumberAt(lineNumber, rowNumber, data);
//		}
//		if(data < 100 && data > 9){
//			lcd->printNumberAt(lineNumber, rowNumber + 1, data);
//		}
//		if(data < 10){
//			lcd->printNumberAt(lineNumber, rowNumber + 2, data);
//		}
//}
//
//
