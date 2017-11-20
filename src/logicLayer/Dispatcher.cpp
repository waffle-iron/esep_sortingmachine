/*
 * Dummy.cpp
 *
 *  Created on: 17.11.2017
 *      Author: abx724
 */

#include "Header.h"
#include "Dispatcher.h"


namespace logicLayer {

Dispatcher::Dispatcher(
		Channel& controller
) :
controller_(controller),
t_( std::ref(*this) )
{

}

Dispatcher::~Dispatcher() {
	// TODO Auto-generated destructor stub
}


void Dispatcher::operator ()(){
	Signal sig;
	while(true){
		sig.name = Signalname::TEST;
		controller_ << sig;
		std::cout << "dispatcher sended signal ... " << endl;
		WAIT(1000);
	}
}

} /* namespace logicLayer */
