/*
 * Dispatcher.h
 *
 *  Created on: Oct 28, 2017
 *      Author: stammtisch
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

namespace logicLayer {

class Dispatcher {
public:
	Dispatcher();
	virtual ~Dispatcher();
	void subscribe(Controller cont);
	void unsubscibe(Controller cont);
	void sendToControllers(Signal signal); // all lb_signal
private:
	Sorting sorting;
};

} /* namespace logicLayer */
#endif /* DISPATCHER_H_ */
