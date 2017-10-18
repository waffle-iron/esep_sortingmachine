/*
 * GPIO.h
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#ifndef GPIO_H_
#define GPIO_H_

enum class PORT {
    A,
    B,
    C
};

namespace hal {
namespace io {


class GPIO {
public:
	static GPIO *instance();
	virtual ~GPIO();
	void gainAccess();
	int  read(   PORT port);
	void setBits(PORT port, int bitmask);
	void clearBits(PORT port, int bitmask);

private:
	static GPIO  *_instance;

	GPIO();
	void write(  PORT port, int val);
};

} /* namespace gpio */
} /* namespace hal */
#endif /* GPIO_H_ */
