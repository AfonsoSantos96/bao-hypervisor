
#include <stdint.h>


#ifndef RZT2M_H
 #define RZT2M_H

/* Ensure Renesas MCU variation definitions are included to ensure MCU
 * specific register variations are handled correctly. */
#define   __I     volatile const       /*!< Defines 'read only' permissions */
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

#define R_RWP_NS_BASE        0x80281A10UL
#define R_RWP_S_BASE         0x81281A00UL
#define R_PORT_NSR_BASE      0x800A0000UL
#define R_PORT_SR_BASE       0x81030000UL
#define R_SCI0_BASE          0x80001000UL
#define R_SCI1_BASE          0x80001400UL
#define R_SCI2_BASE          0x80001800UL
#define R_SCI3_BASE          0x80001C00UL
#define R_SCI4_BASE          0x80002000UL
#define R_SCI5_BASE          0x81001000UL

#define R_PTADR_BASE         0x81030C00UL
#define R_SYSC_S_BASE        0x81280000UL
#define R_SYSC_NS_BASE       0x80280000UL
#define R_CLMA0_BASE         0x81280800UL
#define R_CLMA1_BASE         0x81280820UL
#define R_CLMA2_BASE         0x81280840UL
#define R_CLMA3_BASE         0x81280860UL

#define R_RWP_NS        ((R_RWP_NS_Type *) R_RWP_NS_BASE)
#define R_RWP_S         ((R_RWP_S_Type *) R_RWP_S_BASE)
#define R_PORT_NSR      ((R_PORT_COMMON_Type *) R_PORT_NSR_BASE)
#define R_PORT_SR       ((R_PORT_COMMON_Type *) R_PORT_SR_BASE)
#define R_SCI0          ((R_SCI0_Type *) R_SCI0_BASE)
#define R_SCI1          ((R_SCI0_Type *) R_SCI1_BASE)
#define R_SCI2          ((R_SCI0_Type *) R_SCI2_BASE)
#define R_SCI3          ((R_SCI0_Type *) R_SCI3_BASE)
#define R_SCI4          ((R_SCI0_Type *) R_SCI4_BASE)
#define R_SCI5          ((R_SCI0_Type *) R_SCI5_BASE)

#define R_PTADR         ((R_PTADR_Type *) R_PTADR_BASE)
#define R_SYSC_S        ((R_SYSC_S_Type *) R_SYSC_S_BASE)
#define R_SYSC_NS       ((R_SYSC_NS_Type *) R_SYSC_NS_BASE)
#define R_CLMA0         ((R_CLMA0_Type *) R_CLMA0_BASE)
#define R_CLMA1         ((R_CLMA0_Type *) R_CLMA1_BASE)
#define R_CLMA2         ((R_CLMA0_Type *) R_CLMA2_BASE)
#define R_CLMA3         ((R_CLMA0_Type *) R_CLMA3_BASE)





/* =========================================================================================================================== */
/* ================                                         R_SYSC_S                                          ================ */
/* =========================================================================================================================== */

/* ========================================================  SCKCR2  ========================================================= */
 #define R_SYSC_S_SCKCR2_FSELCPU0_Pos        (0UL)          /*!< FSELCPU0 (Bit 0)                                      */
 #define R_SYSC_S_SCKCR2_FSELCPU0_Msk        (0x3UL)        /*!< FSELCPU0 (Bitfield-Mask: 0x03)                        */
 #define R_SYSC_S_SCKCR2_FSELCPU1_Pos        (2UL)          /*!< FSELCPU1 (Bit 2)                                      */
 #define R_SYSC_S_SCKCR2_FSELCPU1_Msk        (0xcUL)        /*!< FSELCPU1 (Bitfield-Mask: 0x03)                        */
 #define R_SYSC_S_SCKCR2_DIVSELSUB_Pos       (5UL)          /*!< DIVSELSUB (Bit 5)                                     */
 #define R_SYSC_S_SCKCR2_DIVSELSUB_Msk       (0x20UL)       /*!< DIVSELSUB (Bitfield-Mask: 0x01)                       */
 #define R_SYSC_S_SCKCR2_SPI3ASYNCSEL_Pos    (24UL)         /*!< SPI3ASYNCSEL (Bit 24)                                 */
 #define R_SYSC_S_SCKCR2_SPI3ASYNCSEL_Msk    (0x1000000UL)  /*!< SPI3ASYNCSEL (Bitfield-Mask: 0x01)                    */
 #define R_SYSC_S_SCKCR2_SCI5ASYNCSEL_Pos    (25UL)         /*!< SCI5ASYNCSEL (Bit 25)                                 */
 #define R_SYSC_S_SCKCR2_SCI5ASYNCSEL_Msk    (0x2000000UL)  /*!< SCI5ASYNCSEL (Bitfield-Mask: 0x01)                    */
/* ========================================================  PLL0MON  ======================================================== */
 #define R_SYSC_S_PLL0MON_PLL0MON_Pos        (0UL)          /*!< PLL0MON (Bit 0)                                       */
 #define R_SYSC_S_PLL0MON_PLL0MON_Msk        (0x1UL)        /*!< PLL0MON (Bitfield-Mask: 0x01)                         */
/* ========================================================  PLL1MON  ======================================================== */
 #define R_SYSC_S_PLL1MON_PLL1MON_Pos        (0UL)          /*!< PLL1MON (Bit 0)                                       */
 #define R_SYSC_S_PLL1MON_PLL1MON_Msk        (0x1UL)        /*!< PLL1MON (Bitfield-Mask: 0x01)                         */
/* ========================================================  PLL1EN  ========================================================= */
 #define R_SYSC_S_PLL1EN_PLL1EN_Pos          (0UL)          /*!< PLL1EN (Bit 0)                                        */
 #define R_SYSC_S_PLL1EN_PLL1EN_Msk          (0x1UL)        /*!< PLL1EN (Bitfield-Mask: 0x01)                          */
/* ========================================================  LOCOCR  ========================================================= */
 #define R_SYSC_S_LOCOCR_LCSTP_Pos           (0UL)          /*!< LCSTP (Bit 0)                                         */
 #define R_SYSC_S_LOCOCR_LCSTP_Msk           (0x1UL)        /*!< LCSTP (Bitfield-Mask: 0x01)                           */
/* =======================================================  HIZCTRLEN  ======================================================= */
 #define R_SYSC_S_HIZCTRLEN_CLMA3MASK_Pos    (0UL)          /*!< CLMA3MASK (Bit 0)                                     */
 #define R_SYSC_S_HIZCTRLEN_CLMA3MASK_Msk    (0x1UL)        /*!< CLMA3MASK (Bitfield-Mask: 0x01)                       */
 #define R_SYSC_S_HIZCTRLEN_CLMA0MASK_Pos    (1UL)          /*!< CLMA0MASK (Bit 1)                                     */
 #define R_SYSC_S_HIZCTRLEN_CLMA0MASK_Msk    (0x2UL)        /*!< CLMA0MASK (Bitfield-Mask: 0x01)                       */
 #define R_SYSC_S_HIZCTRLEN_CLMA1MASK_Pos    (2UL)          /*!< CLMA1MASK (Bit 2)                                     */
 #define R_SYSC_S_HIZCTRLEN_CLMA1MASK_Msk    (0x4UL)        /*!< CLMA1MASK (Bitfield-Mask: 0x01)                       */
/* ========================================================  SWRSYS  ========================================================= */
 #define R_SYSC_S_SWRSYS_SWR_Pos             (0UL)          /*!< SWR (Bit 0)                                           */
 #define R_SYSC_S_SWRSYS_SWR_Msk             (0xffffffffUL) /*!< SWR (Bitfield-Mask: 0xffffffff)                       */
/* ========================================================  SWRCPU0  ======================================================== */
 #define R_SYSC_S_SWRCPU0_SWR_Pos            (0UL)          /*!< SWR (Bit 0)                                           */
 #define R_SYSC_S_SWRCPU0_SWR_Msk            (0xffffffffUL) /*!< SWR (Bitfield-Mask: 0xffffffff)                       */
/* ========================================================  SWRCPU1  ======================================================== */
 #define R_SYSC_S_SWRCPU1_SWR_Pos            (0UL)          /*!< SWR (Bit 0)                                           */
 #define R_SYSC_S_SWRCPU1_SWR_Msk            (0xffffffffUL) /*!< SWR (Bitfield-Mask: 0xffffffff)                       */
/* ========================================================  MSTPCRF  ======================================================== */
 #define R_SYSC_S_MSTPCRF_MSTPCRF00_Pos      (0UL)          /*!< MSTPCRF00 (Bit 0)                                     */
 #define R_SYSC_S_MSTPCRF_MSTPCRF00_Msk      (0x1UL)        /*!< MSTPCRF00 (Bitfield-Mask: 0x01)                       */
