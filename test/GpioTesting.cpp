/*
 * GpioTesting.cpp
 *
 *  Created on: 23.10.2017
 *      Author: abx724
 */

#include "GpioTesting.h"
#include <iostream>
#include "Header.h"
#include <thread>
#include <chrono>




void GpioTesting::write(PORT port, port_t val){
	cout << "# rmw-cycle starting #" << endl;
	WAIT(500);
	cout << "# rmw-cycle finished #" << endl;
}
