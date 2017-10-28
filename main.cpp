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
	cout << "blubb" << endl;

	hal::HAL hal;
	cout << "blubb" << endl;


	WAIT(2000);

	hal::io::AsyncChannel::getChannel().sendMessage({3,0});
	hal::io::AsyncChannel::getChannel().sendMessage({3,0});
	hal::io::AsyncChannel::getChannel().sendMessage({4,1});
	hal::io::AsyncChannel::getChannel().sendMessage({5,0});
	cout << "blubb" << endl;
	WAIT(1000);
	cout << (int)hal.getSignal().name << endl;
	cout << "blubb" << endl;
	WAIT(1000);
	cout << (int)hal.getSignal().name << endl;
	cout << "blubb" << endl;
	WAIT(1000);
	cout << (int)hal.getSignal().name << endl;


	WAIT(2000);

	logicLayer::test::Test test = logicLayer::test::Test(&hal);
	test.actuatorsTest();
	test.mmiTest();

	test.threadSafenessInGpioTest();

	cout << "Starting Sortingmachine ... done !" << endl;

  return EXIT_SUCCESS;
}

