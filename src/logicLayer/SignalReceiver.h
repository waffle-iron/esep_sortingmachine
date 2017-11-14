/*
 * SignalReceiver.h
 *
 *  Created on: 14.11.2017
 *      Author: abx724
 */

#ifndef SIGNALRECEIVER_H_
#define SIGNALRECEIVER_H_

#include "Channel.h"
#include <thread>

namespace logicLayer {

class SignalReceiver {
public:
	SignalReceiver();
	virtual ~SignalReceiver();
	Channel& getChannel();
	void operator()();

protected:
	Channel channel_;

private:
	std::thread receiver_;

};

} /* namespace logicLayer */
#endif /* SIGNALRECEIVER_H_ */
