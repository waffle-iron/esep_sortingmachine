#include <sys/neutrino.h>
#include <cstdlib>
#include <iostream>
#include "test.h"
#include "HAL.h"

using namespace std;

int main(int argc, char *argv[])
{
//#ifdef SIMULATION
//  IOaccess_open();
//#endif

	ThreadCtl(_NTO_TCTL_IO_PRIV, 0);
	cout << "Starting Sortingmachine ..." << endl;

	Test test = Test();
	test.setBit(PIN_YELLOW_LIGHT);
	test.clearBit(PIN_GREEN_LIGHT);

	hal::HAL hal;
	hal.motorStart();


	cout << "Starting Sortingmachine ... done !" << endl;
//#ifdef SIMULATION
//  IOaccess_close();
//#endif
  return EXIT_SUCCESS;
}

