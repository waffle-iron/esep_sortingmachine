#include "Header.h"
#include <iostream>

#include "Serial.h"
#include "Receiver.h"

#include "HardwareLayer.h"
#include "LogicLayer.h"
#include "Test.h"


using namespace std;

int main(int argc, char *argv[])
{


//	cout << "Starting Sortingmachine ..." << endl;
//
//	LOG_SCOPE;
//	LOG_SET_LEVEL(DEBUG);
//
//	hardwareLayer::HardwareLayer hal;
//	logicLayer::LogicLayer loLay = logicLayer::LogicLayer(hal);
//
//	logicLayer::test::Test test = logicLayer::test::Test(&hal);
//	test.mmiTest();
//	test.actuatorsTest();
//	test.sensorsTest();
//	test.threadSafenessInGpioTest();
//	test.singletonThreadSafeTest();






	//connect to serial
	hardwareLayer::io::serial::Serial ser1("/dev/ser1");
	hardwareLayer::io::serial::Serial ser2("/dev/ser2");

	//sender object
	hardwareLayer::io::serial::WatchDog dog(ser1);

	//receiver object
	hardwareLayer::io::serial::Receiver receiver(ser2, dog);

	//start threads
	std::thread th_sender(std::ref(dog));
	std::thread th_receiver(std::ref(receiver));

	//wait for Key Q to end program
	while(1){
		char in;
		std::cin >> in;
		if(in=='q' || in=='Q')  break;
	}



	//cleanup receiver
	std::cout << "stop receiver thread" << std::endl;

	receiver.stop();
	//wake thread from blocking
	pthread_kill(th_receiver.native_handle(), SIGUSR1);
	std::cout << "wait for receiver thread to join" << std::endl;
	th_receiver.join();

	//clean up sender
	std::cout << "stop sender thread" << std::endl;
	//sender.stop();
	std::cout << "wait for sender thread to join" << std::endl;
	th_sender.join();


	std::cout << "Goodbye!" << std::endl;


	cout << "Starting Sortingmachine ... done !" << endl;

	return EXIT_SUCCESS;

}

