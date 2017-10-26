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

	cout << "test motor (clockwise, fast) " << endl;
	hal.motorStart();
	hal.motorRotateClockwise(); // BUG?
	hal.motorFast();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test motor (clockwise, slow) " << endl;
	hal.motorSlow();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test motor stop" << endl;
	hal.motorStop();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test open switch point - please continue soon" << endl;
	hal.switchPointOpen();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test close switch point " << endl;
	hal.switchPointClose();

	if( !nextTest(__FUNCTION__) ) return;

	cout << __FUNCTION__ <<  "  successful." << endl;

}


void Test::mmiTest(){

	hal::HAL hal;

	cout << "start " << __FUNCTION__ << endl;
	cout << "test lamps on: red, yellow, green" << endl;
	hal.yellowLightOn();
	hal.redLightOn();
	hal.greenLightOn();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test lamps off: red, yellow, green" << endl;
	hal.yellowLightOff();
	hal.redLightOff();
	hal.greenLightOff();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test blinking fast: red, yello, green " << endl;
	hal.blinkGreen(Speed::fast);
	hal.blinkRed(Speed::fast);
	hal.blinkYellow(Speed::fast);
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test blinking fast: yellow, green" << endl;
	hal.redLightOff();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test blinking fast: green" << endl;
	hal.yellowLightOff();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test blinking slow: red, yellow, green" << endl;
	hal.blinkGreen(Speed::slow);
	hal.blinkYellow(Speed::slow);
	hal.blinkRed(Speed::slow);
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test blinking slow: yellow, green" << endl;
	hal.redLightOff();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test blinking slow: green" << endl;
	hal.yellowLightOff();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test blinking slow: nothing" << endl;
	hal.greenLightOff();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test blinking slow: red, yellow, green" << endl;
	hal.blinkGreen(Speed::slow);
	hal.blinkYellow(Speed::slow);
	hal.blinkRed(Speed::slow);
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test blinking fast: red, yellow, green" << endl;
	hal.blinkGreen(Speed::fast);
	hal.blinkYellow(Speed::fast);
	hal.blinkRed(Speed::fast);
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test blinking slow: red, yellow, green" << endl;
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
	cout << "######################" 	<< endl;
	cout << "# rmw-cycle starting #" 	<< endl;
	cout << "# rmw-cycle finished #" 	<< endl;
	cout << "# rmw-cycle starting #" 	<< endl;
	cout << "# rmw-cycle finished #" 	<< endl;
	cout << "# ================== #" 	<< endl;

	GpioTesting *gpio = new GpioTesting;
	gpio->gainAccess();
	thread t1(&writeSomethingElse, gpio, 1);
	thread t2(&writeSomethingElse, gpio, 2);
	t1.join();
	t2.join();
	cout << "######################" << endl;
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
