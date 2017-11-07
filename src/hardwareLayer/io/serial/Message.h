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

struct Message {
	Message() :
		checkNumber( 0 )
	{

	}
	int checkNumber;
	Signal signal;
	Item payload;
};






#endif /* MESSAGE_H_ */
