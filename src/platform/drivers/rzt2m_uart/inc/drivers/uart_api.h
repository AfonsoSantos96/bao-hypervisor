/** UART Configuration */
#include <stdint.h>
#include "bsp_module_stop.h"
#include "drivers/renesas.h"


#define BSP_FEATURE_SCI_UART_FIFO_CHANNELS             (0x3FFU)

#define FSP_HARDWARE_REGISTER_WAIT(reg, required_value)    while (reg != required_value) { /* Wait. */}

#ifndef BSP_CFG_IRQ_MASK_LEVEL_FOR_CRITICAL_SECTION
 #define BSP_CFG_IRQ_MASK_LEVEL_FOR_CRITICAL_SECTION    (0U)
#endif

#define FSP_CRITICAL_SECTION_SET_STATE            set_pmr


#define FSP_CRITICAL_SECTION_GET_CURRENT_STATE    get_pmr

#define FSP_CRITICAL_SECTION_IRQ_MASK_SET         ((uint8_t) (BSP_CFG_IRQ_MASK_LEVEL_FOR_CRITICAL_SECTION << 3U))

#define FSP_CRITICAL_SECTION_DEFINE              uint32_t old_mask_level = 0U

#ifndef FSP_CRITICAL_SECTION_ENTER
  #define FSP_CRITICAL_SECTION_ENTER                            \
     old_mask_level = FSP_CRITICAL_SECTION_GET_CURRENT_STATE(); \
     FSP_CRITICAL_SECTION_SET_STATE(FSP_CRITICAL_SECTION_IRQ_MASK_SET)
#endif


// /** This macro restores the previously saved interrupt state, reenabling interrupts. */
 #ifndef FSP_CRITICAL_SECTION_EXIT
  #define FSP_CRITICAL_SECTION_EXIT              FSP_CRITICAL_SECTION_SET_STATE(old_mask_level)
 #endif




// /*******************************************************************************************************************//**
//  * Cancels the module stop state.
//  *
//  * @param      ip       fsp_ip_t enum value for the module to be stopped
//  * @param      channel  The channel. Use channel 0 for modules without channels.
//  **********************************************************************************************************************/
 #define R_BSP_MODULE_START(ip, channel)            {FSP_CRITICAL_SECTION_DEFINE;                                   \
                                                     FSP_CRITICAL_SECTION_ENTER;                                    \
                                                     BSP_MSTP_REG_ ## ip(channel) &= ~BSP_MSTP_BIT_ ## ip(channel); \
                                                     BSP_MSTP_REG_ ## ip(channel);                                  \
                                                     BSP_MSTP_DMY_ ## ip(channel);                                  \
                                                     BSP_MSTP_DMY_ ## ip(channel);                                  \
                                                     BSP_MSTP_DMY_ ## ip(channel);                                  \
                                                     BSP_MSTP_DMY_ ## ip(channel);                                  \
                                                     BSP_MSTP_DMY_ ## ip(channel);                                  \
                                                     FSP_CRITICAL_SECTION_EXIT;}

 /*******************************************************************************************************************//**
  * Enables the module stop state.
  *
  * @param      ip       fsp_ip_t enum value for the module to be stopped
  * @param      channel  The channel. Use channel 0 for modules without channels.
  **********************************************************************************************************************/
 #define R_BSP_MODULE_STOP(ip, channel)             {FSP_CRITICAL_SECTION_DEFINE;                                  \
                                                     FSP_CRITICAL_SECTION_ENTER;                                    \
                                                     BSP_MSTP_REG_ ## ip(channel) |= BSP_MSTP_BIT_ ## ip(channel); \
                                                     BSP_MSTP_REG_ ## ip(channel);                                 \
                                                     FSP_CRITICAL_SECTION_EXIT;}



/** UART Data bit length definition */
typedef enum e_uart_data_bits
{
    UART_DATA_BITS_8,                  ///< Data bits 8-bit
    UART_DATA_BITS_7,                  ///< Data bits 7-bit
    UART_DATA_BITS_9                   ///< Data bits 9-bit
} uart_data_bits_t;


typedef enum e_bsp_reg_protect
{
    /** Enables writing to the registers related to the clock generation circuit. */
    BSP_REG_PROTECT_CGC = 0,

    /** Enables writing to the registers related to low power consumption and reset. */
    BSP_REG_PROTECT_LPC_RESET,

    /** Enables writing to the registers related to GPIO. */
    BSP_REG_PROTECT_GPIO,

    /** Enables writing to the registers related to Non-Safety reg. */
    BSP_REG_PROTECT_SYSTEM,
} bsp_reg_protect_t;

/** UART Parity definition */
typedef enum e_uart_parity
{
    UART_PARITY_OFF  = 0U,             ///< No parity
    UART_PARITY_EVEN = 1U,             ///< Even parity
    UART_PARITY_ODD  = 3U,             ///< Odd parity
} uart_parity_t;

/** UART Stop bits definition */
typedef enum e_uart_stop_bits
{
    UART_STOP_BITS_1 = 0U,             ///< Stop bit 1-bit
    UART_STOP_BITS_2 = 1U,             ///< Stop bits 2-bit
} uart_stop_bits_t;


typedef struct st_uart_cfg
{
    /* UART generic configuration */
    uint8_t          channel;          ///< Select a channel corresponding to the channel number of the hardware.
    uart_data_bits_t data_bits;        ///< Data bit length (8 or 7 or 9)
    uart_parity_t    parity;           ///< Parity type (none or odd or even)
    uart_stop_bits_t stop_bits;        ///< Stop bit length (1 or 2)

    /* Pointer to UART peripheral specific configuration */
    void * p_extend;                              ///< UART hardware dependent configuration
} uart_cfg_t;