/* ========================================================  MSTPCRG  ======================================================== */
 #define R_SYSC_S_MSTPCRG_MSTPCRG00_Pos      (0UL)          /*!< MSTPCRG00 (Bit 0)                                     */
 #define R_SYSC_S_MSTPCRG_MSTPCRG00_Msk      (0x1UL)        /*!< MSTPCRG00 (Bitfield-Mask: 0x01)                       */
 #define R_SYSC_S_MSTPCRG_MSTPCRG01_Pos      (1UL)          /*!< MSTPCRG01 (Bit 1)                                     */
 #define R_SYSC_S_MSTPCRG_MSTPCRG01_Msk      (0x2UL)        /*!< MSTPCRG01 (Bitfield-Mask: 0x01)                       */
 #define R_SYSC_S_MSTPCRG_MSTPCRG02_Pos      (2UL)          /*!< MSTPCRG02 (Bit 2)                                     */
 #define R_SYSC_S_MSTPCRG_MSTPCRG02_Msk      (0x4UL)        /*!< MSTPCRG02 (Bitfield-Mask: 0x01)                       */
 #define R_SYSC_S_MSTPCRG_MSTPCRG03_Pos      (3UL)          /*!< MSTPCRG03 (Bit 3)                                     */
 #define R_SYSC_S_MSTPCRG_MSTPCRG03_Msk      (0x8UL)        /*!< MSTPCRG03 (Bitfield-Mask: 0x01)                       */
 #define R_SYSC_S_MSTPCRG_MSTPCRG04_Pos      (4UL)          /*!< MSTPCRG04 (Bit 4)                                     */
 #define R_SYSC_S_MSTPCRG_MSTPCRG04_Msk      (0x10UL)       /*!< MSTPCRG04 (Bitfield-Mask: 0x01)                       */
 #define R_SYSC_S_MSTPCRG_MSTPCRG05_Pos      (5UL)          /*!< MSTPCRG05 (Bit 5)                                     */
 #define R_SYSC_S_MSTPCRG_MSTPCRG05_Msk      (0x20UL)       /*!< MSTPCRG05 (Bitfield-Mask: 0x01)                       */
 #define R_SYSC_S_MSTPCRG_MSTPCRG08_Pos      (8UL)          /*!< MSTPCRG08 (Bit 8)                                     */
 #define R_SYSC_S_MSTPCRG_MSTPCRG08_Msk      (0x100UL)      /*!< MSTPCRG08 (Bitfield-Mask: 0x01)                       */
 #define R_SYSC_S_MSTPCRG_MSTPCRG09_Pos      (9UL)          /*!< MSTPCRG09 (Bit 9)                                     */
 #define R_SYSC_S_MSTPCRG_MSTPCRG09_Msk      (0x200UL)      /*!< MSTPCRG09 (Bitfield-Mask: 0x01)                       */
 #define R_SYSC_S_MSTPCRG_MSTPCRG10_Pos      (10UL)         /*!< MSTPCRG10 (Bit 10)                                    */
 #define R_SYSC_S_MSTPCRG_MSTPCRG10_Msk      (0x400UL)      /*!< MSTPCRG10 (Bitfield-Mask: 0x01)                       */
 #define R_SYSC_S_MSTPCRG_MSTPCRG11_Pos      (11UL)         /*!< MSTPCRG11 (Bit 11)                                    */
 #define R_SYSC_S_MSTPCRG_MSTPCRG11_Msk      (0x800UL)      /*!< MSTPCRG11 (Bitfield-Mask: 0x01)                       */
/* ========================================================  MSTPCRH  ======================================================== */
 #define R_SYSC_S_MSTPCRH_MSTPCRH01_Pos      (1UL)          /*!< MSTPCRH01 (Bit 1)                                     */
 #define R_SYSC_S_MSTPCRH_MSTPCRH01_Msk      (0x2UL)        /*!< MSTPCRH01 (Bitfield-Mask: 0x01)                       */


/**
 * @brief Register Write Protection for Safety Area (R_SYSC_S)
 */

typedef struct                         /*!< (@ 0x81280000) R_SYSC_S Structure                                         */
{
    __IM uint32_t RESERVED;

    union
    {
        __IOM uint32_t SCKCR2;               /*!< (@ 0x00000004) System Clock Control Register 2                            */

        struct
        {
            __IOM uint32_t FSELCPU0 : 2;     /*!< [1..0] Set the frequency of the clock provided to Coretex-R52
                                              *   CPU0 in combination with bit 5 (DIVSELSUB). The combination
                                              *   is shown below.                                                           */
            __IOM uint32_t FSELCPU1 : 2;     /*!< [3..2] Set the frequency of the clock provided to Coretex-R52
                                              *   CPU1 in combination with bit 5 (DIVSELSUB).                               */
            uint32_t                    : 1;
            __IOM uint32_t DIVSELSUB    : 1; /*!< [5..5] Select the base clock frequency for peripheral module.             */
            uint32_t                    : 18;
            __IOM uint32_t SPI3ASYNCSEL : 1; /*!< [24..24] Select clock frequency when asynchronous serial clock
                                              *   is selected in SPI3                                                       */
            __IOM uint32_t SCI5ASYNCSEL : 1; /*!< [25..25] Select clock frequency when asynchronous serial clock
                                              *   is selected in SCI5                                                       */
            uint32_t : 6;
        } SCKCR2_b;
    };
    __IM uint32_t RESERVED1[6];

    union
    {
        __IM uint32_t PLL0MON;         /*!< (@ 0x00000020) PLL0 Monitor Register                                      */

        struct
        {
            __IM uint32_t PLL0MON : 1; /*!< [0..0] PLL0 Lock State Monitor                                            */
            uint32_t              : 31;
        } PLL0MON_b;
    };
    __IM uint32_t RESERVED2[7];

    union
    {
        __IM uint32_t PLL1MON;         /*!< (@ 0x00000040) PLL1 Monitor Register                                      */

        struct
        {
            __IM uint32_t PLL1MON : 1; /*!< [0..0] PLL1 Lock State Monitor                                            */
            uint32_t              : 31;
        } PLL1MON_b;
    };
    __IM uint32_t RESERVED3[3];

    union
    {
        __IOM uint32_t PLL1EN;         /*!< (@ 0x00000050) PLL1 Enable Register                                       */

        struct
        {
            __IOM uint32_t PLL1EN : 1; /*!< [0..0] PLL1 Enable                                                        */
            uint32_t              : 31;
        } PLL1EN_b;
    };
    __IM uint32_t RESERVED4[7];

    union
    {
        __IOM uint32_t LOCOCR;         /*!< (@ 0x00000070) Low-Speed On-Chip Oscillator Control Register              */

        struct
        {
            __IOM uint32_t LCSTP : 1;  /*!< [0..0] LOCO Stop                                                          */
            uint32_t             : 31;
        } LOCOCR_b;
    };
    __IM uint32_t RESERVED5[3];

    union
    {
        __IOM uint32_t HIZCTRLEN;         /*!< (@ 0x00000080) High-Impedance Control Enable Register                     */

        struct
        {
            __IOM uint32_t CLMA3MASK : 1; /*!< [0..0] CLMA3 error mask to POE3 and POEG                                  */
            __IOM uint32_t CLMA0MASK : 1; /*!< [1..1] CLMA0 error mask to POE3 and POEG                                  */
            __IOM uint32_t CLMA1MASK : 1; /*!< [2..2] CLMA1 error mask to POE3 and POEG                                  */
            uint32_t                 : 29;
        } HIZCTRLEN_b;
    };
    __IM uint32_t RESERVED6[99];

    union
    {
        __OM uint32_t SWRSYS;          /*!< (@ 0x00000210) System Software Reset Register                             */

        struct
        {
            __OM uint32_t SWR : 32;    /*!< [31..0] System Software Reset                                             */
        } SWRSYS_b;
    };
    __IM uint32_t RESERVED7[3];

    union
    {
        __IOM uint32_t SWRCPU0;        /*!< (@ 0x00000220) CPU0 Software Reset Register                               */

        struct
        {
            __IOM uint32_t SWR : 32;   /*!< [31..0] CPU0 Software Reset                                               */
        } SWRCPU0_b;
    };
    __IM uint32_t RESERVED8[3];

    union
    {
        __IOM uint32_t SWRCPU1;        /*!< (@ 0x00000230) CPU1 Software Reset Register                               */

        struct
        {
            __IOM uint32_t SWR : 32;   /*!< [31..0] CPU1 Software Reset                                               */
        } SWRCPU1_b;
    };
    __IM uint32_t RESERVED9[56];

    union
    {
        __IOM uint32_t MSTPCRF;           /*!< (@ 0x00000314) Module Stop Control Register F                             */

        struct
        {
            __IOM uint32_t MSTPCRF00 : 1; /*!< [0..0] Trace Clock for Debugging Interface Module Stop                    */
            uint32_t                 : 31;
        } MSTPCRF_b;
    };

    union
    {
        __IOM uint32_t MSTPCRG;           /*!< (@ 0x00000318) Module Stop Control Register G                             */

        struct
        {
            __IOM uint32_t MSTPCRG00 : 1; /*!< [0..0] SCI Unit 5 Module Stop                                             */
            __IOM uint32_t MSTPCRG01 : 1; /*!< [1..1] IIC Unit 2 Module Stop                                             */
            __IOM uint32_t MSTPCRG02 : 1; /*!< [2..2] SPI Unit 3 Module Stop                                             */
            __IOM uint32_t MSTPCRG03 : 1; /*!< [3..3] GPT Unit 2 Module Stop                                             */
            __IOM uint32_t MSTPCRG04 : 1; /*!< [4..4] CRC Unit 1 Module Stop                                             */
            __IOM uint32_t MSTPCRG05 : 1; /*!< [5..5] RTC Module Stop                                                    */
            uint32_t                 : 2;
            __IOM uint32_t MSTPCRG08 : 1; /*!< [8..8] CLMA3 Module Stop                                                  */
            __IOM uint32_t MSTPCRG09 : 1; /*!< [9..9] CLMA0 Module Stop                                                  */
            __IOM uint32_t MSTPCRG10 : 1; /*!< [10..10] CLMA1 Module Stop                                                */
            __IOM uint32_t MSTPCRG11 : 1; /*!< [11..11] CLMA2 Module Stop                                                */
            uint32_t                 : 20;
        } MSTPCRG_b;
    };

    union
    {
        __IOM uint32_t MSTPCRH;        /*!< (@ 0x0000031C) Module Stop Control Register H                             */

        struct
        {
            uint32_t                 : 1;
            __IOM uint32_t MSTPCRH01 : 1; /*!< [1..1] CPU1 Module Stop                                                   */
            uint32_t                 : 30;
        } MSTPCRH_b;
    };
} R_SYSC_S_Type;                          /*!< Size = 800 (0x320)                                                        */





