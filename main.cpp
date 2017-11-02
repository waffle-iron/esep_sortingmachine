#include "Header.h"
#include <iostream>
#include "HAL.h"
#include "Test.h"

using namespace std;


int main(int argc, char *argv[])
{

	cout << "Starting Sortingmachine ..." << endl;

	LOG_SCOPE;
	LOG_SET_LEVEL(DEBUG);

	hal::HAL hal;

	logicLayer::test::Test test = logicLayer::test::Test(&hal);
	test.mmiTest();
	test.actuatorsTest();
	test.sensorsTest();
	test.threadSafenessInGpioTest();
	test.singletonThreadSafeTest();


	cout << "Starting Sortingmachine ... done !" << endl;

  return EXIT_SUCCESS;
}

