/*
 * Serial.h
 *
 *  Created on: 15.11.2017
 *      Author: abj240
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include "Interface.h"
#include "WatchDog.h"
#include "Receiver.h"
#include "SignalGenerator.h"

namespace hardwareLayer {
namespace io {
namespace serial {

class Serial {
public:
	Serial(SignalGenerator& signalGenerator);
	virtual ~Serial();
	void send(Message message);

private:
	Interface _serialSender;
	Interface _serialReceiver;
	WatchDog _watchDog;
	Receiver _receiver;
};

} /* namespace serial */
} /* namespace io */
} /* namespace hardwareLayer */
#endif /* SERIAL_H_ */
