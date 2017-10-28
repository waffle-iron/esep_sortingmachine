/*
 * Item.h
 *
 *  Created on: Oct 28, 2017
 *      Author: stammtisch
 */

#ifndef ITEM_H_
#define ITEM_H_

namespace logicLayer {

class Item {
public:
	Item();
	virtual ~Item();

	bool lb_input_interrupted();
	bool lb_input_not_interrupted();
	bool lb_height_interrupted();
	bool lb_height_not_interrupted();
	bool lb_switch_interrupted();
	bool lb_switch_not_interrupted();
	bool lb_slide_interrupted();
	bool lb_slide_not_interrupted();
	bool lb_output_interrupted();
	bool lb_output_not_interrupted();


};

} /* namespace logicLayer */
#endif /* ITEM_H_ */
