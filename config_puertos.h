/* 
 * File:   config_puertos.h
 * Author: Felipe
 *
 * Created on 11 de octubre de 2021, 08:39 PM
 */

#ifndef CONFIG_PUERTOS_H
#define	CONFIG_PUERTOS_H

#define INPUT 1
#define OUTPUT 0
#define ON 1
#define OFF 0

#define CFG_PIR TRISB7
#define CFG_LAMP TRISB0
#define Direction_Port TRISC

#define PIR RB7
#define LAMP LATB0
#define write_port LATC            /* latch register to write data on port */
#define read_port PORTC             /* PORT register to read data of port */
#define KEYPAD_WRITE LATC             /* latch register to write data on port */
#define KEYPAD_READ PORTC             /* PORT register to read data of port */


#endif	/* CONFIG_PUERTOS_H */

