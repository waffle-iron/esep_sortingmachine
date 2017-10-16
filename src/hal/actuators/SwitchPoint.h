/*
 * SwitchPoint.h
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#ifndef SWITCHPOINT_H_
#define SWITCHPOINT_H_

namespace hal {
namespace actuators {

class SwitchPoint {
public:
	static SwitchPoint *instance();
	virtual ~SwitchPoint();

private:
	SwitchPoint();

	static SwitchPoint *_instance;
};

} /* namespace actuators */
} /* namespace hal */

#endif /* SWITCHPOINT_H_ */
