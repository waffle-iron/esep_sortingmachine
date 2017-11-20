/*
 * SignalReceiver.cpp
 *
 *  Created on: 14.11.2017
 *      Author: abx724
 */
#include "Header.h"
#include "SignalReceiver.h"
#include "Channel.h"


namespace logicLayer {

	SignalReceiver::SignalReceiver() :
			channel_(10),
			running(true)
	{
		std::cout << "create SignalReceiver" << endl;

	}

	SignalReceiver::~SignalReceiver() {
		cout << "call signal receiver's destructor" << endl;
		terminate();
	}

	Channel& SignalReceiver::getChannel(){
		return channel_;
	}

	void SignalReceiver::terminate(){
		running = false;
		channel_ << Signal();
		cout << "after channel destroy" << endl;
		receiver_.join();
		cout << "after join" << endl;
	}


} /* namespace logicLayer */
