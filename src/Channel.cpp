/*
 * Channel.cpp
 *
 *  Created on: 13.11.2017
 *      Author: aca311
 */

#include "Channel.h"

Channel::Channel(const size_t max_size)
: sem_free_spaces_ {max_size}
, sem_size_ {}
, queue_ {}
, mtx_ {}
{}

size_t Channel::size(void) const {
	return sem_size_.get_value();
}

size_t Channel::max_size(void) const {
	return sem_free_spaces_.get_value() + sem_size_.get_value();
}

Signal Channel::dequeue(void) {
	sem_size_.wait();
	mtx_.lock();
	auto return__ = queue_.front();
	queue_.pop();
	mtx_.unlock();
	sem_free_spaces_.post();
	return return__;
}

void Channel::enqueue(const Signal element) {
	sem_free_spaces_.wait();
	mtx_.lock();
	queue_.push(element);
	mtx_.unlock();
	sem_size_.post();
}

void Channel::operator<<(const Signal element) {
	enqueue(element);
}


void Channel::destroy() {
	sem_free_spaces_.destroy();
	sem_size_.destroy();
}
