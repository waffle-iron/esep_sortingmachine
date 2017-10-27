/*
 * SingletenTest.h
 *
 *  Created on: 27.10.2017
 *      Author: aca311
 */

#ifndef SINGLETONTEST_H_
#define SINGLETONTEST_H_

class SingletonTest {
public:
	SingletonTest();
	virtual ~SingletonTest();
	static SingletonTest& instance();
};

#endif /* SINGLETONTEST_H_ */
