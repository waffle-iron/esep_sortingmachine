#include "Header.h"
#include <iostream>

#include "Interface.h"
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

	cb_first =  CB_FIRST;
	cb_all = CB_ALL;


	string textInput;
	do {
	cout<<"Are you conveyor belt 1? (yes/no):"<<endl;
	cin >> textInput;
	} while(!(textInput.compare("yes") xor textInput.compare("no")));

	if(!textInput.compare("yes")) {
		cb_this =  cb_first;
	}
	cin.get(); // get rid of extra return


	hardwareLayer::HardwareLayer hal;
	logicLayer::LogicLayer loLay = logicLayer::LogicLayer(hal);

	WAIT(5000);
	cout<<"READY FOR TESTING"<<endl;

	logicLayer::test::Test test = logicLayer::test::Test(&hal);

	if (cb_this == cb_1) {
		cin.get();
		test.actuatorsTest();
		test.mmiTest();
		hal.getSignalGenerator().pushBackOnSignalBuffer(Signal(Signalname::SENSOR_TEST_START));
		test.threadSafenessInGpioTest();
		test.singletonThreadSafeTest();
	}


	cout<<"Shut down?"<<endl;
	cin.get();


	cout << "Starting Sortingmachine ... done !" << endl;

	return EXIT_SUCCESS;

}

