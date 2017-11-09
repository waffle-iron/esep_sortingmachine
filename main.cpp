#include "Header.h"
#include <iostream>

#include "Serial.h"
#include "Receiver.h"
#include "Parameter.h"

#include "HardwareLayer.h"
#include "LogicLayer.h"
#include "Test.h"


#include "HeightSensor.h"

using namespace std;

int main(int argc, char *argv[])
{


	cout << "Starting Sortingmachine ..." << endl;

	LOG_SCOPE;
	LOG_SET_LEVEL(DEBUG);

	string textInput;
	do {
	cout<<"Are you conveyor belt 1? (yes/no):"<<endl;
	cin >> textInput;
	} while(!(textInput.compare("yes") xor textInput.compare("no")));

	if(!textInput.compare("yes")) {
		cb_this =  Parameter<uint8_t>(cb_1, "Conveyer belt 1");
	}

	cb_this.parameterList.showParameters();


	hardwareLayer::HardwareLayer hal;
	logicLayer::LogicLayer loLay = logicLayer::LogicLayer(hal);



	while(1);




//
//	logicLayer::test::Test test = logicLayer::test::Test(&hal);
//	test.mmiTest();
//	test.actuatorsTest();
//	test.sensorsTest();
//	test.threadSafenessInGpioTest();
//	test.singletonThreadSafeTest();



	cout << "Starting Sortingmachine ... done !" << endl;

	return EXIT_SUCCESS;

}

