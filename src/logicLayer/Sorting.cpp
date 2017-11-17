/*
 * Sorting.cpp
 *
 *  Created on: 15.11.2017
 *      Author: abx724
 */

#include "Signals.h"
#include "Sorting.h"

namespace logicLayer {

Sorting::Sorting() :
SignalReceiver::SignalReceiver()
{
	// TODO Auto-generated constructor stub

}

Sorting::~Sorting() {
	// TODO Auto-generated destructor stub
}

/**
 * @override
 */
void Sorting::operator ()(){
	Signal sig;
	while(running){
		sig << channel_; // blocking io, read from dedicated channel

		switch (sig.name) {
			case Signalname::TEST :
				std::cout << "TEST";
				break;
			default:
				break;
		}
	}
}

} /* namespace logicLayer */
