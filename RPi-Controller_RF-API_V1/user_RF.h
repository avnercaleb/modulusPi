
/*
 * File:   user.h
 * Author: André Gomes
 *
 */
#ifndef USER_H
#define	USER_H

#include <stdio.h>
#include <sys/time.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART
#include <errno.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

#include "M1_RF.h"
#include "memory.h"
#include "AES_ECB_PIC32.h"
#include "wiringPi.h"
#include "wiringSerial.h"

#ifdef RF_RFM22B
	#include "RF_RFM22B.h"
#endif
#ifdef RF_RFM69HCW
	#include "RF_RFM69HCW.h"
#endif
#ifdef RF_RFM95W
	#include "RF_RFM95W.h"
#endif
#ifdef TPP
	#include "SPI_TPP.h"
#endif


//Custom definitions
#define TX_BUFFER 300
#define RX_BUFFER 300

#define MAX_SAMPLE 605 

#define REMOTE_POLL

#ifdef REMOTE_POLL

	#define PROCESS_INTERVAL 500
	
#else
	
	#define PROCESS_INTERVAL 8 //Ethernet only usage
	
#endif

#define CHECK_RF_INTERVAL 360 //6 minutes

/*********************************************************************************/
/*                              PROTOCOL DEFINE                                 */
/*********************************************************************************/

//#define UDP
//#define TCP
#define RS485



/*********************************************************************************/
/*                               DEVIDE DEFINE                                   */
/*********************************************************************************/

//#define JANITZA
//#define CCK
//#define FRONIUS
//#define EMBRASUL_MD30_ETH
#define 3R



/* Hardware defines */
#define RF_INT_PIN		5		/* Interrupt pin that able the program to implement the state-machine (receiving/transmitting) */


/* Define for the length of the encryption/decryption message buffer */
#define BLOCK_SIZE_1        16
#define BLOCK_SIZE_2        32
#define BLOCK_SIZE_3        48


/******************************************************************************/
/* User Level #define Macros - Hardware Configurations                        */
/******************************************************************************/
#define DEBUG_VERSION_MSG       (0)
#define DEBUG_RF_RX_MSGPRINT	(0)
#define DEBUG_RF_RX_MSGHANDLER	(0)
#define DEBUG_SEND_RF_MSG		(0)
#define DEBUG_RF_ERROR			(0)
#define DEBUG_RF_5S				(0)
#define DEBUG_RCV_RF			(0)
#define DEBUG_RESEND_RF			(0)
#define DEBUG_RESEND_RF			(0)
#define DEBUG_WRONG_MSG			(0)
#define DEBUG_RF_INT			(0)
//#define DEBUG_RF_STTMCH	    	(0)
#define DEBUG_FLAG   			(0)
#define TEST					(0)

/******************************************************************************/
/* User Level #define Macros - System Settings                                */
/******************************************************************************/

/* Auxiliary defines */
#define N_MEAN               9               /* Number of values for mean calculations */


/* Defines for System State Machine */
#define SYS_OFF             0
#define SYS_ON              1



/******************************************************************************/
/* User System Structs                                                        */
/******************************************************************************/

/* Auxiliary buffer for the mean calculations */
typedef struct
{
	unsigned int    buff[N_MEAN];
	unsigned int	ind;

}MEAN_STRUCT;


typedef struct
{
	/* Saved and used data in the RF msgs */
	unsigned int	net;            /* Network number for RF communication */
	unsigned int    sn;             /* Serial number for RF communication */
	unsigned int    ldr;            /* LDR measured */
	int      		tempLED;        /* Temperature of the LEDs measured */
	int      		tempPCB;        /* Temperature of the PCB measured */
	unsigned int    volt;           /* Input voltage measured */
	unsigned int    current;        /* Current of the system LDR measured */
	unsigned int    sysStt;         /* System ON/OFF */
	unsigned int    profileStt;     /* Profiles ON/OFF */
	unsigned int    setLDR;         /* LDR Setpoint - LUX */
	unsigned int    ldrCtrl;        /* LDR control OFF/Setpoint/Threshold */
	unsigned int    ttlMAX;         /* MAX value for the TTL */
	unsigned int    dutyTmp;        /* Duty-Cycle information for the PWM channels */
	unsigned int    workHours;      /* Total of hours that the system is ON */
	unsigned int    debugCtrl;      /* Flag to control the "print" of informations to the UART */
	unsigned int    encCtrl;        /* Flag to control if the RF messages are encripted or not */
	/* Unsaved and unused data in the RF msgs */
	unsigned int    sysSttAnt;      /* Anterior System Status */
	unsigned int    updateID;       /* Update ID order by RF message - Calendar, Profiles*/
	unsigned int    flag1s;         /* flag for 1s control */
	unsigned int    flag1min;       /* flag for 1minute control */
	unsigned int    flag1h;         /* flag for 1h control */
	unsigned int    flag12h;        /* flag for 12h control */
	unsigned int    flag24h;        /* flag for 24h/1 day control */
	unsigned int    flagInit;       /* flag that indicates the first cycle */

}SYS_STRUCT;


