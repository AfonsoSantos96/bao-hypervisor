#include <stdint.h>

/* "PORT" in ASCII, used to determine if the module is open */
#define IOPORT_OPEN                (0x504F5254U)

/* Private definition to set enumeration values. */
#define IOPORT_P_OFFSET             (0U)
#define IOPORT_PM_OFFSET            (1U)
#define IOPORT_PMC_OFFSET           (3U)
#define IOPORT_PFC_OFFSET           (4U)
#define IOPORT_DRCTL_OFFSET         (8U)
#define IOPORT_RSELP_OFFSET         (14U)


 typedef enum e_bsp_io_port_pin_t
 {
     BSP_IO_PORT_00_PIN_0 = 0x0000,     ///< IO port 0 pin 0
     BSP_IO_PORT_00_PIN_1 = 0x0001,     ///< IO port 0 pin 1
     BSP_IO_PORT_00_PIN_2 = 0x0002,     ///< IO port 0 pin 2
     BSP_IO_PORT_00_PIN_3 = 0x0003,     ///< IO port 0 pin 3
     BSP_IO_PORT_00_PIN_4 = 0x0004,     ///< IO port 0 pin 4
     BSP_IO_PORT_00_PIN_5 = 0x0005,     ///< IO port 0 pin 5
     BSP_IO_PORT_00_PIN_6 = 0x0006,     ///< IO port 0 pin 6
     BSP_IO_PORT_00_PIN_7 = 0x0007,     ///< IO port 0 pin 
     BSP_IO_PORT_01_PIN_0 = 0x0100,     ///< IO port 1 pin 0
     BSP_IO_PORT_01_PIN_1 = 0x0101,     ///< IO port 1 pin 1
     BSP_IO_PORT_01_PIN_2 = 0x0102,     ///< IO port 1 pin 2
     BSP_IO_PORT_01_PIN_3 = 0x0103,     ///< IO port 1 pin 3
     BSP_IO_PORT_01_PIN_4 = 0x0104,     ///< IO port 1 pin 4
     BSP_IO_PORT_01_PIN_5 = 0x0105,     ///< IO port 1 pin 5
     BSP_IO_PORT_01_PIN_6 = 0x0106,     ///< IO port 1 pin 6
     BSP_IO_PORT_01_PIN_7 = 0x0107,     ///< IO port 1 pin 
     BSP_IO_PORT_02_PIN_0 = 0x0200,     ///< IO port 2 pin 0
     BSP_IO_PORT_02_PIN_1 = 0x0201,     ///< IO port 2 pin 1
     BSP_IO_PORT_02_PIN_2 = 0x0202,     ///< IO port 2 pin 2
     BSP_IO_PORT_02_PIN_3 = 0x0203,     ///< IO port 2 pin 3
     BSP_IO_PORT_02_PIN_4 = 0x0204,     ///< IO port 2 pin 4
     BSP_IO_PORT_02_PIN_5 = 0x0205,     ///< IO port 2 pin 5
     BSP_IO_PORT_02_PIN_6 = 0x0206,     ///< IO port 2 pin 6
     BSP_IO_PORT_02_PIN_7 = 0x0207,     ///< IO port 2 pin 
     BSP_IO_PORT_03_PIN_0 = 0x0300,     ///< IO port 3 pin 0
     BSP_IO_PORT_03_PIN_1 = 0x0301,     ///< IO port 3 pin 1
     BSP_IO_PORT_03_PIN_2 = 0x0302,     ///< IO port 3 pin 2
     BSP_IO_PORT_03_PIN_3 = 0x0303,     ///< IO port 3 pin 3
     BSP_IO_PORT_03_PIN_4 = 0x0304,     ///< IO port 3 pin 4
     BSP_IO_PORT_03_PIN_5 = 0x0305,     ///< IO port 3 pin 5
     BSP_IO_PORT_03_PIN_6 = 0x0306,     ///< IO port 3 pin 6
     BSP_IO_PORT_03_PIN_7 = 0x0307,     ///< IO port 3 pin 
     BSP_IO_PORT_04_PIN_0 = 0x0400,     ///< IO port 4 pin 0
     BSP_IO_PORT_04_PIN_1 = 0x0401,     ///< IO port 4 pin 1
     BSP_IO_PORT_04_PIN_2 = 0x0402,     ///< IO port 4 pin 2
     BSP_IO_PORT_04_PIN_3 = 0x0403,     ///< IO port 4 pin 3
     BSP_IO_PORT_04_PIN_4 = 0x0404,     ///< IO port 4 pin 4
     BSP_IO_PORT_04_PIN_5 = 0x0405,     ///< IO port 4 pin 5
     BSP_IO_PORT_04_PIN_6 = 0x0406,     ///< IO port 4 pin 6
     BSP_IO_PORT_04_PIN_7 = 0x0407,     ///< IO port 4 pin 
     BSP_IO_PORT_05_PIN_0 = 0x0500,     ///< IO port 5 pin 0
     BSP_IO_PORT_05_PIN_1 = 0x0501,     ///< IO port 5 pin 1
     BSP_IO_PORT_05_PIN_2 = 0x0502,     ///< IO port 5 pin 2
     BSP_IO_PORT_05_PIN_3 = 0x0503,     ///< IO port 5 pin 3
     BSP_IO_PORT_05_PIN_4 = 0x0504,     ///< IO port 5 pin 4
     BSP_IO_PORT_05_PIN_5 = 0x0505,     ///< IO port 5 pin 5
     BSP_IO_PORT_05_PIN_6 = 0x0506,     ///< IO port 5 pin 6
     BSP_IO_PORT_05_PIN_7 = 0x0507,     ///< IO port 5 pin 
     BSP_IO_PORT_06_PIN_0 = 0x0600,     ///< IO port 6 pin 0
     BSP_IO_PORT_06_PIN_1 = 0x0601,     ///< IO port 6 pin 1
     BSP_IO_PORT_06_PIN_2 = 0x0602,     ///< IO port 6 pin 2
     BSP_IO_PORT_06_PIN_3 = 0x0603,     ///< IO port 6 pin 3
     BSP_IO_PORT_06_PIN_4 = 0x0604,     ///< IO port 6 pin 4
     BSP_IO_PORT_06_PIN_5 = 0x0605,     ///< IO port 6 pin 5
     BSP_IO_PORT_06_PIN_6 = 0x0606,     ///< IO port 6 pin 6
     BSP_IO_PORT_06_PIN_7 = 0x0607,     ///< IO port 6 pin 
     BSP_IO_PORT_07_PIN_0 = 0x0700,     ///< IO port 7 pin 0
     BSP_IO_PORT_07_PIN_1 = 0x0701,     ///< IO port 7 pin 1
     BSP_IO_PORT_07_PIN_2 = 0x0702,     ///< IO port 7 pin 2
     BSP_IO_PORT_07_PIN_3 = 0x0703,     ///< IO port 7 pin 3
     BSP_IO_PORT_07_PIN_4 = 0x0704,     ///< IO port 7 pin 4
     BSP_IO_PORT_07_PIN_5 = 0x0705,     ///< IO port 7 pin 5
     BSP_IO_PORT_07_PIN_6 = 0x0706,     ///< IO port 7 pin 6
     BSP_IO_PORT_07_PIN_7 = 0x0707,     ///< IO port 7 pin 
     BSP_IO_PORT_08_PIN_0 = 0x0800,     ///< IO port 8 pin 0
     BSP_IO_PORT_08_PIN_1 = 0x0801,     ///< IO port 8 pin 1
     BSP_IO_PORT_08_PIN_2 = 0x0802,     ///< IO port 8 pin 2
     BSP_IO_PORT_08_PIN_3 = 0x0803,     ///< IO port 8 pin 3
     BSP_IO_PORT_08_PIN_4 = 0x0804,     ///< IO port 8 pin 4
     BSP_IO_PORT_08_PIN_5 = 0x0805,     ///< IO port 8 pin 5
     BSP_IO_PORT_08_PIN_6 = 0x0806,     ///< IO port 8 pin 6
     BSP_IO_PORT_08_PIN_7 = 0x0807,     ///< IO port 8 pin 
     BSP_IO_PORT_09_PIN_0 = 0x0900,     ///< IO port 9 pin 0
     BSP_IO_PORT_09_PIN_1 = 0x0901,     ///< IO port 9 pin 1
     BSP_IO_PORT_09_PIN_2 = 0x0902,     ///< IO port 9 pin 2
     BSP_IO_PORT_09_PIN_3 = 0x0903,     ///< IO port 9 pin 3
     BSP_IO_PORT_09_PIN_4 = 0x0904,     ///< IO port 9 pin 4
     BSP_IO_PORT_09_PIN_5 = 0x0905,     ///< IO port 9 pin 5
     BSP_IO_PORT_09_PIN_6 = 0x0906,     ///< IO port 9 pin 6
     BSP_IO_PORT_09_PIN_7 = 0x0907,     ///< IO port 9 pin 
     BSP_IO_PORT_10_PIN_0 = 0x0A00,     ///< IO port 10 pin 0
     BSP_IO_PORT_10_PIN_1 = 0x0A01,     ///< IO port 10 pin 1
     BSP_IO_PORT_10_PIN_2 = 0x0A02,     ///< IO port 10 pin 2
     BSP_IO_PORT_10_PIN_3 = 0x0A03,     ///< IO port 10 pin 3
     BSP_IO_PORT_10_PIN_4 = 0x0A04,     ///< IO port 10 pin 4
     BSP_IO_PORT_10_PIN_5 = 0x0A05,     ///< IO port 10 pin 5
     BSP_IO_PORT_10_PIN_6 = 0x0A06,     ///< IO port 10 pin 6
     BSP_IO_PORT_10_PIN_7 = 0x0A07,     ///< IO port 10 pin 
     BSP_IO_PORT_11_PIN_0 = 0x0B00,     ///< IO port 11 pin 0
     BSP_IO_PORT_11_PIN_1 = 0x0B01,     ///< IO port 11 pin 1
     BSP_IO_PORT_11_PIN_2 = 0x0B02,     ///< IO port 11 pin 2
     BSP_IO_PORT_11_PIN_3 = 0x0B03,     ///< IO port 11 pin 3
     BSP_IO_PORT_11_PIN_4 = 0x0B04,     ///< IO port 11 pin 4
     BSP_IO_PORT_11_PIN_5 = 0x0B05,     ///< IO port 11 pin 5
     BSP_IO_PORT_11_PIN_6 = 0x0B06,     ///< IO port 11 pin 6
     BSP_IO_PORT_11_PIN_7 = 0x0B07,     ///< IO port 11 pin 
     BSP_IO_PORT_12_PIN_0 = 0x0C00,     ///< IO port 12 pin 0
     BSP_IO_PORT_12_PIN_1 = 0x0C01,     ///< IO port 12 pin 1
     BSP_IO_PORT_12_PIN_2 = 0x0C02,     ///< IO port 12 pin 2
     BSP_IO_PORT_12_PIN_3 = 0x0C03,     ///< IO port 12 pin 3
     BSP_IO_PORT_12_PIN_4 = 0x0C04,     ///< IO port 12 pin 4
     BSP_IO_PORT_12_PIN_5 = 0x0C05,     ///< IO port 12 pin 5
     BSP_IO_PORT_12_PIN_6 = 0x0C06,     ///< IO port 12 pin 6
     BSP_IO_PORT_12_PIN_7 = 0x0C07,     ///< IO port 12 pin 
     BSP_IO_PORT_13_PIN_0 = 0x0D00,     ///< IO port 13 pin 0
     BSP_IO_PORT_13_PIN_1 = 0x0D01,     ///< IO port 13 pin 1
     BSP_IO_PORT_13_PIN_2 = 0x0D02,     ///< IO port 13 pin 2
     BSP_IO_PORT_13_PIN_3 = 0x0D03,     ///< IO port 13 pin 3
     BSP_IO_PORT_13_PIN_4 = 0x0D04,     ///< IO port 13 pin 4
     BSP_IO_PORT_13_PIN_5 = 0x0D05,     ///< IO port 13 pin 5
     BSP_IO_PORT_13_PIN_6 = 0x0D06,     ///< IO port 13 pin 6
     BSP_IO_PORT_13_PIN_7 = 0x0D07,     ///< IO port 13 pin 
     BSP_IO_PORT_14_PIN_0 = 0x0E00,     ///< IO port 14 pin 0
     BSP_IO_PORT_14_PIN_1 = 0x0E01,     ///< IO port 14 pin 1
     BSP_IO_PORT_14_PIN_2 = 0x0E02,     ///< IO port 14 pin 2
     BSP_IO_PORT_14_PIN_3 = 0x0E03,     ///< IO port 14 pin 3
     BSP_IO_PORT_14_PIN_4 = 0x0E04,     ///< IO port 14 pin 4
     BSP_IO_PORT_14_PIN_5 = 0x0E05,     ///< IO port 14 pin 5
     BSP_IO_PORT_14_PIN_6 = 0x0E06,     ///< IO port 14 pin 6
     BSP_IO_PORT_14_PIN_7 = 0x0E07,     ///< IO port 14 pin 
     BSP_IO_PORT_15_PIN_0 = 0x0F00,     ///< IO port 15 pin 0
     BSP_IO_PORT_15_PIN_1 = 0x0F01,     ///< IO port 15 pin 1
     BSP_IO_PORT_15_PIN_2 = 0x0F02,     ///< IO port 15 pin 2
     BSP_IO_PORT_15_PIN_3 = 0x0F03,     ///< IO port 15 pin 3
     BSP_IO_PORT_15_PIN_4 = 0x0F04,     ///< IO port 15 pin 4
     BSP_IO_PORT_15_PIN_5 = 0x0F05,     ///< IO port 15 pin 5
     BSP_IO_PORT_15_PIN_6 = 0x0F06,     ///< IO port 15 pin 6
     BSP_IO_PORT_15_PIN_7 = 0x0F07,     ///< IO port 15 pin 
     BSP_IO_PORT_16_PIN_0 = 0x1000,     ///< IO port 16 pin 0
     BSP_IO_PORT_16_PIN_1 = 0x1001,     ///< IO port 16 pin 1
     BSP_IO_PORT_16_PIN_2 = 0x1002,     ///< IO port 16 pin 2
     BSP_IO_PORT_16_PIN_3 = 0x1003,     ///< IO port 16 pin 3
     BSP_IO_PORT_16_PIN_4 = 0x1004,     ///< IO port 16 pin 4
     BSP_IO_PORT_16_PIN_5 = 0x1005,     ///< IO port 16 pin 5
     BSP_IO_PORT_16_PIN_6 = 0x1006,     ///< IO port 16 pin 6
     BSP_IO_PORT_16_PIN_7 = 0x1007,     ///< IO port 16 pin 
     BSP_IO_PORT_17_PIN_0 = 0x1100,     ///< IO port 17 pin 0
     BSP_IO_PORT_17_PIN_1 = 0x1101,     ///< IO port 17 pin 1
     BSP_IO_PORT_17_PIN_2 = 0x1102,     ///< IO port 17 pin 2
     BSP_IO_PORT_17_PIN_3 = 0x1103,     ///< IO port 17 pin 3
     BSP_IO_PORT_17_PIN_4 = 0x1104,     ///< IO port 17 pin 4
     BSP_IO_PORT_17_PIN_5 = 0x1105,     ///< IO port 17 pin 5
     BSP_IO_PORT_17_PIN_6 = 0x1106,     ///< IO port 17 pin 6
     BSP_IO_PORT_17_PIN_7 = 0x1107,     ///< IO port 17 pin 
     BSP_IO_PORT_18_PIN_0 = 0x1200,     ///< IO port 18 pin 0
     BSP_IO_PORT_18_PIN_1 = 0x1201,     ///< IO port 18 pin 1
     BSP_IO_PORT_18_PIN_2 = 0x1202,     ///< IO port 18 pin 2
     BSP_IO_PORT_18_PIN_3 = 0x1203,     ///< IO port 18 pin 3
     BSP_IO_PORT_18_PIN_4 = 0x1204,     ///< IO port 18 pin 4
     BSP_IO_PORT_18_PIN_5 = 0x1205,     ///< IO port 18 pin 5
     BSP_IO_PORT_18_PIN_6 = 0x1206,     ///< IO port 18 pin 6
     BSP_IO_PORT_18_PIN_7 = 0x1207,     ///< IO port 18 pin 
     BSP_IO_PORT_19_PIN_0 = 0x1300,     ///< IO port 19 pin 0
     BSP_IO_PORT_19_PIN_1 = 0x1301,     ///< IO port 19 pin 1
     BSP_IO_PORT_19_PIN_2 = 0x1302,     ///< IO port 19 pin 2
     BSP_IO_PORT_19_PIN_3 = 0x1303,     ///< IO port 19 pin 3
     BSP_IO_PORT_19_PIN_4 = 0x1304,     ///< IO port 19 pin 4
     BSP_IO_PORT_19_PIN_5 = 0x1305,     ///< IO port 19 pin 5
     BSP_IO_PORT_19_PIN_6 = 0x1306,     ///< IO port 19 pin 6
     BSP_IO_PORT_19_PIN_7 = 0x1307,     ///< IO port 19 pin 
     BSP_IO_PORT_20_PIN_0 = 0x1400,     ///< IO port 20 pin 0
     BSP_IO_PORT_20_PIN_1 = 0x1401,     ///< IO port 20 pin 1
     BSP_IO_PORT_20_PIN_2 = 0x1402,     ///< IO port 20 pin 2
     BSP_IO_PORT_20_PIN_3 = 0x1403,     ///< IO port 20 pin 3
     BSP_IO_PORT_20_PIN_4 = 0x1404,     ///< IO port 20 pin 4
     BSP_IO_PORT_20_PIN_5 = 0x1405,     ///< IO port 20 pin 5
     BSP_IO_PORT_20_PIN_6 = 0x1406,     ///< IO port 20 pin 6
     BSP_IO_PORT_20_PIN_7 = 0x1407,     ///< IO port 20 pin 
     BSP_IO_PORT_21_PIN_0 = 0x1500,     ///< IO port 21 pin 0
     BSP_IO_PORT_21_PIN_1 = 0x1501,     ///< IO port 21 pin 1
     BSP_IO_PORT_21_PIN_2 = 0x1502,     ///< IO port 21 pin 2
     BSP_IO_PORT_21_PIN_3 = 0x1503,     ///< IO port 21 pin 3
     BSP_IO_PORT_21_PIN_4 = 0x1504,     ///< IO port 21 pin 4
     BSP_IO_PORT_21_PIN_5 = 0x1505,     ///< IO port 21 pin 5
     BSP_IO_PORT_21_PIN_6 = 0x1506,     ///< IO port 21 pin 6
     BSP_IO_PORT_21_PIN_7 = 0x1507,     ///< IO port 21 pin 
     BSP_IO_PORT_22_PIN_0 = 0x1600,     ///< IO port 22 pin 0
     BSP_IO_PORT_22_PIN_1 = 0x1601,     ///< IO port 22 pin 1
     BSP_IO_PORT_22_PIN_2 = 0x1602,     ///< IO port 22 pin 2
     BSP_IO_PORT_22_PIN_3 = 0x1603,     ///< IO port 22 pin 3
     BSP_IO_PORT_22_PIN_4 = 0x1604,     ///< IO port 22 pin 4
     BSP_IO_PORT_22_PIN_5 = 0x1605,     ///< IO port 22 pin 5
     BSP_IO_PORT_22_PIN_6 = 0x1606,     ///< IO port 22 pin 6
     BSP_IO_PORT_22_PIN_7 = 0x1607,     ///< IO port 22 pin 
     BSP_IO_PORT_23_PIN_0 = 0x1700,     ///< IO port 23 pin 0
     BSP_IO_PORT_23_PIN_1 = 0x1701,     ///< IO port 23 pin 1
     BSP_IO_PORT_23_PIN_2 = 0x1702,     ///< IO port 23 pin 2
     BSP_IO_PORT_23_PIN_3 = 0x1703,     ///< IO port 23 pin 3
     BSP_IO_PORT_23_PIN_4 = 0x1704,     ///< IO port 23 pin 4
     BSP_IO_PORT_23_PIN_5 = 0x1705,     ///< IO port 23 pin 5
     BSP_IO_PORT_23_PIN_6 = 0x1706,     ///< IO port 23 pin 6
     BSP_IO_PORT_23_PIN_7 = 0x1707,     ///< IO port 23 pin 
     BSP_IO_PORT_24_PIN_0 = 0x1800,     ///< IO port 24 pin 0
     BSP_IO_PORT_24_PIN_1 = 0x1801,     ///< IO port 24 pin 1
     BSP_IO_PORT_24_PIN_2 = 0x1802,     ///< IO port 24 pin 2
     BSP_IO_PORT_24_PIN_3 = 0x1803,     ///< IO port 24 pin 3
     BSP_IO_PORT_24_PIN_4 = 0x1804,     ///< IO port 24 pin 4
     BSP_IO_PORT_24_PIN_5 = 0x1805,     ///< IO port 24 pin 5
     BSP_IO_PORT_24_PIN_6 = 0x1806,     ///< IO port 24 pin 6
     BSP_IO_PORT_24_PIN_7 = 0x1807,     ///< IO port 24 pin 7
 } bsp_io_port_pin_t;

