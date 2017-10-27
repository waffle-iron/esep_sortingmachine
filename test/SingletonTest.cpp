/*
 * SingletenTest.cpp
 *
 *  Created on: 27.10.2017
 *      Author: aca311
 */

#include "SingletonTest.h"
#include <thread>
#include <chrono>
#include "Header.h"


SingletonTest& SingletonTest::instance() {
	static SingletonTest instance;
	return instance;
}



SingletonTest::SingletonTest() {
	cout<< "creating singleton" << endl;
	WAIT(5000);

}

SingletonTest::~SingletonTest() {
	// TODO Auto-generated destructor stub
}


