/*
 * Motor.h
 *
 *  Created on: 16.10.2017
 *      Author: abj240
 */

#ifndef MOTOR_H_
#define MOTOR_H_

namespace hal {
namespace actuators {

class Motor {
public:
	/**
	* @brief creates singleton instance on first call, otherwise returns instance
	* @return singleton instance
	*/
	static Motor& instance();

	/**
	* @brief starts the motor without changing other behaviors
	*/
	void start();

	/**
	* @brief stops the motor without changing other behaviors
	*/
	void stop();

	/**
	* @brief sets the motor to clockwise rotation without changing other behaviors
	*/
	void setClockwiseRotation();

	/**
	* @brief sets the motor to counterclockwise rotation without changing other behaviors
	*/
	void setCounterclockwiseRotation();

	/**
	* @brief sets motor's slow bit
	*/
	void setSlow();

	/**
	* @brief unsets motor's slow bit
	*/
	void clearSlow();

private:
	Motor();
	Motor(Motor const&);
	Motor& operator=(Motor const&);
	~Motor();
};

} /* namespace actuators */
} /* namespace hal */

#endif /* MOTOR_H_ */
