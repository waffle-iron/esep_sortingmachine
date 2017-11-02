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


Test::Test(hal::HAL* hal) {
	_hal = hal;
}

Test::~Test() {
}


void Test::actuatorsTest(){

	cout << "start " << __FUNCTION__ << endl;

	cout << "test motor (counterclockwise, fast) " << endl;
	_hal->motorStart();
	_hal->motorRotateCounterclockwise();
	_hal->motorFast();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test motor (counterclockwise, slow) " << endl;
	_hal->motorStart();
	_hal->motorRotateCounterclockwise();
	_hal->motorSlow();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test motor (clockwise, fast) " << endl;
	_hal->motorStart();
	_hal->motorRotateClockwise();
	_hal->motorFast();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test motor (clockwise, slow) " << endl;
	_hal->motorSlow();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test motor stop" << endl;
	_hal->motorStop();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test open switch point - please continue soon" << endl;
	_hal->switchPointOpen();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test close switch point " << endl;
	_hal->switchPointClose();

	if( !nextTest(__FUNCTION__) ) return;

	cout << __FUNCTION__ <<  "  successful." << endl;

}


void Test::mmiTest(){

	cout << "start " << __FUNCTION__ << endl;
	cout << "test lamps on: red, yellow, green" << endl;
	_hal->yellowLightOn();
	_hal->redLightOn();
	_hal->greenLightOn();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test lamps off: red, yellow, green" << endl;
	_hal->yellowLightOff();
	_hal->redLightOff();
	_hal->greenLightOff();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test blinking fast: red, yello, green " << endl;
	_hal->blinkGreen(Speed::fast);
	_hal->blinkRed(Speed::fast);
	_hal->blinkYellow(Speed::fast);
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test blinking fast: yellow, green" << endl;
	_hal->redLightOff();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test blinking fast: green" << endl;
	_hal->yellowLightOff();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test blinking slow: red, yellow, green" << endl;
	_hal->blinkGreen(Speed::slow);
	_hal->blinkYellow(Speed::slow);
	_hal->blinkRed(Speed::slow);
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test blinking slow: yellow, green" << endl;
	_hal->redLightOff();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test blinking slow: green" << endl;
	_hal->yellowLightOff();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test blinking slow: nothing" << endl;
	_hal->greenLightOff();
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test blinking slow: red, yellow, green" << endl;
	_hal->blinkGreen(Speed::slow);
	_hal->blinkYellow(Speed::slow);
	_hal->blinkRed(Speed::slow);
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test blinking fast: red, yellow, green" << endl;
	_hal->blinkGreen(Speed::fast);
	_hal->blinkYellow(Speed::fast);
	_hal->blinkRed(Speed::fast);
	if( !nextTest(__FUNCTION__) ) return;

	cout << "test blinking slow: red, yellow, green" << endl;
	_hal->blinkGreen(Speed::slow);
	_hal->blinkYellow(Speed::slow);
	_hal->blinkRed(Speed::slow);
	if( !nextTest(__FUNCTION__) ) return;

	cout  << __FUNCTION__ << " successful. " << endl;
}


