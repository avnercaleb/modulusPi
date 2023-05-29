/* 
 * File:   RF_RFM95W.h
 * Author: Claudio Monteiro
 *
 * Created on August 6th 2018, 12:00
 */

#ifndef RF_RFM95W_H
#define	RF_RFM95W_H

#include "wiringPi.h"
#include "wiringPiSPI.h"
#include "M1_RF.h"


/******************************************************************************/
/* Registers for the RF module config                                         */
/******************************************************************************/
#define RF_REG_FIFO             0x00    /* FIFO read/write access */
#define RF_REG_OPMODE           0x01    /* Operating modes of the transceiver */
#define RF_REG_FRFMSB           0x06    /* RF Carrier Frequency, Most Significant Bits */
#define RF_REG_FRFMID           0x07    /* RF Carrier Frequency, Intermediate Bits */    
#define RF_REG_FRFLSB           0x08    /* RF Carrier Frequency, Least Significant Bits */
#define RF_REG_PALEVEL          0x09    /* PA selection and Output Power control */
#define RF_REG_PARAMP           0x0A    /* Control of the PA ramp time in FSK mode */
#define RF_REG_OCP              0x0B    /* Over Current Protection control */
#define RF_REG_LNA              0x0C    /* LNA settings */
#define RF_REG_FIFO_ADDR_PTR    0x0D    /* SPI interface FIFO address pointer */
#define RF_REG_FIFO_TX_ADDR     0x0E    /* Write base address in FIFO data buffer for TX modulator */
#define RF_REG_FIFO_RX_ADDR     0x0F    /* read base address in FIFO data buffer for RX demodulator */
#define RF_REG_FIFO_CURR_ADDR   0x10    /* Start address (in data buffer) of last packet received */
#define RF_REG_IRQ_FLAGS_MASKS  0x11    /* IRQ masks */
#define RF_REG_IRQ_FLAGS        0x12    /* IRQ flags */
#define RF_REG_RX_NB_BYTES      0x13    /* Number of bytes of the latest payload received */
#define RF_REG_MODEM_STATUS     0x18    /* Modem status */
#define RF_REG_MODEM_CONF_1     0x1D    /* LoRa BW, coding rate (CR), implicit header mode */
#define RF_REG_MODEM_CONF_2     0x1E    /* LoRa SF and etc */
#define RF_REG_SYMBOL_TO        0x1F    /* Symbol timeout LSB */
#define RF_REG_PREAMBLEMSB      0x20    /* Preamble length, MSB */
#define RF_REG_PREAMBLELSB      0x21    /* Preamble length, LSB */
#define RF_REG_PAYLOAD_LEN      0x22    /* Payload length. Must be set in implicit mode. Always different from 0 */
#define RF_REG_MAX_PAYLOAD_LEN  0x23    /* Maximum payload length. POR = 0xFF */
#define RF_REG_RX_BYTE_ADDR     0x25    /* Address of the last byte written in FIFO */
#define RF_REG_MODEM_CONF_3     0x26    /* Mobile node, AGC auto on/off */
#define RF_REG_DETECTION_OPT    0x31
#define RF_REG_LORA_INVERT_IQ   0x33
#define RF_REG_DETECTION_THSD   0x37
#define RF_REG_SYNC_WORD        0x39
#define RF_REG_DIOMAPPING1      0x40    /* Mapping of pins DIO0 to DIO3 */
#define RF_REG_DIOMAPPING2      0x41    /* Mapping of pins DIO4 and DIO5 */
#define RF_REG_TCXO             0x4B    /* TXCO or XTAL input setting */
#define RF_REG_PA_DAC           0x4D    /* PA higher level */
#define RF_REG_PLL_HF           0x70    /* PLL bandwidth */


typedef struct
{
    RFMSG_STRUCT    rxMsg;
    RFMSG_STRUCT    txMsg;
    unsigned int    int_RF;
    unsigned int    msgRcv;
    unsigned int    msgSent;
    unsigned int    msgIDsend;
    unsigned int    cnt5s;
    unsigned int    rssiVal;
    unsigned int    freq;

}RF_STRUCT;


/**
 * Function to write 1 Register of 1 Byte
 */
void RF_RFM95W_WrtReg(uint8_t reg, uint8_t data);


/**
 * Function to write 1 array of x bytes
 */
void RF_RFM95W_WrtArray(uint8_t reg, uint8_t *array, uint8_t arraySize);


/**
 * Function to read 1 Register of 1 Byte
 */
uint8_t RF_RFM95W_ReadReg(uint8_t reg);


/**
 * Function to read 1 array of x bytes
 */
void RF_RFM95W_ReadArray(uint8_t reg, uint8_t *array, uint8_t arraySize);


/**
 * Function to clear RF Interrupts
 */
void RF_RFM95W_ClrRfInt(void);


/**
 * Function to Configure the RF Module
 */
void RF_RFM95W_Config(void);


/**
 * Function to set the RF module to Standby MODE
 */
void RF_RFM95W_StandbyMode(void);


/**
 * Function to set the RF module to FS (Frequency Synthesizer) MODE
 */
void RF_RFM95W_FSMode(void);


/**
 * Function to set the RF module to RX MODE
 */
void RF_RFM95W_RxMode(void);


/**
 * Function to set the RF module to TX MODE
 */
void RF_RFM95W_TxMode(void);


/**
 * Function to write in the tx fifo and start to transmit according to Sensing RF protocol
 */
void RF_RFM95W_WrtTXfifo(uint8_t *msg, uint8_t len);


/**
 * Function to Get received RF messages
 */
void RF_RFM95W_ReadRXfifo(uint8_t *msg, uint8_t *len);


uint8_t RF_RFM95W_GetRSSI(void);


/**
 * Function to get the status
 */
uint8_t RF_RFM95W_GetDevStt(void);


/**
 * Function to Change RF State
 */
void RF_RFM95W_ChgStt(void);


#endif	/* RF_RFM95W_H */

