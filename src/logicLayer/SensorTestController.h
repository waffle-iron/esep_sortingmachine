/*
 * SensorTestController.h
 *
 *  Created on: 16.11.2017
 *      Author: abj240
 */

#ifndef SENSORTESTCONTROLLER_H_
#define SENSORTESTCONTROLLER_H_

#include "Signals.h"
#include "HardwareLayer.h"
#include "Header.h"
#include <iostream>

namespace logicLayer {

struct Data{
	Data(int d) : data1(d){}
	int data1;
};

class SensorTestController {
private:
	struct State {//top-level state
		virtual void lb_input_interrupted(){}//put code here for signalA in superstate
		virtual void lb_input_freed(){}//put code here for signalA in superstate
		virtual void lb_height_interrupted(){}//put code here for signalA in superstate
		virtual void lb_height_freed(){}//put code here for signalA in superstate

		hardwareLayer::HardwareLayer* hal;
		Data* data;// pointer to data, which physically resides inside the context class (contextdata)
	} *statePtr;   // a pointer to current state. Used for polymorphism.

	struct TestFailed : public State {
	};

	struct WaitingForLB_INPUT : public State {
		virtual void lb_input_interrupted(){// put code here for transition from A with signalA
			cout<<__FUNCTION__<<endl;
			hal->motorRotateClockwise();
			hal->motorFast();
			hal->motorStart();
		}
		virtual void lb_input_freed(){//put code here for state B and signalA. Data may be accessed via data->
			cout<<__FUNCTION__<<endl;
			new (this) WaitingForLB_HEIGHT;
		}
	};

	struct WaitingForLB_HEIGHT : public State {
		virtual void lb_height_interrupted(){//put code here for state B and signalA. Data may be accessed via data->
			cout<<__FUNCTION__<<endl;
			WAIT(50);
			hal->motorRotateCounterclockwise();
		}
		virtual void lb_height_freed(){//put code here for state B and signalA. Data may be accessed via data->
			cout<<__FUNCTION__<<endl;
			new (this) WaitingForLB_INPUT;
		}
	};

	WaitingForLB_INPUT stateMember;//The memory for the state is part of context object

	hardwareLayer::HardwareLayer& hal;
	Data contextdata;  //Data is also kept inside the context object

public:
	SensorTestController(hardwareLayer::HardwareLayer& hal)
	: statePtr(&stateMember) // assigning start state
	, hal(hal)
	, contextdata(0)         // initializing data
	{
		statePtr->hal = &hal;
		statePtr->data = &contextdata; // connecting state->data with the context data
	}

	virtual void lb_input_interrupted(){statePtr->lb_input_interrupted();} // context delegates signals to state
	virtual void lb_input_freed(){statePtr->lb_input_freed();} // context delegates signals to state
	virtual void lb_height_interrupted(){statePtr->lb_height_interrupted();} // context delegates signals to state
	virtual void lb_height_freed(){statePtr->lb_height_freed();} // context delegates signals to state
};

} /* namespace logicLayer */
#endif /* SENSORTESTCONTROLLER_H_ */
