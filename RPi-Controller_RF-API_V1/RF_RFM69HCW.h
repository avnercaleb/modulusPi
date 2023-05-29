/* 
 * File:   RF_RFM69HCW.h
 * Author: André Gomes
 *
 * Created on 11 June 2015, 12:00
 */

#ifndef RF_RFM69HCW_H
#define	RF_RFM69HCW_H

#include "wiringPi.h"
#include "wiringPiSPI.h"
#include "M1_RF.h"


/******************************************************************************/
/* Registers for the RF module config                                         */
/******************************************************************************/
#define RF_REG_FIFO             0x00    /* FIFO read/write access */
#define RF_REG_OPMODE           0x01    /* Operating modes of the transceiver */
#define RF_REG_DATAMODUL        0x02    /* Data operation mode and Modulation settings */
#define RF_REG_BITRATE_MSB      0x03    /* Bit Rate setting, Most Significant Bits */
#define RF_REG_BITRATE_LSB      0x04    /* Bit Rate setting, Least Significant Bits */
#define RF_REG_FDEV_MSB         0x05    /* Frequency Deviation setting, Most Significant Bits */
#define RF_REG_FDEV_LSB         0x06    /* Frequency Deviation setting, Least Significant Bits */
#define RF_REG_FRFMSB           0x07    /* RF Carrier Frequency, Most Significant Bits */
#define RF_REG_FRFMID           0x08    /* RF Carrier Frequency, Intermediate Bits */    
#define RF_REG_FRFLSB           0x09    /* RF Carrier Frequency, Least Significant Bits */
#define RF_REG_OSC1             0x0A    /* RC Oscillators Settings */
#define RF_REG_AFCCTRL          0x0B    /* AFC control in low modulation index situations */
#define RF_REG_LISTEN1          0x0D    /* Listen Mode settings */
#define RF_REG_LISTEN2          0x0E    /* Listen Mode Idle duration */
#define RF_REG_LISTEN3          0x0F    /* Listen Mode Rx duration */
#define RF_REG_VERSION          0x10    /* RF Module Version */ 
#define RF_REG_PALEVEL          0x11    /* PA selection and Output Power control */
#define RF_REG_PARAMP           0x12    /* Control of the PA ramp time in FSK mode */
#define RF_REG_OCP              0x13    /* Over Current Protection control */
#define RF_REG_LNA              0x18    /* LNA settings */
#define RF_REG_RXBW             0x19    /* Channel Filter BW Control */
#define RF_REG_AFCBW            0x1A    /* Channel Filter BW control during the AFC routine */
#define RF_REG_OOKPEAK          0x1B    /* OOK demodulator selection and control in peak mode */
#define RF_REG_OOKAVG           0x1C    /* Average threshold control of the OOK demodulator */
#define RF_REG_OOKFIX           0x1D    /* Fixed threshold control of the OOK demodulator */
#define RF_REG_AFCFEI           0x1E    /* AFC and FEI control and status */
#define RF_REG_AFCMSB           0x1F    /* MSB of the frequency correction of the AFC */
#define RF_REG_AFCLSB           0x20    /* LSB of the frequency correction of the AFC */
#define RF_REG_FEIMSB           0x21    /* MSB of the calculated frequency error */
#define RF_REG_FEILSB           0x22    /* LSB of the calculated frequency error */
#define RF_REG_RSSICONFIG       0x23    /* RSSI-related settings */
#define RF_REG_RSSIVALUE        0x24    /* RSSI value in dBm */
#define RF_REG_DIOMAPPING1      0x25    /* Mapping of pins DIO0 to DIO3 */
#define RF_REG_DIOMAPPING2      0x26    /* RegIrqFlags1 0x80 Status register: PLL Lock state, Timeout, RSSI > Threshold... */
#define RF_REG_IRQFLAGS1        0x27    /* Interrupts Status register 1: Operation Modes, RSSI... */
#define RF_REG_IRQFLAGS2        0x28    /* Interrupts Status register 2: FIFO handling flags... */ 
#define RF_REG_RSSITHRESH       0x29    /* RegRxTimeout1 0x00 Timeout duration between Rx request and RSSI detection */
#define RF_REG_RXTIMEOUT1       0x2A    /* Timeout duration between Rx request and RSSI detection */
#define RF_REG_RXTIMEOUT2       0x2B    /* Timeout duration between RSSI detection and PayloadReady */
#define RF_REG_PREAMBLEMSB      0x2C    /* Preamble length, MSB */
#define RF_REG_PREAMBLELSB      0x2D    /* Preamble length, LSB */
#define RF_REG_SYNCCONFIG       0x2E    /* Sync Word Recognition control */
#define RF_REG_SYNCVALUE1       0x2F    /* Sync Word bytes, 1 through 8 */
#define RF_REG_SYNCVALUE2       0x30
#define RF_REG_SYNCVALUE3       0x31
#define RF_REG_SYNCVALUE4       0x32
#define RF_REG_SYNCVALUE5       0x33
#define RF_REG_SYNCVALUE6       0x33
#define RF_REG_SYNCVALUE7       0x33
#define RF_REG_SYNCVALUE8       0x36
#define RF_REG_PACKETCONFIG1    0x37    /* Packet mode settings */
#define RF_REG_PAYLOADLENGTH    0x38    /* Payload length setting */
#define RF_REG_NODEADRS         0x39    /* Node address */
#define RF_REG_BROADCASTADRS    0x3A    /* Broadcast address */
#define RF_REG_AUTOMODES        0x3B    /* Auto modes settings */
#define RF_REG_FIFOTHRESH       0x3C    /* Fifo threshold, Tx start condition */
#define RF_REG_PACKETCONFIG2    0x3D    /* Packet mode settings */
#define RF_REG_AESKEY1          0x3E    /* 16 bytes of the cypher key */
#define RF_REG_AESKEY2          0x3F
#define RF_REG_AESKEY3          0x40
#define RF_REG_AESKEY4          0x41
#define RF_REG_AESKEY5          0x42
#define RF_REG_AESKEY6          0x43
#define RF_REG_AESKEY7          0x44
#define RF_REG_AESKEY8          0x45
#define RF_REG_AESKEY9          0x46
#define RF_REG_AESKEY10         0x47
#define RF_REG_AESKEY11         0x48
#define RF_REG_AESKEY12         0x49
#define RF_REG_AESKEY13         0x4A
#define RF_REG_AESKEY14         0x4B
#define RF_REG_AESKEY15         0x4C
#define RF_REG_AESKEY16         0x4D
#define RF_REG_TEMP1            0x4E    /* Temperature Sensor control */
#define RF_REG_TEMP2            0x4F    /* Temperature readout */
#define RF_REG_TESTLNA          0x58    /* Sensitivity boost */
#define RF_REG_TESTPA1          0x5A    /* High Power PA settings */
#define RF_REG_TESTPA2          0x5C    /* High Power PA settings */
#define RF_REG_TESTDAGC         0x6F    /* Fading Margin Improvement */
#define RF_REG_TESTAFC          0x71    /* AFC offset for low modulation index AFC */

