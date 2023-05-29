/*
 * File:   RF_RFM22B.c
 * Author: Andr� Gomes
 *
 * Created on 4 de Fevereiro de 2013, 17:24
 */


#include "RF_RFM22B.h"


volatile RF_STRUCT rf;          /* Struct with the header (ordid, msgid, net, sn), payload, ttl and cks */
volatile RF_STRUCT *rfPt;       /* Pointer for the handling of the struct*/


uint8_t tmpBuff[RF_BUFF_LEN];             /* Temp Buffer to get and send the message */


/**
 * Function to write 1 Register of 1 Byte
 */
void RF_RFM22B_WrtReg(uint8_t reg, uint8_t data)
{
	uint8_t spiData[3];

	spiData [0] = CMD_WRITE | reg;
	spiData [1] = data;

	wiringPiSPIDataRW (SPI_PORT, spiData, 2);
}


/**
 * Function to write 1 array of x bytes
 */
void RF_RFM22B_WrtArray(uint8_t reg, uint8_t *array, uint8_t arraySize)
{
    tmpBuff[0] = reg | CMD_WRITE;				/* Set the MSb to write to a register */
    memcpy(tmpBuff+1, array, arraySize);

	wiringPiSPIDataRW (SPI_PORT, tmpBuff, arraySize+1);
}


/**
 * Function to read 1 Register of 1 Byte
 */
uint8_t RF_RFM22B_ReadReg(uint8_t reg)
{
    uint8_t spiData[4];

    spiData [0] = reg;
    wiringPiSPIDataRW (SPI_PORT, spiData, 2) ;

	return spiData [1];
}


/**
 * Function to read 1 array of x bytes
 */
void RF_RFM22B_ReadArray(uint8_t reg, uint8_t *array, uint8_t arraySize)
{
    tmpBuff[0] = reg;							/* Set the MSb to write to a register */

	wiringPiSPIDataRW (SPI_PORT, tmpBuff, arraySize+1);

    memcpy(array, tmpBuff+1, arraySize);
}


/**
 * Function to clear RF Interrupts
 */
void RF_RFM22B_ClrRfInt(void)
{
    RF_RFM22B_ReadReg(RF_REG_INTSTT1);
    RF_RFM22B_ReadReg(RF_REG_INTSTT2);
}



/**
 * Function to Configure the RF Module
 */