/* Structure for Power consumption calculation */
typedef struct
{
	unsigned int	flag;           /* Flag fot Power consuption calculation */
	unsigned int    intrSec;        /* Interval for the Power Calculation in seconds */
	unsigned int    intrF;          /* Interval for the Power Calculation in seconds - Interrupt Flag */
	double          intr2hs;        /* Conversion of the interval in seconds to hour share */
	double          kw;             /* Active power */
	double          kvar;           /* Reactive power */
	double          pwrFact;        /* Power factor */
	double          kva;            /* Apparent power */
	double          kwh;            /* Active power consumption */
	double          kvarh;          /* Reactive power consumption */
	double          kwhSum;         /* Sum of the active power consumption */
	double          kvarhSum;       /* Sum of the reactive power consumption */
	unsigned int    flagInit;       /* Variable to control if any power consumption had been saved */
	MEAN_STRUCT     currMean;       /* Struct to do a mean calculation for the current value */
	MEAN_STRUCT     voltMean;       /* Struct to do a mean calculation for the voltage value */

}PWR_CONSUME_STRUCT;


	int modbusAddr[1024];
    int nDataModbus; 
	

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/


 /**
 * Function to config the IO Ports and the Peripherals
 */
uint8_t ConfigInit(void);


/* RF Functions */

/**
 * Function to Initialize the RF Module
 */
int8_t RF_RFM22B_Setup(volatile RF_STRUCT *rfData);

int8_t RF_RFM69HCW_Setup(volatile RF_STRUCT *rfData);

int8_t RF_RFM95W_Setup(volatile RF_STRUCT *rfData);


/**
 * Function to process the received RF message
 * @param 1 - RF_STRUCT pointer
 * @param 2 - MSGBUFF_STRUCT pointer
 * @param 3 - SYS_STRUCT pointer
 */
void RF_ProcessMsg(RF_STRUCT *rfData, MSGBUFF_STRUCT *msgBuffData, SYS_STRUCT *sysData);


/**
 * Function to send a RF message
 * @param 1 - RF_STRUCT pointer
 * @param 2 - MSGBUFF_STRUCT pointer
 * @param 3 - SYS_STRUCT pointer
 */
void RF_SendMsg(RF_STRUCT *rfData, MSGBUFF_STRUCT *msgBuffData, SYS_STRUCT *sysData);


/**
 * Function to be called when a interrupt occurs on the pin 5 - RF Interrupt
 */
void RF_Interrupt(void);


/**
 * Function to implement the State-Machine for the RF communication
 * @param 1 - RF_STRUCT pointer
 * @param 2 - MSGBUFF_STRUCT pointer
 * @param 3 - SYS_STRUCT pointer
 */
void RF_RFM22B_SttMachine(RF_STRUCT *rfData, MSGBUFF_STRUCT *msgBuffData, SYS_STRUCT *sysData);

void RF_RFM69HCW_SttMachine(RF_STRUCT *rfData, MSGBUFF_STRUCT *msgBuffData, SYS_STRUCT *sysData);
 
void RF_RFM95W_SttMachine(RF_STRUCT *rfData, MSGBUFF_STRUCT *msgBuffData, SYS_STRUCT *sysData);


/**
 * Function to Set a Software Reset on the RF module
 * @param 1 - RF_STRUCT pointer
 */
void RF_RFM22B_Reset(RF_STRUCT *rfData);

void RF_RFM69HCW_Reset(RF_STRUCT *rfData);

void RF_RFM95W_Reset(RF_STRUCT *rfData);


/**
 * Function to clear the RF buffer
 */
void RF_ClrMsg(RFMSG_STRUCT *msg);


/**
 * Function to calculate the checksum of buffer of x bytes
 */
uint8_t RF_CksCalc(RFMSG_STRUCT *msg);



/* System Functions */

/**
 * Function to Get the data from the memory file
 */
uint8_t Memory_GetSavedData(SYS_STRUCT *sysData, RF_STRUCT *rfData);



/* Encryption functions */

/* The session_key should have been calculated before
 * Returns the new length of the message
 */
uint8_t AES128_Encrypt(uint8_t *buff, uint8_t buffLen, uint8_t *buffEnc, void *sessionKey);


/* The session_key should have been calculated before */
uint8_t AES128_Decrypt(uint8_t *buffEnc, uint8_t buffLen, uint8_t *buffDec, void *sessionKey);



void SYS_ClearBuff(uint8_t *buff, uint8_t len);


void InitConnections(void);
void ClearRx();
void ClearTx();
void PrintString(int filestream, char *str, unsigned char length);
void ConvertLittleToBigEndian(unsigned char firstIndex, unsigned char length);
unsigned int CRC16(unsigned char *nData, unsigned int wLength);
void HandleProcess();
void ResetProcessVars(void);
void AverageMeasures(void);


void ModbusAddr_Read(int *AddrData, int nData);

#endif

