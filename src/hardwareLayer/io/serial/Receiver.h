/*
 * Receiver.h
 *
 *  Created on: 16.10.2017
 *      Author: aca311
 */

#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "Serial.h"
#include "WatchDog.h"


namespace hardwareLayer {
namespace io {
namespace serial {

class Receiver {
public:
    Receiver(Serial& serial, WatchDog& dog);
    void operator()();
    void stop();

private:
    Serial& serial_;
    WatchDog& dog_;
    bool running;
};

} /* namespace serial */
} /* namespace io */
} /* namespace hal */


#endif /* RECEIVER_H_ */
