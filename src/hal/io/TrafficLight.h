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
	static trafficLight *instance();
	virtual ~TrafficLight();
	constexpr int PIN_RED_LIGHT = 7;
	constexpr int PIN_YELLOW_LIGHT = 6;
	constexpr int PIN_GREEN_LIGHT = 5;

	constexpr int PORT_A_ADDR = 0x300;


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

};
} /* namespace io */
} /* namespace hal */

#endif /* TRAFFICLIGHT_H_ */
