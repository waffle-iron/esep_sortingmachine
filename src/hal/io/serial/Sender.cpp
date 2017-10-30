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
			struct Message msg;
			msg.signal  = Signalname::SEND_ITEM;
			msg.payload = 42;

			serial_.send(&msg);
			std::cout << "Message send!" << std::endl;
			WAIT(1000);
		}
	}

	void Sender::stop(){
		running = false;
	}

} /* namespace serial */
} /* namespace io */
} /* namespace hal */


