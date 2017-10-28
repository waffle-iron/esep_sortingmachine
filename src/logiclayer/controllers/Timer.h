/*
 * Timer.h
 *
 *  Created on: Oct 28, 2017
 *      Author: stammtisch
 */

#ifndef TIMER_H_
#define TIMER_H_

namespace logicLayer {

class Timer {
public:
	Timer();
	virtual ~Timer();
	void setTimeframe(Item* item);
	Signal getSignal(); // motor signale
	void sendSignalToItemController(Signal light_barrier_simulation_signal);
private:
	void setInTimeFrameFlag(Item* item);
	void setOutOfTimeFrameFlag(Item* item);
};

} /* namespace logicLayer */
#endif /* TIMER_H_ */
