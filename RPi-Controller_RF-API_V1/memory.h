/*
 * memory.h
 *
 *  Created on: 15 Nov 2016
 *      Author: André Gomes
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "wiringPi.h"


/* The memory consist in a .txt file and each line is a position of the memory
 * The first line (position 0) is the header of the file */
#define NET_POS			1
#define SRN_POS			2
#define RF_FREQ_POS		3
#define ENC_POS			4
#define TTLMAX_POS		5


/* Size of the data needed for the system */
#define UINT8_SIZE              1
#define UINT16_SIZE             2
#define INT16_SIZE              2
#define UINT32_SIZE             4
#define DOUBLE_SIZE             4

#define CONF_SIZE               6



/* Function to open memory file */
uint8_t Memory_Open(void);


/* Function to read one position of the memory file - one line per position */
void Memory_ReadPos(unsigned int pos, unsigned int *data);


/* Function to write one position on the memory file - one line per position */
void Memory_WritePos(unsigned int pos, unsigned int *data);


/* Function to close the memory file */
void Memory_Close(void);



#endif /* MEMORY_H_ */


