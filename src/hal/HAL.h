/*
 * HAL.h
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#ifndef HAL_H_
#define HAL_H_

#include "Motor.h"

namespace hal {

	class HAL {
	public:
		HAL();
		virtual ~HAL();

		void greenLightOn();
		void greenLightOff();
		void yellowLightOn();
		void yellowLightOff();
		void redLightOn();
		void redLightOff();

		void motorStart();
		void motorRotateClockwise();

	private:
		actuators::Motor *_motor;

	};

}

#endif /* HAL_H_ */
