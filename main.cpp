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


	hal::io::AsyncChannel::getChannel().sendMessage({4, hal::io::AsyncChannel::LIGHT_BARRIER_INPUT_NOT_INTERRUPTED.bitmask});
	hal::io::AsyncChannel::getChannel().sendMessage({5, 0});
	hal::io::AsyncChannel::getChannel().sendMessage({4, hal::io::AsyncChannel::LIGHT_BARRIER_HEIGHT_NOT_INTERRUPTED.bitmask});
	hal::io::AsyncChannel::getChannel().sendMessage({5, 0});

	WAIT(1000);

	cout << "test Signal " << hal::io::AsyncChannel::LIGHT_BARRIER_INPUT_NOT_INTERRUPTED.name<< endl;
	if (hal.getSignal().name == Signalname::LIGHT_BARRIER_INPUT_NOT_INTERRUPTED){
		cout << "test successful." << endl;
	} else {
		cout << "test NOT successful." << endl;
	}
	cout << "test opposite Signal of " << hal::io::AsyncChannel::LIGHT_BARRIER_INPUT_NOT_INTERRUPTED.name<< endl;
	if (hal.getSignal().name == Signalname::LIGHT_BARRIER_INPUT_INTERRUPTED){
		cout << "test successful." << endl;
	} else {
		cout << "test NOT successful." << endl;
	}

	cout << "test Signal " << hal::io::AsyncChannel::LIGHT_BARRIER_HEIGHT_NOT_INTERRUPTED.name<< endl;
	if (hal.getSignal().name == Signalname::LIGHT_BARRIER_HEIGHT_NOT_INTERRUPTED){
		cout << "test successful." << endl;
	} else {
		cout << "test NOT successful." << endl;
	}
	cout << "test opposite Signal of " << hal::io::AsyncChannel::LIGHT_BARRIER_HEIGHT_NOT_INTERRUPTED.name<< endl;
	if (hal.getSignal().name == Signalname::LIGHT_BARRIER_HEIGHT_INTERRUPTED){
		cout << "test successful." << endl;
	} else {
		cout << "test NOT successful." << endl;
	}



	WAIT(2000);

	logicLayer::test::Test test = logicLayer::test::Test(&hal);
	test.actuatorsTest();
	test.mmiTest();

	test.threadSafenessInGpioTest();

	cout << "Starting Sortingmachine ... done !" << endl;

  return EXIT_SUCCESS;
}

