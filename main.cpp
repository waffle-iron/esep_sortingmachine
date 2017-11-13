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

	Channel c(5);// create a communication channel
	logicLayer::Timer timer = logicLayer::Timer(c);
	thread ReceiverThread(ref(timer));// create thread. Pass functor object with channel as argument
	logicLayer::Dispatcher dispatcher = logicLayer::Dispatcher(c);
	thread SenderThread(ref(dispatcher));// create another thread. Pass functor with channel.
	SenderThread.join();// stop here until SenderThread has come to an end.
	ReceiverThread.join();//stop here until ReceiverThread has come to an end.
	c.destroy();//clean up the channel
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
