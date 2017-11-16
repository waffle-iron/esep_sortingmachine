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


namespace hardwareLayer {
namespace io {
namespace serial {

class Interface {
	public:
		Interface(std::string dev);
		Interface(std::string dev, int baud);
		~Interface();

		/*
		 *  @brief sends Message to serial interface
		 *  @return the number of written bytes or -1 if error occured.
		 */
		int send(Message msg);

		/*
		 *@brief: receives Message from serial interface in a threadsafe manner.
		 *@brief: waits till sizeof(Message) bytes received or timeout happened.
		 *@return: 0 or -1 when error occured.
		 */
		int recv(Message *msg);

		/*
		 *@brief: performs flush on serial interface in a threadsafe manner.
		 *@return: 0 or -1 when error occured.
		 */
		int flush(void);

	private:
		/*
		 * @brief init serial interface
		 * @return 0 or negativ when error(s) occured.
		 *
		 * with following options:
		 *
		 */
		int init(int baud);
		Interface(const Interface& other);
		Interface& operator=(const Interface& other);

		int fdesc_;
	};


} /* namespace serial */
} /* namespace io */
} /* namespace hal */

#endif /* INTERFACE_H_ */
