/*
 * Sorting.h
 *
 *  Created on: Oct 28, 2017
 *      Author: stammtisch
 */

#ifndef SORTING_H_
#define SORTING_H_

#include "Item.h"

namespace logicLayer {

class Sorting {
public:
	Sorting();
	virtual ~Sorting();
	bool amIWanted(Item* item);
	void setOtherSlideFull();
	void setOtherSlideEmpty();
};

} /* namespace logicLayer */
#endif /* SORTING_H_ */
