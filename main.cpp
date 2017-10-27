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
#include "observerpattern.hpp"

using namespace std;

int main(int argc, char *argv[])
{

	HardwareLayer hal;
	LogicLayer ll = LogicLayer(ref(hal));

	hal.notify_observers();
	return EXIT_SUCCESS;
}

