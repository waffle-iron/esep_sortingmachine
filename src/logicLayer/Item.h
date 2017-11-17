
/*
 * Item.h
 *
 *  Created on: 15.11.2017
 *      Author: abx724
 */

#ifndef ITEM_H_
#define ITEM_H_

#include "SignalReceiver.h"

namespace logicLayer {

class Item: public logicLayer::SignalReceiver {
public:
	Item();
	virtual ~Item();
	void operator()();
};

} /* namespace logicLayer */
#endif /* ITEM_H_ */
