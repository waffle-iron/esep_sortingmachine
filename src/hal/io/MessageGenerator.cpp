/*
 * InterruptHandler.cpp
 *
 *  Created on: Oct 19, 2017
 *      Author: stammtisch
 */

#include "MessageGenerator.h"
#include "Header.h"
#include "AsyncChannel.h"
#include "ISR.h"
#include <iostream>
#include "GPIO.h"

constexpr int MAGIC_NUMBER = 15;

namespace hal {
namespace io {

MessageGenerator::MessageGenerator():
running(true) {
	hal::io::GPIO::instance()->gainAccess();
	ISR::registerISR(AsyncChannel::getChannel(), MAGIC_NUMBER);
	thread = std::thread(std::ref(*this));
}

MessageGenerator::~MessageGenerator() {
	stop();
	AsyncChannel::getChannel().sendMessage({0,0});
	thread.join();
	ISR::unregisterISR();
}

void MessageGenerator::operator()() {
	while (running) {
		AsyncMsg message;
		message = AsyncChannel::getChannel().getNextMessage();
		std::cout << message.value << std::endl;
	}
}

void MessageGenerator::stop() {
	running = false;
}

} /* namespace io */
} /* namespace hal */
