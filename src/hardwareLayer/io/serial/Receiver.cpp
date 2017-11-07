/*
 * Receiver.cpp
 *
 *  Created on: 16.10.2017
 *      Author: Flo <florian.heuer@haw-hamburg.de>
 */

#include <iostream>
#include "Receiver.h"
#include "TrafficLight.h"

namespace hardwareLayer {
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

			//check sum is correct
			if(msg.checkNumber == 654321 ){

				switch (msg.signal.name) {
					case Signalname::SERIAL_IM_ALIVE:
						dog_.setOtherDogIsAlive(true);
					break;
					case Signalname::SERIAL_ARE_YOU_ALIVE:
						dog_.sendImAlive();
					break;
					case Signalname::SIGNAL_DUMMY:
						hardwareLayer::mmi::TrafficLight::instance().blinkGreen(Speed::fast);
					break;
					default:
						//default signal
					break;
				}
			}
			else{
				//if not
				serial_.flush();
			}

		}
	}

	void Receiver::stop(){
		running = false;
	}

} /* namespace serial */
} /* namespace io */
} /* namespace hal */

