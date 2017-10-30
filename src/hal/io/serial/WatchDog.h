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


namespace hal {
namespace io {
namespace serial {

	class WatchDog {

		private:
			std::chrono::steady_clock::time_point lastFeeding;
			Serial& serial_;

		public:
			WatchDog(Serial& serial);
			virtual ~WatchDog();
			void operator()();
			void feed();
	};

} /* namespace serial */
} /* namespace io */
} /* namespace hal */


#endif /* WATCHDOG_H_ */
