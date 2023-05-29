/*
 * File:   M1_RF.h
 * Author: Andr� Gomes
 *
 * Created on 6 de Maio de 2015, 11:03
 */

#ifndef M1_RF_H
#define	M1_RF_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "wiringPi.h"
#include "wiringPiSPI.h"

//#define RF_RFM22B
//#define RF_RFM69HCW
#define RF_RFM95W
//#define TPP


/* Interrupt pin that able the program to implement the state-machine (receiving/transmitting) */
#define RF_INT_PIN	5    


/* Available frequencies for the communication */
#define RF_868MHZ		868
#define RF_918MHZ		918


#define SPI_SPEED       1000000
#define SPI_PORT		0

#define RF_BUFF_LEN		128 //64

#define CMD_WRITE       0x80
#define CMD_READ        0x00


/******************************************************************************/
/* Positions of the bytes in the messages of the protocol                     */
/******************************************************************************/
#define HEADER                  6           /* Ord ID + Msg ID + NET + SN */
#define NET_HEADER              4           /* NET + SN */
#define TELEM_DATA_LEN          13          /* It is 18 but the PWM and KW.h are added after */
#define TELEM_KWH_POS           14
#define TOTALIZERS_DATA_LEN     12          /* Data length of the totalizers = 3 x DOUBLE_SIZE */
#define ASTROCLK_DATA_LEN       4

#define MAX_RFMSG_LEN           48
#define MIN_RFMSG_LEN           8

#define BROADCAST               0xFFFF


/******************************************************************************/
/* Message IDs | Definitions | Messages Length  -  For the protocol           */
/******************************************************************************/


/************************/
/* Messages length      */
/************************/
#define CONF_NET_LEN            0x08
#define ACK_CONF_NET_LEN        0x09

#define CAL_UPDATE_LEN          0x0F
#define ACK_CAL_UPDATE_LEN      0x09

#define CONF_PROFILE_LEN        0x1C
#define ACK_CONF_PROFILE_LEN    0x09

#define ASK_PROFILE_LEN         0x08
#define ANS_PROFILE_LEN         0x1C

#define CONF_ASTOCLK_LEN        0x10
#define ACK_CONF_ASTOCLK_LEN    0x09

#define CONF_PWM_LEN            0x09
#define ACK_CONF_PWM_LEN        0x09

#define CONF_GENERAL_LEN        0x0E
#define ACK_CONF_GENERAL_LEN    0x09

#define ASK_TELEM_EXT_LEN       0x08
#define ANS_TELEM_LEN           0x16        /* Not suported in this version and future versions */
#define ANS_TELEM_EXT_LEN       0x1A        /* Extended version of the telemetry message, with KW.h */
#define ANS_TELEM_ENERGY_LEN	0x30		/* Telemetry for powermeter with active power -> do not fit 48 bytes encryption*/
#define ANS_TELEM_ENERGY_LEN_2	0x2A		/* Telemetry for powermeter with power factor -> fits 48 bytes encryption */


#define CONF_SENSORS_LEN        0x15
#define ACK_CONF_SENSORS_LEN    0x09

#define CONF_ALARMS_LEN         0x16
#define ACK_CONF_ALARMS_LEN     0x09

#define CONF_SENSORS_LEN        0x15
#define ACK_CONF_SENSORS_LEN    0x09

#define CONF_ALARMS_LEN         0x16
#define ACK_CONF_ALARMS_LEN     0x09

#define CONF_ADDON_LEN          0x0C
#define ACK_CONF_ADDON_LEN      0x09

#define SYS_MONITORING_LEN      0x08
#define ANS_SYS_MONITORING_LEN  0x14

#define SYS_TOTALTEL_LEN        0x08
#define ANS_SYS_TOTALTEL_LEN    0x14

#define PIR_CONTROL_LEN         0x09

#define LDR_CONTROL_LEN         0x0E

#define ALARM_MSG_LEN           0x0F

#define ASK_WHOIS_LEN           0x08
#define ANS_WHOIS_LEN           0x09

#define ASK_WHAT_CLK_LEN        0x08
#define ANS_WHAT_CLK_LEN        0x0F

#define CONF_ENC_LEN            0x09
#define ACK_CONF_ENC_LEN        0x09

#define PM_SAVE2FLASH_LEN       0x08
#define ACK_PM_SAVE2FLASH_LEN   0x09


/************************/
/* Order IDs         */
/************************/
#define DEBUG_ORD_ID        0xFF	/* Order ID used for the debug/technical messages */

/************************/
/* Message IDs            */
/************************/
#define CONF_NET            0x01  	/* Msg ID for Network Configuration */
#define ACK_CONF_NET        0x10  	/* Msg ID for ACK of Network Configuration */

#define CAL_UPDATE          0x020F      /* Msg ID for Date and Time (RTC) UPDATE | Length */
#define ACK_CAL_UPDATE      0x20        /* Msg ID for ACK Date ant Time (RTC) UPDATE */

#define CONF_PROFILE        0x031C      /* Msg ID for profiles configuration | Length */
#define ACK_CONF_PROFILE    0x30        /* Msg ID for ACK Profiles Configuration */

