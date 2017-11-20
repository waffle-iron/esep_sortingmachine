/* The IRQ handler
 *
 * The IRQ-Handler checks the DIO48 IRQ-Statusregister.
 * If PortB IRQ is signaled the IRQ-Statusregister is cleared and
 * the event SIGEV_INTR is returned. Elsewise nothing is done and
 * the event SIGEV_NONE is returned.
 *
 */

#include "ISR.h"
#include <sys/neutrino.h>
#include <hw/inout.h>
#include "DIO48.h"
#include "GPIO.h"

#define HW_INTERRUPT 11

constexpr uint8_t UPPER_BYTE = 0xf0;
constexpr uint8_t FULL_BYTE = 0xff;

using namespace std;

namespace hardwareLayer {
namespace io {

int ISR::isrId;
struct sigevent ISR::isrEvent;

int storedMask;

ISR::ISR() {
	GPIO::instance().gainAccess();
	storedMask = GPIO::instance().read(PORT::C)<<8 | GPIO::instance().read(PORT::B);
}

int ISR::getPendingIntFlags() {
	return in8(DIO_BASE + DIO_CHG_STATE_IRQ_STATUS);
}

void ISR::disableInterrupts() {
	out8(DIO_BASE + DIO_CHG_STATE_IRQ_ENABLE, FULL_BYTE);
}

void ISR::enableInterrupts(int mask) {
	 out8(DIO_BASE + DIO_CHG_STATE_IRQ_ENABLE, ~(mask));
}

void ISR::clearPendingIntFlag(int bit) {
	int tmp = in8(DIO_BASE + DIO_CHG_STATE_IRQ_STATUS);
	tmp &= ~(1 << bit);
	out8(DIO_BASE + DIO_CHG_STATE_IRQ_STATUS, tmp);
}

// no debug message allowed, otherwise isr crashes
void ISR::clearAllPendingIntFlag() {
	out8(DIO_BASE + DIO_CHG_STATE_IRQ_STATUS, 0);
}


const struct sigevent* ISR::mainISR(void* arg, int id) {
	int mask = ((GPIO::instance().read(PORT::C) & UPPER_BYTE) << 8) |
				(GPIO::instance().read(PORT::B) & FULL_BYTE);

	if((mask xor storedMask) == 0) { 	// IRQ not for us
		return nullptr;
	} else {						// IRQ for us
		// reset IRQ
		ISR::clearAllPendingIntFlag();
		// update stored mask
		storedMask = mask;
		// prepare event task
		struct sigevent* event = (struct sigevent*) arg;
		event->sigev_value.sival_int = mask;
		return event;
	}
}


void ISR::registerISR(AsyncChannel& chan, char msgType){
    // disable IRQ
    ISR::disableInterrupts();

    // clear any possible pending irq
    ISR::clearAllPendingIntFlag();

	// initialize event structure
    SIGEV_PULSE_INIT(&isrEvent, chan.getConnectionId(), SIGEV_PULSE_PRIO_INHERIT, (int)msgType, 0);

    // attach mainISR handler to hardware interrupt
    isrId = InterruptAttach(HW_INTERRUPT, ISR::mainISR, &isrEvent, sizeof(isrEvent), 0);
    if (isrId == -1) {
        LOG_ERROR<<"Could not attach mainISR handler to hw interrupt"<<std::endl;
        exit(EXIT_FAILURE);
    }

    // enable IRQ for PortB and PortC
    ISR::enableInterrupts(DIO_GROUP0_PB_IRQ_ENABLE | DIO_GROUP0_PC_IRQ_ENABLE);
}

void ISR::unregisterISR(){

    // detach interrupt handler
    if( InterruptDetach(isrId) < 0 ){
        LOG_ERROR<<"Could not detach interrupt handler"<<std::endl;
        exit(EXIT_FAILURE);
    }

    // disable IRQ
    ISR::disableInterrupts();

    // clear any possible pending irq
    ISR::clearAllPendingIntFlag();
}

} /* io */
} /* hardwareLayer */