/**
 * @brief System Control for Non-safety region (R_SYSC_NS)
 */

typedef struct                               /*!< (@ 0x80280000) R_SYSC_NS Structure                                        */
{
    union
    {
        __IOM uint32_t SCKCR;                /*!< (@ 0x00000000) System Clock Control Register                              */

        struct
        {
            __IOM uint32_t FSELXSPI0 : 3;    /*!< [2..0] Set the frequency of the clock provided to xSPI Unit
                                              *   0 in combination with bit 6 (DIVSELXSPI0). The combination
                                              *   is shown below.                                                           */
            uint32_t                   : 3;
            __IOM uint32_t DIVSELXSPI0 : 1;  /*!< [6..6] Select the base clock to generate serial clock for xSPI
                                              *   Unit 0                                                                    */
            uint32_t                 : 1;
            __IOM uint32_t FSELXSPI1 : 3;    /*!< [10..8] Set the frequency of the clock provided to xSPI Unit
                                              *   1 in combination with bit 14 (DIVSELXSPI1).                               */
            uint32_t                   : 3;
            __IOM uint32_t DIVSELXSPI1 : 1;  /*!< [14..14] Select the base clock to generate serial clock for
                                              *   xSPI Unit 1                                                               */
            uint32_t            : 1;
            __IOM uint32_t CKIO : 3;         /*!< [18..16] Set the frequency of the external bus clock (CKIO)
                                              *   and the clock supplied to BSC in combination with the DIVSELSUB
                                              *   in the SCKCR2 register. The combination is shown below.                   */
            uint32_t                 : 1;
            __IOM uint32_t FSELCANFD : 1;    /*!< [20..20] Select the frequency of the clock supplied to CANFD              */
            __IOM uint32_t PHYSEL    : 1;    /*!< [21..21] Select the Ehternet PHY reference clock output (ETHn_REFCLK,
                                              *   n = 0 to 2)                                                               */
            __IOM uint32_t CLMASEL : 1;      /*!< [22..22] Select alternative clock when main clock abnormal oscillation
                                              *   is detected in CLMA3                                                      */
            uint32_t                    : 1;
            __IOM uint32_t SPI0ASYNCSEL : 1; /*!< [24..24] Select clock frequency when asynchronous serial clock
                                              *   is selected in SPI0                                                       */
            __IOM uint32_t SPI1ASYNCSEL : 1; /*!< [25..25] Select clock frequency when asynchronous serial clock
                                              *   is selected in SPI1                                                       */
            __IOM uint32_t SPI2ASYNCSEL : 1; /*!< [26..26] Select clock frequency when asynchronous serial clock
                                              *   is selected in SPI2                                                       */
            __IOM uint32_t SCI0ASYNCSEL : 1; /*!< [27..27] Select clock frequency when asynchronous serial clock
                                              *   is selected in SCI0                                                       */
            __IOM uint32_t SCI1ASYNCSEL : 1; /*!< [28..28] Select clock frequency when asynchronous serial clock
                                              *   is selected in SCI1                                                       */
            __IOM uint32_t SCI2ASYNCSEL : 1; /*!< [29..29] Select clock frequency when asynchronous serial clock
                                              *   is selected in SCI2                                                       */
            __IOM uint32_t SCI3ASYNCSEL : 1; /*!< [30..30] Select clock frequency when asynchronous serial clock
                                              *   is selected in SCI3                                                       */
            __IOM uint32_t SCI4ASYNCSEL : 1; /*!< [31..31] Select clock frequency when asynchronous serial clock
                                              *   is selected in SCI4                                                       */
        } SCKCR_b;
    };
    __IM uint32_t RESERVED[127];

    union
    {
        __IOM uint32_t RSTSR0;         /*!< (@ 0x00000200) Reset Status Register 0                                    */

        struct
        {
            uint32_t             : 1;
            __IOM uint32_t TRF   : 1;  /*!< [1..1] RES# Pin Reset Detect Flag                                         */
            __IOM uint32_t ERRF  : 1;  /*!< [2..2] Error Reset Detect Flag                                            */
            __IOM uint32_t SWRSF : 1;  /*!< [3..3] System Software Reset Detect Flag                                  */
            __IOM uint32_t SWR0F : 1;  /*!< [4..4] CPU0 Software Reset Detect Flag                                    */
            __IOM uint32_t SWR1F : 1;  /*!< [5..5] CPU1 Software Reset Detect Flag                                    */
            uint32_t             : 26;
        } RSTSR0_b;
    };
    __IM uint32_t RESERVED1[15];

    union
    {
        __IOM uint32_t MRCTLA;         /*!< (@ 0x00000240) Module Reset Control Register A                            */

        struct
        {
            uint32_t                : 4;
            __IOM uint32_t MRCTLA04 : 1; /*!< [4..4] xSPI Unit 0 Reset Control                                          */
            __IOM uint32_t MRCTLA05 : 1; /*!< [5..5] xSPI Unit 1 Reset Control                                          */
            uint32_t                : 26;
        } MRCTLA_b;
    };
    __IM uint32_t RESERVED2[3];

    union
    {
        __IOM uint32_t MRCTLE;           /*!< (@ 0x00000250) Module Reset Control Register E                            */

        struct
        {
            __IOM uint32_t MRCTLE00 : 1; /*!< [0..0] GMAC (PCLKH clock domain) Reset Control                            */
            __IOM uint32_t MRCTLE01 : 1; /*!< [1..1] GMAC (PCLKM clock domain) Reset Control                            */
            __IOM uint32_t MRCTLE02 : 1; /*!< [2..2] ETHSW Reset Control                                                */
            __IOM uint32_t MRCTLE03 : 1; /*!< [3..3] ESC (Bus clock domain) Reset Control                               */
            __IOM uint32_t MRCTLE04 : 1; /*!< [4..4] ESC (IP clock domain) Reset Control                                */
            __IOM uint32_t MRCTLE05 : 1; /*!< [5..5] Ethernet Subsystem Register Reset Control                          */
            __IOM uint32_t MRCTLE06 : 1; /*!< [6..6] MII Converter Reset Control                                        */
            uint32_t                : 25;
        } MRCTLE_b;
    };
    __IM uint32_t RESERVED3[43];

    union
    {
        __IOM uint32_t MSTPCRA;           /*!< (@ 0x00000300) Module Stop Control Register A                             */

        struct
        {
            __IOM uint32_t MSTPCRA00 : 1; /*!< [0..0] BSC Module Stop                                                    */
            uint32_t                 : 3;
            __IOM uint32_t MSTPCRA04 : 1; /*!< [4..4] xSPI Unit 0 Module Stop                                            */
            __IOM uint32_t MSTPCRA05 : 1; /*!< [5..5] xSPI Unit 1 Module Stop                                            */
            uint32_t                 : 2;
            __IOM uint32_t MSTPCRA08 : 1; /*!< [8..8] SCI Unit 0 Module Stop                                             */
            __IOM uint32_t MSTPCRA09 : 1; /*!< [9..9] SCI Unit 1 Module Stop                                             */
            __IOM uint32_t MSTPCRA10 : 1; /*!< [10..10] SCI Unit 2 Module Stop                                           */
            __IOM uint32_t MSTPCRA11 : 1; /*!< [11..11] SCI Unit 3 Module Stop                                           */
            __IOM uint32_t MSTPCRA12 : 1; /*!< [12..12] SCI Unit 4 Module Stop                                           */
            uint32_t                 : 19;
        } MSTPCRA_b;
    };

    union
    {
        __IOM uint32_t MSTPCRB;           /*!< (@ 0x00000304) Module Stop Control Register B                             */

        struct
        {
            __IOM uint32_t MSTPCRB00 : 1; /*!< [0..0] IIC Unit 0 Module Stop                                             */
            __IOM uint32_t MSTPCRB01 : 1; /*!< [1..1] IIC Unit 1 Module Stop                                             */
            uint32_t                 : 2;
            __IOM uint32_t MSTPCRB04 : 1; /*!< [4..4] SPI Unit 0 Module Stop                                             */
            __IOM uint32_t MSTPCRB05 : 1; /*!< [5..5] SPI Unit 1 Module Stop                                             */
            __IOM uint32_t MSTPCRB06 : 1; /*!< [6..6] SPI Unit 2 Module Stop                                             */
            uint32_t                 : 25;
        } MSTPCRB_b;
    };

    union
    {
        __IOM uint32_t MSTPCRC;           /*!< (@ 0x00000308) Module Stop Control Register C                             */

        struct
        {
            __IOM uint32_t MSTPCRC00 : 1; /*!< [0..0] MTU3 Module Stop                                                   */
            __IOM uint32_t MSTPCRC01 : 1; /*!< [1..1] GPT Unit 0 Module Stop                                             */
            __IOM uint32_t MSTPCRC02 : 1; /*!< [2..2] GPT Unit 1 Module Stop                                             */
            uint32_t                 : 2;
            __IOM uint32_t MSTPCRC05 : 1; /*!< [5..5] TFU Module Stop                                                    */
            __IOM uint32_t MSTPCRC06 : 1; /*!< [6..6] ADC12 Unit 0 Module Stop                                           */
            __IOM uint32_t MSTPCRC07 : 1; /*!< [7..7] ADC12 Unit 1 Module Stop                                           */
            uint32_t                 : 24;
        } MSTPCRC_b;
    };

    union
    {
        __IOM uint32_t MSTPCRD;           /*!< (@ 0x0000030C) Module Stop Control Register D                             */

        struct
        {
            __IOM uint32_t MSTPCRD00 : 1; /*!< [0..0] DSMIF Unit 0 Module Stop                                           */
            __IOM uint32_t MSTPCRD01 : 1; /*!< [1..1] DSMIF Unit 1 Module Stop                                           */
            __IOM uint32_t MSTPCRD02 : 1; /*!< [2..2] CMT Unit 0 Module Stop                                             */
            __IOM uint32_t MSTPCRD03 : 1; /*!< [3..3] CMT Unit 1 Module Stop                                             */
            __IOM uint32_t MSTPCRD04 : 1; /*!< [4..4] CMT Unit 2 Module Stop                                             */
            __IOM uint32_t MSTPCRD05 : 1; /*!< [5..5] CMTW Unit 0 Module Stop                                            */
            __IOM uint32_t MSTPCRD06 : 1; /*!< [6..6] CMTW Unit 1 Module Stop                                            */
            __IOM uint32_t MSTPCRD07 : 1; /*!< [7..7] TSU Module Stop                                                    */
            __IOM uint32_t MSTPCRD08 : 1; /*!< [8..8] DOC Module Stop                                                    */
            __IOM uint32_t MSTPCRD09 : 1; /*!< [9..9] CRC Unit 0 Module Stop                                             */
            __IOM uint32_t MSTPCRD10 : 1; /*!< [10..10] CANFD Module Stop                                                */
            __IOM uint32_t MSTPCRD11 : 1; /*!< [11..11] CKIO Module Stop                                                 */
            uint32_t                 : 20;
        } MSTPCRD_b;
    };

    union
    {
        __IOM uint32_t MSTPCRE;           /*!< (@ 0x00000310) Module Stop Control Register E                             */

        struct
        {
            __IOM uint32_t MSTPCRE00 : 1; /*!< [0..0] GMAC Module Stop                                                   */
            __IOM uint32_t MSTPCRE01 : 1; /*!< [1..1] ETHSW Module Stop                                                  */
            __IOM uint32_t MSTPCRE02 : 1; /*!< [2..2] ESC Module Stop                                                    */
            __IOM uint32_t MSTPCRE03 : 1; /*!< [3..3] Ethernet Subsystem Register Module Stop                            */
            __IOM uint32_t MSTPCRE04 : 1; /*!< [4..4] Encoder Interface Module Stop                                      */
            uint32_t                 : 3;
            __IOM uint32_t MSTPCRE08 : 1; /*!< [8..8] USB Module Stop                                                    */
            uint32_t                 : 23;
        } MSTPCRE_b;
    };
    __IM uint32_t RESERVED4[891];

    union
    {
        __IM uint32_t MD_MON;          /*!< (@ 0x00001100) Operating Mode Monitor Register                            */

        struct
        {
            __IM uint32_t MDDMON  : 1; /*!< [0..0] MDD status flag                                                    */
            uint32_t              : 3;
            __IM uint32_t MDWMON  : 1; /*!< [4..4] MDW status flag                                                    */
            uint32_t              : 3;
            __IM uint32_t MDP     : 2; /*!< [9..8] Package type                                                       */
            uint32_t              : 2;
            __IM uint32_t MD0MON  : 1; /*!< [12..12] MD0 pin status flag                                              */
            __IM uint32_t MD1MON  : 1; /*!< [13..13] MD1 pin status flag                                              */
            __IM uint32_t MD2MON  : 1; /*!< [14..14] MD2 pin status flag                                              */
            uint32_t              : 1;
            __IM uint32_t MDV0MON : 1; /*!< [16..16] MDV0 status flag (ETH0 domain)                                   */
            __IM uint32_t MDV1MON : 1; /*!< [17..17] MDV1 status flag (ETH1 domain)                                   */
            __IM uint32_t MDV2MON : 1; /*!< [18..18] MDV2 status flag (ETH2 domain)                                   */
            __IM uint32_t MDV3MON : 1; /*!< [19..19] MDV3 status flag (xSPI0 domain)                                  */
            __IM uint32_t MDV4MON : 1; /*!< [20..20] MDV4 status flag (xSPI1 domain)                                  */
            uint32_t              : 11;
        } MD_MON_b;
    };
} R_SYSC_NS_Type;                      /*!< Size = 4356 (0x1104)                                                      */



