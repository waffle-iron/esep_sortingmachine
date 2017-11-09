#include "Header.h"
#include <iostream>

#include "Serial.h"
#include "Receiver.h"

#include "HardwareLayer.h"
#include "LogicLayer.h"
#include "Test.h"


#include "HeightSensor.h"

using namespace std;

int main(int argc, char *argv[])
{


	cout << "Starting Sortingmachine ..." << endl;

	LOG_SCOPE;
	LOG_SET_LEVEL(DEBUG);

	hardwareLayer::HardwareLayer hal;



	Message msg;
	msg.signal.name = Signalname::SIGNAL_DUMMY;

	hal.sendSerialMsg(&msg);

	while(1);



//	logicLayer::LogicLayer loLay = logicLayer::LogicLayer(hal);
//
//	logicLayer::test::Test test = logicLayer::test::Test(&hal);
//	test.mmiTest();
//	test.actuatorsTest();
//	test.sensorsTest();
//	test.threadSafenessInGpioTest();
//	test.singletonThreadSafeTest();



	cout << "Starting Sortingmachine ... done !" << endl;

	return EXIT_SUCCESS;

}

