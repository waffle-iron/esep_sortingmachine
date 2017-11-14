/*
 * Serial.cpp
 *
 *  Created on: 19.05.2017
 *      Author: aca216
 */

#include "Serial.h"

#include <fcntl.h>
#include <termios.h>
#include <iostream>

using namespace std;

namespace hardwareLayer {
namespace io {
namespace serial {

Serial::Serial(string dev){

	// Open File descriptor
	fdesc_ = open(dev.c_str(), O_RDWR);
	if(this->fdesc_ == -1){
		LOG_ERROR << __FUNCTION__ << " error opening serial " << dev;
		exit(EXIT_FAILURE);
	}

	// initialize settings for Serial Interface
	init(B19200);
}
Serial::Serial(string dev, int baud){
	// Open File descriptor
	fdesc_ = open(dev.c_str(), O_RDWR);
	if(this->fdesc_ == -1){
		LOG_ERROR << __FUNCTION__ << " error opening serial " << dev;
		exit(EXIT_FAILURE);
	}
	// initialize settings for Serial Interface
	init(baud);
}

Serial::~Serial(){
	// Close File descriptor
	if( close(this->fdesc_) < 0 ){
		LOG_ERROR << __FUNCTION__ << " error closing serial ";
		exit(EXIT_FAILURE);
	}
}

void Serial::init(int baud){
    struct termios ts;
    tcflush(this->fdesc_, TCIOFLUSH);
    tcgetattr(this->fdesc_, &ts);
    cfsetispeed(&ts, baud);
    cfsetospeed(&ts, baud);
    ts.c_cflag &= ~CSIZE;
    ts.c_cflag &= ~CSTOPB;
    ts.c_cflag &= ~PARENB;
    ts.c_cflag |= CS8;
    ts.c_cflag |= CREAD;
    ts.c_cflag |= CLOCAL;
    tcsetattr(this->fdesc_, TCSANOW, &ts);
}

/**
 *  @brief write simple char messages to serial interface
 */
int Serial::send(char* buffer, unsigned char numBytes){
	write(this->fdesc_, buffer, numBytes);
	return 0;
}

/**
 *  @brief read simple char messages from serial interface
 */
int Serial::recv(char* p){
	if( readcond(this->fdesc_, p, sizeof(char), sizeof(char),0,10000) > 0) {
		return 0;
	}
	return -1;
}


/**
 *  @brief write ... to serial interface
 */
int Serial::send( Message msg ) {
	serial_mutex.lock();
	write(this->fdesc_, &msg, sizeof(Message));
	serial_mutex.unlock();
	return 0;
}

/**
 *  @brief read ... from serial interface
 */
int Serial::recv( Message *msg ){
	if( readcond(this->fdesc_, msg, sizeof(Message), sizeof(Message),0,10000) > 0) {
		return 0;
	}
	return -1;
}

void Serial::flush() {
	LOG_WARNING << __FUNCTION__ << " perform flush.";
	serial_mutex.lock();
	tcflush(this->fdesc_, TCIOFLUSH);
	serial_mutex.unlock();
}




} /* namespace serial */
} /* namespace io */
} /* namespace hal */
