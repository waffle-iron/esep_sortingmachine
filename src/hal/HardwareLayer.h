/*
 * HardwareLayer.h
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#ifndef HARDWARELAYER_H_
#define HARDWARELAYER_H_

#include "Motor.h"
#include "SwitchPoint.h"
#include "TrafficLight.h"
#include "Observable.h"

namespace hardwareLayer {

	class HardwareLayer : public Observable{
	public:
		HardwareLayer();
		virtual ~HardwareLayer();

		string getSignal();

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

	private:
		actuators::Motor& _motor;
		actuators::SwitchPoint& _switchPoint;
		mmi::TrafficLight& _trafficLight;

	};

}

#endif /* HARDWARELAYER_H_ */
