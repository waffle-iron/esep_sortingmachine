#include "Header.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "HAL.h"
#include "AsyncChannel.h"
#include "Test.h"

using namespace std;


int main(int argc, char *argv[])
{

	cout << "Starting Sortingmachine ..." << endl;

	LOG_SCOPE;
	LOG_SET_LEVEL(DEBUG);
	LOG_DEBUG<<"hello world \n";

	hal::HAL hal;

	logicLayer::test::Test test = logicLayer::test::Test(&hal);
	test.sensorsTest();
//	test.actuatorsTest();
//	test.mmiTest();
//	test.threadSafenessInGpioTest();

	cout << "Starting Sortingmachine ... done !" << endl;

  return EXIT_SUCCESS;
}

