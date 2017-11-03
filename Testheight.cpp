
#include <sys/neutrino.h>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>

#include <stdint.h>
#include <hw/inout.h>

#include <unistd.h>


using namespace std;

uint16_t getHeight(void) {
  static const uint16_t baseAddress = 0x320;
  static const uint16_t readLowAddressOffset = 0x2;
  static const uint16_t startConversionAddressOffset = 0x2;
  static const uint16_t readHighAddressOffset = 0x3;
  static const uint16_t startConversionOpCode = 0x10;
  static const uint16_t only12BitBitmask = 0x0FFF;

  uint16_t height;

  // write opcode to start conversion
  out8(baseAddress + startConversionAddressOffset, startConversionOpCode);

  //wait for conversion to complete
  usleep(10);

  //read low bytes
  height = in8(baseAddress + readLowAddressOffset);

  //cout << height << endl;

  //read high bytes
  height |= (uint16_t)in8(baseAddress + readHighAddressOffset) << 8;

  //cout << height << endl;

  // height sensor value is only 12 bit
  height &= only12BitBitmask;

  //cout << height << endl;

  return height;
}

//int main(int argc, char *argv[]) {
//
//static const uint16_t ioControlAddress = 0x303;
//static const uint8_t ioControlBitmask  = 0b10001010;
//uint16_t heightValue;
//
///* Zugriffsrechte von QNX fuer diesen Thread, auf die Hardware erbitten. */
//if( ThreadCtl(_NTO_TCTL_IO_PRIV,0) == -1 ){
//  cout << "Can't get Hardware access, therefore can't do anything." << endl;
//}
//
///* IO Register als Eingänge bzw. Ausgänge definieren. */
//out8(ioControlAddress, ioControlBitmask);
//
//while (true) {
//heightValue = getHeight();
//cout << heightValue << endl;
//usleep(250000);
//}
//return EXIT_SUCCESS;
//}
