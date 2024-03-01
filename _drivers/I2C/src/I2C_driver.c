/*************************************************************************//**
  @file     I2C_driver.c

  @brief    Driver Library to use I2C

  @author   Tomas Pentacolo (TP)

  @date     29/02/2024

  @version  v0.0.1 - Initial release.
 ******************************************************************************/

#ifndef __DRIVER_I2C.{port}._C__
#define __DRIVER_I2C.{port}._C__

/*==================[inclusions]=============================================*/

#include <inc/I2C.{port}._driver.h>
#include <inc/stream.h>

/*==================[internal data declaration]==============================*/

static unsigned char i2cInDataBuffer[MAX_I2C_IN];
static unsigned char i2cOutDataBuffer[MAX_I2C_OUT];

static uint16_t i2cInFrameBuffer[FrameQty];
static uint16_t i2cOutFrameBuffer[FrameQty];

stream_t i2c.{port}.InStream = 
{
	.data_idx_entr = 0,
	.data_idx_sal = 0,
	.data_idx_sal_aux = 0,
	.data_count_entr = 0,
	.data_count_sal = 0,
	.data_count_sal_aux = 0,
	.frame_idx_entr = 0,
	.frame_idx_sal = 0,
	.frame_count = 0,
	.frame_fifo 	= i2cInFrameBuffer,
	.data_fifo 	= i2cInDataBuffer,
	.frame_indentifier = i2c_frame_indentifier,
	.data_idx_mask = MAX_I2C_IN-1,
	.frame_idx_mask = FrameQty-1
};

stream_t i2c.{port}.OutStream = 
{
	.data_idx_entr = 0,
	.data_idx_sal = 0,
	.data_idx_sal_aux = 0,
	.data_count_entr = 0,
	.data_count_sal = 0,
	.data_count_sal_aux = 0,
	.frame_idx_entr = 0,
	.frame_idx_sal = 0,
	.frame_count = 0,
	.frame_fifo 	= i2cOutFrameBuffer,
	.data_fifo 	= i2cOutDataBuffer,
	.frame_indentifier = i2c_frame_indentifier,
	.data_idx_mask = MAX_I2C_OUT-1,
	.frame_idx_mask = FrameQty-1
};

static const i2c_config_t i2c_init_structure = {
    .mode = 1,                  //master mode
    .frec = 400,                //400 KHz
    .address = 'M',             //Own address
    .i2c_channel = .{port}.,    //i2c_channel
    .en_interrupt = 1,          //enable interrupt
    .pull_up = 0                //disable pull up
};

static char i2crfi_estado = I2C_ESTADO_IDLE;
static char i2crfi_estado_rcv = I2C_ESTADO_RCV_IDLE;
static char i2crfi_indice = 0; // to send the frame head
static uint8_t stopflag = 0;

const streamIn_t  streamIn_I2C = {getI2cStreamIn,countI2cStreamIn};
const streamOut_t streamOut_I2C = {setI2cStreamOut,getAvailable_out_count}; //Count not tested

/*==================[internal functions implementations]======================*/

/**
 * @brief Initializes the I2C driver.
 *
 * This function initializes the I2C driver using a predefined
 * initialization structure.
 *
 * @return None
 */
void Init_I2C_Driver(void)
{
	Init_I2C(i2c_init_structure);
}

/**
 * @brief Gets the available count of output data.
 *
 * This function calculates and returns the available count of output data.
 * The calculation is based on the maximum number of I2C output data and the
 * current data indices of the output stream.
 *
 * @note This function has not been tested.
 *
 * @return The available count of output data.
 */
uint16_t getAvailable_out_count(void) //Not Tested
{
    return MAX_I2C_OUT - ( (MAX_I2C_OUT-1) & (i2cOutStream.data_idx_sal - i2cOutStream.data_idx_entr ) );
}

/**
 * @brief Counts the number of elements in the I2C input stream.
 *
 * This function counts the number of elements in the I2C input stream.
 *
 * @return The count of elements in the I2C input stream.
 */
uint16_t countI2cStreamIn(void)
{
	return i2c.{port}.InStream.data_count_sal;
}

/**
 * @brief Retrieves a character from the I2C input stream.
 *
 * This function retrieves a character from the I2C input stream.
 *
 * @return The character retrieved from the I2C input stream.
 */
char getI2cStreamIn(void)
{
	return pop_I2C_IN();
}

/**
 * @brief Sets a character into the I2C output stream.
 *
 * This function sets a character into the I2C output stream.
 *
 * @param data The character to be set into the I2C output stream.
 * @return None
 */
void setI2cStreamOut(char data)
{
	push_I2C_OUT(data);
}

/**
 * @brief Initiates an I2C transmission.
 *
 * This function initiates an I2C transmission if the I2C start condition
 * has not already been set.
 *
 * @note This function assumes the presence of an I2C initialization structure.
 *       It also initializes the I2C transmission process.
 *
 * @return None
 */