void RF_RFM22B_Config (volatile RF_STRUCT *rfData)
{
    RF_RFM22B_WrtReg(RF_REG_INTENABLE1, 0x02);		//RX interrupt
    RF_RFM22B_WrtReg(RF_REG_INTENABLE2, 0x00);		//no more interrupts
    RF_RFM22B_WrtReg(RF_REG_OP_MODE1, 0x04);		//RX Mode
    RF_RFM22B_WrtReg(RF_REG_OP_MODE2, 0x00);		//No automatic transmission, no multi packet, no antena diversity
    RF_RFM22B_WrtReg(RF_REG_OSCCONF, 0x7F);         //30Mhz Crystal Load Capacitance 12.5pF
    RF_RFM22B_WrtReg(RF_REG_GPIO0CONF, 0x12);		//GPIO0 -> TX STATE (for RF switch)
    RF_RFM22B_WrtReg(RF_REG_GPIO1CONF, 0x15);		//GPIO1 -> RX State (for RF switch)
    RF_RFM22B_WrtReg(RF_REG_PORTCONF, 0x00);		//Port configurations
    RF_RFM22B_WrtReg(RF_REG_ADCCONF1, 0x70);		//No ADC
    RF_RFM22B_WrtReg(RF_REG_ADCCONF2, 0x00);
    RF_RFM22B_WrtReg(RF_REG_TEMPCONF1, 0x00);		//No Temperature Sensor
    RF_RFM22B_WrtReg(RF_REG_TEMPCONF2, 0x00);

    if (rfData->freq == RF_868MHZ)
    {
        RF_RFM22B_WrtReg(RF_REG_IF_FILTCONF, 0x06);		//IF Filter Bandwidth
        RF_RFM22B_WrtReg(RF_REG_AFCCONF, 0x40);         //AFC -> Enable
        RF_RFM22B_WrtReg(RF_REG_CLKRECOVER, 0x45);		//Clock Recovery
        RF_RFM22B_WrtReg(RF_REG_CLKCONF2, 0x01);
        RF_RFM22B_WrtReg(RF_REG_CLKCONF1, 0xD7);
        RF_RFM22B_WrtReg(RF_REG_CLKCONF0, 0xDC);
        RF_RFM22B_WrtReg(RF_REG_CLKRECTG1, 0x03);
        RF_RFM22B_WrtReg(RF_REG_CLKRECTG0, 0xB8);
    }
    else if (rfData->freq == RF_918MHZ)
    {
        RF_RFM22B_WrtReg(RF_REG_IF_FILTCONF, 0x89);		//IF Filter Bandwidth
        RF_RFM22B_WrtReg(RF_REG_AFCCONF, 0x40);         //AFC -> Enabled
        RF_RFM22B_WrtReg(RF_REG_CLKRECOVER, 0xD0);		//Clock Recovery
        RF_RFM22B_WrtReg(RF_REG_CLKCONF2, 0x00);
        RF_RFM22B_WrtReg(RF_REG_CLKCONF1, 0x9D);
        RF_RFM22B_WrtReg(RF_REG_CLKCONF0, 0x49);
        RF_RFM22B_WrtReg(RF_REG_CLKRECTG1, 0x00);
        RF_RFM22B_WrtReg(RF_REG_CLKRECTG0, 0x7B);
        RF_RFM22B_WrtReg(RF_REG_AFCLIMITER, 0x50); 
    }

    RF_RFM22B_WrtReg(RF_REG_DATACONF, 0xAD);		//Data Access Control
    RF_RFM22B_WrtReg(RF_REG_HEADERCTRL1, 0x00);		//Header Control
    RF_RFM22B_WrtReg(RF_REG_HEADERCTRL2, 0x02);     //2 Bytes Sync Word Length (Word 3 and Word 2)
    RF_RFM22B_WrtReg(RF_REG_PRELENCONF, 0x08);		//Preamble Length
    RF_RFM22B_WrtReg(RF_REG_PRECTRLCONF, 0x22);		//Preamble Control
    RF_RFM22B_WrtReg(RF_REG_SYNCCONF3, 0x2D);		//Sync Word
    RF_RFM22B_WrtReg(RF_REG_SYNCCONF2, 0xD4);
    RF_RFM22B_WrtReg(RF_REG_SYNCCONF1, 0x00);
    RF_RFM22B_WrtReg(RF_REG_SYNCCONF0, 0x00);
    RF_RFM22B_WrtReg(RF_REG_THEADER3, 0x00);		//Header
    RF_RFM22B_WrtReg(RF_REG_THEADER2, 0x00);
    RF_RFM22B_WrtReg(RF_REG_THEADER1, 0x00);
    RF_RFM22B_WrtReg(RF_REG_THEADER0, 0x00);
    RF_RFM22B_WrtReg(RF_REG_CHKHEADER3, 0x00);		//Check Header
    RF_RFM22B_WrtReg(RF_REG_CHKHEADER2, 0x00);
    RF_RFM22B_WrtReg(RF_REG_CHKHEADER1, 0x00);
    RF_RFM22B_WrtReg(RF_REG_CHKHEADER0, 0x00);
    RF_RFM22B_WrtReg(RF_REG_HEADEREN3, 0xFF);		//Header Disable
    RF_RFM22B_WrtReg(RF_REG_HEADEREN2, 0xFF);
    RF_RFM22B_WrtReg(RF_REG_HEADEREN1, 0xFF);
    RF_RFM22B_WrtReg(RF_REG_HEADEREN0, 0xFF);

    if (rfData->freq == RF_868MHZ)
    {
        RF_RFM22B_WrtReg(RF_REG_TXPOWER, 0x0F);         //TX Power -> +20 dBm and set LNA_SW bit
        RF_RFM22B_WrtReg(RF_REG_TXBAUDRATE1, 0x0E);		//TX Data Rate
        RF_RFM22B_WrtReg(RF_REG_TXBAUDRATE0, 0xBF);
        RF_RFM22B_WrtReg(RF_REG_MODCONF1, 0x08);		//Modulation Control
        RF_RFM22B_WrtReg(RF_REG_MODCONF2, 0x22);		//Modulation Control
        RF_RFM22B_WrtReg(RF_REG_FREQDEV, 0x2E);         //Frequency deviation - 29KHz
        RF_RFM22B_WrtReg(RF_REG_FREQBAND, 0x73);		//Frequency band select
        RF_RFM22B_WrtReg(RF_REG_FREQCARRIER1, 0x64);	//Nominal carrier frequency
        RF_RFM22B_WrtReg(RF_REG_FREQCARRIER0, 0x00);
    }
    else if (rfData->freq == RF_918MHZ)
    {
        RF_RFM22B_WrtReg(RF_REG_TXPOWER, 0x0D);         //TX Power -> +14 dBm (0x0B) and set LNA_SW bit
        RF_RFM22B_WrtReg(RF_REG_TXBAUDRATE1, 0x0E);		//TX Data Rate
        RF_RFM22B_WrtReg(RF_REG_TXBAUDRATE0, 0xBF);
        RF_RFM22B_WrtReg(RF_REG_MODCONF1, 0x08);		//Modulation Control
        RF_RFM22B_WrtReg(RF_REG_MODCONF2, 0x22);		//Modulation Control (0x22) c/ test mode (0x32)
        RF_RFM22B_WrtReg(RF_REG_FREQDEV, 0xF0);         //Frequency deviation - 150KHz
        RF_RFM22B_WrtReg(RF_REG_FREQBAND, 0x75);		//Frequency band select
        RF_RFM22B_WrtReg(RF_REG_FREQCARRIER1, 0xE1);	//Nominal carrier frequency 918 MHz
        RF_RFM22B_WrtReg(RF_REG_FREQCARRIER0, 0x00);
    }

    /* Clear the RF interrupts to avoid problems*/
    RF_RFM22B_ClrRfInt();

}


