/*
 * ItemController.cpp
 *
 *  Created on: Oct 28, 2017
 *      Author: stammtisch
 */

#include "ItemController.h"

namespace logicLayer {
namespace controller {

ItemController::ItemController(hal::HAL& hal) :
Controller(hal),
errorController(Errorcontroller(hal))
{

}

ItemController::~ItemController() {
	// TODO Auto-generated destructor stub
}

} /* namespace controller */
} /* namespace logicLayer */
