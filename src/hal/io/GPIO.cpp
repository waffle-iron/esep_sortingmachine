/*
 * GPIO.cpp
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#include <sys/neutrino.h>
#include <hw/inout.h>

#include "GPIO.h"

#define DIO_BASE 0x300

namespace hal {
namespace io {

GPIO *GPIO::_instance = nullptr;

GPIO* GPIO::instance() {
	if (_instance == nullptr) {
		_instance = new GPIO;
	}
	return _instance;
}

GPIO::GPIO() {
	// TODO Auto-generated constructor stub

}

GPIO::~GPIO() {
	// TODO Auto-generated destructor stub
}

void GPIO::gainAccess(){

}

void GPIO::write(PORT port, int val){
    out8(DIO_BASE+(int)port, val);
}

int GPIO::read(PORT port){
    return in8(DIO_BASE+(int)port);
}


} /* namespace gpio */
} /* namespace hal */
