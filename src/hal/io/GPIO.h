/*
 * GPIO.h
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#include "Header.h"

#ifndef GPIO_H_
#define GPIO_H_

enum class PORT {
    A,
    B,
    C
};

namespace hal {
namespace io {

class Base{
	public:
		void a(){
			cout << "BASE:A" << endl;
			b();
		}
		virtual ~Base(){}

	protected:
		virtual void b(){
			cout << "BASE:B" << endl;
		}
};


class GPIO {
public:
	static GPIO *instance();
	virtual ~GPIO();
	void gainAccess();
	port_t read(PORT port);
	void setBits(PORT port, port_t bitmask);
	void clearBits(PORT port, port_t bitmask);

protected:
	static GPIO  *_instance;
	GPIO();
	virtual void write(  PORT port, port_t val);
};

} /* namespace gpio */
} /* namespace hal */
#endif /* GPIO_H_ */
