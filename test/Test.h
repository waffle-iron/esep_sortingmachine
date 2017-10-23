/*
 * Test.h
 *
 *  Created on: 23.10.2017
 *      Author: abx724
 */

#ifndef TEST_H_
#define TEST_H_

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

	/**
	 *	@brief go to next test
	 */
	bool nextTest();

	/**
	 *  @brief test thread safeness in GPIO class
	 */
	void threadSafenessInGpioTest();
};


} /* test */
} /* logicLayer */

#endif /* TEST_H_ */


