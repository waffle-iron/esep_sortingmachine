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

using namespace std;

namespace base {

} /*base*/




int main(int argc, char *argv[])
{
	cout << "Starting Sortingmachine ..." << endl;

	LOG_SCOPE;
	LOG_SET_LEVEL(DEBUG);
	LOG_DEBUG<<"hello world \n";


	hal::io::Base *d = new Derived();
	d->a();


	logicLayer::test::Test test;
	//test.actuatorsTest();
	//test.mmiTest();

	test.threadSafenessInGpioTest();

	cout << "Starting Sortingmachine ... done !" << endl;
  return EXIT_SUCCESS;
}