void Test::sensorsTest(){
	cout << "start " << __FUNCTION__ <<endl;

	sensorTestHelper(	hal::io::SignalGenerator::LIGHT_BARRIER_INPUT,
						Signalname::LIGHT_BARRIER_INPUT_INTERRUPTED,
						Signalname::LIGHT_BARRIER_INPUT_NOT_INTERRUPTED);

	sensorTestHelper(	hal::io::SignalGenerator::LIGHT_BARRIER_HEIGHT,
						Signalname::LIGHT_BARRIER_HEIGHT_INTERRUPTED,
						Signalname::LIGHT_BARRIER_HEIGHT_NOT_INTERRUPTED);

	sensorTestHelper(	hal::io::SignalGenerator::LIGHT_BARRIER_SWITCH,
						Signalname::LIGHT_BARRIER_SWITCH_INTERRUPTED,
						Signalname::LIGHT_BARRIER_SWITCH_NOT_INTERRUPTED);

	sensorTestHelper(	hal::io::SignalGenerator::LIGHT_BARRIER_SLIDE,
						Signalname::LIGHT_BARRIER_SLIDE_INTERRUPTED,
						Signalname::LIGHT_BARRIER_SLIDE_NOT_INTERRUPTED);

	sensorTestHelper(	hal::io::SignalGenerator::LIGHT_BARRIER_OUTPUT,
						Signalname::LIGHT_BARRIER_OUTPUT_INTERRUPTED,
						Signalname::LIGHT_BARRIER_OUTPUT_NOT_INTERRUPTED);

	sensorTestHelper(	hal::io::SignalGenerator::SENSOR_HEIGHT_MATCH,
						Signalname::SENSOR_HEIGHT_MATCH,
						Signalname::SENSOR_HEIGHT_NOT_MATCH);

	sensorTestHelper(	hal::io::SignalGenerator::SENSOR_SWITCH_OPEN,
						Signalname::SENSOR_SWITCH_IS_OPEN,
						Signalname::SENSOR_SWITCH_IS_CLOSED);

	sensorTestHelper(	hal::io::SignalGenerator::SENSOR_METAL_MATCH,
						Signalname::SENSOR_METAL_MATCH,
						Signalname::SENSOR_METAL_NOT_MATCH);

	sensorTestHelper(	hal::io::SignalGenerator::BUTTON_START,
						Signalname::BUTTON_START_PUSHED,
						Signalname::BUTTON_START_PULLED);

	sensorTestHelper(	hal::io::SignalGenerator::BUTTON_STOP,
						Signalname::BUTTON_STOP_PUSHED,
						Signalname::BUTTON_STOP_PULLED);

	sensorTestHelper(	hal::io::SignalGenerator::BUTTON_RESET,
						Signalname::BUTTON_RESET_PUSHED,
						Signalname::BUTTON_RESET_PULLED);

	sensorTestHelper(	hal::io::SignalGenerator::BUTTON_E_STOP,
						Signalname::BUTTON_E_STOP_PUSHED,
						Signalname::BUTTON_E_STOP_PULLED);

	if( !nextTest(__FUNCTION__) ) return;

	cout  << __FUNCTION__ << " successful. " <<endl<<endl;
}

void Test::sensorTestHelper(hal::io::SignalBitmask signalBitmask, Signalname eventTriggerStart, Signalname eventTriggerEnd) {

	_hal->resetSignals();

	cout <<endl<< "test " << signalBitmask.name << "\n - please trigger sensor one or several times. Hit return key afterwards.";

	while (cin.get() != '\n');

	bool running = true;
	bool success = false;
	int triggerCounter = 0;
	do {
		Signal firstSignal =  _hal->getSignal();
		Signal secondSignal = _hal->getSignal();
		if (firstSignal.name == eventTriggerStart and secondSignal.name == eventTriggerEnd) {
			success = true;
			triggerCounter++;
		} else {
			running = false;
			if (firstSignal.name == Signalname::SIGNAL_BUFFER_EMPTY) {
				success = true;
			}
		}
	} while(running);

	if ( success ){
		cout << "test successful. (triggered " << triggerCounter << " time(s))"<<endl;
	} else {
		cout << "test NOT successful. (triggered " << triggerCounter << " time(s))" << endl;
	}
}

void Test::writeSomethingElse(hal::io::GPIO *gpio, int difference) {
	port_t port = gpio->read(PORT::A); // read port to write definetly something different so write method gets called
	gpio->setBits(PORT::A, port + difference);
}

void createInstance(){
	GpioTesting& instance = GpioTesting::instance(true);
	instance.helloWorld();
}


void Test::singletonThreadSafeTest(){
	cout << "start " << __FUNCTION__ << endl;

	cout << "Get one singleton created and Two Hello Worlds?"<<endl;
	thread t1(&createInstance);
	thread t2(&createInstance);
	t1.join();
	t2.join();

	if( !nextTest(__FUNCTION__) ) return;

	cout << __FUNCTION__ << " successful." << endl;

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

	GpioTesting *gpio = new GpioTesting();
	gpio->gainAccess();
	thread t1(&writeSomethingElse, gpio, 1);
	thread t2(&writeSomethingElse, gpio, 2);
	t1.join();
	t2.join();
	cout << "######################" << endl;

	if( !nextTest(__FUNCTION__) ) return;

	cout << __FUNCTION__ << " successful." << endl;
}


bool Test::nextTest(string functionName){
	cout <<endl<< "Was the test successful and do you want to go on?\n"<<
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
