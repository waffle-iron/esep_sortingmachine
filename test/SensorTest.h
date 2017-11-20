/*
 * SensorTest.h
 *
 *  Created on: 16.11.2017
 *      Author: abj240
 */

#ifndef SENSORTEST_H_
#define SENSORTEST_H_

#include "Signals.h"
#include "HardwareLayer.h"
#include "Header.h"
#include "Item.h"
#include <iostream>
#include <string>

namespace logicLayer {

class SensorTest {
private:
	struct State {//top-level state
		virtual void sensor_test_start(){		testFailed(__FUNCTION__);}
		virtual void sensor_test_successful(uint8_t sender){	testFailed(__FUNCTION__);}
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
			new (this) LB_INPUT_Test;
		}

		std::string name() const { return typeid(*this).name(); }

		hardwareLayer::HardwareLayer* hal;
		Item* testItem;
	} *statePtr;   // a pointer to current state. Used for polymorphism.

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
				cout<<"please put item on master's input again."<<endl;
				hal->motorStop();
			} else {
				hal->sendSerial(Signal(cb_this, cb_next, Signalname::SENSOR_TEST_START));
				hal->sendSerial(testItem);
			}
		}
		virtual void lb_output_freed() {
			cout<<__FUNCTION__<<endl;
			cout<<name()<<" successfully"<<endl;
			if(cb_this != cb_last) {
				cout<<"Test continues on next conveyer belt. When item reaches last conveyer belt's output, please put it on input of master again."<<endl;
			}
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
			hal->sendSerial(Signal(cb_this,cb_1,Signalname::SENSOR_TEST_SUCCESSFUL));
			new (this) OTHER_CBs_Test;
		}
	};

	struct OTHER_CBs_Test : public State {
		virtual void sensor_test_successful(uint8_t sender) {
			cout<<"Test was successful on conveyer belt: "<<(int)sender<<endl;
			if(sender == cb_last) {
				cout<<"### SENSOR TEST finished ###"<<endl;
				cout<<"hit enter to go on"<<endl;
				new (this) LB_INPUT_Test;
			}
		}
		virtual void sensor_test_unsuccessful(uint8_t sender) {
			cout<<"Test UNsuccessful on conveyer belt: "<<(int)sender<<endl;
			cout<<"Please restart test."<<endl;
			new (this) LB_INPUT_Test;
		}
	};


	LB_INPUT_Test stateMember;//The memory for the state is part of context object

	hardwareLayer::HardwareLayer& hal;
	Item testItem;

public:
	SensorTest(hardwareLayer::HardwareLayer& hal)
	: statePtr(&stateMember) // assigning start state
	, hal(hal)
	{
		statePtr->hal = &hal;
		statePtr->testItem = &testItem; // connecting state->testItem with the SensorTest::testItem

		if(cb_this == cb_1) {
		cout<<"### SENSOR TEST started ###"<<endl;
		cout<<"Please put item (metal above) on master's input."<<endl;
		}
	}

	virtual ~SensorTest(){};

	virtual void sensor_test_start(){		statePtr->sensor_test_start();}
	virtual void sensor_test_successful(uint8_t sender){	statePtr->sensor_test_successful(sender);}
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
#endif /* SENSORTEST_H_ */
