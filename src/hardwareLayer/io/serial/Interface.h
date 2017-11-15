/*
 * Serial.h
 *
 *  Created on: 16.10.2017
 *      Author: aca311
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <string>
#include <Message.h>
#include <mutex>


namespace hardwareLayer {
namespace io {
namespace serial {

class Serial {
	public:
		Serial(std::string dev);
		Serial(std::string dev, int baud);
		~Serial();
		void init(int baud);

		int send(char* buffer, unsigned char numBytes);
		int recv(char* p);

		/*
		 *@brief: #TODO check if msg gets send asynchronous or synchronous.
		 *@brief: if asynchronous we need to refactor this method
		 */
		int send(Message msg);
		int recv(Message *msg);

		void flush(void);

	private:
		Serial(const Serial& other);
		Serial& operator=(const Serial& other);

		int fdesc_;
		std::mutex serial_mutex;
	};


} /* namespace serial */
} /* namespace io */
} /* namespace hal */

#endif /* INTERFACE_H_ */
