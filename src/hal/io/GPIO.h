/*
 * GPIO.h
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#include "Header.h"

#ifndef GPIO_H_
#define GPIO_H_

#include <mutex>

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
	port_t read(PORT port);
	void setBits(PORT port, port_t bitmask);
	void clearBits(PORT port, port_t bitmask);

protected:
	virtual void write(  PORT port, port_t val);
	GPIO();

	std::mutex gpio_mutex;

private:
	static GPIO  *_instance;

};

} /* namespace gpio */
} /* namespace hal */
#endif /* GPIO_H_ */
