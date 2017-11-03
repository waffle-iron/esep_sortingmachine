#include "Header.h"
#include <sys/neutrino.h>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>
#include "HAL.h"
#include "GPIO.h"
#include "Test.h"
#include "GpioTesting.h"
#include "HeightSensor.h"






using namespace std;


int main(int argc, char *argv[])
{
	cout << "Starting Sortingmachine ..." << endl;

	LOG_SCOPE;
	LOG_SET_LEVEL(DEBUG);
	LOG_DEBUG<<"hello world \n";

	hal::HAL hal;
	logicLayer::test::Test test = logicLayer::test::Test(&hal);
	uint16_t heightValue;
	test.actuatorsTest();
//	test.mmiTest();
//	test.threadSafenessInGpioTest();
//	test.singletonThreadSafeTest();
	 while (true) {
	    heightValue = hal.getHeight();
	    cout << heightValue << endl;
	}


	cout << "Starting Sortingmachine ... done !" << endl;
  return EXIT_SUCCESS;
}

