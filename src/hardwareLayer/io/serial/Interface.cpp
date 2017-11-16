/*
 * Serial.cpp
 *
 *  Created on: 19.05.2017
 *      Author: aca216
 */

#include "Interface.h"

#include <fcntl.h>
#include <termios.h>
#include <iostream>
#include <cerrno>


using namespace std;

namespace hardwareLayer {
namespace io {
namespace serial {

struct termios termino;
constexpr int STANDARD_BAUD_RATE = B19200;
constexpr int TIMEOUT_1_SECOND = 10;

Interface::Interface(string dev) :
Interface(dev, STANDARD_BAUD_RATE)
{
	LOG_SCOPE
}
Interface::Interface(string dev, int baud) {
	LOG_SCOPE
	// Open File descriptor
	fdesc_ = open(dev.c_str(), O_RDWR);
	if(this->fdesc_ == -1) {
		LOG_ERROR << __FUNCTION__ << ": error while opening file desriptor occureed."<<endl;
		LOG_ERROR<<errno<<" "<<strerror(errno)<<endl;
		exit(EXIT_FAILURE);
	}

	// initialize settings for Serial Interface
	if(init(baud) < 0) {
		LOG_ERROR << __FUNCTION__ << ": error while initializing serial interface occureed."<<endl;
		LOG_ERROR<<errno<<" "<<strerror(errno)<<endl;
		exit(EXIT_FAILURE);
	}
}

Interface::~Interface() {
	LOG_SCOPE
	// Close File descriptor
	if( close(this->fdesc_) < 0 ) {
		LOG_ERROR << __FUNCTION__ << ": error while closing file descriptor occured."<<endl;
		LOG_ERROR<<errno<<" "<<strerror(errno)<<endl;
		exit(EXIT_FAILURE);
	}
}

int Interface::init(int baud) {
	LOG_SCOPE
	int ret = 0;
    flush();
	ret += tcgetattr(this->fdesc_, &termino); 			// get the current terminal control settings
	ret += cfsetispeed(&termino, baud);					// set input baud rate
	ret += cfsetospeed(&termino, baud);					// set output baud rate
	termino.c_cflag &= ~CSIZE;							// number of data bits per character
	termino.c_cflag &= ~CSTOPB;							// disable two stop bits and use just one
	termino.c_cflag &= ~PARENB;							// disable parity
	termino.c_cflag |= CS8;								// set 8 data bits
	termino.c_cflag |= CREAD;							// enable receiver
	termino.c_cflag |= CLOCAL;							// ignore modem status lines
	ret += tcsetattr(this->fdesc_, TCSANOW, &termino); 	// set terminal control settings immediately
	return ret;
}

int Interface::send(Message& message) {
	LOG_SCOPE
	int ret = 0;

	ret = write(this->fdesc_, &message, sizeof(Message));

	if(ret == -1) {
		LOG_ERROR << __FUNCTION__ << ": error while writing Message on file descriptor occured."<<endl;
		LOG_ERROR<<errno<<" "<<strerror(errno)<<endl;
	}
	return ret;
}

int Interface::recv( Message *msg ) {
	LOG_SCOPE
	int ret = readcond(this->fdesc_, msg, sizeof(Message), sizeof(Message),0,TIMEOUT_1_SECOND);
	if(ret == -1) {
		LOG_ERROR << __FUNCTION__ << ": error while reading Message from file descriptor occured."<<endl;
		LOG_ERROR<<errno<<" "<<strerror(errno)<<endl;
	}
	return ret;
}

int Interface::flush() {
	LOG_SCOPE
	int ret = 0;

	ret = tcflush(this->fdesc_, TCIOFLUSH);

	if(ret == -1) {
		LOG_ERROR << __FUNCTION__ << ": error while flushing file descriptor occured."<<endl;
		LOG_ERROR<<errno<<" "<<strerror(errno)<<endl;
	}

	return ret;
}


} /* namespace serial */
} /* namespace io */
} /* namespace hal */
