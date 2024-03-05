/*************************************************************************//**

  @file     stream.h

  @brief    Util Stream Library

  @author   Pentacolo Tomas

  @date     30/03/2023

  @version  v0.0.1   Initial release.
 ******************************************************************************/


typedef struct stream_S
{
  uint16_t data_idx_entr;
  uint16_t data_idx_sal;
  uint16_t data_idx_sal_aux;
  uint16_t data_count_entr;
  uint16_t data_count_sal;
  uint16_t data_count_sal_aux;
  uint16_t frame_idx_entr;
  uint16_t frame_idx_sal;
  uint16_t frame_count;
  uint16_t* frame_fifo;
  unsigned char*  data_fifo;
  const char frame_indentifier;
  const uint16_t data_idx_mask;
  const uint16_t frame_idx_mask;

} stream_t;

void streamPushCtr(stream_t* stream, unsigned char dato);
void streamPush(stream_t* stream, unsigned char dato);
unsigned char streamPop(stream_t* stream);
void streamOpenWriteFrame(stream_t* stream);
void streamOpenReadFrame(stream_t* stream);
void streamReOpenReadFrame(stream_t* stream);
void streamCloseReadFrame(stream_t* stream);