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
#include <string>

namespace logicLayer {

struct Data{
	Data(int d) : data1(d){}
	int data1;
};

class SensorTestController {
private:
	struct State {//top-level state
		virtual void start_sensor_test(){		testFailed(__FUNCTION__);}
		virtual void lb_input_interrupted(){	testFailed(__FUNCTION__);}
		virtual void lb_input_freed(){			testFailed(__FUNCTION__);}
		virtual void lb_height_interrupted(){	testFailed(__FUNCTION__);}
		virtual void lb_height_freed(){			testFailed(__FUNCTION__);}
		virtual void lb_switch_interrupted(){	testFailed(__FUNCTION__);}
		virtual void lb_switch_freed(){			testFailed(__FUNCTION__);}
		virtual void lb_slide_interrupted(){	testFailed(__FUNCTION__);}
		virtual void lb_slide_freed(){			testFailed(__FUNCTION__);}
		virtual void lb_output_interrupted(){	testFailed(__FUNCTION__);}
		virtual void lb_output_freed(){			testFailed(__FUNCTION__);}

		void testFailed(string functionname) {
			cout<<"Test failed: "<<name()<<", caused of "<<functionname<<endl;
			hal->motorStop();
			hal->greenLightOff();
			hal->blinkRed(Speed::fast);
			new (this) IDLE;
		}

		std::string name() const { return typeid(*this).name(); }

		hardwareLayer::HardwareLayer* hal;
		Data* data;// pointer to data, which physically resides inside the context class (contextdata)
	} *statePtr;   // a pointer to current state. Used for polymorphism.

	struct IDLE : public State {
		virtual void start_sensor_test() {
			cout<<"### SENSOR TEST started ###"<<endl;
			new (this) LB_INPUT_Test;
		}
	};

	struct LB_INPUT_Test : public State {
		virtual void lb_input_interrupted() {
			cout<<__FUNCTION__<<endl;
			hal->motorRotateClockwise();
			hal->motorFast();
			hal->motorStart();
		}
		virtual void lb_input_freed() {
			cout<<__FUNCTION__<<endl;
			cout<<name()<<" successfully"<<endl;
			new (this) LB_HEIGHT_Test;
		}
	};

	struct LB_HEIGHT_Test : public State {
		virtual void lb_height_interrupted() {
			cout<<__FUNCTION__<<endl;
		}
		virtual void lb_height_freed() {
			cout<<__FUNCTION__<<endl;
			cout<<name()<<" successfully"<<endl;
			new (this) LB_SWITCH_Test;
		}
	};

	struct LB_SWITCH_Test : public State {
		virtual void lb_switch_interrupted() {
			cout<<__FUNCTION__<<endl;
			hal->switchPointOpen();
		}
		virtual void lb_switch_freed() {
			cout<<__FUNCTION__<<endl;
			cout<<name()<<" successfully"<<endl;
			new (this) LB_OUTPUT_Test;
		}
	};

	struct LB_OUTPUT_Test : public State {
		virtual void lb_output_interrupted() {
			cout<<__FUNCTION__<<endl;
			hal->switchPointClose();
			if(cb_this == cb_last) {
				hal->motorStop();
			} else {
				hal->sendSerial(Signal(cb_this, cb_next, Signalname::START_SENSOR_TEST));
			}
		}
		virtual void lb_switch_freed() {
			cout<<__FUNCTION__<<endl;
			cout<<name()<<" successfully"<<endl;
			new (this) LB_SLIDE_Test;
		}
	};

	struct LB_SLIDE_Test : public State {
		virtual void lb_input_interrupted() {
			hal->motorRotateClockwise();
			hal->motorFast();
			hal->motorStart();
		}
		virtual void lb_input_freed() {}
		virtual void lb_height_interrupted() {}
		virtual void lb_height_freed() {}
		virtual void lb_switch_interrupted() {}
		virtual void lb_switch_freed() {}
		virtual void lb_slide_interrupted() {
			cout<<__FUNCTION__<<endl;
			hal->motorStop();
		}
		virtual void lb_slide_freed() {
			cout<<__FUNCTION__<<endl;
			cout<<name()<<" successfully"<<endl;
			cout<<"### SENSOR TEST finished ###"<<endl;
			new (this) IDLE;
		}
	};


	LB_INPUT_Test stateMember;//The memory for the state is part of context object

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

	virtual ~SensorTestController(){};

	virtual void start_sensor_test(){		statePtr->start_sensor_test();}
	virtual void lb_input_interrupted(){	statePtr->lb_input_interrupted();}
	virtual void lb_input_freed(){			statePtr->lb_input_freed();}
	virtual void lb_height_interrupted(){	statePtr->lb_height_interrupted();}
	virtual void lb_height_freed(){			statePtr->lb_height_freed();}
	virtual void lb_switch_interrupted(){	statePtr->lb_switch_interrupted();}
	virtual void lb_switch_freed(){			statePtr->lb_switch_freed();}
	virtual void lb_slide_interrupted(){	statePtr->lb_slide_interrupted();}
	virtual void lb_slide_freed(){			statePtr->lb_slide_freed();}
	virtual void lb_output_interrupted(){	statePtr->lb_output_interrupted();}
	virtual void lb_output_freed(){			statePtr->lb_output_freed();}
};

} /* namespace logicLayer */
#endif /* SENSORTESTCONTROLLER_H_ */
