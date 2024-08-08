/*************************************************************************//**
  @file     LTC2500.h

  @brief    Driver Library to use LTC 2500 ADC

  @author   Rottoli Luciano

  @date     10/07/2024

  @version  v0.0.1 - Initial release.
 ******************************************************************************/

#ifndef __LTC2500_H__
#define __LTC2500_H__

/*==================[inclusions]=============================================*/
#include <xc.h>

/**
 * @union LT2500_32_CONTW
 * @brief Union for the configuration word.
 * 
 * This union represents the 16-bit configuration word for the LTC2500 ADC.
 */
union LT2500_32_CONTW{
    uint16_t all_bits; // Represents the 16 bits as a single integer
    struct {
        uint16_t padding : 4;              // 4 bits padding (not sent)
        uint16_t FILTER_TYPE : 4;          // Bits [3:0]
        uint16_t DOWN_SAMPLING_FACTOR : 4; // Bits [7:4]
        uint16_t DGC : 1;                  // Bit 8
        uint16_t DGE : 1;                  // Bit 9
        uint16_t c10 : 1;                  // Bit 10
        uint16_t c11 : 1;                  // Bit 11 (más significativo)           
    } bits;
};
extern union LT2500_32_CONTW LTC2500Config;
/**
 * @struct LTC2500ConfigWord
 * @brief Structure for the 8-bit configuration word.
 * 
 * This structure defines the 8-bit configuration word for the LTC2500 ADC.
 */
typedef struct {
    uint8_t filter_type : 4;             // The 4 least significant bits
    uint8_t downsampling_factor : 4;     // The 4 most significant bits
} LTC2500ConfigWord;

/**
 * @struct LTC2500Result
 * @brief Structure for the total 40 bits.
 * 
 * This structure defines the 40-bit result for the LTC2500 ADC, including 32 data bits and 8 configuration bits.
 */
typedef struct {
    uint32_t data;              // 32 data bits
    LTC2500ConfigWord config;   // 8 configuration bits
} LTC2500Result;

/** 
 * @defgroup FilterTypeMacros Macros for FILTER TYPE (C[3:0])
 * @{
 */
#define SET_FILTER_TYPE_SINC1(contw)      (contw.bits.FILTER_TYPE = 0x1) // Set filter type to SINC1
#define SET_FILTER_TYPE_SINC2(contw)      (contw.bits.FILTER_TYPE = 0x2) // Set filter type to SINC2
#define SET_FILTER_TYPE_SINC3(contw)      (contw.bits.FILTER_TYPE = 0x3) // Set filter type to SINC3
#define SET_FILTER_TYPE_SINC4(contw)      (contw.bits.FILTER_TYPE = 0x4) // Set filter type to SINC4
#define SET_FILTER_TYPE_SSINC(contw)      (contw.bits.FILTER_TYPE = 0x5) // Set filter type to SSINC
#define SET_FILTER_TYPE_FLAT_PASSBAND(contw) (contw.bits.FILTER_TYPE = 0x6) // Set filter type to Flat Passband
#define SET_FILTER_TYPE_AVERAGING(contw)  (contw.bits.FILTER_TYPE = 0x7) // Set filter type to Averaging
/** @} */

/** 
 * @defgroup DownSamplingFactorMacros Macros for DOWN SAMPLING FACTOR (C[7:4])
 * @{
 */
#define SET_DF_4(contw)       (contw.bits.DOWN_SAMPLING_FACTOR = 0x2) // Set downsampling factor to 4
#define SET_DF_8(contw)       (contw.bits.DOWN_SAMPLING_FACTOR = 0x3) // Set downsampling factor to 8
#define SET_DF_16(contw)      (contw.bits.DOWN_SAMPLING_FACTOR = 0x4) // Set downsampling factor to 16
#define SET_DF_32(contw)      (contw.bits.DOWN_SAMPLING_FACTOR = 0x5) // Set downsampling factor to 32
#define SET_DF_64(contw)      (contw.bits.DOWN_SAMPLING_FACTOR = 0x6) // Set downsampling factor to 64
#define SET_DF_128(contw)     (contw.bits.DOWN_SAMPLING_FACTOR = 0x7) // Set downsampling factor to 128
#define SET_DF_256(contw)     (contw.bits.DOWN_SAMPLING_FACTOR = 0x8) // Set downsampling factor to 256
#define SET_DF_512(contw)     (contw.bits.DOWN_SAMPLING_FACTOR = 0x9) // Set downsampling factor to 512
#define SET_DF_1024(contw)    (contw.bits.DOWN_SAMPLING_FACTOR = 0xA) // Set downsampling factor to 1024
#define SET_DF_2048(contw)    (contw.bits.DOWN_SAMPLING_FACTOR = 0xB) // Set downsampling factor to 2048
#define SET_DF_4096(contw)    (contw.bits.DOWN_SAMPLING_FACTOR = 0xC) // Set downsampling factor to 4096
#define SET_DF_8192(contw)    (contw.bits.DOWN_SAMPLING_FACTOR = 0xD) // Set downsampling factor to 8192
#define SET_DF_16384(contw)   (contw.bits.DOWN_SAMPLING_FACTOR = 0xE) // Set downsampling factor to 16384
/** @} */

/** 
 * @defgroup DGCEMacros Macros for DCE (C[8])
 * @{
 */
#define SET_DGE_OFF(contw)    (contw.bits.DGC = 0) // Disable DGE
#define SET_DGE_ON(contw)     (contw.bits.DGC = 1) // Enable DGE
/** @} */

/** 
 * @defgroup DGCMacros Macros for DGC (C[9])
 * @{
 */
#define SET_DGC_OFF(contw)    (contw.bits.DGE = 0) // Disable DGC
#define SET_DGC_ON(contw)     (contw.bits.DGE = 1) // Enable DGC
/** @} */


/**
 * @brief Initializes the LTC2500 ADC.
 *
 * This function configures the GPIO pins and initializes the SPI port
 * for communication with the LTC2500 ADC.
 */
void LTC2500_init(void);

/**
 * @brief Reads a result from the LTC2500 ADC.
 *
 * This function reads 5 bytes from the SPI port and constructs a 
 * 32-bit data word and an 8-bit configuration word.
 *
 * @return A LTC2500Result structure containing the read data and configuration.
 */
LTC2500Result LTC2500_readFiltered(void);

/**
 * @brief Configures the LTC2500 ADC.
 *
 * This function splits the 16-bit configuration word into two bytes
 * and sends them via SPI.
 */
void LTC2500_SendConfig(void);

void LTC2500_StartConv(void);
uint8_t LTC2500_DRLStatus(void);

#endif  /* __LTC2500_H__ */