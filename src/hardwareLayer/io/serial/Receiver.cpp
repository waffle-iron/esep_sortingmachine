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

	Receiver::Receiver(Serial& serial, WatchDog& dog, SignalGenerator& sgen ):
	serial_(serial),
	dog_(dog),
	sgen_(sgen),
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
					default:
						sgen_.pushBackOnSignalBuffer(msg.signal);
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

/*
 * 	// motor
	MOTOR_FAST,
	MOTOR_SLOW,
	MOTOR_STOP,
	MOTOR_START,
	MOTOR_ROTATE_CLOCKWISE,
	MOTOR_ROTATE_COUNTER_CLOCKWISE,
	//switch
	SWITCH_OPEN,
	SWITCH_CLOSE,
	//traffic light
	GREEN_LIGHT_ON,
	GREEN_LIGHT_OFF,
	YELLOW_LIGHT_ON,
	YELLOW_LIGHT_OFF,
	RED_LIGHT_ON,
	RED_LIGHT_OFF,
	BLINK_GREEN_FAST,
	BLINK_GREEN_SLOW,
	BLINK_YELLOW_FAST,
	BLINK_YELLOW_SLOW,
	BLINK_RED_FAST,
	BLINK_RED_SLOW,
 *
 *
 * */

