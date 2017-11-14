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
			receiver_(std::ref(*this))
	{

	}

	void SignalReceiver::operator()(){
		while(1);
	}

	SignalReceiver::~SignalReceiver() {
		// TODO Auto-generated destructor stub
	}



} /* namespace logicLayer */
