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
#include "SignalGenerator.h"

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

		Signal getSignal();
		/*
		 * @brief removes all signals from Buffer and adds SIGNAL_BUFFER_EMPTY signal
		 * if removing all signals fails a error message gets logged.
		 */
		void resetSignals();

	private:
		actuators::Motor& _motor;
		actuators::SwitchPoint& _switchPoint;
		mmi::TrafficLight& _trafficLight;
		io::SignalGenerator signalGenerator;

};

}

#endif /* HAL_H_ */
