#ifndef __RADIO_API_C__
#define __RADIO_API_C__

#include "inc/Radio_api.h"

uint8_t Sended_Data = 0;
uint8_t fskSendFlag = 0;
uint8_t FskApi_state = WAITING;
uint8_t fskMessage[46] = "";
uint8_t fskMessageLsength = 0;

/**
 * @brief Initializes the FSK chart for testing purposes.
 *
 * This function initializes the FSK chart for testing purposes. It sets pointers to different elements of the 'resampledAcc' and 'resampledForc' arrays, as well as 'sourfaceCardInfo'.
 *
 * @return None
 */
void RadioInit(void)
{
    FskChart.packet0 = (uint8_t*) &resampledAcc[0];   // Pointer to the beginning of resampledAcc
    FskChart.packet1 = (uint8_t*) &resampledAcc[16];  // Pointer to element 16 of resampledAcc
    FskChart.packet2 = (uint8_t*) &resampledAcc[32];  // Pointer to element 32 of resampledAcc
    FskChart.packet3 = (uint8_t*) &resampledAcc[48];  // Pointer to element 48 of resampledAcc

    FskChart.packet4 = (uint8_t*) &resampledForc[0];   // Pointer to the beginning of resampledForc
    FskChart.packet5 = (uint8_t*) &resampledForc[16];  // Pointer to element 16 of resampledForc
    FskChart.packet6 = (uint8_t*) &resampledForc[32];  // Pointer to element 32 of resampledForc
    FskChart.packet7 = (uint8_t*) &resampledForc[48];  // Pointer to element 48 of resampledForc

    FskChart.packet8 = (uint8_t*) &sourfaceCardInfo;   // Pointer to sourfaceCardInfo
    FskChart.packet9 = (uint8_t*) &sourfaceCardInfo;   // Pointer to sourfaceCardInfo
}

/**
 * @brief Puts the radio module to sleep.
 *
 * This function puts the radio module to sleep.
 *
 * @return None
 */
void RadioSleep(void)
{
    FSK_Sleep();
}

/**
 * @brief Wakes up the radio module.
 *
 * This function wakes up the radio module.
 *
 * @return None
 */
void RadioWakeUp(void)
{
    FSK_WakeUp();
}

/**
 * @brief Prepares and sends an FSK message.
 *
 * This function prepares and sends an FSK message by setting the necessary flags and copying the message data.
 *
 * @param message The message to be sent.
 * @return None
 */
void pFSKM(char* message)
{
    fskSendFlag = 2;
    fskMessageLength = strlen(message);
    fskMessage[0] = FRAME_MESSAGE;
    strcpy((char*)(fskMessage+1), (char*)message);
}

/**
 * @brief Prepares to send data obtained from the dynamometer card via FSK.
 *
 * This function prepares to send data obtained from the dynamometer card via FSK by setting the necessary flags and data.
 *
 * @return None
 */
void pFSKD()
{
    fskSendFlag = 1;
    Sended_Data = 0;
}

/**
 * @brief Polls the Radio module for sending and receiving data.
 *
 * This function polls the Radio module for sending and receiving data according to the current state of the FSK API.
 *
 * @return None
 */
