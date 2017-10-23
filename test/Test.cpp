/*
 * Test.cpp
 *
 *  Created on: 23.10.2017
 *      Author: abx724
 */


#include <iostream>
#include <thread>
#include "Test.h"
#include "HAL.h"
#include "Header.h"
#include "GpioTesting.h"
#include <sys/neutrino.h>
#include <hw/inout.h>

using namespace std;

namespace logicLayer{
namespace test{


Test::Test() {
	// TODO Auto-generated constructor stub

}

Test::~Test() {
	// TODO Auto-generated destructor stub
}


void Test::actuatorsTest(){

	hal::HAL hal;


	cout << "start " << __FUNCTION__ << endl;

	cout << "Teste Motoraktorik (schnell) " << endl;
	hal.motorStart();
	hal.motorRotateClockwise(); // BUG
	hal.motorFast();
	if( !nextTest() ) return;

	cout << "Teste Motoraktorik (langsam) " << endl;
	hal.motorSlow();
	if( !nextTest() ) return;

	cout << "Teste Motorstopp" << endl;
	hal.motorStop();
	if( !nextTest() ) return;

	cout << "Teste Weiche auf (bitte nicht zu lang auf lassen) " << endl;
	hal.switchPointOpen();
	if( !nextTest() ) return;

	cout << "Teste Weiche zu " << endl;
	hal.switchPointClose();

	if( !nextTest() ) return;

	cout << __FUNCTION__ <<  " beendet!" << endl;

}


void Test::mmiTest(){

	hal::HAL hal;

	hal.blinkGreen(Speed::fast);

	cout << "start " << __FUNCTION__ << endl;
	cout << "Teste alle Lichter der Ampel an " << endl;
	hal.yellowLightOn();
	hal.redLightOn();
	hal.greenLightOn();
	if( !nextTest() ) return;

	cout << "Teste alle Lichter der Ampel aus " << endl;
	hal.yellowLightOff();
	hal.redLightOff();
	hal.greenLightOff();
	if( !nextTest() ) return;

	cout << "Teste blinken der Ampel (schnell) " << endl;
	hal.blinkGreen(Speed::fast);
	hal.blinkRed(Speed::fast);
	hal.blinkYellow(Speed::fast);
	if( !nextTest() ) return;

	cout << "Rotes Licht der Ampel aus" << endl;
	hal.redLightOff();
	if( !nextTest() ) return;

	cout << "Gelbes Licht der Ampel aus" << endl;
	hal.yellowLightOff();
	if( !nextTest() ) return;

	cout << "Grünes Licht der Ampel aus" << endl;
	hal.greenLightOff();
	if( !nextTest() ) return;

	cout << "Teste blinken der Ampel (langsam) " << endl;
	hal.blinkGreen(Speed::slow);
	hal.blinkYellow(Speed::slow);
	hal.blinkRed(Speed::slow);
	if( !nextTest() ) return;

	cout << "Rotes Licht der Ampel aus" << endl;
	hal.redLightOff();
	if( !nextTest() ) return;

	cout << "Gelbes Licht der Ampel aus" << endl;
	hal.yellowLightOff();
	if( !nextTest() ) return;

	cout << "Grünes Licht der Ampel aus" << endl;
	hal.greenLightOff();
	if( !nextTest() ) return;

	cout << "Teste blinken der Ampel (langsam) " << endl;
	hal.blinkGreen(Speed::slow);
	hal.blinkYellow(Speed::slow);
	hal.blinkRed(Speed::slow);
	if( !nextTest() ) return;


	cout << "Teste blinken der Ampel (schnell) " << endl;
	hal.blinkGreen(Speed::fast);
	hal.blinkYellow(Speed::fast);
	hal.blinkRed(Speed::fast);
	if( !nextTest() ) return;

	cout << "Teste blinken der Ampel (langsam) " << endl;
	hal.blinkGreen(Speed::slow);
	hal.blinkYellow(Speed::slow);
	hal.blinkRed(Speed::slow);
	if( !nextTest() ) return;


	cout  << __FUNCTION__ << " beendet! " << endl;
}


void Test::sensorsTest(){

}

void Test::threadSafenessInGpioTest(){
	LOG_SCOPE;
	cout << "enter method " << __FUNCTION__ << endl;
	LOG_DEBUG << "1";
	ThreadCtl(_NTO_TCTL_IO_PRIV, 0);
	GpioTesting *gpio = new GpioTesting;

	cout << " after instance " << endl;
	LOG_DEBUG << "2";
	gpio->setBits(PORT::A, 0b11111111); //alles an
	cout << " after setBits " << endl;
	LOG_DEBUG << "3";
}


bool Test::nextTest(){
	cout << "Weiter zum nächsten Test? (Eingabe=Enter - Abbruch=beliebige Eingabe + Enter" << endl;
	return cin.get() == '\n';
}


} // end test
} // end logicLayer
