/*
 * SwitchPoint.h
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#ifndef SWITCHPOINT_H_
#define SWITCHPOINT_H_

/**
 * Switchpoint open
 */

namespace hardwareLayer {
namespace actuators {

class SwitchPoint {
public:

	static SwitchPoint& instance();

	/**
	 *  @brief opens switchpoint
	 */
	void open();

	/**
	 *  @brief closes switchpoint
	 */
	void close();

private:
	SwitchPoint();
	SwitchPoint(SwitchPoint const&);
	SwitchPoint& operator=(SwitchPoint const&);
	~SwitchPoint();


};

} /* namespace actuators */
} /* namespace hal */

#endif /* SWITCHPOINT_H_ */