/**
 * @brief Clock Monitor Circuit 0 (R_CLMA0)
 */

typedef struct                         /*!< (@ 0x81280800) R_CLMA0 Structure                                          */
{
    union
    {
        __IOM uint8_t CTL0;            /*!< (@ 0x00000000) CLMA Control Register 0                                    */

        struct
        {
            __IOM uint8_t CLME : 1;    /*!< [0..0] Clock Monitor m Enable (m = 0 to 3)                                */
            uint8_t            : 7;
        } CTL0_b;
    };
    __IM uint8_t  RESERVED;
    __IM uint16_t RESERVED1[3];

    union
    {
        __IOM uint16_t CMPL;           /*!< (@ 0x00000008) CLMA Compare Register L                                    */

        struct
        {
            __IOM uint16_t CMPL : 12;  /*!< [11..0] Clock Monitor m Compare L (m = 0 to 3)                            */
            uint16_t            : 4;
        } CMPL_b;
    };
    __IM uint16_t RESERVED2;

    union
    {
        __IOM uint16_t CMPH;           /*!< (@ 0x0000000C) CLMA Compare Register H                                    */

        struct
        {
            __IOM uint16_t CMPH : 12;  /*!< [11..0] Clock Monitor m Compare H (m = 0 to 3)                            */
            uint16_t            : 4;
        } CMPH_b;
    };
    __IM uint16_t RESERVED3;
    __OM uint8_t  PCMD;                /*!< (@ 0x00000010) CLMA Command Register                                      */
    __IM uint8_t  RESERVED4;
    __IM uint16_t RESERVED5;

    union
    {
        __IM uint8_t PROTSR;           /*!< (@ 0x00000014) CLMA Protection Status Register                            */

        struct
        {
            __IM uint8_t PRERR : 1;    /*!< [0..0] CLMAm Error (m = 0 to 3)                                           */
            uint8_t            : 7;
        } PROTSR_b;
    };
    __IM uint8_t  RESERVED6;
    __IM uint16_t RESERVED7;
} R_CLMA0_Type;                        /*!< Size = 24 (0x18)                                                          */



/**
 * @brief R_PORT_DRCTL [DRCTL] (I/O Buffer [0..24] Function Switching Register)
 */
