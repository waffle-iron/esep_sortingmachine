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

Serial::Serial(SignalGenerator& signalGenerator) :
_serialSender("/dev/ser1"),
_serialReceiver("/dev/ser2"),
_watchDog(_serialSender, signalGenerator),
_receiver(_serialReceiver, _watchDog, signalGenerator),
_th_receiver(std::ref(_receiver))
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
