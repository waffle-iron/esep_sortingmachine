/*
 * Dummy.cpp
 *
 *  Created on: 17.11.2017
 *      Author: abx724
 */

#include "Header.h"
#include "Dispatcher.h"

namespace logicLayer {

Dispatcher::Dispatcher() {
	// TODO Auto-generated constructor stub

}

Dispatcher::~Dispatcher() {
	// TODO Auto-generated destructor stub
}


void Dispatcher::operator ()(){
	Signal sig;
	while(true){
		sig.name = Signalname::TEST;
		ctr_.getChannel() << sig;
		std::cout << "dispatcher sended signal ... " << endl;
		WAIT(1000);
	}
}

} /* namespace logicLayer */
