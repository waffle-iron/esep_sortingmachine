/*
 * Channel.h
 *
 *  Created on: 13.11.2017
 *      Author: aca311
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_

//TODO delete unused imports
#include <queue>
#include "Signals.h"
#include "Semaphore2.h"

using namespace std;

class Channel {
public:
	explicit Channel(const size_t);
	~Channel();
	size_t size(void) const;
	size_t max_size(void) const;
	inline Signal dequeue(void);
	inline void enqueue(const Signal);
	void operator<<(const Signal);
	Signal friend operator<<(Signal& target, Channel& source) { return target = source.dequeue();}
	void friend operator<<(Channel& target, Channel& source) { target.enqueue(source.dequeue());}
	void destroy();

private:
	Semaphore2 sem_free_spaces_, sem_size_;
	queue<Signal> queue_;
	mutex mtx_;
};

#endif /* CHANNEL_H_ */