typedef struct
{
    union
    {
        __IOM uint32_t L;              /*!< (@ 0x00000000) I/O Buffer m Function Switching Register 0-3               */

        struct
        {
            __IOM uint32_t DRV0 : 2;   /*!< [1..0] Pm_0 Driving Ability Control                                       */
            __IOM uint32_t PUD0 : 2;   /*!< [3..2] Pm_0 Pull-Up/Down Control                                          */
            __IOM uint32_t SMT0 : 1;   /*!< [4..4] Pm_0 Schmitt Trigger Control                                       */
            __IOM uint32_t SR0  : 1;   /*!< [5..5] Pm_0 Slew Rate Control                                             */
            uint32_t            : 2;
            __IOM uint32_t DRV1 : 2;   /*!< [9..8] Pm_1 Driving Ability Control                                       */
            __IOM uint32_t PUD1 : 2;   /*!< [11..10] Pm_1 Pull-Up/Down Control                                        */
            __IOM uint32_t SMT1 : 1;   /*!< [12..12] Pm_1 Schmitt Trigger Control                                     */
            __IOM uint32_t SR1  : 1;   /*!< [13..13] Pm_1 Slew Rate Control                                           */
            uint32_t            : 2;
            __IOM uint32_t DRV2 : 2;   /*!< [17..16] Pm_2 Driving Ability Control                                     */
            __IOM uint32_t PUD2 : 2;   /*!< [19..18] Pm_2 Pull-Up/Down Control                                        */
            __IOM uint32_t SMT2 : 1;   /*!< [20..20] Pm_2 Schmitt Trigger Control                                     */
            __IOM uint32_t SR2  : 1;   /*!< [21..21] Pm_2 Slew Rate Control                                           */
            uint32_t            : 2;
            __IOM uint32_t DRV3 : 2;   /*!< [25..24] Pm_3 Driving Ability Control                                     */
            __IOM uint32_t PUD3 : 2;   /*!< [27..26] Pm_3 Pull-Up/Down Control                                        */
            __IOM uint32_t SMT3 : 1;   /*!< [28..28] Pm_3 Schmitt Trigger Control                                     */
            __IOM uint32_t SR3  : 1;   /*!< [29..29] Pm_3 Slew Rate Control                                           */
            uint32_t            : 2;
        } L_b;
    };

    union
    {
        __IOM uint32_t H;              /*!< (@ 0x00000004) I/O Buffer m Function Switching Register 4-7               */

        struct
        {
            __IOM uint32_t DRV4 : 2;   /*!< [1..0] Pm_4 Driving Ability Control                                       */
            __IOM uint32_t PUD4 : 2;   /*!< [3..2] Pm_4 Pull-Up/Down Control                                          */
            __IOM uint32_t SMT4 : 1;   /*!< [4..4] Pm_4 Schmitt Trigger Control                                       */
            __IOM uint32_t SR4  : 1;   /*!< [5..5] Pm_4 Slew Rate Control                                             */
            uint32_t            : 2;
            __IOM uint32_t DRV5 : 2;   /*!< [9..8] Pm_5 Driving Ability Control                                       */
            __IOM uint32_t PUD5 : 2;   /*!< [11..10] Pm_5 Pull-Up/Down Control                                        */
            __IOM uint32_t SMT5 : 1;   /*!< [12..12] Pm_5 Schmitt Trigger Control                                     */
            __IOM uint32_t SR5  : 1;   /*!< [13..13] Pm_5 Slew Rate Control                                           */
            uint32_t            : 2;
            __IOM uint32_t DRV6 : 2;   /*!< [17..16] Pm_6 Driving Ability Control                                     */
            __IOM uint32_t PUD6 : 2;   /*!< [19..18] Pm_6 Pull-Up/Down Control                                        */
            __IOM uint32_t SMT6 : 1;   /*!< [20..20] Pm_6 Schmitt Trigger Control                                     */
            __IOM uint32_t SR6  : 1;   /*!< [21..21] Pm_6 Slew Rate Control                                           */
            uint32_t            : 2;
            __IOM uint32_t DRV7 : 2;   /*!< [25..24] Pm_7 Driving Ability Control                                     */
            __IOM uint32_t PUD7 : 2;   /*!< [27..26] Pm_7 Pull-Up/Down Control                                        */
            __IOM uint32_t SMT7 : 1;   /*!< [28..28] Pm_7 Schmitt Trigger Control                                     */
            __IOM uint32_t SR7  : 1;   /*!< [29..29] Pm_7 Slew Rate Control                                           */
            uint32_t            : 2;
        } H_b;
    };
} R_PORT_DRCTL_Type;                   /*!< Size = 8 (0x8)                                                            */







/**
 * @brief Port Address Selection (R_PTADR)
 */

typedef struct                         /*!< (@ 0x81030C00) R_PTADR Structure                                          */
{
    union
    {
        __IOM uint8_t RSELP[25];       /*!< (@ 0x00000000) Port [0..24] Region Select Register                        */

        struct
        {
            __IOM uint8_t RS0 : 1;     /*!< [0..0] Pm_n pin I/O port registers Region Select (n = bit position)       */
            __IOM uint8_t RS1 : 1;     /*!< [1..1] Pm_n pin I/O port registers Region Select (n = bit position)       */
            __IOM uint8_t RS2 : 1;     /*!< [2..2] Pm_n pin I/O port registers Region Select (n = bit position)       */
            __IOM uint8_t RS3 : 1;     /*!< [3..3] Pm_n pin I/O port registers Region Select (n = bit position)       */
            __IOM uint8_t RS4 : 1;     /*!< [4..4] Pm_n pin I/O port registers Region Select (n = bit position)       */
            __IOM uint8_t RS5 : 1;     /*!< [5..5] Pm_n pin I/O port registers Region Select (n = bit position)       */
            __IOM uint8_t RS6 : 1;     /*!< [6..6] Pm_n pin I/O port registers Region Select (n = bit position)       */
            __IOM uint8_t RS7 : 1;     /*!< [7..7] Pm_n pin I/O port registers Region Select (n = bit position)       */
        } RSELP_b[25];
    };
} R_PTADR_Type;                        /*!< Size = 25 (0x19)                                                          */









/**
 * @brief R_PORT_NSR_ELC_PDBF [ELC_PDBF] (ELC Port Buffer Register [0..1])
 */
typedef struct
{
    union
    {
        __IOM uint8_t BY;              /*!< (@ 0x00000000) ELC Port Buffer Register n                                 */

        struct
        {
            __IOM uint8_t PB0 : 1;     /*!< [0..0] Port Buffer 0                                                      */
            __IOM uint8_t PB1 : 1;     /*!< [1..1] Port Buffer 1                                                      */
            __IOM uint8_t PB2 : 1;     /*!< [2..2] Port Buffer 2                                                      */
            __IOM uint8_t PB3 : 1;     /*!< [3..3] Port Buffer 3                                                      */
            __IOM uint8_t PB4 : 1;     /*!< [4..4] Port Buffer 4                                                      */
            __IOM uint8_t PB5 : 1;     /*!< [5..5] Port Buffer 5                                                      */
            __IOM uint8_t PB6 : 1;     /*!< [6..6] Port Buffer 6                                                      */
            __IOM uint8_t PB7 : 1;     /*!< [7..7] Port Buffer 7                                                      */
        } BY_b;
    };
    __IM uint8_t RESERVED[3];
} R_PORT_NSR_ELC_PDBF_Type;            /*!< Size = 4 (0x4)                                                            */












/**
 * @brief I/O Ports (Non safety region) (R_PORT_NSR)
 */

