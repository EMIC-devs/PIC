#include "inc/streamIn.h"

float streamIn_t_ptr_to_float(streamIn_t* dataIn)
{
    char str[16];
    char* strPtr = str;
    int i;
    for (i = 0 ; i < 16 && dataIn->count() ; i ++)
    {
        *strPtr = dataIn->get();
        strPtr ++;
    }
    *strPtr = 0;

    return (float)atof(str);

}

char streamIn_t_ptr_to_char(streamIn_t* dataIn)
{
    char str[16];
    char* strPtr = str;
    int i;
    for (i = 0 ; i < 16 && dataIn->count() ; i ++)
    {
        *strPtr = dataIn->get();
        strPtr ++;
    }
    *strPtr = 0;

    return str[0];
}

uint8_t streamIn_t_ptr_to_uint8_t(streamIn_t* dataIn)
{
    char str[16];
    char* strPtr = str;
    int i;
    for (i = 0 ; i < 16 && dataIn->count() ; i ++)
    {
        *strPtr = dataIn->get();
        strPtr ++;
    }
    *strPtr = 0;

    return ato_uint8_t(str);
}

uint16_t streamIn_t_ptr_to_uint16_t(streamIn_t* dataIn)
{
    char str[16];
    char* strPtr = str;
    int i;
    for (i = 0 ; i < 16 && dataIn->count() ; i ++)
    {
        *strPtr = dataIn->get();
        strPtr ++;
    }
    *strPtr = 0;

    return ato_uint16_t(str);

}

uint32_t streamIn_t_ptr_to_uint32_t(streamIn_t* dataIn)
{
    char str[16];
    char* strPtr = str;
    int i;
    for (i = 0 ; i < 16 && dataIn->count() ; i ++)
    {
        *strPtr = dataIn->get();
        strPtr ++;
    }
    *strPtr = 0;

    return ato_uint32_t(str);

}

uint64_t streamIn_t_ptr_to_uint64(streamIn_t* dataIn)
{
    char str[16];
    char* strPtr = str;
    int i;
    for (i = 0 ; i < 16 && dataIn->count() ; i ++)
    {
        *strPtr = dataIn->get();
        strPtr ++;
    }
    *strPtr = 0;

    return ato_uint64_t(str);

}

int8_t streamIn_t_ptr_to_int8_t(streamIn_t* dataIn)
{
    char str[16];
    char* strPtr = str;
    int i;
    for (i = 0 ; i < 16 && dataIn->count() ; i ++)
    {
        *strPtr = dataIn->get();
        strPtr ++;
    }
    *strPtr = 0;

    return ato_int8_t(str);

}

int16_t streamIn_t_ptr_to_int16_t(streamIn_t* dataIn)
{
    char str[16];
    char* strPtr = str;
    int i;
    for (i = 0 ; i < 16 && dataIn->count() ; i ++)
    {
        *strPtr = dataIn->get();
        strPtr ++;
    }
    *strPtr = 0;

    return ato_int16_t(str);

}

int32_t streamIn_t_ptr_to_int32_t(streamIn_t* dataIn)
{
    char str[16];
    char* strPtr = str;
    int i;
    for (i = 0 ; i < 16 && dataIn->count() ; i ++)
    {
        *strPtr = dataIn->get();
        strPtr ++;
    }
    *strPtr = 0;

    return ato_int32_t(str);

}

int64_t streamIn_t_ptr_to_int64_t(streamIn_t* dataIn)
{
    char str[16];
    char* strPtr = str;
    int i;
    for (i = 0 ; i < 16 && dataIn->count() ; i ++)
    {
        *strPtr = dataIn->get();
        strPtr ++;
    }
    *strPtr = 0;

    return ato_int64_t(str);

}


void streamIn_t_ptr_to_ascii(streamIn_t* dataIn,char* string,int count)
{
    char* strPtr = string;
    int i;
    for (i = 0 ; i < count && dataIn->count() ; i ++)
    {
        *strPtr = dataIn->get();
        strPtr ++;
    }
    *strPtr = 0;
}


