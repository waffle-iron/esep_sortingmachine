/*
 * WatchDog.cpp
 *
 *  Created on: 30.10.2017
 *      Author: abx724
 */

#include "Header.h"
#include "WatchDog.h"

namespace hardwareLayer {
namespace io {
namespace serial {

constexpr int period = 250;

WatchDog::WatchDog(Serial& serial, SignalGenerator& sgen) :
serial_(serial),
sgen_(sgen),
watchdog(std::ref(*this)),
dogWasFed(false),
status(Connection::CONNECTED),
running(true)
{

}

WatchDog::~WatchDog() {
	terminate();
	watchdog.join();
}


void WatchDog::operator()(){

	Message token( Signal(cb_1, cb_all, Signalname::SERIAL_WATCHDOG_TOKEN) );

	Signal connectionLost(cb_this,cb_this, Signalname::CONNECTION_LOST);
	Signal connectionConnected(cb_this,cb_this, Signalname::CONNECTION_CONNECTED);

	while(running) {

		dogWasFed = false;

		if(cb_this == cb_1) serial_.send(token);
		WAIT(period);
		if(cb_this == cb_1) serial_.send(token);
		WAIT(period);

		if(status == Connection::LOST && dogWasFed){
			status = Connection::CONNECTED;
			sgen_.pushBackOnSignalBuffer(connectionConnected);
		}
		else if(status == Connection::CONNECTED && !dogWasFed){
			status = Connection::LOST;
			sgen_.pushBackOnSignalBuffer(connectionLost);
		}
	}
}

void WatchDog::terminate() {
	running = false;
}

void WatchDog::feed(){
	dogWasFed = true;
}

} /* namespace serial */
} /* namespace io */
} /* namespace hal */
