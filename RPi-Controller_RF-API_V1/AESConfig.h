/********************************************************************
 * FileName:		AESConfig.h
 * Dependencies:
 * Processor:		PIC32MX
 * Hardware:		N/A
 * Assembler:		N/A
 * Linker:		    N/A
 * Company:		    Microchip Technology Inc..
 *
 * Software License Agreement:
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * $Id: INT.h,v 1.6 2006/11/07 23:29:45 C12923 Exp $
 * $Name:  $

 ********************************************************************/

#ifndef _AES_CONFIGURATION_H
#define _AES_CONFIGURATION_H

// *****************************************************************************
/* AES Key 128

  Summary:
    Using an AES key lenght of 128 bits

  Description:
    When this macro is defined, an AES key length of 128 will be used.  Based of
    of this 128-bit key length, the session key size and number of round required will
    be configured.

  Remarks:
    This define is excluzive and macros for 192 and 256-bit key lengths can not be defined.
*/
#define _AES_KEY_128

// *****************************************************************************
/* AES Key 192

  Summary:
    Using an AES key lenght of 192 bits

  Description:
    When this macro is defined, an AES key length of 192 will be used.  Based of
    of this 192-bit key length, the session key size and number of round required will
    be configured.

  Remarks:
    This define is excluzive and macros for 128 and 256-bit key lengths can not be defined.
*/
//#define _AES_KEY_192

// *****************************************************************************
/* AES Key 256

  Summary:
    Using an AES key lenght of 256 bits

  Description:
    When this macro is defined, an AES key length of 192 will be used.  Based of
    of this 256-bit key length, the session key size and number of round required will
    be configured.

  Remarks:
    This define is excluzive and macros for 128 and 192-bit key lengths can not be defined.
*/
//#define _AES_KEY_256
#endif