#define ASK_PROFILE         0x0408      /* Msg ID for Request to send Profiles configuration | Length */
#define ANS_PROFILE         0x40        /* Msg ID for Reply Profiles configuration */

#define CONF_ASTOCLK        0x1410      /* Msg ID for setting the Astronomical Clock settings - Sunset/Sunrise */
#define ACK_CONF_ASTOCLK    0x41        /* Msg ID for ACK setting the Astronomical Clock settings */

#define CONF_PWM            0x0509      /* Msg ID for PWM Configuration | Length */
#define ACK_CONF_PWM        0x50        /* Msg ID for ACK PWM Configuration */

#define CONF_GENERAL        0x060E      /* Msg ID for General Configurations | Length */
#define ACK_CONF_GENERAL    0x60        /* Msg ID for ACK General Configurations */

#define ASK_TELEM_EXT       0x0708      /* Msg ID for Request to send Telemetry | Length */
#define ANS_TELEM_EXT       0x70        /* Msg ID for Reply Telemetry */

#define CONF_SENSORS        0x0815      /* Msg ID for Sensors configuration | Length */
#define ACK_CONF_SENSORS    0x80        /* Msg ID for ACK Sensors configuration */

#define CONF_ALARMS         0x0916      /* Msg ID for Alarms setpoint's configurations | Length */
#define ACK_CONF_ALARMS     0x90        /* Msg ID for ACK Alarms setpoint's configurations */

#define CONF_ADDON          0x0C0C      /* Msg ID for Additional Configurations | Length */
#define ACK_CONF_ADDON      0xC0        /* Msg ID for ACK Additional Configurations | Length */

#define SYS_MONITORING      0x0D08      /* Msg ID for System Monitoring | Length */
#define ANS_SYS_MONITORING  0xD0        /* Msg ID for ANS System Monitoring */

#define SYS_TOTALTEL        0x0E08      /* Msg ID for System totalizers telemetry | Length */
#define ANS_SYS_TOTALTEL    0xE0        /* Msg ID for ANS System total telemetry */

#define PIR_CONTROL         0x0A09      /* Msg ID for PIR control (On/Off) | Length */
#define PIR_CONTROL_SEND    0x0A        /* Msg ID for PIR control (On/Off) - When is to send msg */

#define LDR_CONTROL         0x1A0E      /* Msg ID for LDR control Message (Lux value measured) */
#define LDR_CONTROL_SEND    0x1A        /* Msg ID for LDR control Message (Lux value measured) */

#define ALARM_MSG           0xB0        /* Msg ID for Alarm Message */

//Technical messages
#define ASK_WHOIS           0xCF08      /* Msg ID for WHO IS request | Length */
#define ANS_WHOIS           0xFC        /* Msg ID for Reply to WHO IS request */

#define ASK_WHAT_CLK        0xCE08      /* Msg ID for WHAT CLOCK request | Length */
#define ANS_WHAT_CLK        0xEC        /* Msg ID for Reply to WHAT CLOCK request */

#define CONF_ENC            0xCD09      /* Msg ID for CONF ENC request - sets ON/OFF the encryption | Length  */
#define ACK_CONF_ENC        0xDC        /* Msg ID for the Reply to CONF ENC request */


/* Define for message handling */
#define NO_MSG              0x00        /* No messages to be send */

#define RE_SEND             0xFF	//Value for the flag - Re-send message
/* => All the other values for the flag are the Msg ID */


/*****************************************/
/*  Positions for the alarm information  */
/*****************************************/
#define ALR_LAMP            0
#define ALR_TEMPLAMP        1
#define ALR_TEMPPCB         2
#define ALR_STAB            3
#define ALR_VOLT            4
#define ALR_CURR            5
#define ALR_LDR             6


/************************************/
/*  Delays for the send of RF msgs  */
/************************************/
#define RE_SEND_DLY         1
#define RE_SEND_RND_DLY		15

#define ACK_ANS_DLY     	85
#define ACK_ANS_RND_DLY		20

#define DEBUG_DLY           1
#define DEBUG_RND_DLY		100


/**********************************/
/*  RF msgs handling - Msg Buffer */
/**********************************/
#define DATA_SIZE_CLEAR         13      /* 1*UINT8_SIZE + 3*UINT8_SIZE + 3*UINT8_SIZE + 3*UINT16_SIZE */
#define RF_CNT_MSGS				4		/* Value in seconds to detect repeated messages */

/***************************/
/* Other RF msg defines    */
/***************************/
#define OK_MSG          0x01

#define TTL_DEFAULT     100



typedef struct
{
    uint8_t ind;
    uint8_t ordID[3];
    uint8_t msgID[3];
    uint16_t net[3];
    uint8_t ordIDact;

}MSGBUFF_STRUCT;


typedef struct
{
    uint8_t ordID;
    uint8_t msgID;
    uint16_t net;
    uint16_t sn;
    uint8_t data[MAX_RFMSG_LEN];       /* It is included the TTL and checksum */
    uint8_t ttl;
    uint8_t cks;
    uint8_t len;

}RFMSG_STRUCT;


/* In the new version of RF Protocol we should have the Length and the ID of the message
 * in sequential positions to compare the both in one IF
 */


#endif	/* M1_RF_H */

