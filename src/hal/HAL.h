/*
 * HAL.h
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#ifndef HAL_H_
#define HAL_H_

#include "Motor.h"
#include "SwitchPoint.h"
#include "TrafficLight.h"
#include "Item.h"

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

		void blinkGreen(Speed speed);
		void blinkRed(Speed speed);
		void blinkYellow(Speed speed);

		void motorStart();
		void motorStop();
		void motorSlow();
		void motorFast();
		void motorRotateClockwise();
		void motorRotateCounterclockwise();

		void switchPointOpen();
		void switchPointClose();

		/*
		 * @brief used to send a signal via serial interface
		 */
		void sendSignal(Signal signal);

		/*
		 * @brief used to send an item via serial interface
		 */
		void sendItem(logicLayer::Item item);

	private:
		actuators::Motor& _motor;
		actuators::SwitchPoint& _switchPoint;
		mmi::TrafficLight& _trafficLight;

	};

}

#endif /* HAL_H_ */
