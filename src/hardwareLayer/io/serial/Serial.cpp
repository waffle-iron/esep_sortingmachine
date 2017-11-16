/*
 * Serial.cpp
 *
 *  Created on: 15.11.2017
 *      Author: abj240
 */

#include "Serial.h"

namespace hardwareLayer {
namespace io {
namespace serial {

constexpr auto COM1 = "/dev/ser1";
constexpr auto COM2 = "/dev/ser2";

Serial::Serial(SignalGenerator& signalGenerator) :
_serialSender(COM1),
_serialReceiver(COM2),
_watchDog(_serialSender, signalGenerator),
_receiver(_serialReceiver, _watchDog, signalGenerator)
{

}

Serial::~Serial() {
	// TODO Auto-generated destructor stub
}

void Serial::send(Message message) {
	// TODO error handling
	_serialSender.send(message);
}

} /* namespace serial */
} /* namespace io */
} /* namespace hardwareLayer */
