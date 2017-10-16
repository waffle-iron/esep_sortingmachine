/*
 * HardwareAbstractionLayer.h
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#ifndef HARDWAREABSTRACTIONLAYER_H_
#define HARDWAREABSTRACTIONLAYER_H_

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

	};

}

#endif /* HARDWAREABSTRACTIONLAYER_H_ */