/** Superset list of all possible IO ports. */
typedef enum e_bsp_io_port
{
    BSP_IO_PORT_00 = 0x0000,           ///< IO port 0
    BSP_IO_PORT_01 = 0x0100,           ///< IO port 1
    BSP_IO_PORT_02 = 0x0200,           ///< IO port 2
    BSP_IO_PORT_03 = 0x0300,           ///< IO port 3
    BSP_IO_PORT_04 = 0x0400,           ///< IO port 4
    BSP_IO_PORT_05 = 0x0500,           ///< IO port 5
    BSP_IO_PORT_06 = 0x0600,           ///< IO port 6
    BSP_IO_PORT_07 = 0x0700,           ///< IO port 7
    BSP_IO_PORT_08 = 0x0800,           ///< IO port 8
    BSP_IO_PORT_09 = 0x0900,           ///< IO port 9
    BSP_IO_PORT_10 = 0x0A00,           ///< IO port 10
    BSP_IO_PORT_11 = 0x0B00,           ///< IO port 11
    BSP_IO_PORT_12 = 0x0C00,           ///< IO port 12
    BSP_IO_PORT_13 = 0x0D00,           ///< IO port 13
    BSP_IO_PORT_14 = 0x0E00,           ///< IO port 14
    BSP_IO_PORT_15 = 0x0F00,           ///< IO port 15
    BSP_IO_PORT_16 = 0x1000,           ///< IO port 16
    BSP_IO_PORT_17 = 0x1100,           ///< IO port 17
    BSP_IO_PORT_18 = 0x1200,           ///< IO port 18
    BSP_IO_PORT_19 = 0x1300,           ///< IO port 19
    BSP_IO_PORT_20 = 0x1400,           ///< IO port 20
    BSP_IO_PORT_21 = 0x1500,           ///< IO port 21
    BSP_IO_PORT_22 = 0x1600,           ///< IO port 22
    BSP_IO_PORT_23 = 0x1700,           ///< IO port 23
    BSP_IO_PORT_24 = 0x1800,           ///< IO port 24
} bsp_io_port_t;

typedef struct st_ioport_pin_cfg
{
    uint32_t          pin_cfg;         ///< Pin configuration - Use ioport_cfg_options_t parameters to configure
    bsp_io_port_pin_t pin;             ///< Pin identifier
} ioport_pin_cfg_t;

typedef struct st_ioport_cfg
{
    uint16_t                 number_of_pins; ///< Number of pins for which there is configuration data
    ioport_pin_cfg_t         * p_pin_cfg_data; ///< Pin configuration data
    void                     * p_extend;       ///< Pointer to hardware extend configuration
} ioport_cfg_t;

typedef struct st_ioport_instance_ctrl
{
    uint32_t             open;         // Whether or not ioport is open
    void                 * p_context;    // Pointer to context to be passed into callback
    ioport_cfg_t* p_cfg;        // Pointer to the configuration block
} ioport_instance_ctrl_t;


typedef ioport_instance_ctrl_t ioport_ctrl_t;

void ioport_open (ioport_ctrl_t* p_ctrl, ioport_cfg_t* p_cfg);
void enable_pin_access (void);
void disable_pin_access (void);
void pins_config (ioport_cfg_t * p_cfg);