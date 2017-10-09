#include <cstdlib>
#include <iostream>
#include "test.h"

using namespace std;

int main(int argc, char *argv[])
{
//#ifdef SIMULATION
//  IOaccess_open();
//#endif

  cout << "Starting Sortingmachine ..." << endl;

  Test test = Test();

  cout << "Starting Sortingmachine ... done !" << endl;
//#ifdef SIMULATION
//  IOaccess_close();
//#endif
  return EXIT_SUCCESS;
}