void RadioPoll(void)
{
	switch (FskApi_state)
	{
	case SENDING_CHART:
		switch (Sending_Available())
		{
		case TX_NO_ACK:
		{
			#ifdef event_errorFSK_active
			errorFSK();
			#endif
			FskApi_state = WAITING;
			break;
		}
		case TX_SENDING:
			break;
		case TX_AVAILABLE:
		{
			if(Sended_Data >= PacketsCounts)
			{
				Sended_Data=0;
				FskApi_state=WAITING;
				break;
			}
			uint8_t data[34] = "";
			data[0] = FRAME_DATA;
			data[1] = Sended_Data;
			switch(data[1])
                {
					case 0:
						for(int i = 0; i < 32 ; i++)
						{
							data[i+2] = FskChart.packet0[i];
						}
						break;
                    case 1:
                        for(int i = 0; i < 32 ; i++)
                        {
                            data[i+2] = FskChart.packet1[i];
                        }
                        break;
                    case 2:
                        for(int i = 0; i < 32 ; i++)
                        {
                        	data[i+2] = FskChart.packet2[i];
                        }
                        break;
                    case 3:
                        for(int i = 0 ; i < 32 ; i++)
                        {
                            data[i+2] = FskChart.packet3[i];
                        }
                        break;

					case 4:
						for(int i = 0; i < 32 ; i++)
						{
							data[i+2] = FskChart.packet4[i];
						}
						break;
                    case 5:
                        for(int i = 0; i < 32 ; i++)
                        {
                            data[i+2] = FskChart.packet5[i];
                        }
                        break;
                    case 6:
                        for(int i = 0; i < 32 ; i++)
                        {
                        	data[i+2] = FskChart.packet6[i];
                        }
                        break;
                    case 7:
                        for(int i = 0 ; i < 32 ; i++)
                        {
                            data[i+2] = FskChart.packet7[i];
                        }
                        break;
                    case 8:
                        for(int i = 0 ; i < 32 ; i++)
                        {
                            data[i+2] = FskChart.packet8[i];
                        }
                        break;


                }
			SendFSKMessage(data, 34);
			Sended_Data++;
			break;
		}
		default:
			break;
		}
		break;
	case WAITING:
	{
		if(Data_Available())
		{
			uint8_t data[34] = "";
			uint8_t length = Read_Data(data);
			switch (data[0])
			{
			case FRAME_MESSAGE:
			#ifdef event_eFSKM_active
				eFSKM(data+1);
			#endif
				break;
			case FRAME_DATA:				
				switch(data[1])
                {
                    case 0:
                        for(int i = 2 ; i < length ; i++)
                        {
                           FskChart.packet0[i-2] = data[i];
                        }
                        break;
                    case 1:
                        for(int i = 2 ; i < length ; i++)
                        {
                           FskChart.packet1[i-2] = data[i];
                        }
                        break;
                    case 2:
                        for(int i = 2 ; i < length ; i++)
                        {
                           FskChart.packet2[i-2] = data[i];
                        }
                        break;
                    case 3:
                        for(int i = 2 ; i < length ; i++)
                        {
                           FskChart.packet3[i-2] = data[i];
                        }
                        break;
                    case 4:
                        for(int i = 2 ; i < length ; i++)
                        {
                           FskChart.packet4[i-2] = data[i];
                        }
                        break;
                    case 5:
                        for(int i = 2 ; i < length ; i++)
                        {
                           FskChart.packet5[i-2] = data[i];
                        }
                        break;
                    case 6:
                        for(int i = 2 ; i < length ; i++)
                        {
                           FskChart.packet6[i-2] = data[i];
                        }
                        break;
                    case 7:
                        for(int i = 2 ; i < length ; i++)
                        {
                           FskChart.packet7[i-2] = data[i];
                        }
                        break;
                    case 8:
                        for(int i = 2 ; i < length ; i++)
                        {
                           FskChart.packet8[i-2] = data[i];
                        }
                        break;
					default:
						break;
                }
				#ifdef event_eFSKD_active
				if(data[1] == PacketsCounts -1)
				{
					eFSKD();
				}
				#endif
				break;
			default:
				break;
			}
		}
		else if (fskSendFlag == 1)
		{
			FskApi_state = SENDING_CHART;
			fskSendFlag = 0;
		}
		else if (fskSendFlag == 2)
		{
			FskApi_state = SENDING_MESSAGE;
			//fskSendFlag = 0;
		}
	}
		break;
	case SENDING_MESSAGE:
	{
		switch (Sending_Available())
		{
			case TX_SENDING:
				break;
			case TX_NO_ACK:
			{
				#ifdef event_errorFSK_active
				errorFSK();
				#endif
				FskApi_state = WAITING;
				fskSendFlag = 0;
				break;
			}
			case TX_AVAILABLE:
			{
				if (fskSendFlag)
				{
					SendFSKMessage(fskMessage, fskMessageLength+1);
					fskSendFlag = 0;
				}
				else
				{
					FskApi_state = WAITING;
				}
				
				break;
			}
			default:
				break;
		}
	}
		break;	
	default:
		break;
	}

}



#endif