typedef struct                         /*!< (@ 0x800A0000) R_PORT_NSR Structure                                       */
{
    union
    {
        __IOM uint8_t P[25];           /*!< (@ 0x00000000) Port [0..24] Register                                      */

        struct
        {
            __IOM uint8_t POUT_0 : 1;  /*!< [0..0] Pm_n Output Data Store (n: bit position)                           */
            __IOM uint8_t POUT_1 : 1;  /*!< [1..1] Pm_n Output Data Store (n: bit position)                           */
            __IOM uint8_t POUT_2 : 1;  /*!< [2..2] Pm_n Output Data Store (n: bit position)                           */
            __IOM uint8_t POUT_3 : 1;  /*!< [3..3] Pm_n Output Data Store (n: bit position)                           */
            __IOM uint8_t POUT_4 : 1;  /*!< [4..4] Pm_n Output Data Store (n: bit position)                           */
            __IOM uint8_t POUT_5 : 1;  /*!< [5..5] Pm_n Output Data Store (n: bit position)                           */
            __IOM uint8_t POUT_6 : 1;  /*!< [6..6] Pm_n Output Data Store (n: bit position)                           */
            __IOM uint8_t POUT_7 : 1;  /*!< [7..7] Pm_n Output Data Store (n: bit position)                           */
        } P_b[25];
    };
    __IM uint8_t  RESERVED;
    __IM uint16_t RESERVED1;
    __IM uint32_t RESERVED2[121];

    union
    {
        __IOM uint16_t PM[25];         /*!< (@ 0x00000200) Port [0..24] Mode Register                                 */

        struct
        {
            __IOM uint16_t PM0 : 2;    /*!< [1..0] Pm_0 I/O Select                                                    */
            __IOM uint16_t PM1 : 2;    /*!< [3..2] Pm_1 I/O Select                                                    */
            __IOM uint16_t PM2 : 2;    /*!< [5..4] Pm_2 I/O Select                                                    */
            __IOM uint16_t PM3 : 2;    /*!< [7..6] Pm_3 I/O Select                                                    */
            __IOM uint16_t PM4 : 2;    /*!< [9..8] Pm_4 I/O Select                                                    */
            __IOM uint16_t PM5 : 2;    /*!< [11..10] Pm_5 I/O Select                                                  */
            __IOM uint16_t PM6 : 2;    /*!< [13..12] Pm_6 I/O Select                                                  */
            __IOM uint16_t PM7 : 2;    /*!< [15..14] Pm_7 I/O Select                                                  */
        } PM_b[25];
    };
    __IM uint16_t RESERVED3;
    __IM uint32_t RESERVED4[115];

    union
    {
        __IOM uint8_t PMC[25];         /*!< (@ 0x00000400) Port [0..24] Mode Control Register                         */

        struct
        {
            __IOM uint8_t PMC0 : 1;    /*!< [0..0] Pm_n Pin Mode Control (n: bit position)                            */
            __IOM uint8_t PMC1 : 1;    /*!< [1..1] Pm_n Pin Mode Control (n: bit position)                            */
            __IOM uint8_t PMC2 : 1;    /*!< [2..2] Pm_n Pin Mode Control (n: bit position)                            */
            __IOM uint8_t PMC3 : 1;    /*!< [3..3] Pm_n Pin Mode Control (n: bit position)                            */
            __IOM uint8_t PMC4 : 1;    /*!< [4..4] Pm_n Pin Mode Control (n: bit position)                            */
            __IOM uint8_t PMC5 : 1;    /*!< [5..5] Pm_n Pin Mode Control (n: bit position)                            */
            __IOM uint8_t PMC6 : 1;    /*!< [6..6] Pm_n Pin Mode Control (n: bit position)                            */
            __IOM uint8_t PMC7 : 1;    /*!< [7..7] Pm_n Pin Mode Control (n: bit position)                            */
        } PMC_b[25];
    };
    __IM uint8_t  RESERVED5;
    __IM uint16_t RESERVED6;
    __IM uint32_t RESERVED7[121];

    union
    {
        __IOM uint32_t PFC[25];        /*!< (@ 0x00000600) Port [0..24] Function Control Register                     */

        struct
        {
            __IOM uint32_t PFC0 : 4;   /*!< [3..0] Pm_0 Pin function Select                                           */
            __IOM uint32_t PFC1 : 4;   /*!< [7..4] Pm_1 Pin function Select                                           */
            __IOM uint32_t PFC2 : 4;   /*!< [11..8] Pm_2 Pin function Select                                          */
            __IOM uint32_t PFC3 : 4;   /*!< [15..12] Pm_3 Pin function Select                                         */
            __IOM uint32_t PFC4 : 4;   /*!< [19..16] Pm_4 Pin function Select                                         */
            __IOM uint32_t PFC5 : 4;   /*!< [23..20] Pm_5 Pin function Select                                         */
            __IOM uint32_t PFC6 : 4;   /*!< [27..24] Pm_6 Pin function Select                                         */
            __IOM uint32_t PFC7 : 4;   /*!< [31..28] Pm_7 Pin function Select                                         */
        } PFC_b[25];
    };
    __IM uint32_t RESERVED8[103];

    union
    {
        __IM uint8_t PIN[25];          /*!< (@ 0x00000800) Port [0..24] Input Register                                */

        struct
        {
            __IM uint8_t PIN0 : 1;     /*!< [0..0] Pm_n Pin Input (n: bit position)                                   */
            __IM uint8_t PIN1 : 1;     /*!< [1..1] Pm_n Pin Input (n: bit position)                                   */
            __IM uint8_t PIN2 : 1;     /*!< [2..2] Pm_n Pin Input (n: bit position)                                   */
            __IM uint8_t PIN3 : 1;     /*!< [3..3] Pm_n Pin Input (n: bit position)                                   */
            __IM uint8_t PIN4 : 1;     /*!< [4..4] Pm_n Pin Input (n: bit position)                                   */
            __IM uint8_t PIN5 : 1;     /*!< [5..5] Pm_n Pin Input (n: bit position)                                   */
            __IM uint8_t PIN6 : 1;     /*!< [6..6] Pm_n Pin Input (n: bit position)                                   */
            __IM uint8_t PIN7 : 1;     /*!< [7..7] Pm_n Pin Input (n: bit position)                                   */
        } PIN_b[25];
    };
    __IM uint8_t            RESERVED9;
    __IM uint16_t           RESERVED10;
    __IM uint32_t           RESERVED11[121];
    __IOM R_PORT_DRCTL_Type DRCTL[25]; /*!< (@ 0x00000A00) I/O Buffer [0..24] Function Switching Register             */
    __IM uint32_t           RESERVED12[206];

    union
    {
        __IOM uint8_t ELC_PGR[2];      /*!< (@ 0x00000E00) ELC Port Group Setting Register [0..1]                     */

        struct
        {
            __IOM uint8_t PG0 : 1;     /*!< [0..0] Port Group Setting                                                 */
            __IOM uint8_t PG1 : 1;     /*!< [1..1] Port Group Setting                                                 */
            __IOM uint8_t PG2 : 1;     /*!< [2..2] Port Group Setting                                                 */
            __IOM uint8_t PG3 : 1;     /*!< [3..3] Port Group Setting                                                 */
            __IOM uint8_t PG4 : 1;     /*!< [4..4] Port Group Setting                                                 */
            __IOM uint8_t PG5 : 1;     /*!< [5..5] Port Group Setting                                                 */
            __IOM uint8_t PG6 : 1;     /*!< [6..6] Port Group Setting                                                 */
            __IOM uint8_t PG7 : 1;     /*!< [7..7] Port Group Setting                                                 */
        } ELC_PGR_b[2];
    };

    union
    {
        __IOM uint8_t ELC_PGC[2];               /*!< (@ 0x00000E02) ELC Port Group Control Register [0..1]                     */

        struct
        {
            __IOM uint8_t PGCI   : 2;           /*!< [1..0] Event Output Edge Select                                           */
            __IOM uint8_t PGCOVE : 1;           /*!< [2..2] PDBF Overwrite                                                     */
            uint8_t              : 1;
            __IOM uint8_t PGCO   : 3;           /*!< [6..4] Port Group Operation Select                                        */
            uint8_t              : 1;
        } ELC_PGC_b[2];
    };
    __IOM R_PORT_NSR_ELC_PDBF_Type ELC_PDBF[2]; /*!< (@ 0x00000E04) ELC Port Buffer Register [0..1]                            */

    union
    {
        __IOM uint8_t ELC_PEL[4];               /*!< (@ 0x00000E0C) ELC Port Setting Register [0..3]                           */

        struct
        {
            __IOM uint8_t PSB : 3;              /*!< [2..0] Bit Number Specification                                           */
            __IOM uint8_t PSP : 2;              /*!< [4..3] Port Number Specification                                          */
            __IOM uint8_t PSM : 2;              /*!< [6..5] Event Link Specification                                           */
            uint8_t           : 1;
        } ELC_PEL_b[4];
    };

    union
    {
        __IOM uint8_t ELC_DPTC;        /*!< (@ 0x00000E10) ELC Edge Detection Control Register                        */

        struct
        {
            __IOM uint8_t PTC0 : 1;    /*!< [0..0] Single Input Port n Edge Detection                                 */
            __IOM uint8_t PTC1 : 1;    /*!< [1..1] Single Input Port n Edge Detection                                 */
            __IOM uint8_t PTC2 : 1;    /*!< [2..2] Single Input Port n Edge Detection                                 */
            __IOM uint8_t PTC3 : 1;    /*!< [3..3] Single Input Port n Edge Detection                                 */
            uint8_t            : 4;
        } ELC_DPTC_b;
    };

    union
    {
        __IOM uint8_t ELC_ELSR2;       /*!< (@ 0x00000E11) ELC Port Event Control Register                            */

        struct
        {
            uint8_t            : 2;
            __IOM uint8_t PEG1 : 1;    /*!< [2..2] ELC Port Buffer Register (ELC_PDBFn) write access control.
                                        *   When set to 1, writing to the ELC_PDBFn register via Internal
                                        *   peripheral bus is disabled, preventing overwriting.                       */
            __IOM uint8_t PEG2 : 1;    /*!< [3..3] ELC Port Buffer Register (ELC_PDBFn) write access control.
                                        *   When set to 1, writing to the ELC_PDBFn register via Internal
                                        *   peripheral bus is disabled, preventing overwriting.                       */
            __IOM uint8_t PES0 : 1;    /*!< [4..4] Single Port n Event Link Function Enable                           */
            __IOM uint8_t PES1 : 1;    /*!< [5..5] Single Port n Event Link Function Enable                           */
            __IOM uint8_t PES2 : 1;    /*!< [6..6] Single Port n Event Link Function Enable                           */
            __IOM uint8_t PES3 : 1;    /*!< [7..7] Single Port n Event Link Function Enable                           */
        } ELC_ELSR2_b;
    };
    __IM uint16_t RESERVED13;
} R_PORT_COMMON_Type;                  /*!< Size = 3604 (0xe14)                                                       */



/**
 * @brief Register Write Protection for Safety Area (R_RWP_S)
 */