void I2C_Begin_Transmision(void)
{
	if (!IsI2cStart(i2c_init_structure))
	{
		{
			streamOpenReadFrame(&i2c.{port}.OutStream);
			i2crfi_indice = -2;// pongo el indice en -2 para mandar los 2 bytes del id del modulo
			i2crfi_estado = I2C_ESTADO_SENDING;
			Start_I2C(i2c_init_structure);
		}
	}
}

/**
 * @brief Initializes the input stream of the I2C module.
 *
 * This function initializes various parameters of the input stream
 * of the I2C module for a specific port.
 *
 * @return None
 */
void ini_I2C_IN(void)
{
	i2c.{port}.InStream.data_idx_entr 		= 0;
	i2c.{port}.InStream.data_idx_sal 		= 0;
	i2c.{port}.InStream.data_idx_sal_aux 	= 0;
	i2c.{port}.InStream.data_count_entr 	= 0;
	i2c.{port}.InStream.data_count_sal 		= 0;
	i2c.{port}.InStream.data_count_sal_aux 	= 0;
	i2c.{port}.InStream.frame_idx_entr 		= 0;
	i2c.{port}.InStream.frame_idx_sal 		= 0;
	i2c.{port}.InStream.frame_count		 	= 0;
}

/**
 * @brief Initializes the output stream of the I2C module.
 *
 * This function initializes various parameters of the output stream
 * of the I2C module for a specific port.
 *
 * @return None
 */
void ini_I2C_OUT(void)
{
	i2c.{port}.OutStream.data_idx_entr 		= 0;
	i2c.{port}.OutStream.data_idx_sal 		= 0;
	i2c.{port}.OutStream.data_idx_sal_aux 	= 0;
	i2c.{port}.OutStream.data_count_entr 	= 0;
	i2c.{port}.OutStream.data_count_sal 	= 0;
	i2c.{port}.OutStream.data_count_sal_aux = 0;
	i2c.{port}.OutStream.frame_idx_entr 	= 0;
	i2c.{port}.OutStream.frame_idx_sal 		= 0;
	i2c.{port}.OutStream.frame_count 		= 0;
}

/**
 * @brief Initializes the frame count of the output stream of the I2C module.
 *
 * This function initializes the frame count of the output stream
 * of the I2C module for a specific port to zero.
 *
 * @return None
 */
void ini_I2C_OUT_FM(void)
{
	i2c.{port}.OutStream.frame_count = 0;
}

/**
 * @brief Resets the I2C frame parameters.
 *
 * This function resets the I2C frame parameters of the output stream
 * for a specific port by restoring the previous indices and counts.
 *
 * @return None
 */
void reset_I2C_FRAME(void)
{
	i2c.{port}.OutStream.data_idx_sal = i2c.{port}.OutStream.data_idx_sal_aux;
    i2c.{port}.OutStream.data_count_sal = i2c.{port}.OutStream.data_count_sal_aux; 
}

/**
 * @brief Pushes data into the I2C input stream.
 *
 * This function pushes data into the I2C input stream for a specific port.
 * It also manages the data count and index of the input stream.
 *
 * @param dato The data to be pushed into the I2C input stream.
 * @return None
 */
void push_I2C_IN(char dato)
{
	if (dato == i2c_frame_indentifier && i2c.{port}.InStream.data_count_entr)
	{
		i2cCloseWriteFrame(&i2c.{port}.InStream);
		return;
	}
	i2c.{port}.InStream.data_fifo[i2c.{port}.InStream.data_idx_entr] = dato;
    i2c.{port}.InStream.data_idx_entr ++;
    i2c.{port}.InStream.data_count_entr ++;
    i2c.{port}.InStream.data_idx_entr &= i2c.{port}.InStream.data_idx_mask;
}

/**
 * @brief Pushes data into the I2C output stream.
 *
 * This function pushes data into the I2C output stream for a specific port.
 * It also manages the data count and index of the output stream.
 * If the pushed data is the frame identifier, it opens a new write frame.
 *
 * @param dato The data to be pushed into the I2C output stream.
 * @return None
 */
void push_I2C_OUT(char dato)
{
	i2c.{port}.OutStream.data_fifo[i2c.{port}.OutStream.data_idx_entr] = dato;
    i2c.{port}.OutStream.data_idx_entr ++;
    i2c.{port}.OutStream.data_count_entr ++;
    i2c.{port}.OutStream.data_idx_entr &= i2c.{port}.OutStream.data_idx_mask;
	if (dato == i2c_frame_indentifier)
	{
		streamOpenWriteFrame(&i2c.{port}.OutStream);
	}
}

/**
 * @brief Pops data from the I2C input stream.
 *
 * This function pops data from the I2C input stream for a specific port.
 * It also manages the data count and index of the input stream.
 *
 * @return The popped data from the I2C input stream.
 */
char pop_I2C_IN(void)
{
	unsigned char dato;
    dato = i2c.{port}.InStream.data_fifo[i2c.{port}.InStream.data_idx_sal];
    i2c.{port}.InStream.data_idx_sal ++;
    i2c.{port}.InStream.data_count_sal --;
    i2c.{port}.InStream.data_idx_sal &= i2c.{port}.InStream.data_idx_mask;
    return dato;
}

