#ifndef __FSK_C__
#define __FSK_C__

#icnlude "inc/FSK.h"

static uint8_t idGrupo=0;

static int8_t SleepFlag = 0;

static uint8_t message [46];								//Data to send.
static uint8_t message_length;								//Length of data to send.

static uint8_t read_data[66];								//Received data.
static uint8_t read_data_length;							//Length of read data.

static uint8_t new_data_to_read = 0;						//Flag that indicates if there are new data to read. 

static uint8_t tx_pending_data = 0;							//Flag that indicates if there is sending data.

static int8_t tx_right = 1;									//Flag that indicates if the RFM69 could be transmitted correctly.

static uint8_t tx_packet_id = 0;
static uint8_t last_rx_packet_id = -1;

void FSK_Init(void)
{
    RF_Init();
}

void SendFSKMessage(uint8_t* data, uint8_t length)
{
	if (!tx_pending_data)   //If there isn't data to send.
	{
		//Builds the packet to send and save the length of the buffer.
		message_length = length + 2;
		message[0] = idGrupo;
        message[1] = tx_packet_id++;
		//memcpy((message+2),data, length);
        for(int i = 0; i<length; i++)
        {
            message[i+2]=data[i];
        }
		//Sets the flag to indicate that there is data to send.
		tx_pending_data = 1;
        tx_right = TX_SENDING;
		//return 1;
	}
    //return 0;
}

uint8_t ReadFSKMessage(void)
{
    read_data_length = RFM69_Read(read_data);   //Read the new data.
    
    if (read_data_length > 2 && read_data[1] != last_rx_packet_id)
    {
        last_rx_packet_id = read_data[1];
        // for(int i = 0 ; i < read_data_length-2 ; i++)
        // {
        //     read_data[i]=read_data[i+2];
        // }
        //memcpy(read_data, read_data + 2, read_data_length - 2);
        new_data_to_read = 1;                   //Set the flag that indicates this.
        return 1;
    }
    else return 0;
    //read_data_length = read_data_length - 2;       
    
    //RFM69_ClearFIFO();                          //Clear the chip FIFO.
}

int8_t Sending_Available(void)
{
    if (tx_right == TX_NO_ACK)
    {
        tx_right = TX_AVAILABLE;
        return TX_NO_ACK;
    }
    else
    return tx_right;
}

uint8_t Data_Available(void)
{
    if (new_data_to_read)
    {
        new_data_to_read = 0;
        return 1;
    }
    return 0;
}

uint8_t Read_Data(uint8_t* data)
{
    //memcpy(data, read_data, read_data_length);
    for(int i = 0 ; i < read_data_length-2 ; i++)
    {
        data[i]=read_data[i+2];
    }
    return read_data_length-2;
}

void FSK_Sleep(void)
{
    SleepFlag = 1;
}

void FSK_WakeUp(void)
{
    SleepFlag = -1;
}

