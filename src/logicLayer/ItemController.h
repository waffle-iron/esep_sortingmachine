/*
 * ItemController.h
 *
 *  Created on: 15.11.2017
 *      Author: abx724
 */

#ifndef ITEMCONTROLLER_H_
#define ITEMCONTROLLER_H_

#include "SignalReceiver.h"

namespace logicLayer {

class ItemController: public logicLayer::SignalReceiver {
public:
	ItemController();
	virtual ~ItemController();
};

} /* namespace logicLayer */
#endif /* ITEMCONTROLLER_H_ */
