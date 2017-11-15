/*
 * Dispatcher.cpp
 *
 *  Created on: 13.11.2017
 *      Author: aca311
 */

#include "Dispatcher.h"
#include "LogicLayer.h"
#include "Signals.h"

namespace logicLayer {

Dispatcher::Dispatcher(LogicLayer& lol) :
		lol_(lol)
//		listingThread_(std::ref(*this))
{
}

void Dispatcher::operator()(){

}

Dispatcher::~Dispatcher() {
	// TODO Auto-generated destructor stub
}

} /* namespace logicLayer */
