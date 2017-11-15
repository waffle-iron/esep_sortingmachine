/*
 * Receiver.cpp
 *
 *  Created on: 16.10.2017
 *      Author: Flo <florian.heuer@haw-hamburg.de>
 */

#include "Receiver.h"

namespace hardwareLayer {
namespace io {
namespace serial {

	Receiver::Receiver(Interface& serial, WatchDog& dog, SignalGenerator& sgen ):
	serial_(serial),
	dog_(dog),
	sgen_(sgen),
	running(true)
	{

	}

	void Receiver::operator()(){
		while(running) {

			struct Message msg;

			//blocking io
			serial_.recv(&msg);

			//check sum is correct
			if(msg.checkNumber == 654321 ){
				if((msg.signal.receiver & cb_this) > 0 || cb_this == 0) {

					switch (msg.signal.name) {
						case Signalname::SERIAL_WATCHDOG_TOKEN:
							// set feed signal
							if (cb_this == cb_1) {
								if (cb_available == 0) {
									cb_available = Parameter<uint8_t>(msg.signal.sender, "All available conveyer belts.");
								}
								if (msg.signal.sender == cb_available){
									sgen_.pushBackOnSignalBuffer(Signal(cb_this,cb_available, Signalname::SERIAL_WATCHDOG_FEED));
								}
							}
							//bit manipulation
							if( cb_this != 0 ){
								msg.signal.sender |= cb_this;
							}
							else if((int)msg.signal.sender < 128 ){
								cb_this = Parameter<uint8_t>(msg.signal.sender + 1, "Conveyer belt 2");
								msg.signal.sender |= cb_this;
							}
							else{
								LOG_ERROR << __FUNCTION__ << "Machine number to big.";
								exit(EXIT_FAILURE);
							}

						break;
						case Signalname::SERIAL_WATCHDOG_FEED:
							if (cb_available == 0) {
								cb_available = Parameter<uint8_t>(msg.signal.receiver, "All connected conveyer belts.");
							}
							dog_.feed();
						break;
						default:
							sgen_.pushBackOnSignalBuffer(msg.signal);
						break;
					}
				}
				if(cb_this != cb_1) {
					if(msg.signal.receiver > cb_this) {
						sgen_.pushBackOnSignalBuffer(msg.signal);
					}
				}
			}
			else{
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

