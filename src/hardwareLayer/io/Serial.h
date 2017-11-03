/*
 * Serial.h
 *
 *  Created on: 16.10.2017
 *      Author: aca311
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include <string>

namespace hardwareLayer {
namespace io {

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

	private:
		Serial(const Serial& other);
		Serial& operator=(const Serial& other);
	};


}
}
#endif /* SERIAL_H_ */
