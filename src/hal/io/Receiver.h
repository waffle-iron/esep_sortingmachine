/*
 * Receiver.h
 *
 *  Created on: 16.10.2017
 *      Author: aca311
 */

#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "Serial.h"

namespace hardwareLayer {
namespace io {

class Receiver {
public:
    Receiver(Serial& serial);
    void operator()();
    void stop();

private:
    Serial& serial_;
    bool running;
};

}
}


#endif /* RECEIVER_H_ */
