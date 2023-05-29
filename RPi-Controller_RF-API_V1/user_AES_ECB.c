/*
 * user_AES_ECB.c
 *
 *  Created on: 22 de Abr de 2014
 *      Author: André Gomes
 */

#include "user_AES_ECB.h"
#include "string.h"


/* AES 128bit Encryption consts & variables */
/********************************************/

/* Variable to receive the session key */
AES_SESSION_KEY_128_BIT session_key;


uint8_t encrypt[MAX_AESBUFF_LEN]={0};
uint8_t decrypt[MAX_AESBUFF_LEN]={0};
uint8_t auxBuff[MAX_AESBUFF_LEN]={0};
uint8_t auxBuff2[AES_BLOCK_SIZE]={0};

uint8_t auxLen;
/********************************************/



/* The session_key should have been calculated before */
uint8_t AES128_Encrypt(uint8_t *buff, uint8_t buffLen, uint8_t *buffEnc, void *sessionKey)
{
    /* Copy to auxiliary buffer and add the length of the original message */
    auxLen = buffLen + 1;
    auxBuff[0] = buffLen;
    memcpy(auxBuff+1, buff, auxLen);

    /* The encryption is done in a 16bit block size*/
    if ((auxLen < AES_BLOCK_SIZE) && (auxLen > 0))
    {
        /* block with less than 16 bytes */

        /* Set the rest of the bytes to 0 */
        memset(auxBuff+auxLen, 0, AES_BLOCK_SIZE-auxLen);

        AESECBEncryptBlock(auxBuff, sessionKey, buffEnc, AES_KEY_TYPE_128_BIT);

        return AES_BLOCK_SIZE;
    }
    else if ((auxLen > MIN_AESBUFF_LEN) && (auxLen <= MAX_AESBUFF_LEN))
    {
        /* block with more than 16 bytes */

        /* Encrypt the first block already in auxBuff */
        AESECBEncryptBlock(auxBuff, sessionKey, buffEnc, AES_KEY_TYPE_128_BIT);

        /* Set the rest of the bytes to 0 */
        if (auxLen < MAX_AESBUFF_LEN)
        	memset(auxBuff+auxLen, 0, MAX_AESBUFF_LEN-auxLen);

        /* Encrypt the second block */
        AESECBEncryptBlock(auxBuff+AES_BLOCK_SIZE, sessionKey, buffEnc+AES_BLOCK_SIZE, AES_KEY_TYPE_128_BIT);

        return MAX_AESBUFF_LEN;
    }
    else if (auxLen == AES_BLOCK_SIZE)
    {
        /* block of 16 bytes */
        AESECBEncryptBlock(auxBuff, sessionKey, buffEnc, AES_KEY_TYPE_128_BIT);

        return AES_BLOCK_SIZE;
    }

    /* Return 0 if the message isn't valid */
    return 0;
}



/* The session_key should have been calculated before */
uint8_t AES128_Decrypt(uint8_t *buffEnc, uint8_t buffLen, uint8_t *buffDec, void *sessionKey)
{
    /* The encryption is done in a 16bit block size*/
    if (buffLen == AES_BLOCK_SIZE)
    {
        /* block of 16 bytes */
        AESECBDecryptBlock(buffEnc, sessionKey, auxBuff, AES_KEY_TYPE_128_BIT);
    }
    else if (buffLen == MAX_AESBUFF_LEN)
    {
        /* block with 32 bytes */

        /* Decrypt the first block */
        AESECBDecryptBlock(buffEnc, sessionKey, auxBuff, AES_KEY_TYPE_128_BIT);

        /* Decrypt the second block */
        AESECBDecryptBlock(buffEnc+AES_BLOCK_SIZE, sessionKey, auxBuff+AES_BLOCK_SIZE, AES_KEY_TYPE_128_BIT);
    }
    else
    {
    	/* Not a valid message */
        return 0;
    }

    /* Copy from auxiliary buffer */
    memcpy(buffDec, auxBuff+1, buffLen);

    /* Return the length of the message decrypted */
    return auxBuff[0];
}

