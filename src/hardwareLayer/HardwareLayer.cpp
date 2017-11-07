/*
 * HardwareAbstractionLayer.cpp
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#include "HardwareLayer.h"
#include "GPIO.h"
#include "Signals.h"

namespace hardwareLayer {

HardwareLayer::HardwareLayer() :
_motor(actuators::Motor::instance()),
_switchPoint(actuators::SwitchPoint::instance()),
_trafficLight(mmi::TrafficLight::instance()),
_heightSensor(sensors::HeightSensor::instance())
{
	LOG_SCOPE;

	motorStop();
	motorRotateClockwise();
	switchPointClose();
	greenLightOff();
	redLightOff();
	yellowLightOff();
}

HardwareLayer::~HardwareLayer() {
	LOG_SCOPE;

	motorStop();
	switchPointClose();
	greenLightOff();
	redLightOff();
	yellowLightOff();

}

void HardwareLayer::motorStart() {
	_motor.start();
}

void HardwareLayer::motorStop() {
	_motor.stop();
}

void HardwareLayer::motorSlow() {
	_motor.setSlow();
}

void HardwareLayer::motorFast() {
	_motor.clearSlow();
}

void HardwareLayer::motorRotateClockwise() {
	_motor.setClockwiseRotation();
}

void HardwareLayer::motorRotateCounterclockwise() {
	_motor.setCounterclockwiseRotation();
}

void HardwareLayer::switchPointOpen(){
	_switchPoint.open();
}

void HardwareLayer::switchPointClose(){
	_switchPoint.close();
}

void HardwareLayer::greenLightOn(){
	_trafficLight.greenLightOn();
}

void HardwareLayer::greenLightOff(){
	_trafficLight.greenLightOff();
}

void HardwareLayer::yellowLightOn(){
	_trafficLight.yellowLightOn();
}

void HardwareLayer::yellowLightOff(){
	_trafficLight.yellowLightOff();
}

void HardwareLayer::redLightOn(){
	_trafficLight.redLightOn();
}

void HardwareLayer::redLightOff(){
	_trafficLight.redLightOff();
}

void HardwareLayer::blinkGreen(Speed speed) {
	_trafficLight.blinkGreen(speed);
}

void HardwareLayer::blinkYellow(Speed speed) {
	_trafficLight.blinkYellow(speed);
}

void HardwareLayer::blinkRed(Speed speed) {
	_trafficLight.blinkRed(speed);
}

Signal HardwareLayer::getSignal() {
	return signalGenerator.nextSignal();
}

void HardwareLayer::clearSignalBuffer() {
	signalGenerator.clearSignalBuffer();
}

uint16_t HardwareLayer::getHeight() {
	return _heightSensor.getHeight();
}

} /* hardwareLayer */
