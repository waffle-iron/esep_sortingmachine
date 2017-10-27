/*
 * Sender.cpp
 *
 *  Created on: 16.10.2017
 *      Author: aca311
 */
#include <thread>
#include <chrono>

#include "Header.h"
#include "Sender.h"

namespace hal {
namespace io {
namespace serial {

	Sender::Sender(Serial& serial):
	serial_(serial),
	running(true)
	{

	}

	void Sender::operator()(){
		while(running){
			char buffer[] = "HalloWelt\n\r";
			serial_.send(buffer, sizeof(buffer)-1);
			WAIT(1400);
		}
	}

	void Sender::stop(){
		running = false;
	}

} /* namespace serial */
} /* namespace io */
} /* namespace hal */


