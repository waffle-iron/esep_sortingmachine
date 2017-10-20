/*
 * InterruptHandler.cpp
 *
 *  Created on: Oct 19, 2017
 *      Author: stammtisch
 */

#include "MessageGenerator.h"
#include "Header.h"
#include "AsyncChannel.h"
#include <iostream>

namespace hal {
namespace io {

MessageGenerator::MessageGenerator():
running(true) {
	t_prio_low = std::thread(std::ref(*this));
}

MessageGenerator::~MessageGenerator() {
	stop();
	AsyncChannel::getChannel().sendMessage({0,0});
	t_prio_low.join();
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
