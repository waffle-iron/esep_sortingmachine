/*
 * SignalReceiver.cpp
 *
 *  Created on: 14.11.2017
 *      Author: abx724
 */

#include "SignalReceiver.h"
#include "Channel.h"


namespace logicLayer {

	SignalReceiver::SignalReceiver() :
			channel_(channelSize),
			running(true),
			receiver_(std::ref(*this))
	{

	}

	void SignalReceiver::operator()(){
		//silence is golden...
	}

	SignalReceiver::~SignalReceiver() {
		// TODO Auto-generated destructor stub
	}

	Channel& SignalReceiver::getChannel(){
		return channel_;
	}


} /* namespace logicLayer */
