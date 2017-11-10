/*
 * LogicLayer.cpp
 *
 *  Created on: 26.10.2017
 *      Author: abj240
 */

#include "LogicLayer.h"


namespace logicLayer {

LogicLayer::LogicLayer(hardwareLayer::HardwareLayer& hal) :
hal(hal)
{
	//hal.register_observer(this);
	hal.getSignalGenerator().register_observer(this); //listen to SignalGenerator
}

LogicLayer::~LogicLayer() {
	// TODO Auto-generated destructor stub
}


void LogicLayer::notify(){
	Signal signal;

	cout << "notify called";

	while((signal = hal.getSignal()).name != Signalname::SIGNAL_BUFFER_EMPTY) {
		cout << "LogicLayer: I have been notified! Now I go get the Signal."
				<< endl;

		switch (signal.name) {
		// LIGHTS
		case Signalname::YELLOW_LIGHT_ON:
			hal.yellowLightOn();
			break;
		case Signalname::RED_LIGHT_ON:
			hal.redLightOn();
			break;
		case Signalname::GREEN_LIGHT_ON:
			hal.greenLightOn();
			break;
		case Signalname::BLINK_GREEN_FAST:
			hal.blinkGreen(Speed::fast);
			break;
		case Signalname::BLINK_RED_FAST:
			hal.blinkRed(Speed::fast);
			break;
		case Signalname::BLINK_YELLOW_FAST:
			hal.blinkYellow(Speed::fast);
			break;
		case Signalname::BLINK_GREEN_SLOW:
			hal.blinkGreen(Speed::slow);
			break;
		case Signalname::BLINK_YELLOW_SLOW:
			hal.blinkYellow(Speed::slow);
			break;
		case Signalname::BLINK_RED_SLOW:
			hal.blinkRed(Speed::slow);
			break;
		case Signalname::RED_LIGHT_OFF:
			hal.redLightOff();
			break;
		case Signalname::YELLOW_LIGHT_OFF:
			hal.yellowLightOff();
			break;
		case Signalname::GREEN_LIGHT_OFF:
			hal.greenLightOff();
			break;

			// MOTOR
		case Signalname::MOTOR_START:
			hal.motorStart();
			break;
		case Signalname::MOTOR_STOP:
			hal.motorStop();
			break;
		case Signalname::MOTOR_FAST:
			hal.motorFast();
			break;
		case Signalname::MOTOR_ROTATE_CLOCKWISE:
			hal.motorRotateClockwise();
			break;
		case Signalname::MOTOR_ROTATE_COUNTER_CLOCKWISE:
			hal.motorRotateCounterclockwise();
			break;

			// SWITCH
		case Signalname::SWITCH_OPEN:
			hal.switchPointOpen();
			break;
		case Signalname::SWITCH_CLOSE:
			hal.switchPointClose();
			break;


		case Signalname::CONNECTION_LOST:
			hal.blinkRed(Speed::slow);
			break;
		case Signalname::CONNECTION_CONNECTED:
			hal.redLightOff();
			break;
		default:
			break;
		}

	}
	cout << "LogicLayer: I have been notified! All signals read." << endl;
	//cout << hal.getSignal().name << endl;
}
} /* namespace logicLayer */
