/******************************************************************************/
/*  Files to Include                                                          */
/******************************************************************************/

#include <time.h>
#include "user_RF.h"


/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

extern volatile SYS_STRUCT sys;
extern SYS_STRUCT *sysPt;

extern volatile PWR_CONSUME_STRUCT pwr;
extern PWR_CONSUME_STRUCT *pwrPt;

extern volatile RF_STRUCT rf;
extern RF_STRUCT *rfPt;

extern volatile MSGBUFF_STRUCT msgBuff;     /* Struct to create a buffer of the last 3 msgs received */
extern MSGBUFF_STRUCT *msgBuffPt;

struct timeval ti1s, tf1s;	/* Structures to count 2s to compare RF messages */
struct timeval timerInit, timerFinal; /* Structures to count process interval in ms */
struct timeval timerRF_init, timerRF_final;
uint16_t timer1s;
uint16_t timerMs;
uint16_t timerRF;
uint8_t  RX_flag = 0;

extern int uart0_filestream;
extern int clientSocket;




#if TEST
	#define pinTest 0
	extern float v1,v2,v3;
	extern float i1,i2,i3;
	extern float p1,p2,p3;
	extern float kwhSum;
	extern float mwhSum;
	extern int fp1,fp2,fp3;
	extern float sample;
#endif

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int main(int argc, char *argv[])
{
	/* Initialize memory and peripherals */
	if (ConfigInit() != 0) exit(1);

	/* Start 1s counting */
	gettimeofday(&ti1s, NULL);
	
	/* Start ms counting */
	gettimeofday(&timerInit, NULL);
	
	/* Start RF test counting */
	gettimeofday(&timerRF_init, NULL);
	
	/* Initializa connections */	
	InitConnections();	
	
	ResetProcessVars();	
	
	#if TEST
		pinMode(pinTest, OUTPUT);
	#endif
	
	printf("\r\nRPi Controller V2.6 - 29/11/2019\r\n"); 
	
	printf("=1,SN=%u,NET=%u,ENC=%d,RFFreq=%d,TTL=%d\r\n", sys.sn, sys.net, sys.encCtrl, rf.freq, sys.ttlMAX);
	
	/* Infinite cycle */
    for(;;)
    {
		/* Check if there is any RF interrupt*/
        if (rf.int_RF == 1)
        {
            if (rf.msgSent == 0) RX_flag = 1;           
            
            /* Call RF State Machine to handle with the interrupt */            
			#ifdef RF_RFM22B
				RF_RFM22B_SttMachine(rfPt, msgBuffPt, sysPt);
			#endif
			#ifdef RF_RFM69HCW
				RF_RFM69HCW_SttMachine(rfPt, msgBuffPt, sysPt);
			#endif
			#ifdef RF_RFM95W
				RF_RFM95W_SttMachine(rfPt, msgBuffPt, sysPt);
			#endif
			#ifdef TPP
				
			#endif			
			
            rf.int_RF = 0;
        }


		/* Avoid missed INT0 interrupts */
#ifdef RF_RFM22B
		if ((rf.int_RF == 0) && (digitalRead (RF_INT_PIN) == 0))
#endif
#ifdef RF_RFM69HCW
		if ((rf.int_RF == 0) && (digitalRead (RF_INT_PIN) == 1))
#endif
#ifdef RF_RFM95W
		if ((rf.int_RF == 0) && (digitalRead (RF_INT_PIN) == 1))
#endif	
        {
            rf.int_RF = 1;
            
            #if DEBUG_RF_INT
                printf("\n RF Int missed! \n");
            #endif
        }


        /* Check if there is an order to send a message*/
        if (rf.msgIDsend > 0)
        {
            RF_SendMsg(rfPt, msgBuffPt, sysPt);
            rf.msgIDsend = 0;
        }    	
    	
    	/* Check Delta ms */
    	gettimeofday(&timerFinal, NULL);
    	timerMs = (int)(1000*(timerFinal.tv_sec - timerInit.tv_sec) + (timerFinal.tv_usec - timerInit.tv_usec)/1000);

        /* Control for PROCESS INTERVAL ms tasks */
        if (timerMs > PROCESS_INTERVAL)
        {
			/* Update the timer */
        	gettimeofday(&timerInit, NULL);
        	
        	HandleProcess();        	       				
        } 
        
        // Enter sleep mode to let the processor "breathe"
        usleep(500);
        
        //RF blockage test
        gettimeofday(&timerRF_final, NULL);
        timerRF = (uint16_t)(timerRF_final.tv_sec - timerRF_init.tv_sec);
        
        if (timerRF > CHECK_RF_INTERVAL)
        {
			if (RX_flag == 0)
			{
				#ifdef RF_RFM22B
					RF_RFM22B_Reset(rfPt);
				#endif
				#ifdef RF_RFM69HCW
					RF_RFM69HCW_Reset(rfPt);
				#endif
				#ifdef RF_RFM95W
					RF_RFM95W_Reset(rfPt);
				#endif				
			}
			else
			{
				RX_flag = 0;
			}
			
			timerRF = 0;
			gettimeofday(&timerRF_init, NULL);
		}
		
        
        #if TEST
			if (digitalRead(pinTest) == 0) digitalWrite(pinTest, 1); else digitalWrite(pinTest, 0); 
			//Check the time interval for 1s counting
			gettimeofday(&tf1s, NULL);
			timer1s = (uint16_t)(tf1s.tv_sec - ti1s.tv_sec);
			if (timer1s > 0)
			{
				gettimeofday(&ti1s, NULL);
				printf("#%5.1f\r\n",sample);
				printf("V1(V) = %6.2f  I1(A) = %6.2f  P1(W) = %6.2f  FP1 = %6.4f\r\n",v1,i1,p1,(float)fp1/10000.0);
				printf("V2(V) = %6.2f  I2(A) = %6.2f  P2(W) = %6.2f  FP2 = %6.4f\r\n",v2,i2,p2,(float)fp2/10000.0);
				printf("V3(V) = %6.2f  I3(A) = %6.2f  P3(W) = %6.2f  FP3 = %6.4f\r\n",v3,i3,p3,(float)fp3/10000.0);
				printf("Consumption(kWh) = %10.2f\r\n\n",kwhSum);
			}
		#endif		
                      
    } // END for(;;)
    
	#ifdef UDP
	
		shutdown(clientSocket,SHUT_RDWR);
		
	#else
		
		serialClose(uart0_filestream);

	#endif
	
    return 0;

} // END main(void)