void FSK_Poll(void)
{
	static int8_t estadoRf = RF_WAIT;
	static int8_t estadoRx = RX_IN;
    static int8_t estadoTx = TX_IN;
	
    static uint8_t txRetries = 0;
    static uint32_t txCRCTimeOut = 0;
	static uint32_t txSendingTimeOut = 0;
    static uint8_t rxACKcount = 0;
    
    uint16_t radioStatus;

	radioStatus = RFM69_getStatus();

	switch (estadoRf)
	{
		case RF_SLEEP:
		{
            switch (SleepFlag)
            {
            case 1:
                SleepFlag = 0;
                break;
            case -1:
                SleepFlag = 0;
                estadoRf = RF_WAIT;
                RFM69_EntryRx();
                #ifdef event_wakeupFSK_active
				wakeupFSK();
				#endif 
                break;
            default:
                break;
            }
			break;
		}
		case RF_WAIT:
		{
            if (SleepFlag == 1)
            {
                SleepFlag = 0;
                estadoRf = RF_SLEEP;
                RFM69_Sleep();
                #ifdef event_sleepFSK_active
				sleepFSK();
				#endif 
            }
			else if (RFM69_isPayloadReady(radioStatus)) 	    //Is there a message?
			{           
				estadoRf = RF_RX;					            //Reads data.
			} else if (tx_pending_data)				            //If not, and if there is data to send.
            {           
                estadoRf = RF_TX;					            //Sends data.
            }
            break;
        }
		case RF_TX:
		{
			switch(estadoTx)
			{
				case TX_IN:
				{
                    RFM69_EntryStandby();
                    __delay_ms(1);
                    RFM69_Transmit(message, message_length);    //Put the new message in the chip´s FIFO.
					RFM69_EntryTx();                            //Put the chip in TX mode.
                    estadoTx = TX_SENDING_DATA;                 //Changes to the next state.
                    txSendingTimeOut = timeStamp;               //Save the current time to avoid freezing caused by incorrect FIFO data.
					break;
				}
				case TX_SENDING_DATA:
				{
					if (RFM69_isPacketSent(radioStatus))        //ACA HAY UN PROBLEMA
					{
                        RFM69_EntryRx();                        //Put the chip in RX mode.
						estadoTx = TX_WAITING_ACK;              //Goes to the next state.
                        txCRCTimeOut = timeStamp;               //Set the current time for time out control.
					}
                    break;
				}
                case TX_WAITING_ACK:
                {
                    if (RFM69_isCrcOk(radioStatus)) 	        //Is there a CRC OK?
			        {
                        RFM69_ClearFIFO();                      //Clear the chip FIFO.
                        estadoTx = TX_IN;                       //Reinitialize the TX states machine.
                        estadoRf = RF_WAIT;                     //Go to the stable state.
						tx_pending_data = 0;                    //Clear the flag that indicates that there are sending data.
                        tx_right = TX_AVAILABLE;
                        txRetries = 0;
                    }
                    else if (timeStamp - txCRCTimeOut > 25)     //Is timeOut?   
                    {
                        if (txRetries < 10)                     //Are there retries left?
                        {
                            txRetries++;                        //Try a new retry.
                            estadoTx = TX_IN;                   //Goes to the first state.                   
                        }
                        else                                    
                        {
                            txRetries = 0;                      //Clear the number of tries.
                            estadoTx = TX_IN;                   //Reinitialize the TX states machine.           
                            estadoRf = RF_WAIT;                 //Go to the stable state.
                            tx_pending_data = 0;                //Clear the flag that indicates that there are sending data.
                            tx_right = TX_NO_ACK;               //Set the flag that indicates that an error occurs.
                        }
                    }
                }
			}			
			break;
		}
        case RF_RX:
        {
			switch (estadoRx)
            {
                case RX_IN:
                {
                    if(ReadFSKMessage())						//Executes the event.
                    {
                        estadoRx = RX_SEND_ACK_IN;                  //Changes to the next state.
                        rxACKcount = 0;

                    }
                    else
                    {
                        estadoRf = RF_WAIT;	                    //Go to the stable state.
                    }
                    RFM69_ClearFIFO();                      //Clear the chip FIFO.
                    break;
                }
                case RX_SEND_ACK_IN:
                {
                    if (rxACKcount < 3)
                    {
                        rxACKcount++;
                        RFM69_EntryStandby();
                        __delay_ms(1);
                        RFM69_Transmit(&idGrupo, 1);            //Sending a CRC OK.
                        RFM69_EntryTx();                        //Put the chip in TX mode.
                        estadoRx = RX_SENDING_ACK;              //Changes to the next state.
                    }
                    else if (RFM69_isPacketSent(radioStatus))        //Was the CRC OK message sent?
                    {
                        RFM69_EntryRx();                        //Put the chip in RX mode.
                        estadoRx = RX_IN;                       //Reinitilize the RX states machine.
                        estadoRf = RF_WAIT;	                    //Go to the stable state.
                    }
                    break;
                }
                case RX_SENDING_ACK:
                {
                    if (RFM69_isPacketSent(radioStatus))        //Was the CRC OK message sent?
                    {
                        //RFM69_EntryRx();                        //Put the chip in RX mode.
                        estadoRx = RX_SEND_ACK_IN;                       //Reinitilize the RX states machine.
                        //estadoRf = RF_WAIT;	                    //Go to the stable state.
                    }
                    break;
                }
            }
        }
    }
}

#endif