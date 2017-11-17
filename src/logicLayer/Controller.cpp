/*
 * Controller.cpp
 *
 *  Created on: 15.11.2017
 *      Author: abx724
 */

#include "Controller.h"

namespace logicLayer {

Controller::Controller() {
	// TODO Auto-generated constructor stub

}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

void Controller::operator ()(){
	Signal sig;
	while(running){
		channel_ >> sig;
		switch (sig.name) {
			case Signalname::TEST:
				std::cout << "Controller receives signal." << endl;
				break;
			default:
				break;
		}
	}
}

} /* namespace logicLayer */
