/*
 * Observable.h
 *
 *  Created on: 30.10.2017
 *      Author: abx852
 */

#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include <vector>
#include "Observer.h"

class Observable {
public:
	void register_observer(Observer* o) {
		//check if observer already exists
		if (observers.size() > 0) {
			for (auto &observer : observers) {
				if (observer == o) {
					LOG_ERROR<<"tried to add Observer for second time"<<endl;
				}
			}
		} else {
			observers.push_back(o);
		}
	}
	void notify_observers() {
		for (vector<Observer*>::iterator  it = observers.begin(); it != observers.end(); ++it) {
			(*it)->notify();
		}
	}
private:
	vector<Observer*> observers;
};

#endif /* OBSERVABLE_H_ */