/* Other defines */
#define NODE_ADDRESS            0x5C


typedef struct
{
    RFMSG_STRUCT    	rxMsg;
    RFMSG_STRUCT    	txMsg;
    unsigned int    	int_RF;
    unsigned int        msgRcv;
    unsigned int        msgSent;
    unsigned int        msgIDsend;
    unsigned int        cnt5s;
    unsigned int        rssiVal;
    unsigned int        freq;

}RF_STRUCT;


/**
 * Function to write 1 Register of 1 Byte
 */
void RF_RFM69HCW_WrtReg(uint8_t reg, uint8_t data);


/**
 * Function to write 1 array of x bytes
 */
void RF_RFM69HCW_WrtArray(uint8_t reg, uint8_t *array, uint8_t arraySize);


/**
 * Function to read 1 Register of 1 Byte
 */
uint8_t RF_RFM69HCW_ReadReg(uint8_t reg);


/**
 * Function to read 1 array of x bytes
 */
void RF_RFM69HCW_ReadArray(uint8_t reg, uint8_t *array, uint8_t arraySize);


/**
 * Function to clear RF Interrupts
 */
void RF_RFM69HCW_ClrRfInt(void);


/**
 * Function to Configure the RF Module
 */
void RF_RFM69HCW_Config(void);


/**
 * Function to set the RF module to Standby MODE
 */
void RF_RFM69HCW_StandbyMode(void);


/**
 * Function to set the RF module to FS (Frequency Synthesizer) MODE
 */
void RF_RFM69HCW_FSMode(void);


/**
 * Function to set the RF module to RX MODE
 */
void RF_RFM69HCW_RxMode(void);


/**
 * Function to set the RF module to TX MODE
 */
void RF_RFM69HCW_TxMode(void);


/**
 * Function to write in the tx fifo and start to transmit according to Sensing RF protocol
 */
void RF_RFM69HCW_WrtTXfifo(uint8_t *msg, uint8_t len);


/**
 * Function to Get received RF messages
 */
void RF_RFM69HCW_ReadRXfifo(uint8_t *msg, uint8_t *len);


uint8_t RF_RFM69HCW_GetRSSI(void);


/**
 * Function to get the status
 */
uint8_t RF_RFM69HCW_GetDevStt(void);


/**
 * Function to Change RF State
 */
void RF_RFM69HCW_ChgStt(void);



#endif	/* RF_RFM69HCW_H */

