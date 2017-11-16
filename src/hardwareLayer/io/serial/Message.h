/*
 * Message.h
 *
 *  Created on: 30.10.2017
 *      Author: Flo
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "Header.h"
#include "Item.h"
#include "Signals.h"

constexpr int CORRECT_CN = 654321;
constexpr int WRONG_CN = 123456;

struct Message {
	Message() :
	Message(Signal(), CORRECT_CN)
	{

	}
	Message(Signal signal) :
	Message(signal, CORRECT_CN)
	{

	}
	Message(bool wrongCheckNumber) :
	Message(Signal(), wrongCheckNumber ? WRONG_CN : CORRECT_CN)
	{

	}
	Message(Signal signal, int checkNumber) :
	checkNumber(checkNumber),
	signal(signal)
	{

	}

	int checkNumber;
	Signal signal;
	Item payload;
};






#endif /* MESSAGE_H_ */