typedef struct                         /*!< (@ 0x81281A00) R_RWP_S Structure                                          */
{
    union
    {
        __IOM uint32_t PRCRS;          /*!< (@ 0x00000000) Safety Area Protect Register                               */

        struct
        {
            __IOM uint32_t PRC0 : 1;   /*!< [0..0] Protect 0                                                          */
            __IOM uint32_t PRC1 : 1;   /*!< [1..1] Protect 1                                                          */
            __IOM uint32_t PRC2 : 1;   /*!< [2..2] Protect 2                                                          */
            __IOM uint32_t PRC3 : 1;   /*!< [3..3] Protect 3                                                          */
            uint32_t            : 4;
            __OM uint32_t PRKEY : 8;   /*!< [15..8] PRC Key Code                                                      */
            uint32_t            : 16;
        } PRCRS_b;
    };
} R_RWP_S_Type;                        /*!< Size = 4 (0x4)                                                            */




/**
 * @brief Register Write Protection for Non-safety Area (R_RWP_NS)
 */

typedef struct                         /*!< (@ 0x80281A10) R_RWP_NS Structure                                         */
{
    union
    {
        __IOM uint32_t PRCRN;          /*!< (@ 0x00000000) Non_Safety Area Protect Register                           */

        struct
        {
            __IOM uint32_t PRC0 : 1;   /*!< [0..0] Protect 0                                                          */
            __IOM uint32_t PRC1 : 1;   /*!< [1..1] Protect 1                                                          */
            __IOM uint32_t PRC2 : 1;   /*!< [2..2] Protect 2                                                          */
            uint32_t            : 5;
            __OM uint32_t PRKEY : 8;   /*!< [15..8] PRC Key Code                                                      */
            uint32_t            : 16;
        } PRCRN_b;
    };
} R_RWP_NS_Type;                       /*!< Size = 4 (0x4)                                                            */



/**
 * @brief Serial Communication Interface 0 (R_SCI0)
 */

