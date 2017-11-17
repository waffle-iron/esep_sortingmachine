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
	running(true),
	_th_receiver(std::ref(*this))
	{

	}

	void Receiver::operator()(){
		while(running) {

			Message msg = Message(false);

			//blocking io
			serial_.recv(&msg);

			//check sum is correct
			if(msg.checkNumber == CORRECT_CN ){
				if((msg.signal.receiver & cb_this) > 0 || cb_this == 0) {

					switch (msg.signal.name) {
						case Signalname::SERIAL_WATCHDOG_TOKEN:
							// set feed signal
							if (cb_this == cb_1) {
								if (cb_available == 0) {
									cb_available = msg.signal.sender;
									setNext_cb();
								}
								if (msg.signal.sender == cb_available) {
									if(cb_last == 0) {
										cb_last = (cb_available + 1) >> 1;
									}

									Message feed(Signal(cb_this,cb_available, Signalname::SERIAL_WATCHDOG_FEED));
									serial_.send(feed);
								}
							}
							//bit manipulation
							if( cb_this != 0 ){
								msg.signal.sender |= cb_this;
							}
							else if((int)msg.signal.sender < 128 ){
								cb_this = msg.signal.sender + 1;
								msg.signal.sender |= cb_this;
							}
							else{
								LOG_ERROR << __FUNCTION__ << "Machine number to big.";
								exit(EXIT_FAILURE);
							}

						break;
						case Signalname::SERIAL_WATCHDOG_FEED:
							if (cb_available == 0) {
								cb_available = msg.signal.receiver;
								cb_last = (msg.signal.receiver + 1) >> 1;
								setNext_cb();
							}
							dog_.feed();
						break;
						default:
							sgen_.pushBackOnSignalBuffer(msg.signal);
						break;
					}
				}
				if(cb_this != cb_1 && msg.signal.receiver > cb_this) {
					serial_.send(msg);
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

	void Receiver::setNext_cb() {
		LOG_SCOPE
		if(cb_this == 0 or cb_available == 0) {
			LOG_ERROR<<"cb_this or cb_available not set yet."<<endl;
			exit(EXIT_FAILURE);
		} else {
			if(cb_this << 1 > cb_available) {
				cb_next = cb_first;
			} else {
				cb_next = cb_this << 1;
			}
		}
	}


} /* namespace serial */
} /* namespace io */
} /* namespace hal */


