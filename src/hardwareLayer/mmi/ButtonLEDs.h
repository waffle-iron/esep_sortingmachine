/*
 * ButtonLEDs.h
 *
 *  Created on: 10.11.2017
 *      Author: aca311
 */

#ifndef BUTTONLEDS_H_
#define BUTTONLEDS_H_

namespace hardwareLayer {
namespace mmi {

class ButtonLEDs {
public:
	/**
	* @brief creates singleton instance on first call, otherwise returns instance
	* @return singleton instance
	*/
	static ButtonLEDs& instance();
	/**
	* @brief turns the Start LED on
	*/
	void LEDStartOn();
	/**
	* @brief turns the Start LED off
	*/
	void LEDStartOff();
	/**
	* @brief turns the Reset LED on
	*/
	void LEDResetOn();
	/**
	* @brief turns the Reset LED off
	*/
	void LEDResetOff();
	/**
	* @brief turns LED Q1 on
	*/
	void LEDQ1On();
	/**
	* @brief turns LED Q1 off
	*/
	void LEDQ1Off();
	/**
	* @brief turns LED Q2 on
	*/
	void LEDQ2On();
	/**
	* @brief turns LED Q2 off
	*/
	void LEDQ2Off();


private:
	ButtonLEDs();
	virtual ~ButtonLEDs();
	ButtonLEDs(ButtonLEDs const&);
	ButtonLEDs& operator=(ButtonLEDs const&);
};

}
}

#endif /* BUTTONLEDS_H_ */
