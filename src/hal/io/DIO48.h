/*
 * DIO48.h
 *
 *  Created on: 07.04.2017
 *      Author: Nils Schoenherr
 */

#ifndef DIO48_H_
#define DIO48_H_


#define DIO_BASE 0x300

// Sehe Manual M104-DIO-48S.A1i, Kap. 5: Programming
#define CTRL_REG_GROUP0     (DIO_BASE + 0x03)
/*
 * PORT A : OUTPUT
 * PORT B : INPUT
 * PORT C Lo : OUTPUT
 * PORT C Hi : INPUT
 * Mode Select : 00
 */
#define DEFAULT_PORTS_SETTINGS 0x8A

#define PORTA 0x00
#define PORTB 0x01
#define PORTC 0x02


/*
 * Bit defintion Change-of-state Interrupt Enable Register
 *
 * Writing a "0" means IRQ-Enable
 *
 *      Bit 0   Port A, Group 0
 *      Bit 1   Port B, Group 0
 *      Bit 2   Port C  Group 0
 *      Bit 3   Port A, Group 1
 *      Bit 4   Port B, Group 1
 *      Bit 5   Port C  Group 1
 */
#define DIO_GROUP0_PA_IRQ_ENABLE		0x01
#define DIO_GROUP0_PB_IRQ_ENABLE		0x02
#define DIO_GROUP0_PC_IRQ_ENABLE		0x04

/*
 * Bit defintion Change-of-state Interrupt Status Register
 *
 * Reading a "1" means Change-of-state occured
 *
 *      Bit 0   Port A, Group 0
 *      Bit 1   Port B, Group 0
 *      Bit 2   Port C lo, Group 0
 *      Bit 3   Port C hi, Group 0
 *      Bit 4   Port A, Group 1
 *      Bit 5   Port B, Group 1
 *      Bit 6   Port C lo, Group 1
 *      Bit 7   Port C hi, Group 1
 */
#define DIO_GROUP0_PA_STATE_CHANGED     0x01
#define DIO_GROUP0_PB_STATE_CHANGED     0x02
#define DIO_GROUP0_PC_LO_STATE_CHANGED  0x04
#define DIO_GROUP0_PC_HI_STATE_CHANGED  0x08


/* Change of state register for both port groups	*/
#define DIO_CHG_STATE_IRQ_ENABLE        0x0B
#define DIO_CHG_STATE_IRQ_STATUS        0x0F
#define DIO_CHG_STATE_IRQ_CLR	        0x0F


/* DIO48 IRQ level as defined by jumper  */
#define IRQ_LEVEL 11



#endif /* DIO48_H_ */
