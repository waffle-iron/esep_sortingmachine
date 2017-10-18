/*
 * GPIO.cpp
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#include <sys/neutrino.h>
#include <hw/inout.h>
#include "header.h"

#include "GPIO.h"


namespace hal {
namespace io {

constexpr int DIO_BASE = 0x300;
GPIO *GPIO::_instance = nullptr;

GPIO* GPIO::instance() {
	if (_instance == nullptr) {
		_instance = new GPIO;
	}
	return _instance;
}

GPIO::GPIO() {
	LOG_SCOPE;

}

GPIO::~GPIO() {
	LOG_SCOPE;
}

void GPIO::gainAccess(){
	ThreadCtl(_NTO_TCTL_IO_PRIV, 0);
}

void GPIO::write(PORT port, port_t val){
    out8(DIO_BASE+(port_t)port, val);
}

port_t GPIO::read(PORT port){
    return in8(DIO_BASE+(port_t)port);
}

void GPIO::setBits(PORT port, port_t bitmask) {
	port_t storedPortValue = this->read(port);
	this->write(port, storedPortValue | bitmask);
}

void GPIO::clearBits(PORT port, port_t bitmask) {
	port_t storedPortValue = this->read(port);
	this->write(port, storedPortValue & ~bitmask);
}


} /* namespace gpio */
} /* namespace hal */
