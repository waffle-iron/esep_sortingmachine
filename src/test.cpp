/*
 * test.cpp
 *
 *  Created on: 09.10.2017
 *      Author: abj240
 */

#include "test.h"


Test::Test() {
	// TODO Auto-generated constructor stub

}

Test::~Test() {
	// TODO Auto-generated destructor stub
}

void Test::setBit(int bit)
{
	if(bit < 8) {
		int port_a = in8(PORT_A_ADDR);
		out8(PORT_A_ADDR, port_a | (1 << bit));
	}
}

void Test::clearBit(int bit)
{
	if(bit < 8) {
		int port_a = in8(PORT_A_ADDR);
		out8(PORT_A_ADDR, port_a & ~(1 << bit));
	}
}
