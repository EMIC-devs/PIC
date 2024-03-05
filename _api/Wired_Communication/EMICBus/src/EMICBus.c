/*****************************************************************************
  @file     EMICBus.c

  @brief    API Library to use emic bus

  @author   Rottoli Luciano (based on Tomas Pentacolo)

  @date 	04/03/2024

  @version  v0.0.1
 ******************************************************************************/
 #include "inc/I2C_driver.h"
 #include "inc/streamIn.h"
 #include "inc/stream.h"

 enum
{
	tipoTrama_noUsar=0,
	tipoTrama_mensaje=1,
	tipoTrama_ejecutable=2,
	tipoTrama_control=3,
	tipoTrama_bootloader=4,
	tipoTrama_buffer=5
};

void pI2C(char* format_,...)
{
	va_list arg;
    va_start(arg, format_);
	push_I2C_OUT(tipoTrama_mensaje);

	sendDataToStream(&streamOut_I2C,format_,arg);

	va_end(arg);
	push_I2C_OUT(i2c_frame_indentifier);
}


/**
 * @brief	emicBus poll function
 * checks if a new frame was received or if it's time to start sending
 */
void poll_emicBus(void)
{
	char d;
	if(IsI2cReceiveOverflow(i2c_init_structure))//si hay un overflow lo resetea
	{
		OverflowReset_I2C(i2c_init_structure);
	}

	if (i2c.{port}.InStream.frame_count)
	{
		streamOpenReadFrame(&i2c.{port}.InStream);
		d=pop_I2C_IN();
		switch(d)
		{
			case tipoTrama_mensaje:;
			#ifdef event_I2CsetModoReceiveMensajeEvent_active				
				if (i2c.{port}.InStream.data_count_sal > 0)
				{
					char tag[20];
					char d;
					uint8_t i = 0;
					d = pop_I2C_IN();
					while (i2c.{port}.InStream.data_count_sal && d != '\t' && i < 20)
					{
						tag[i++] = d;
						d = pop_I2C_IN();
					}
					tag[i] = 0;
					eI2C(tag, &streamIn_I2C);
					while(i2c.{port}.InStream.data_count_sal)
					{
						pop_I2C_IN();
					}		
				}
			#else
			while (i2c.{port}.InStream.data_count_sal)
			{
				pop_I2C_IN();
			}
			#endif
				break;
			case tipoTrama_control:;
			if (i2c.{port}.InStream.data_count_sal > 0)
			{
				switch(pop_I2C_IN())
				{
					case 'R'://si es un reset
						//reset_cpu();
						break;
					default:
						while (i2c.{port}.InStream.data_count_sal)
							pop_I2C_IN();
					break;
				}
			}
				break;
			default:
				while (i2c.{port}.InStream.data_count_sal)
					pop_I2C_IN();
				break;
		}	
	}
	
	if(stopflag==1 && IsI2cStop(i2c_init_structure) )
	{
		stopflag=0;
		pop_I2C_OUT_FM();
	}
	if (i2c.{port}.OutStream.frame_count && (!IsI2cStart(i2c_init_structure)))
	{
		if(stopflag == 1)
		{
			stopflag=0;
			//pop_I2C_OUT_FM();
		}
		else
		{
			I2C_Begin_Transmision();
		}
	}
}