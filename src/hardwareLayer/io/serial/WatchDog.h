/*
 * WatchDog.h
 *
 *  Created on: 30.10.2017
 *      Author: abx724
 */

#ifndef WATCHDOG_H_
#define WATCHDOG_H_


#include <chrono>
#include "Serial.h"
#include "SignalGenerator.h"


namespace hardwareLayer {
namespace io {
namespace serial {

	class WatchDog {

		private:
			Serial& serial_;
			SignalGenerator& sgen_;
			bool otherDogisAlive;

		public:
			WatchDog(Serial& serial, SignalGenerator& sgen);
			virtual ~WatchDog();
			void operator()();
			void setOtherDogIsAlive(bool isAlive);
			void sendImAlive();
	};

} /* namespace serial */
} /* namespace io */
} /* namespace hal */


#endif /* WATCHDOG_H_ */