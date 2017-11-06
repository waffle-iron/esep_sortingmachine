#include "Header.h"
#include <sys/neutrino.h>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>
#include "GPIO.h"
#include "Test.h"
#include "GpioTesting.h"
#include "HardwareLayer.h"
#include "LogicLayer.h"
using namespace std;

int main(int argc, char *argv[])
{
	cout << "Starting Sortingmachine ..." << endl;

	LOG_SCOPE;
	LOG_SET_LEVEL(DEBUG);
	LOG_DEBUG<<"hello world \n";

	hardwareLayer::HardwareLayer hal;

	logicLayer::LogicLayer loLay = logicLayer::LogicLayer(hal);
	hal.notify_observers();

	logicLayer::test::Test test = logicLayer::test::Test(&hal);
	test.actuatorsTest();
	test.mmiTest();
	test.threadSafenessInGpioTest();
	test.singletonThreadSafeTest();



	cout << "Starting Sortingmachine ... done !" << endl;
	return EXIT_SUCCESS;
}
