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

	Receiver::Receiver(Serial& serial, WatchDog& dog):
	serial_(serial),
	dog_(dog),
	running(true)
	{

	}






	void Receiver::operator()(){
		while(running){
			struct Message msg;

			//blocking io
			serial_.recv(&msg);

			switch (msg.signal) {
				case Signalname::SERIAL_IM_ALIVE:
					std::cout << "receive signal: SERIAL_IM_ALIVE" << std::endl;
					dog_.setOtherDogIsAlive(true);
				break;
				case Signalname::SERIAL_ARE_YOU_ALIVE:
					std::cout << "receive signal: SERIAL_ARE_YOU_ALIVE" << std::endl;
					std::cout << "send answer" << std::endl;
					dog_.sendImAlive();
				break;
			}

		}
	}

	void Receiver::stop(){
		running = false;
	}

} /* namespace serial */
} /* namespace io */
} /* namespace hal */

