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

//	cout << "notify called";

	while((signal = hal.getSignal()).name != Signalname::SIGNAL_BUFFER_EMPTY) {

		if(cb_this != cb_1 && signal.receiver > cb_this) {
			hal.sendSerialMsg(Message(signal));
		}

		switch (signal.name) {
		// serial
		case Signalname::CONNECTION_LOST:
			cout<<"CONNECTION LOST"<<endl;
			hal.blinkRed(Speed::slow);
			hal.greenLightOff();
			cb_this.parameterList.showParameters();
			break;
		case Signalname::CONNECTION_CONNECTED:
			cout<<"CONNECTION CONNECTED"<<endl;
			hal.blinkGreen(Speed::slow);
			hal.redLightOff();
			cb_this.parameterList.showParameters();
			break;
		case Signalname::SERIAL_WATCHDOG_TOKEN:
			hal.sendSerialMsg(Message(signal));
			break;
		case Signalname::SERIAL_WATCHDOG_FEED:
			hal.sendSerialMsg(Message(signal));
			break;
		// mmi
		// traffic lights
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
		// leds
		case Signalname::Q1_LED_ON:
			hal.Q1LEDOn();
			break;
		case Signalname::Q1_LED_OFF:
			hal.Q1LEDOff();
			break;
		case Signalname::Q2_LED_ON:
			hal.Q2LEDOn();
			break;
		case Signalname::Q2_LED_OFF:
			hal.Q2LEDOff();
			break;
		case Signalname::RESET_LED_ON:
			hal.ResetLEDOn();
			break;
		case Signalname::RESET_LED_OFF:
			hal.ResetLEDOff();
			break;
		case Signalname::START_LED_ON:
			hal.StartLEDOn();
			break;
		case Signalname::START_LED_OFF:
			hal.StartLEDOff();
			break;
		// motor
		case Signalname::MOTOR_START:
			LOG_DEBUG << "call MOTOR start ";
			hal.motorStart();
			LOG_DEBUG << "MOTOR started ";
			break;
		case Signalname::MOTOR_STOP:
			LOG_DEBUG << "call MOTOR stop ";
			hal.motorStop();
			LOG_DEBUG << "call MOTOR stopped ";
			break;
		case Signalname::MOTOR_FAST:
			LOG_DEBUG << "call MOTOR fast ";
			hal.motorFast();
			LOG_DEBUG << "end MOTOR  fast";
			break;
		case Signalname::MOTOR_SLOW:
			LOG_DEBUG << "call MOTOR slow ";
			hal.motorSlow();
			LOG_DEBUG << "end MOTOR  slow";
			break;
		case Signalname::MOTOR_ROTATE_CLOCKWISE:
			LOG_DEBUG << "call MOTOR clockwise ";
			hal.motorRotateClockwise();
			LOG_DEBUG << "end MOTOR  clockwise";
			break;
		case Signalname::MOTOR_ROTATE_COUNTER_CLOCKWISE:
			LOG_DEBUG << "call MOTOR counter clockwise ";
			hal.motorRotateCounterclockwise();
			LOG_DEBUG << "end MOTOR  clockwise";
			break;
		// switch
		case Signalname::SWITCH_OPEN:
			hal.switchPointOpen();
			break;
		case Signalname::SWITCH_CLOSE:
			hal.switchPointClose();
			break;

		default:
			LOG_ERROR<<__FUNCTION__<<" unknown signal occurred.";
			cout<<__FUNCTION__<<" unknown signal occurred."<<endl;
			break;
		}

	}
}
} /* namespace logicLayer */
