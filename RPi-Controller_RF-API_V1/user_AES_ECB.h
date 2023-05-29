/*
 * user_AES_ECB.h
 *
 *  Created on: 22 de Abr de 2014
 *      Author: agomes
 */

#ifndef USER_AES_ECB_H_
#define USER_AES_ECB_H_


#include "AES_ECB_PIC32.h"


/* Define for the length of the message buffer */
#define MIN_AESBUFF_LEN		16
#define MAX_AESBUFF_LEN		32



uint8_t AES128_Encrypt(uint8_t *buff, uint8_t buffLen, uint8_t *buffEnc, void *sessionKey);


uint8_t AES128_Decrypt(uint8_t *buffEnc, uint8_t buffLen, uint8_t *buffDec, void *sessionKey);



#endif /* USER_AES_ECB_H_ */
