/*
 * Serial.h
 *
 *  Created on: 16.10.2017
 *      Author: aca311
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include <string>
#include <Message.h>

namespace hardwareLayer {
namespace io {
namespace serial {

class Serial {
	private:
		int fdesc_;

	public:
		Serial(std::string dev);
		Serial(std::string dev, int baud);
		~Serial();
		void init(int baud);

		int send(char* buffer, unsigned char numBytes);
		int recv(char* p);

		int send(Message msg);
		int recv(Message *msg);

		void flush(void);

	private:
		Serial(const Serial& other);
		Serial& operator=(const Serial& other);
	};


} /* namespace serial */
} /* namespace io */
} /* namespace hal */

#endif /* SERIAL_H_ */
