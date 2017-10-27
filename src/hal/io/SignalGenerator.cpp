/*
 * InterruptHandler.cpp
 *
 *  Created on: Oct 19, 2017
 *      Author: stammtisch
 */

#include "SignalGenerator.h"
#include "Header.h"
#include "AsyncChannel.h"
#include "ISR.h"
#include <iostream>
#include "GPIO.h"

constexpr int MAGIC_NUMBER = 15;

constexpr int MAGIC_NUMBER = 15;
constexpr int MAGIC_NUMBER = 15;
constexpr int MAGIC_NUMBER = 15;
constexpr int MAGIC_NUMBER = 15;
constexpr int MAGIC_NUMBER = 15;
constexpr int MAGIC_NUMBER = 15;
constexpr int MAGIC_NUMBER = 15;
constexpr int MAGIC_NUMBER = 15;
constexpr int MAGIC_NUMBER = 15;
constexpr int MAGIC_NUMBER = 15;
constexpr int MAGIC_NUMBER = 15;
constexpr int MAGIC_NUMBER = 15;
constexpr int MAGIC_NUMBER = 15;
constexpr int MAGIC_NUMBER = 15;
constexpr int MAGIC_NUMBER = 15;
constexpr int MAGIC_NUMBER = 15;
constexpr int MAGIC_NUMBER = 15;
constexpr int MAGIC_NUMBER = 15;
constexpr int MAGIC_NUMBER = 15;
constexpr int MAGIC_NUMBER = 15;


namespace hal {
namespace io {

SignalGenerator::SignalGenerator():
running(true) {
	hal::io::GPIO::instance()->gainAccess(); // first time calling singleton
	ISR::registerISR(AsyncChannel::getChannel(), MAGIC_NUMBER);
	thread = std::thread(std::ref(*this));
}

SignalGenerator::~SignalGenerator() {
	stop();
	AsyncChannel::getChannel().sendMessage({0,0});
	thread.join();
	ISR::unregisterISR();
}

void SignalGenerator::operator()() {
	while (running) {
		AsyncMsg message;
		message = AsyncChannel::getChannel().getNextMessage();
		std::cout << message.value << std::endl;
	}
}

void SignalGenerator::stop() {
	running = false;
}

} /* namespace io */
} /* namespace hal */
