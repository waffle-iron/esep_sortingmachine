/*
 * HardwareLayer.h
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#ifndef HARDWARELAYER_H_
#define HARDWARELAYER_H_

#include <thread>
#include "Signals.h"
#include "Motor.h"
#include "SwitchPoint.h"
#include "TrafficLight.h"
#include "SignalGenerator.h"
#include "Observable.h"
#include "Message.h"
#include "Serial.h"
#include "WatchDog.h"
#include "Receiver.h"
#include "HeightSensor.h"


namespace hardwareLayer {

	class HardwareLayer : public Observable{
	public:
		HardwareLayer();
		virtual ~HardwareLayer();

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

		uint16_t getHeight();

		/**
		 *  @brief Sends messages via serial interface to other machine
		 */
		void sendSerialMsg(Message*);

		/**
		 * @brief 	If a pending signal exists
		 * @return  returns one pending signal generated by SignalGenerator.
		 * 			If there are no pending signals return value is Signal(cb_x,cb_x,SIGNAL_BUFFER_EMPTY)
		 */
		Signal getSignal();

		/**
		 * @brief removes all signals from Buffer and adds SIGNAL_BUFFER_EMPTY signal
		 *
		 * if removing all signals fails a error message gets logged.
		 */
		void clearSignalBuffer();

		//GETTER
		io::SignalGenerator& getSignalGenerator();

	private:
		actuators::Motor& _motor;
		actuators::SwitchPoint& _switchPoint;

		mmi::TrafficLight& _trafficLight;

		io::SignalGenerator signalGenerator;
		io::serial::Serial _serialSender;
		io::serial::Serial _serialReceiver;
		io::serial::WatchDog _watchDog;
		io::serial::Receiver _receiver;

		std::thread _th_watchDog;
		std::thread _th_receiver;

		sensors::HeightSensor &_heightSensor;

};


}

#endif /* HARDWARELAYER_H_ */