/*
 * HeightSensor.h
 *
 *  Created on: 30.10.2017
 *      Author: aca311
 */

#ifndef HEIGHTSENSOR_H_
#define HEIGHTSENSOR_H_

#include "Header.h"


namespace hal {
namespace sensors {
class HeightSensor {
public:
	static HeightSensor& instance();
	uint16_t getHeight(void);

private:
	HeightSensor();
	HeightSensor(HeightSensor const&);
	HeightSensor& operator=(HeightSensor const&);
	~HeightSensor();
};


}
}

#endif /* HEIGHTSENSOR_H_ */
