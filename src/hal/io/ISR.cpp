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

constexpr int HW_INTERRUPT = 11;
constexpr port_t PORT_C_HIGH_MASK = 0xf0;
constexpr port_t E_STOP_BITMASK = 0b10000000;

using namespace std;

namespace hal {
namespace io {

int ISR::isrId;
struct sigevent ISR::isrEvent;

ISR::ISR() {
	hal::io::GPIO::instance().gainAccess();
}

int ISR::getPendingIntFlags() {
	return in8(DIO_BASE + DIO_CHG_STATE_IRQ_STATUS);
}

void ISR::disableInterrupts() {
	return out8(DIO_BASE + DIO_CHG_STATE_IRQ_ENABLE, 0xff);
}

void ISR::enableInterrupts(int mask) {
	return out8(DIO_BASE + DIO_CHG_STATE_IRQ_ENABLE, ~(mask));
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
    struct sigevent* event = (struct sigevent*) arg;
    ISR::clearAllPendingIntFlag();
    port_t portB = GPIO::instance().read(PORT::B);
    port_t portC = GPIO::instance().read(PORT::C) & PORT_C_HIGH_MASK;

    if((!portC) & E_STOP_BITMASK) {
        event->sigev_priority = sched_get_priority_max(1);
    }
    event->sigev_value.sival_int = portB | portC<<8;
    return event;
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
} /* hal */
