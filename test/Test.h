/*
 * Test.h
 *
 *  Created on: 23.10.2017
 *      Author: abx724
 */

#ifndef TEST_H_
#define TEST_H_

#include "GPIO.h"
#include <string>


namespace logicLayer{
namespace test{

class Test {
public:
	Test();
	virtual ~Test();

	/**
	 *
	 */
	void actuatorsTest();

	/**
	 *
	 */
	void mmiTest();

	/**
	 *
	 */
	void sensorsTest();

	void singletonThreadSafeTest();

	/**
	 *  @brief test thread safeness in GPIO class
	 */
	void threadSafenessInGpioTest();
private:
	/**
	 *
	 */
	static void writeSomethingElse(hal::io::GPIO *gpio, int difference);

	/**
	 *	@brief go to next test
	 */
	bool nextTest(string functionName);

};


} /* test */
} /* logicLayer */

#endif /* TEST_H_ */


