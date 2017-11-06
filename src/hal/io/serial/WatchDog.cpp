/*
 * WatchDog.cpp
 *
 *  Created on: 30.10.2017
 *      Author: abx724
 */

#include "Header.h"
#include "WatchDog.h"
#include <thread>

namespace hal {
namespace io {
namespace serial {

WatchDog::WatchDog(Serial& serial) :
		serial_(serial),
		otherDogisAlive(false){}

WatchDog::~WatchDog() {
	// TODO Auto-generated destructor stub
}


void WatchDog::operator()(){
	while(true){
		struct Message msg;
		msg.signal  = Signalname::SERIAL_ARE_YOU_ALIVE;
		msg.payload = 42;


		//ask other machine if it i alive
		serial_.send(&msg);

		WAIT(1000);

		//check if other machine has send keep alive signal -
		//if not error signal
		if(!otherDogisAlive){
			std::cout << "machine is not connected" << std::endl;
		}

	}
}

void WatchDog::setOtherDogIsAlive(bool isAlive){

	otherDogisAlive = isAlive;

}

void WatchDog::sendImAlive(){

	struct Message msg;
	msg.signal  = Signalname::SERIAL_IM_ALIVE;
	msg.payload = 42;

	serial_.send(&msg);

}

} /* namespace serial */
} /* namespace io */
} /* namespace hal */
