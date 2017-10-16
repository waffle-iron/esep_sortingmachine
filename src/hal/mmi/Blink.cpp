	/*
 * Blink.cpp
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#include "Blink.h"
#include "GPIO.h"
#include <iostream>

#include <thread>
#include <chrono>

namespace hal {
namespace mmi {

Blink::Blink() {
	this->fast = fast;
	this->bitmask = 0;
}

Blink::Blink(bool fast) {
	this->fast = fast;
	this->bitmask = 0;
}

Blink::~Blink() {
	// TODO Auto-generated destructor stub
}

void Blink::operator()() {
	while (true) {
		if (fast) {
			hal::io::GPIO::instance()->setBits(PORT::A, this->bitmask);
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			std::cout << "thread middle wait" << std::endl;
			hal::io::GPIO::instance()->clearBits(PORT::A, this->bitmask);
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		} else {
			std::cout << "thread slow" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			hal::io::GPIO::instance()->setBits(PORT::A, this->bitmask);
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			hal::io::GPIO::instance()->clearBits(PORT::A, this->bitmask);
		}
	}
}

void Blink::add(int bitmask) {
	this->bitmask |= bitmask;
}

} /* namespace mmi */
} /* namespace hal */
