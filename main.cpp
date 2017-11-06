#include "Header.h"
#include <iostream>

#include "HardwareLayer.h"
#include "LogicLayer.h"
#include "Test.h"

#include "AsyncChannel.h"
#include <sys/neutrino.h>
#include <sys/siginfo.h>



using namespace std;

struct sigevent event;



int main(int argc, char *argv[])
{

	cout << "Starting Sortingmachine ..." << endl;

	LOG_SCOPE;
	LOG_SET_LEVEL(DEBUG);

//	SIGEV_PULSE_INIT(&event, hal::io::AsyncChannel::instance().getConnectionId(), SIGEV_PULSE_PRIO_INHERIT, 15, 0);

//	struct sigevent* newEvent = (struct sigevent*) &event;
//	newEvent->sigev_value.sival_int = 0b1111000011111111;
//	event = *newEvent;

//	MsgSendPulse_r(
//					hal::io::AsyncChannel::instance().getConnectionId(),
//					sched_get_priority_max(0),
//			    	2,
//			    	0b1111000011111111 );
//	MsgSendPulse_r(
//					hal::io::AsyncChannel::instance().getConnectionId(),
//					sched_get_priority_max(0),
//			    	2,
//			    	0b1111000011111111 );
//	MsgSendPulse_r(
//					hal::io::AsyncChannel::instance().getConnectionId(),
//					sched_get_priority_max(0),
//			    	2,
//			    	0b1111000011111111 );
//	MsgSendPulse_r(
//					hal::io::AsyncChannel::instance().getConnectionId(),
//					15,
//					2,
//					0b1111000011101111 );
//
//	cout<<"SIGEV_PULSE_PRIO_INHERIT: "<<(int)SIGEV_PULSE_PRIO_INHERIT<<endl;
//	cout<<"sched_get_priority_max(0): "<<(int)sched_get_priority_max(0)<<endl;
//	cout<<"sched_get_priority_max(1): "<<(int)sched_get_priority_max(1)<<endl;


	hardwareLayer::HardwareLayer hal;
	logicLayer::LogicLayer loLay = logicLayer::LogicLayer(hal);

	while (cin.get() != '\n');


	hal.getSignalGenerator().terminate();

	while (cin.get() != '\n');

	hal.getSignalGenerator().restart();

	while (cin.get() != '\n');


//	logicLayer::test::Test test = logicLayer::test::Test(&hal);
//	test.mmiTest();
//	test.actuatorsTest();
//	test.sensorsTest();
//	test.threadSafenessInGpioTest();
//	test.singletonThreadSafeTest();



	cout << "Starting Sortingmachine ... done !" << endl;

	return EXIT_SUCCESS;
}
