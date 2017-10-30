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
#include "LogicLayer.h"
#include "HAL.h"
using namespace std;

int main(int argc, char *argv[])
{

	cout << "Starting Sortingmachine ..." << endl;

	LOG_SCOPE;
	LOG_SET_LEVEL(DEBUG);
	LOG_DEBUG<<"hello world \n";

	hal::HAL hal;

	logicLayer::test::Test test = logicLayer::test::Test(&hal);


	logicLayer::LogicLayer loLay = logicLayer::LogicLayer(hal);
	hal.notify_observers();

	cout << "Starting Sortingmachine ... done !" << endl;

  return EXIT_SUCCESS;
}

