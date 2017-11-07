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
	/**
	* @brief creates singleton instance on first call, otherwise returns instance
	* @return singleton instance
	*/
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
} /* namespace hardwareLayer */

#endif /* SWITCHPOINT_H_ */
