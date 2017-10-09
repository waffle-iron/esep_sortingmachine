/*
 * test.h
 *
 *  Created on: 09.10.2017
 *      Author: abj240
 */

#ifndef TEST_H_
#define TEST_H_


#include <stdio.h>
#include <hw/inout.h>
#include <stdint.h>

constexpr int PIN_RED_LIGHT = 7;
constexpr int PIN_YELLOW_LIGHT = 6;
constexpr int PIN_GREEN_LIGHT = 5;

constexpr int PORT_A_ADDR = 0x300;

class Test {



public:
	Test();
	virtual ~Test();
	void setBit(int bit);
	void clearBit(int bit);
};


#endif /* TEST_H_ */
