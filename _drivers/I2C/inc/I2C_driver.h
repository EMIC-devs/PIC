/*************************************************************************//**
  @file     I2C_driver.h

  @brief    Driver Library to use I2C

  @author   Tomas Pentacolo (TP)

  @date     29/02/2024

  @version  v0.0.1 - Initial release.
 ******************************************************************************/

#ifndef __DRIVER_I2C.{port}._H__
#define __DRIVER_I2C.{port}._H__

/*==================[inclusions]=============================================*/

/*==================[typedef]================================================*/

enum{
	I2C_ESTADO_IDLE,
	I2C_ESTADO_SENDING,
	I2C_ESTADO_END
};

enum{
	I2C_ESTADO_RCV_IDLE,
	I2C_ESTADO_PKT_ID,
	I2C_ESTADO_RCV_ID,
	I2C_ESTADO_RCV_DATA
};

#define i2c_frame_indentifier .{frameID}.

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

/*==================[internal functions declaration]===========================*/

void ISR_I2C.{port}._SLAVE_CALLBACK(void);
void ISR_I2C.{port}._MASTER_CALLBACK(void);

void 		Init_I2C_Driver(void);
void 		ini_I2C_IN(void);
void 		ini_I2C_OUT(void);
void 		ini_I2C_OUT_FM(void);
void 		push_I2C_IN(char dato);
void 		push_I2C_OUT(char dato);
char 		pop_I2C_IN(void);
char 		pop_I2C_OUT(void);
void 		pop_I2C_OUT_FM(void);
void 		reset_I2C_FRAME(void);
void 		I2C_Begin_Transmision(void);
uint16_t	countI2cStreamIn(void);
char 		getI2cStreamIn(void);
void		setI2cStreamOut(char);
uint16_t 	getAvailable_out_count(void);

void i2cCloseWriteFrame(stream_t* stream);
void i2cOpenReadFrame(stream_t* stream);

const streamIn_t  streamIn_I2C = {getI2cStreamIn,countI2cStreamIn};
const streamOut_t streamOut_I2C = {setI2cStreamOut,getAvailable_out_count}; //Count not tested

/*==================[end of file]============================================*/
#endif