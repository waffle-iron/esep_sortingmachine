/*
 * TrafficLights.h
 *
 *  Created on: 16.10.2017
 *      Author: aca311
 */

#ifndef TRAFFICLIGHT_H_
#define TRAFFICLIGHT_H_

namespace hal {
namespace io {

class TrafficLight {
public:
	static TrafficLight *instance();
	virtual ~TrafficLight();


	/**
	* @brief turns the green light on
	*/
	void setGreenLight();

	/**
	* @brief turns the yellow light on
	*/
	void setYellowLight();

	/**
	* @brief turns the red light on
	*/
	void setRedLight();

	/**
	* @brief makes the green light blink
	*/
	void blinkGreen();

	/**
	* @brief makes the yellow light blink
	*/
	void blinkYellow();

	/**
	* @brief makes the red light blink
	*/
	void blinkRed();

private:
	TrafficLight();

	static TrafficLight *_instance;

};
} /* namespace io */
} /* namespace hal */

#endif /* TRAFFICLIGHT_H_ */
