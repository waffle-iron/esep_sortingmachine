/*
 * Sender.h
 *
 *  Created on: 16.10.2017
 *      Author: aca311
 */

#ifndef SENDER_H_
#define SENDER_H_

#include "Serial.h"

namespace hal {
namespace io {
namespace serial {

class Sender {
public:
    Sender(Serial& serial);
    void operator()();
    void stop();

private:
    Serial& serial_;
    bool running;
};

} /* namespace serial */
} /* namespace io */
} /* namespace hal */

#endif /* SENDER_H_ */
