#include <iostream>
#include <thread>

#include "Header.h"
#include "HardwareLayer.h"
#include "LogicLayer.h"
#include "Test.h"
#include "Semaphore2.h"
#include "HeightSensor.h"
#include "Channel.h"
#include "Timer.h"
#include "Dispatcher.h"

using namespace std;

int main(int argc, char *argv[])
{

	cout << "Starting Sortingmachine ..." << endl;

	LOG_SCOPE;
	LOG_SET_LEVEL(DEBUG);

	hardwareLayer::HardwareLayer hal;
	logicLayer::LogicLayer loLay = logicLayer::LogicLayer(hal);


//
//
//	logicLayer::Timer timer = logicLayer::Timer();
//	thread ReceiverThread(ref(timer));
//
//	logicLayer::Dispatcher dispatcher = logicLayer::Dispatcher(c);
//	thread SenderThread(ref(dispatcher));
//
//	SenderThread.join();
//	ReceiverThread.join();
//	c.destroy();

	return 0;



//	logicLayer::test::Test test = logicLayer::test::Test(&hal);
//	test.mmiTest();
//	uint16_t heightValue;
//	while (true) {
//		  heightValue = hal.getHeight();
//		  cout << heightValue << endl;
//	}

//	test.actuatorsTest();
//	test.sensorsTest();
//	test.threadSafenessInGpioTest();
//	test.singletonThreadSafeTest();
//	test.sensorsTest();

	cout << "Starting Sortingmachine ... done !" << endl;

	return EXIT_SUCCESS;
}
