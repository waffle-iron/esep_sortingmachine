/*
 * observerpattern.hpp
 *
 *  Created on: 27.10.2017
 *      Author: abx852
 */

#ifndef OBSERVERPATTERN_HPP_
#define OBSERVERPATTERN_HPP_
#include <vector>

class Observer {
	public:
	virtual void notify() = 0;
};

class Subject {
	public:
	void register_observer(Observer* o) 	{
		observers.push_back(o); 		}
	void notify_observers() 		{
		for (vector<Observer*>::iterator  it = observers.begin(); it != observers.end(); ++it) {
			(*it)->notify();
		}
	}
	private:
		vector<Observer*> observers;
};

class HardwareLayer : public Subject {

public:
	string getSignal() {
		return "Hello world!";
	}

};

class LogicLayer	 : public Observer {
	public:
	LogicLayer(HardwareLayer& hal) :
	hal(hal) {
		hal.register_observer(this);
	}
	virtual void notify()  		{
		cout << hal.getSignal() << endl;
	}
	private:
	HardwareLayer& hal;
};

#endif /* OBSERVERPATTERN_HPP_ */