/**
 * Function to set the RF module to RX MODE
 */
void RF_RFM22B_RxMode(void)
{
	RF_RFM22B_WrtReg(RF_REG_INTENABLE1, 0x02);     //RX interrupt enable
	RF_RFM22B_WrtReg(RF_REG_OP_MODE1, 0x04);	//RX Mode
}


/**
 * Function to set the RF module to READY MODE
 */
void RF_RFM22B_ReadyMode(void)
{
	RF_RFM22B_WrtReg(RF_REG_OP_MODE1, 0x01);	//To ready mode
}


/**
 * Function to enable RX interrupts
 */
void RF_RFM22B_EnRfInt(void)
{
	RF_RFM22B_WrtReg(RF_REG_INTENABLE1, 0x02);		//RX interrupt
	RF_RFM22B_WrtReg(RF_REG_INTENABLE2, 0x00);		//no more interrupts
}


/**
 * Function to Disable RX interrupts
 */
void RF_RFM22B_DisRfInt(void)
{
	RF_RFM22B_WrtReg(RF_REG_INTENABLE1, 0x00);		//no interrupts
	RF_RFM22B_WrtReg(RF_REG_INTENABLE2, 0x00);		//no interrupts
}


/**
 * Function to write in the tx fifo and start to transmit according to Sensing RF protocol
 */
void RF_RFM22B_WrtTXfifo(uint8_t *msg, uint8_t len)
{
    RF_RFM22B_WrtReg(RF_REG_TXPKTLEN, len);             /* write number of bytes on packet */
    RF_RFM22B_WrtReg(RF_REG_OP_MODE2, 0x03);            /* FIFO RESET */
    RF_RFM22B_WrtReg(RF_REG_OP_MODE2, 0x00);

    /* deliver packet to FIFO */
    RF_RFM22B_WrtArray(RF_REG_FIFO, msg, len);

    RF_RFM22B_WrtReg(RF_REG_INTENABLE1, 0x04);              //packet sent interrupt enable

    RF_RFM22B_ClrRfInt();

    RF_RFM22B_WrtReg(RF_REG_OP_MODE1, 0x09);                //start Transmiting RF message
}


/**
 * Function to Get received RF messages
 */
uint8_t RF_RFM22B_ReadRXfifo(uint8_t *msg, uint8_t *len)
{
    uint8_t crcComp;

    *len = RF_RFM22B_ReadReg(RF_REG_RXPKTLEN);              /* Get the number of bytes received */

    crcComp = RF_RFM22B_ReadReg(RF_REG_EZMACSTT);           /* Read the result of CRC */
    crcComp = (crcComp & 0x04) >> 2;

    RF_RFM22B_ReadArray(RF_REG_FIFO, msg, *len);            /* read FIFO */

    RF_RFM22B_WrtReg(RF_REG_OP_MODE2, 0x03);                /* FIFO RESET */
    RF_RFM22B_WrtReg(RF_REG_OP_MODE2, 0x00);

    RF_RFM22B_ClrRfInt();                                   /* clear interrupts */

    return !crcComp;
}


uint8_t RF_RFM22B_GetRSSI(void)
{
    return RF_RFM22B_ReadReg(RF_REG_RSSI);
}


/**
 * Function to clear the RF buffer
 */
void RF_RFM22B_ClrMsg(RFMSG_STRUCT *msg)
{
    memset(msg, 0x00, sizeof(RFMSG_STRUCT));
}


/**
 * Function to calculate the checksum of buffer of x bytes
 */
uint8_t RF_RFM22B_CksCalc(RFMSG_STRUCT *msg)
{
    uint8_t i;
    uint8_t *buffPt;
    uint16_t cks=0;

    buffPt = msg;

    for (i=0; i<msg->len-2; i++)
    {
        cks += *(buffPt+i);
    }
    cks += msg->ttl;

    cks = (uint8_t)(cks & 0x00FF);

    return cks;
}


/**
 * Function to get the status
 */
uint8_t RF_RFM22B_GetDevStt(void)
{
    return RF_RFM22B_ReadReg(RF_REG_DEVSTT);
}


/**
 * Function to set the Software Reset
 */
void RF_RFM22B_SetSoftRESET(void)
{
    /* The Software Reset has a 500us to be cleared */
    RF_RFM22B_WrtReg(RF_REG_OP_MODE1, 0x80);
}

