#include <sys/neutrino.h>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>
#include "HAL.h"

#define WAIT(x) (std::this_thread::sleep_for(std::chrono::milliseconds(x)))


using namespace std;

int main(int argc, char *argv[])
{
//#ifdef SIMULATION
//  IOaccess_open();
//#endif

	ThreadCtl(_NTO_TCTL_IO_PRIV, 0);
	cout << "Starting Sortingmachine ..." << endl;



	hal::HAL hal;
	hal.motorStart();
	hal.motorRotateClockwise();
	hal.motorFast();
	WAIT(2000);
	hal.motorSlow();
	WAIT(2000);
	hal.motorStop();
	WAIT(2000);
	hal.switchPointOpen();
	WAIT(2000);
	hal.switchPointClose();
	WAIT(2000);

//	hal.yellowLightOn();
//	hal.redLightOn();
//	hal.greenLightOn();


	cout << "Starting Sortingmachine ... done !" << endl;
//#ifdef SIMULATION
//  IOaccess_close();
//#endif
  return EXIT_SUCCESS;
}

