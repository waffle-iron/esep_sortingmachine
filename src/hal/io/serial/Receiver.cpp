/*
 * Receiver.cpp
 *
 *  Created on: 16.10.2017
 *      Author: aca311
 */

#include <iostream>
#include "Receiver.h"

namespace hal {
namespace io {
namespace serial {

	Receiver::Receiver(Serial& serial):
	serial_(serial),
	running(true)
	{

	}

	void Receiver::operator()(){
		while(running){
			char inbyte;
			serial_.recv(&inbyte);
			std::cout << inbyte;
			std::cout.flush();
		}
	}

	void Receiver::stop(){
		running = false;
	}

} /* namespace serial */
} /* namespace io */
} /* namespace hal */