/**
 * @brief Pops data from the I2C output stream.
 *
 * This function pops data from the I2C output stream for a specific port.
 * It also manages the data count and index of the output stream.
 *
 * @return The popped data from the I2C output stream.
 */
char pop_I2C_OUT(void)
{
    unsigned char dato;
    dato = i2c.{port}.OutStream.data_fifo[i2c.{port}.OutStream.data_idx_sal];
    i2c.{port}.OutStream.data_idx_sal ++;
    i2c.{port}.OutStream.data_count_sal --;
    i2c.{port}.OutStream.data_idx_sal &= i2c.{port}.OutStream.data_idx_mask;
    return dato;
}

/**
 * @brief Pops all data from the I2C output stream.
 *
 * This function pops all data from the I2C output stream for a specific port.
 *
 * @return None
 */
void pop_I2C_OUT_FM(void)
{
	while(i2c.{port}.OutStream.data_count_sal)
	{
		pop_I2C_OUT();
	}	
}

/**
 * @brief Closes the write frame of a stream.
 *
 * This function closes the write frame of a stream by updating
 * various parameters such as the frame count and index.
 *
 * @param stream Pointer to the stream structure.
 * @return None
 */
void i2cCloseWriteFrame(stream_t* stream)
{
        stream->frame_fifo[stream->frame_idx_entr] = stream->data_count_entr;
        stream->frame_idx_entr ++;
        stream->frame_count ++;
        stream->data_count_entr = 0;
        stream->frame_idx_entr &= stream->frame_idx_mask;
}

/**
 * @brief Opens a read frame of a stream.
 *
 * This function opens a read frame of a stream by updating
 * various parameters such as the data count and index.
 *
 * @param stream Pointer to the stream structure.
 * @return None
 */
void i2cOpenReadFrame(stream_t* stream)
{
    stream->data_count_sal = stream->frame_fifo[stream->frame_idx_sal];
    stream->data_idx_sal_aux = stream->data_idx_sal;
    stream->data_count_sal_aux = stream->data_count_sal;
    stream->frame_idx_sal ++;
    stream->frame_count --;
    stream->frame_idx_sal &= stream->frame_idx_mask;
}

/**
 * @brief Interrupt Service Routine for I2C Slave callback.
 *
 * This ISR handles the I2C Slave callback for a specific port.
 * It reads data from the I2C receive buffer and processes it according
 * to the current state of the I2C reception process.
 *
 * @return None
 */
void ISR_I2C.{port}._SLAVE_CALLBACK(void)
{
	uint8_t d;

	_SI2C.{port}.IF = 0;

	if (IsI2cReceiveBufferFull(i2c_init_structure))
	{
		d = Read_I2C(i2c_init_structure,0);

		if (!IsI2cDataOrAddress(i2c_init_structure))
		{
			i2crfi_estado_rcv = I2C_ESTADO_RCV_ID; //I2C_ESTADO_PKT_ID;
			return;
		}
		else if (i2crfi_estado_rcv == I2C_ESTADO_RCV_ID)
		{
			if ( d != I2C_ID )
			{
				i2crfi_estado_rcv = I2C_ESTADO_RCV_DATA;
			}
			else
			{	
				i2crfi_estado_rcv = I2C_ESTADO_RCV_IDLE;
			}
		}
		else if (i2crfi_estado_rcv == I2C_ESTADO_RCV_DATA)
		{
			push_I2C_IN(d);
		}	
	}	
}

/**
 * @brief Interrupt Service Routine for I2C1 Master callback.
 *
 * This ISR handles the I2C1 Master callback.
 * It checks for various conditions such as collision detection, stop condition,
 * and start condition, and performs corresponding actions accordingly.
 *
 * @return None
 */
void ISR_I2C1_MASTER_CALLBACK(void)
{
	_MI2C.{port}.IF = 0;

	if (IsI2cCollisionDetect(i2c_init_structure))
	{
		CollisionReset_I2C(i2c_init_structure);
		i2crfi_estado = I2C_ESTADO_IDLE;
		reset_I2C_FRAME();
		return;
	}	

	if (IsI2cStop(i2c_init_structure))
	{
		i2crfi_estado= I2C_ESTADO_IDLE;
		return;
	}
	if (IsI2cStart(i2c_init_structure))
	{
		if (i2crfi_estado == I2C_ESTADO_SENDING)
		{
			if (i2crfi_indice == -2) //-3)
			{
				Write_I2C(0,i2c_init_structure);
				i2crfi_indice++;
			}	
			else if (i2crfi_indice == -1)
			{
				Write_I2C(I2C_ID,i2c_init_structure);
				i2crfi_indice++;
			}	
			else
			{
				char d;
				d =  pop_I2C_OUT();
				if (d == i2c_frame_indentifier)
				{
					i2crfi_estado = I2C_ESTADO_END;
				}
				Write_I2C(d,i2c_init_structure);
			}				
		}
		else if (i2crfi_estado == I2C_ESTADO_END)
		{
			i2crfi_estado = I2C_ESTADO_IDLE;
			stopflag=1;
			Stop_I2C(i2c_init_structure);
		}
	}		
}	

/*==================[end of file]============================================*/
#endif