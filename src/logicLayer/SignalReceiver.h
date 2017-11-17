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
#include <functional>


namespace logicLayer {

class SignalReceiver {
public:
	SignalReceiver();
	virtual ~SignalReceiver();
	Channel& getChannel();
	virtual void operator()();

protected:
	Channel channel_;
	bool running;

private:
	std::thread receiver_;

};

} /* namespace logicLayer */
#endif /* SIGNALRECEIVER_H_ */
