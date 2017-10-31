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
#include "Errorcontroller.h"
#include "HAL.h"
#include "Item.h"
#include "Timer.h"
#include <vector>

namespace logicLayer {
namespace controller {

class ItemController : public Controller {
public:
	ItemController(hal::HAL& hal);
	virtual ~ItemController();

private:
	/*
	 * @brief adds new item to items vector
	 */
	void addNewItem();

	Errorcontroller errorController;
	Timer timer;
	vector<Item> items;
};

} /* namespace controller */
} /* namespace logicLayer */
#endif /* ITEMCONTROLLER_H_ */
