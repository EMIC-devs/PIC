#include "inc/stream.h"

void streamPushCtr(stream_t* stream, unsigned char dato)
{
    if (dato == stream->frame_indentifier)
    {
        streamOpenWriteFrame(stream);
    }
    else{
        stream->data_fifo[stream->data_idx_entr] = dato;
        stream->data_idx_entr ++;
        stream->data_count_entr ++;

        stream->data_idx_entr &= stream->data_idx_mask;
        //  stream->data_count &= stream->data_idx_mask; prevenir que con se desborde
    }
}

void streamPush(stream_t* stream, unsigned char dato)
{

    stream->data_fifo[stream->data_idx_entr] = dato;
    stream->data_idx_entr ++;
    stream->data_count_entr ++;

    stream->data_idx_entr &= stream->data_idx_mask;
        //  stream->data_count &= stream->data_idx_mask; prevenir que con se desborde
}


unsigned char streamPop(stream_t* stream)
{
    unsigned char dato;
    dato = stream->data_fifo[stream->data_idx_sal];
    stream->data_idx_sal ++;
    stream->data_count_sal --;
    stream->data_idx_sal &= stream->data_idx_mask;
    return dato;
}


void streamOpenWriteFrame(stream_t* stream)
{
        stream->frame_fifo[stream->frame_idx_entr] = stream->data_count_entr;
        stream->frame_idx_entr ++;
        stream->frame_count ++;
        stream->data_count_entr = 0;
        stream->frame_idx_entr &= stream->frame_idx_mask;
        // stream->frame_count &= stream->frame_idx_mask;
}

void streamOpenReadFrame(stream_t* stream)
{
    
    stream->data_count_sal = stream->frame_fifo[stream->frame_idx_sal];

    stream->data_idx_sal_aux = stream->data_idx_sal;
    stream->data_count_sal_aux = stream->data_count_sal;


    stream->frame_idx_sal ++;
    stream->frame_count --;

    stream->frame_idx_sal &= stream->frame_idx_mask;

}

void streamReOpenReadFrame(stream_t* stream)
{

    stream->data_idx_sal = stream->data_idx_sal_aux;
    stream->data_count_sal = stream->data_count_sal_aux;    
}

void streamCloseReadFrame(stream_t* stream)
{
    stream->data_idx_sal += stream->data_count_sal;
    stream->data_idx_sal &= stream->data_idx_mask;

    stream->data_count_sal = 0;
}