/*
 * WatchDog.cpp
 *
 *  Created on: 30.10.2017
 *      Author: abx724
 */

#include "Header.h"
#include "WatchDog.h"
#include <thread>
#include <iostream>

namespace hal {
namespace io {
namespace serial {

WatchDog::WatchDog(Serial& serial) :
		serial_(serial),
		lastFeeding(NOW){

		}

WatchDog::~WatchDog() {
	// TODO Auto-generated destructor stub
}


void WatchDog::operator()(){
	while(true){
		struct Message msg;
		msg.signal  = Signalname::IS_ALIVE;
		msg.payload = 42;

		//feed dog of other machine
		serial_.send(&msg);

		//check if dog of this machine has not been fed
		long int diff = std::chrono::duration_cast<std::chrono::milliseconds>(NOW - lastFeeding).count();
		if( diff > 2000 ){
			std::cout << "!!!Stecker gezogen!!!" << std::endl;
		}


		WAIT(1000);
	}
}

void WatchDog::feed(){

	lastFeeding = NOW;

}

} /* namespace serial */
} /* namespace io */
} /* namespace hal */
