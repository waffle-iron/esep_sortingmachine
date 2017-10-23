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
	if( !nextTest(__FUNCTION__) ) return;

	cout << "Teste Motoraktorik (langsam) " << endl;
	hal.motorSlow();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "Teste Motorstopp" << endl;
	hal.motorStop();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "Teste Weiche auf (bitte nicht zu lang auf lassen) " << endl;
	hal.switchPointOpen();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "Teste Weiche zu " << endl;
	hal.switchPointClose();

	if( !nextTest(__FUNCTION__) ) return;

	cout << __FUNCTION__ <<  "  successful." << endl;

}


void Test::mmiTest(){

	hal::HAL hal;

	hal.blinkGreen(Speed::fast);

	cout << "start " << __FUNCTION__ << endl;
	cout << "Teste alle Lichter der Ampel an " << endl;
	hal.yellowLightOn();
	hal.redLightOn();
	hal.greenLightOn();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "Teste alle Lichter der Ampel aus " << endl;
	hal.yellowLightOff();
	hal.redLightOff();
	hal.greenLightOff();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "Teste blinken der Ampel (schnell) " << endl;
	hal.blinkGreen(Speed::fast);
	hal.blinkRed(Speed::fast);
	hal.blinkYellow(Speed::fast);
	if( !nextTest(__FUNCTION__) ) return;

	cout << "Rotes Licht der Ampel aus" << endl;
	hal.redLightOff();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "Gelbes Licht der Ampel aus" << endl;
	hal.yellowLightOff();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "Grünes Licht der Ampel aus" << endl;
	hal.greenLightOff();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "Teste blinken der Ampel (langsam) " << endl;
	hal.blinkGreen(Speed::slow);
	hal.blinkYellow(Speed::slow);
	hal.blinkRed(Speed::slow);
	if( !nextTest(__FUNCTION__) ) return;

	cout << "Rotes Licht der Ampel aus" << endl;
	hal.redLightOff();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "Gelbes Licht der Ampel aus" << endl;
	hal.yellowLightOff();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "Grünes Licht der Ampel aus" << endl;
	hal.greenLightOff();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "Teste blinken der Ampel (langsam) " << endl;
	hal.blinkGreen(Speed::slow);
	hal.blinkYellow(Speed::slow);
	hal.blinkRed(Speed::slow);
	if( !nextTest(__FUNCTION__) ) return;


	cout << "Teste blinken der Ampel (schnell) " << endl;
	hal.blinkGreen(Speed::fast);
	hal.blinkYellow(Speed::fast);
	hal.blinkRed(Speed::fast);
	if( !nextTest(__FUNCTION__) ) return;

	cout << "Teste blinken der Ampel (langsam) " << endl;
	hal.blinkGreen(Speed::slow);
	hal.blinkYellow(Speed::slow);
	hal.blinkRed(Speed::slow);
	if( !nextTest(__FUNCTION__) ) return;


	cout  << __FUNCTION__ << " successful. " << endl;
}


void Test::sensorsTest(){

}

void Test::writeSomethingElse(hal::io::GPIO *gpio, int difference) {
	port_t port = gpio->read(PORT::A); // read port to write definetly something different so write method gets called
	gpio->setBits(PORT::A, port + difference);
}

void Test::threadSafenessInGpioTest(){
	cout << "start " << __FUNCTION__ << endl;

	cout << "Looks the same?"<<endl;
	cout << "################" << endl;
	cout << "read-modify-write cycle is starting" << endl;
	cout << "read-modify-write cycle finished" << endl;
	cout << "read-modify-write cycle is starting" << endl;
	cout << "read-modify-write cycle finished" << endl;
	cout << "################" << endl;


	GpioTesting *gpio = new GpioTesting;
	gpio->gainAccess();
	cout << "################" << endl;
	thread t1(&writeSomethingElse, gpio, 1);
	thread t2(&writeSomethingElse, gpio, 2);
	t1.join();
	t2.join();
	cout << "################" << endl;
	if( !nextTest(__FUNCTION__) ) return;

	cout << "start " << __FUNCTION__ << endl;

	cout << __FUNCTION__ << " successful." << endl;
}


bool Test::nextTest(string functionName){
	cout << "Was the test successful and do you want to go on?\n"<<
			"  yes: hit return\n"<<
			"  no : hit any key followed by return" << endl;
	if (cin.get() == '\n'){
		return true;
	} else {
		cout << "##### "<<functionName << " NOT succesfull." << " #####"<< endl;
		cout << "Hit return to go on" << endl;
		cin.get();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return false;
	}
}


} /* test */
} /* logicLayer */
