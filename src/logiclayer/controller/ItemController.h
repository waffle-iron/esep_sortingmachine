/*
 * ItemController.h
 *
 *  Created on: Oct 28, 2017
 *      Author: stammtisch
 */

#ifndef ITEMCONTROLLER_H_
#define ITEMCONTROLLER_H_


#include "Header.h"
#include "Controller.h"
#include "Item.h"
#include "Timer.h"
#include <vector>

namespace logicLayer {
namespace controller {

class ItemController : public Controller {
public:
	ItemController();
	virtual ~ItemController();
	void addNewItem();

private:
	Timer timer;
	vector<Item> items;
};

} /* namespace controller */
} /* namespace logicLayer */
#endif /* ITEMCONTROLLER_H_ */
