/*
 * Profiling.h
 *
 *  Created on: Oct 28, 2017
 *      Author: stammtisch
 */

#ifndef PROFILING_H_
#define PROFILING_H_

struct Profil {
	Enum Type,
	int height,
	(int binaryCode)
};

namespace logicLayer {

class Profiling {
public:
	Profiling();
	virtual ~Profiling();
	Signal getSignal(); // SENSOR_HEIGHT_MATCH,SENSOR_HEIGHT_NOT_MATCH,SENSOR_METAL_MATCH,SENSOR_METAL_NOT_MATCH,LIGHT_BARRIER_HEIGHT_INTERRUPTED,LIGHT_BARRIER_HEIGHT_NOT_INTERRUPTED,
	Profile getProfile();
};

} /* namespace logicLayer */
#endif /* PROFILING_H_ */