void sendDataToStream(const streamOut_t* stream, char* format_,va_list arg)
{
    char* format = format_;
	int i;
	char strFormat[10];
	char auxStr[20];
	int okFormat = 0;
	
    //stream->put(tipoTrama_mensaje);

 	for (; *format > 0; format++)
	{
		if ( *format == '%' )
		{
			char* str;
			okFormat = 0;
            uint16_t typeSelector = 16;
			for (i = 0; !okFormat; format++, i++)
			{
				strFormat[i] = *format;
			
				switch (*format)
				{

                    case 'l':
                        typeSelector <<= 1;
                        break;
                    case 'h':
                        typeSelector >>= 1;
                        break;


                    case 'u':
                        okFormat = 1;
                        strFormat[i + 1] = 0;
                        switch (typeSelector)
                        {
                            case 8:
                            {
                                uint8_t* auxPtr;
                                auxPtr = va_arg(arg, uint8_t*);
                                sprintf(auxStr,strFormat,*auxPtr);
                                break;
                            }

                            case 16:
                            {
                                uint16_t* auxPtr;
                                auxPtr = va_arg(arg, uint16_t*);
                                sprintf(auxStr,strFormat,*auxPtr);
                                break;
                            }

                            case 32:
                            {
                                uint32_t* auxPtr;
                                auxPtr = va_arg(arg, uint32_t*);
                                sprintf(auxStr,strFormat,*auxPtr);
                                break;
                            }


                            case 64:
                            {
                                uint64_t* auxPtr;
                                auxPtr = va_arg(arg, uint64_t*);
                                sprintf(auxStr,strFormat,*auxPtr);
                                break;
                            }
                        }
                        break;


                    case 'd':
                        okFormat = 1;
                        strFormat[i + 1] = 0;
                        switch (typeSelector)
                        {
                            case 8:
                            {
                                int8_t* auxPtr;
                                auxPtr = va_arg(arg, int8_t*);
                                sprintf(auxStr,strFormat,*auxPtr);
                                break;
                            }
                            case 16:
                            {
                                int16_t* auxPtr;
                                auxPtr = va_arg(arg, int16_t*);
                                sprintf(auxStr,strFormat,*auxPtr);
                                break;
                            }
                            case 32:
                            {
                                int32_t* auxPtr;
                                auxPtr = va_arg(arg, int32_t*);
                                sprintf(auxStr,strFormat,*auxPtr);
                                break;
                            }
                            case 64:
                            {
                                int64_t* auxPtr;
                                auxPtr = va_arg(arg, int64_t*);
                                sprintf(auxStr,strFormat,*auxPtr);
                                break;
                            }
                        }
                        break;



                    case 'f':
                        okFormat = 1;
                        strFormat[i + 1] = 0;
                        switch (typeSelector)
                        {
                            case 16:
                            {
                                float* auxPtr;
                                auxPtr = va_arg(arg, float*);
                                sprintf(auxStr,strFormat,*auxPtr);
                                break;
                            }
                            case 32:
                            {
                                double* auxPtr;
                                auxPtr = va_arg(arg, double*);
                                sprintf(auxStr,strFormat,*auxPtr);
                                break;  
                            }
                        }
                        break;
				}
			}
			
            str = auxStr;
			while (*str)
			{
				stream->put( *str++);
			}
			format--;
			continue;
			// break;   Se intrrumpe el ciclo principal
		}
		else if ( *format == '$' )
		{
			char* str; 
			streamIn_t* dataIn;
			format++;
			switch (*format)
			{
				case 's':
					str = va_arg(arg, char*);
					while (*str)
					{
						stream->put( *str++);
					}
					break;
				case 'r':
					dataIn = va_arg(arg, streamIn_t*);
					while (dataIn->count())
					{
						stream->put( dataIn->get());
					}
					break;
				default:
					stream->put(*format);
					break;

			}
		}
		else
		{
			stream->put(*format);
		}
	}
	//stream->put(0);
}