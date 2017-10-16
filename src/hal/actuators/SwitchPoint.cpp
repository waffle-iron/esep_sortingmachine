/*
 * SwitchPoint.cpp
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#include "SwitchPoint.h"
#include "GPIO.h"

namespace hal {
	namespace actuators {

		SwitchPoint *SwitchPoint::_instance = nullptr;

		SwitchPoint *SwitchPoint::instance() {
			if (_instance == nullptr) {
				_instance = new SwitchPoint;
			}
			return _instance;
		}

		SwitchPoint::SwitchPoint() {
			// TODO Auto-generated constructor stub

		}

		SwitchPoint::~SwitchPoint() {
			// TODO Auto-generated destructor stub
		}

		void SwitchPoint::open(){

			// 1001 0001 or
			// 0010 0000
			// 1010 0001

			int bits = io::GPIO::instance()->read(PORT::B);
			bits = bits | SP_OPEN;

			io::GPIO::instance()->write(PORT::B, bits );
		}

		void SwitchPoint::close(){

			// 1011 0001 and
			// 1101 1111
			// 1001 0001

			int bits = io::GPIO::instance()->read(PORT::B);
			bits = bits & SP_OPEN;

			io::GPIO::instance()->write(PORT::B, bits );
		}




	} /* namespace actuators */
} /* namespace hal */