/** Enumeration for SCI clock source */
typedef enum e_sci_clk_src
{
    SCI_UART_CLOCK_INT,                      ///< Use internal clock for baud generation
    SCI_UART_CLOCK_INT_WITH_BAUDRATE_OUTPUT, ///< Use internal clock for baud generation and output on SCK
    SCI_UART_CLOCK_EXT8X,                    ///< Use external clock 8x baud rate
    SCI_UART_CLOCK_EXT16X                    ///< Use external clock 16x baud rate
} sci_clk_src_t;

/** UART communication mode definition */
typedef enum e_uart_mode
{
    UART_MODE_RS232    = 0U,           ///< Enables RS232 communication mode
    UART_MODE_RS485_HD = 1U,           ///< Enables RS485 half duplex communication mode
    UART_MODE_RS485_FD = 2U,           ///< Enables RS485 full duplex communication mode
} uart_mode_t;


/** Receive FIFO trigger configuration. */
typedef enum e_sci_uart_rx_fifo_trigger
{
    SCI_UART_RX_FIFO_TRIGGER_1   = 0x1, ///< Callback after each byte is received without buffering
    SCI_UART_RX_FIFO_TRIGGER_MAX = 0xF, ///< Callback when FIFO is full or after 15 bit times with no data (fewer interrupts)
} sci_uart_rx_fifo_trigger_t;

/** Asynchronous Start Bit Edge Detection configuration. */
typedef enum e_sci_uart_start_bit
{
    SCI_UART_START_BIT_LOW_LEVEL    = 0x0, ///< Detect low level on RXDn pin as start bit
    SCI_UART_START_BIT_FALLING_EDGE = 0x1, ///< Detect falling level on RXDn pin as start bit
} sci_uart_start_bit_t;

/** Noise cancellation configuration. */
typedef enum e_sci_uart_noise_cancellation
{
    SCI_UART_NOISE_CANCELLATION_DISABLE                 = 0x0, ///< Disable noise cancellation
    SCI_UART_NOISE_CANCELLATION_ENABLE                  = 0x1, ///< Enable noise cancellation, The base clock signal divided by 1
    SCI_UART_NOISE_CANCELLATION_ENABLE_FILTER_CKS_DIV_1 = 0x2, ///< Enable noise cancellation, The on-chip baud rate generator source clock divided by 1
    SCI_UART_NOISE_CANCELLATION_ENABLE_FILTER_CKS_DIV_2 = 0x3, ///< Enable noise cancellation, The on-chip baud rate generator source clock divided by 2
    SCI_UART_NOISE_CANCELLATION_ENABLE_FILTER_CKS_DIV_4 = 0x4, ///< Enable noise cancellation, The on-chip baud rate generator source clock divided by 4
    SCI_UART_NOISE_CANCELLATION_ENABLE_FILTER_CKS_DIV_8 = 0x5, ///< Enable noise cancellation, The on-chip baud rate generator source clock divided by 8
} sci_uart_noise_cancellation_t;

/** CTS/RTS function of the SSn pin. */
typedef enum e_sci_uart_ctsrts_config
{
    SCI_UART_CTSRTS_RTS_OUTPUT = 0x0,  ///< Disable CTS function (RTS output function is enabled)
    SCI_UART_CTSRTS_CTS_INPUT  = 0x1,  ///< Enable CTS function
} sci_uart_ctsrts_config_t;

/** Synchronizer circuit configuration. */
typedef enum e_sci_uart_synchronizer
{
    SCI_UART_SYNCHRONIZER_NOT_BYPASS = 0x0, ///< Synchronizer bypass disable
    SCI_UART_SYNCHRONIZER_BYPASS     = 0x1  ///< Synchronizer bypass enable
} sci_uart_synchronizer_t;

/** Register settings to achieve a desired baud rate and modulation duty. */
typedef struct st_baud_setting_t
{
    union
    {
        uint32_t ccr2_baudrate_bits;

        struct
        {
            uint8_t       : 4;
            uint8_t bgdm  : 1;         ///< Baud Rate Generator Double-Speed Mode Select
            uint8_t abcs  : 1;         ///< Asynchronous Mode Base Clock Select
            uint8_t abcse : 1;         ///< Asynchronous Mode Extended Base Clock Select 1
            uint8_t       : 1;
            uint8_t brr   : 8;         ///< Bit Rate Register setting
            uint8_t brme  : 1;         ///< Bit Rate Modulation Enable
            uint8_t       : 3;
            uint8_t cks   : 2;         ///< CKS  value to get divisor (CKS = N)
            uint8_t       : 2;
            uint8_t mddr  : 8;         ///< Modulation Duty Register setting
        };
    };
} baud_setting_t;

/** UART on SCI device Configuration */
typedef struct st_sci_uart_extended_cfg
{
    sci_clk_src_t                 clock;         ///< The source clock for the baud-rate generator. If internal optionally output baud rate on SCK
    sci_uart_start_bit_t          rx_edge_start; ///< Start reception on falling edge
    sci_uart_noise_cancellation_t noise_cancel;  ///< Noise cancellation setting

    baud_setting_t * p_baud_setting;             ///< Register settings for a desired baud rate.

    sci_uart_rx_fifo_trigger_t rx_fifo_trigger;  ///< Receive FIFO trigger level, unused if channel has no FIFO or if DMAC is used.

    uart_mode_t              uart_mode;          ///< UART communication mode selection
    sci_uart_ctsrts_config_t ctsrts_en;          ///< CTS/RTS function of the SSn pin
    sci_uart_synchronizer_t  sync_bypass;        ///< Clock synchronizer selection
} sci_uart_extended_cfg_t;



uint32_t get_pmr(void);

void set_pmr(uint32_t value);