typedef struct                         /*!< (@ 0x80001000) R_SCI0 Structure                                           */
{
    union
    {
        __IM uint32_t RDR;             /*!< (@ 0x00000000) Receive Data Register                                      */

        struct
        {
            __IM uint32_t RDAT : 9;    /*!< [8..0] Serial receive data                                                */
            __IM uint32_t MPB  : 1;    /*!< [9..9] Multi-processor flag                                               */
            __IM uint32_t DR   : 1;    /*!< [10..10] Receive data ready flag                                          */
            __IM uint32_t FPER : 1;    /*!< [11..11] FIFO parity error flag                                           */
            __IM uint32_t FFER : 1;    /*!< [12..12] FIFO framing error flag                                          */
            uint32_t           : 11;
            __IM uint32_t ORER : 1;    /*!< [24..24] Overrun Error flag                                               */
            uint32_t           : 2;
            __IM uint32_t PER  : 1;    /*!< [27..27] Parity error flag                                                */
            __IM uint32_t FER  : 1;    /*!< [28..28] Framing error flag                                               */
            uint32_t           : 3;
        } RDR_b;
    };

    union
    {
        __IOM uint32_t TDR;            /*!< (@ 0x00000004) Transmit Data Register                                     */

        struct
        {
            __IOM uint32_t TDAT : 9;   /*!< [8..0] Serial transmit data                                               */
            __IOM uint32_t MPBT : 1;   /*!< [9..9] Multi-processor transfer bit flag                                  */
            uint32_t            : 22;
        } TDR_b;
    };

    union
    {
        __IOM uint32_t CCR0;           /*!< (@ 0x00000008) Common Control Register 0                                  */

        struct
        {
            __IOM uint32_t RE    : 1;  /*!< [0..0] Receive Enable                                                     */
            uint32_t             : 3;
            __IOM uint32_t TE    : 1;  /*!< [4..4] Transmit Enable                                                    */
            uint32_t             : 3;
            __IOM uint32_t MPIE  : 1;  /*!< [8..8] Multi-Processor Interrupt Enable                                   */
            __IOM uint32_t DCME  : 1;  /*!< [9..9] Data Compare Match Enable                                          */
            __IOM uint32_t IDSEL : 1;  /*!< [10..10] ID frame select                                                  */
            uint32_t             : 5;
            __IOM uint32_t RIE   : 1;  /*!< [16..16] Receive Interrupt Enable                                         */
            uint32_t             : 3;
            __IOM uint32_t TIE   : 1;  /*!< [20..20] Transmit Interrupt Enable                                        */
            __IOM uint32_t TEIE  : 1;  /*!< [21..21] Transmit End Interrupt Enable                                    */
            uint32_t             : 2;
            __IOM uint32_t SSE   : 1;  /*!< [24..24] SSn# Pin Function Enable                                         */
            uint32_t             : 7;
        } CCR0_b;
    };

    union
    {
        __IOM uint32_t CCR1;           /*!< (@ 0x0000000C) Common Control Register 1                                  */

        struct
        {
            __IOM uint32_t CTSE   : 1; /*!< [0..0] CTS Enable                                                         */
            __IOM uint32_t CTSPEN : 1; /*!< [1..1] CTS external pin Enable                                            */
            uint32_t              : 2;
            __IOM uint32_t SPB2DT : 1; /*!< [4..4] Serial port break data select                                      */
            __IOM uint32_t SPB2IO : 1; /*!< [5..5] Serial port break I/O                                              */
            uint32_t              : 2;
            __IOM uint32_t PE     : 1; /*!< [8..8] Parity Enable                                                      */
            __IOM uint32_t PM     : 1; /*!< [9..9] Parity Mode                                                        */
            uint32_t              : 2;
            __IOM uint32_t TINV   : 1; /*!< [12..12] TXD invert                                                       */
            __IOM uint32_t RINV   : 1; /*!< [13..13] RXD invert                                                       */
            uint32_t              : 2;
            __IOM uint32_t SPLP   : 1; /*!< [16..16] Loopback Control                                                 */
            uint32_t              : 3;
            __IOM uint32_t SHARPS : 1; /*!< [20..20] Half-duplex communication select                                 */
            uint32_t              : 3;
            __IOM uint32_t NFCS   : 3; /*!< [26..24] Noise Filter Clock Select                                        */
            uint32_t              : 1;
            __IOM uint32_t NFEN   : 1; /*!< [28..28] Digital Noise Filter Function Enable                             */
            uint32_t              : 3;
        } CCR1_b;
    };

    union
    {
        __IOM uint32_t CCR2;           /*!< (@ 0x00000010) Common Control Register 2                                  */

        struct
        {
            __IOM uint32_t BCP   : 3;  /*!< [2..0] Base Clock Pulse                                                   */
            uint32_t             : 1;
            __IOM uint32_t BGDM  : 1;  /*!< [4..4] Baud Rate Generator Double-Speed Mode Select                       */
            __IOM uint32_t ABCS  : 1;  /*!< [5..5] Asynchronous Mode Base Clock Select                                */
            __IOM uint32_t ABCSE : 1;  /*!< [6..6] Asynchronous Mode Extended Base Clock Select                       */
            uint32_t             : 1;
            __IOM uint32_t BRR   : 8;  /*!< [15..8] Bit rate setting                                                  */
            __IOM uint32_t BRME  : 1;  /*!< [16..16] BRME                                                             */
            uint32_t             : 3;
            __IOM uint32_t CKS   : 2;  /*!< [21..20] Clock Select                                                     */
            uint32_t             : 2;
            __IOM uint32_t MDDR  : 8;  /*!< [31..24] Modulation Duty setting                                          */
        } CCR2_b;
    };

    union
    {
        __IOM uint32_t CCR3;            /*!< (@ 0x00000014) Common Control Register 3                                  */

        struct
        {
            __IOM uint32_t CPHA    : 1; /*!< [0..0] Clock Phase Select                                                 */
            __IOM uint32_t CPOL    : 1; /*!< [1..1] Clock Polarity Select                                              */
            uint32_t               : 5;
            __IOM uint32_t BPEN    : 1; /*!< [7..7] Synchronizer bypass enable                                         */
            __IOM uint32_t CHR     : 2; /*!< [9..8] Character Length                                                   */
            uint32_t               : 2;
            __IOM uint32_t LSBF    : 1; /*!< [12..12] LSB First select                                                 */
            __IOM uint32_t SINV    : 1; /*!< [13..13] Transmitted/Received Data Invert                                 */
            __IOM uint32_t STP     : 1; /*!< [14..14] Stop Bit Length                                                  */
            __IOM uint32_t RXDESEL : 1; /*!< [15..15] Asynchronous Start Bit Edge Detection Select                     */
            __IOM uint32_t MOD     : 3; /*!< [18..16] Communication mode select                                        */
            __IOM uint32_t MP      : 1; /*!< [19..19] Multi-Processor Mode                                             */
            __IOM uint32_t FM      : 1; /*!< [20..20] FIFO Mode select                                                 */
            __IOM uint32_t DEN     : 1; /*!< [21..21] Driver enable                                                    */
            uint32_t               : 2;
            __IOM uint32_t CKE     : 2; /*!< [25..24] Clock enable                                                     */
            uint32_t               : 2;
            __IOM uint32_t GM      : 1; /*!< [28..28] GSM Mode                                                         */
            __IOM uint32_t BLK     : 1; /*!< [29..29] Block Transfer Mode                                              */
            uint32_t               : 2;
        } CCR3_b;
    };

    union
    {
        __IOM uint32_t CCR4;           /*!< (@ 0x00000018) Common Control Register 4                                  */

        struct
        {
            __IOM uint32_t CMPD : 9;   /*!< [8..0] Compare Match Data                                                 */
            uint32_t            : 7;
            __IOM uint32_t ASEN : 1;   /*!< [16..16] Adjust receive sampling timing enable                            */
            __IOM uint32_t ATEN : 1;   /*!< [17..17] Adjust transmit timing enable                                    */
            uint32_t            : 6;
            __IOM uint32_t AST  : 3;   /*!< [26..24] Adjustment value for receive Sampling Timing                     */
            __IOM uint32_t AJD  : 1;   /*!< [27..27] Adjustment Direction for receive sampling timing                 */
            __IOM uint32_t ATT  : 3;   /*!< [30..28] Adjustment value for Transmit timing                             */
            __IOM uint32_t AET  : 1;   /*!< [31..31] Adjustment edge for transmit timing                              */
        } CCR4_b;
    };
    __IM uint32_t RESERVED;

    union
    {
        __IOM uint32_t ICR;                /*!< (@ 0x00000020) Simple I2C Control Register                                */

        struct
        {
            __IOM uint32_t IICDL      : 5; /*!< [4..0] SDA Delay Output Select                                            */
            uint32_t                  : 3;
            __IOM uint32_t IICINTM    : 1; /*!< [8..8] IICINTM                                                            */
            __IOM uint32_t IICCSC     : 1; /*!< [9..9] IICCSC                                                             */
            uint32_t                  : 3;
            __IOM uint32_t IICACKT    : 1; /*!< [13..13] IICACKT                                                          */
            uint32_t                  : 2;
            __IOM uint32_t IICSTAREQ  : 1; /*!< [16..16] IICSTAREQ                                                        */
            __IOM uint32_t IICRSTAREQ : 1; /*!< [17..17] IICRSTAREQ                                                       */
            __IOM uint32_t IICSTPREQ  : 1; /*!< [18..18] IICSTPREQ                                                        */
            uint32_t                  : 1;
            __IOM uint32_t IICSDAS    : 2; /*!< [21..20] IICSDAS                                                          */
            __IOM uint32_t IICSCLS    : 2; /*!< [23..22] IICSCLS                                                          */
            uint32_t                  : 8;
        } ICR_b;
    };

    union
    {
        __IOM uint32_t FCR;            /*!< (@ 0x00000024) FIFO Control Register                                      */

        struct
        {
            __IOM uint32_t DRES  : 1;  /*!< [0..0] Receive data ready error select                                    */
            uint32_t             : 7;
            __IOM uint32_t TTRG  : 5;  /*!< [12..8] Transmit FIFO data trigger number                                 */
            uint32_t             : 2;
            __OM uint32_t  TFRST : 1;  /*!< [15..15] Transmit FIFO Data Register Reset                                */
            __IOM uint32_t RTRG  : 5;  /*!< [20..16] Receive FIFO data trigger number                                 */
            uint32_t             : 2;
            __OM uint32_t  RFRST : 1;  /*!< [23..23] Receive FIFO Data Register Reset                                 */
            __IOM uint32_t RSTRG : 5;  /*!< [28..24] RTS# Output Active Trigger Number Select                         */
            uint32_t             : 3;
        } FCR_b;
    };
    __IM uint32_t RESERVED1[2];

    union
    {
        __IOM uint32_t DCR;            /*!< (@ 0x00000030) Driver Control Register                                    */

        struct
        {
            __IOM uint32_t DEPOL : 1;  /*!< [0..0] Driver effective polarity select                                   */
            uint32_t             : 7;
            __IOM uint32_t DEAST : 5;  /*!< [12..8] Driver Assertion Time                                             */
            uint32_t             : 3;
            __IOM uint32_t DENGT : 5;  /*!< [20..16] Driver negate time                                               */
            uint32_t             : 11;
        } DCR_b;
    };
    __IM uint32_t RESERVED2[5];

    union
    {
        __IM uint32_t CSR;             /*!< (@ 0x00000048) Common Status Register                                     */

        struct
        {
            uint32_t             : 4;
            __IM uint32_t ERS    : 1;  /*!< [4..4] Error Signal Status Flag                                           */
            uint32_t             : 10;
            __IM uint32_t RXDMON : 1;  /*!< [15..15] Serial input data monitor                                        */
            __IM uint32_t DCMF   : 1;  /*!< [16..16] Data Compare Match Flag                                          */
            __IM uint32_t DPER   : 1;  /*!< [17..17] Data Compare Match Parity Error Flag                             */
            __IM uint32_t DFER   : 1;  /*!< [18..18] Data Compare Match Framing Error Flag                            */
            uint32_t             : 5;
            __IM uint32_t ORER   : 1;  /*!< [24..24] ORER                                                             */
            uint32_t             : 1;
            __IM uint32_t MFF    : 1;  /*!< [26..26] Mode Fault Error Flag                                            */
            __IM uint32_t PER    : 1;  /*!< [27..27] PER                                                              */
            __IM uint32_t FER    : 1;  /*!< [28..28] FER                                                              */
            __IM uint32_t TDRE   : 1;  /*!< [29..29] Transmit Data Empty Flag                                         */
            __IM uint32_t TEND   : 1;  /*!< [30..30] TEND                                                             */
            __IM uint32_t RDRF   : 1;  /*!< [31..31] RDRF                                                             */
        } CSR_b;
    };

    union
    {
        __IM uint32_t ISR;             /*!< (@ 0x0000004C) Simple I2C Status Register                                 */

        struct
        {
            __IM uint32_t IICACKR : 1; /*!< [0..0] ACK Reception Data Flag                                            */
            uint32_t              : 2;
            __IM uint32_t IICSTIF : 1; /*!< [3..3] Issuing of Start, Restart, or Stop Condition Completed
                                        *   Flag                                                                      */
            uint32_t : 28;
        } ISR_b;
    };

    union
    {
        __IM uint32_t FRSR;            /*!< (@ 0x00000050) FIFO Receive Status Register                               */

        struct
        {
            __IM uint32_t DR   : 1;    /*!< [0..0] DR                                                                 */
            uint32_t           : 7;
            __IM uint32_t R    : 6;    /*!< [13..8] Receive FIFO Data Count                                           */
            uint32_t           : 2;
            __IM uint32_t PNUM : 6;    /*!< [21..16] Parity Error Count                                               */
            uint32_t           : 2;
            __IM uint32_t FNUM : 6;    /*!< [29..24] Framing Error Count                                              */
            uint32_t           : 2;
        } FRSR_b;
    };

    union
    {
        __IM uint32_t FTSR;            /*!< (@ 0x00000054) FIFO Transmit Status Register                              */

        struct
        {
            __IM uint32_t T : 6;       /*!< [5..0] Transmit FIFO Data Count                                           */
            uint32_t        : 26;
        } FTSR_b;
    };
    __IM uint32_t RESERVED3[4];

    union
    {
        __OM uint32_t CFCLR;           /*!< (@ 0x00000068) Common Flag Clear Register                                 */

        struct
        {
            uint32_t            : 4;
            __OM uint32_t ERSC  : 1;   /*!< [4..4] ERSC                                                               */
            uint32_t            : 11;
            __OM uint32_t DCMFC : 1;   /*!< [16..16] DCMFC                                                            */
            __OM uint32_t DPERC : 1;   /*!< [17..17] DPERC                                                            */
            __OM uint32_t DFERC : 1;   /*!< [18..18] DFERC                                                            */
            uint32_t            : 5;
            __OM uint32_t ORERC : 1;   /*!< [24..24] ORERC                                                            */
            uint32_t            : 1;
            __OM uint32_t MFFC  : 1;   /*!< [26..26] MFFC                                                             */
            __OM uint32_t PERC  : 1;   /*!< [27..27] PERC                                                             */
            __OM uint32_t FERC  : 1;   /*!< [28..28] FERC                                                             */
            __OM uint32_t TDREC : 1;   /*!< [29..29] TDREC                                                            */
            uint32_t            : 1;
            __OM uint32_t RDRFC : 1;   /*!< [31..31] RDRFC                                                            */
        } CFCLR_b;
    };

    union
    {
        __OM uint32_t ICFCLR;          /*!< (@ 0x0000006C) Simple I2C Flag Clear Register                             */

        struct
        {
            uint32_t               : 3;
            __OM uint32_t IICSTIFC : 1; /*!< [3..3] IICSTIFC                                                           */
            uint32_t               : 28;
        } ICFCLR_b;
    };

    union
    {
        __OM uint32_t FFCLR;           /*!< (@ 0x00000070) FIFO Flag Clear Register                                   */

        struct
        {
            __OM uint32_t DRC : 1;     /*!< [0..0] DRC                                                                */
            uint32_t          : 31;
        } FFCLR_b;
    };
} R_SCI0_Type;                         /*!< Size = 116 (0x74)  */




#endif