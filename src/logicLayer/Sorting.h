/*
 * Sorting.h
 *
 *  Created on: 15.11.2017
 *      Author: abx724
 */

#ifndef SORTING_H_
#define SORTING_H_

#include "SignalReceiver.h"

namespace logicLayer {

class Sorting : public SignalReceiver {
public:
	Sorting();
	virtual ~Sorting();
	void operator()();
};

} /* namespace logicLayer */
#endif /* SORTING_H_ */
