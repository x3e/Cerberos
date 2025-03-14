#ifndef DEFINES_H
#define DEFINES_H

/**
 * @brief st7789 bool enumeration definition
 */
typedef enum
{
    ST7789_BOOL_FALSE = 0x00,        /**< false */
    ST7789_BOOL_TRUE  = 0x01,        /**< true */
} st7789_bool_t;

/**
 * @brief st7789 gamma curve enumeration definition
 */
typedef enum
{
    ST7789_GAMMA_CURVE_1 = 0x1,        /**< g2.2 */
    ST7789_GAMMA_CURVE_2 = 0x2,        /**< g1.8 */
    ST7789_GAMMA_CURVE_3 = 0x4,        /**< g2.5 */
    ST7789_GAMMA_CURVE_4 = 0x8,        /**< g1.0 */
} st7789_gamma_curve_t;

/**
 * @brief st7789 tearing effect enumeration definition
 */
typedef enum
{
    ST7789_TEARING_EFFECT_V_BLANKING                = 0x0,        /**< v-blanking */
    ST7789_TEARING_EFFECT_V_BLANKING_AND_H_BLANKING = 0x1,        /**< v-blanking and h-blanking */
} st7789_tearing_effect_t;

/**
 * @brief st7789 order enumeration definition
 */
typedef enum
{
    ST7789_ORDER_PAGE_TOP_TO_BOTTOM    = (0 << 7),        /**< top to bottom */
    ST7789_ORDER_PAGE_BOTTOM_TO_TOP    = (1 << 7),        /**< bottom to top */
    ST7789_ORDER_COLUMN_LEFT_TO_RIGHT  = (0 << 6),        /**< left to right */
    ST7789_ORDER_COLUMN_RIGHT_TO_LEFT  = (1 << 6),        /**< right to left */
    ST7789_ORDER_PAGE_COLUMN_NORMAL    = (0 << 5),        /**< normal mode */
    ST7789_ORDER_PAGE_COLUMN_REVERSE   = (1 << 5),        /**< reverse mode */
    ST7789_ORDER_LINE_TOP_TO_BOTTOM    = (0 << 4),        /**< lcd refresh top to bottom */
    ST7789_ORDER_LINE_BOTTOM_TO_TOP    = (1 << 4),        /**< lcd refresh bottom to top */
    ST7789_ORDER_COLOR_RGB             = (0 << 3),        /**< rgb */
    ST7789_ORDER_COLOR_BGR             = (1 << 3),        /**< bgr */
    ST7789_ORDER_REFRESH_LEFT_TO_RIGHT = (0 << 2),        /**< lcd refresh left to right */
    ST7789_ORDER_REFRESH_RIGHT_TO_LEFT = (1 << 2),        /**< lcd refresh right to left */
} st7789_order_t;

/**
 * @brief st7789 rgb interface color format enumeration definition
 */
typedef enum
{
    ST7789_RGB_INTERFACE_COLOR_FORMAT_65K  = 0x5,        /**< 65k of rgb interface */
    ST7789_RGB_INTERFACE_COLOR_FORMAT_262K = 0x6,        /**< 262k of rgb interface */
} st7789_rgb_interface_color_format_t;

/**
 * @brief st7789 control interface color format enumeration definition
 */
typedef enum
{
    ST7789_CONTROL_INTERFACE_COLOR_FORMAT_12_BIT = 0x3,        /**< 12bit/pixel */
    ST7789_CONTROL_INTERFACE_COLOR_FORMAT_16_BIT = 0x5,        /**< 16bit/pixel */
    ST7789_CONTROL_INTERFACE_COLOR_FORMAT_18_BIT = 0x6,        /**< 18bit/pixel */
} st7789_control_interface_color_format_t;

/**
 * @brief st7789 color enhancement mode enumeration definition
 */
typedef enum
{
    ST7789_COLOR_ENHANCEMENT_MODE_OFF            = 0x0,        /**< off */
    ST7789_COLOR_ENHANCEMENT_MODE_USER_INTERFACE = 0x1,        /**< user interface mode */
    ST7789_COLOR_ENHANCEMENT_MODE_STILL_PICTURE  = 0x2,        /**< still picture */
    ST7789_COLOR_ENHANCEMENT_MODE_MOVING_IMAGE   = 0x3,        /**< moving image */
} st7789_color_enhancement_mode_t;

/**
 * @brief st7789 color enhancement level enumeration definition
 */
typedef enum
{
    ST7789_COLOR_ENHANCEMENT_LEVEL_LOW    = 0x0,        /**< low enhancement */
    ST7789_COLOR_ENHANCEMENT_LEVEL_MEDIUM = 0x1,        /**< medium enhancement */
    ST7789_COLOR_ENHANCEMENT_LEVEL_HIGH   = 0x3,        /**< high enhancement */
} st7789_color_enhancement_level_t;

#define ST7789_CMD_NOP             0x00        /**< no operation command */
#define ST7789_CMD_SWRESET         0x01        /**< software reset command */
#define ST7789_CMD_SLPIN           0x10        /**< sleep in command */
#define ST7789_CMD_SLPOUT          0x11        /**< sleep out command */
#define ST7789_CMD_PTLON           0x12        /**< partial mode on command */
#define ST7789_CMD_NORON           0x13        /**< normal display mode on command */
#define ST7789_CMD_INVOFF          0x20        /**< display inversion off command */
#define ST7789_CMD_INVON           0x21        /**< display inversion on command */
#define ST7789_CMD_GAMSET          0x26        /**< display inversion set command */
#define ST7789_CMD_DISPOFF         0x28        /**< display off command */
#define ST7789_CMD_DISPON          0x29        /**< display on command */
#define ST7789_CMD_CASET           0x2A        /**< column address set command */
#define ST7789_CMD_RASET           0x2B        /**< row address set command */
#define ST7789_CMD_RAMWR           0x2C        /**< memory write command */
#define ST7789_CMD_PTLAR           0x30        /**< partial start/end address set command */
#define ST7789_CMD_VSCRDEF         0x33        /**< vertical scrolling definition command */
#define ST7789_CMD_TEOFF           0x34        /**< tearing effect line off command */
#define ST7789_CMD_TEON            0x35        /**< tearing effect line on command */
#define ST7789_CMD_MADCTL          0x36        /**< memory data access control command */
#define ST7789_CMD_VSCRSADD        0x37        /**< vertical scrolling start address command */
#define ST7789_CMD_IDMOFF          0x38        /**< idle mode off command */
#define ST7789_CMD_IDMON           0x39        /**< idle mode on command */
#define ST7789_CMD_COLMOD          0x3A        /**< interface pixel format command */
#define ST7789_CMD_RAMWRC          0x3C        /**< memory write continue command */
#define ST7789_CMD_TESCAN          0x44        /**< set tear scanline command */
#define ST7789_CMD_WRDISBV         0x51        /**< write display brightness command */
#define ST7789_CMD_WRCTRLD         0x53        /**< write CTRL display command */
#define ST7789_CMD_WRCACE          0x55        /**< write content adaptive brightness control and color enhancement command */
#define ST7789_CMD_WRCABCMB        0x5E        /**< write CABC minimum brightness command */
#define ST7789_CMD_RAMCTRL         0xB0        /**< ram control command */
#define ST7789_CMD_RGBCTRL         0xB1        /**< rgb control command */
#define ST7789_CMD_PORCTRL         0xB2        /**< porch control command */
#define ST7789_CMD_FRCTRL1         0xB3        /**< frame rate control 1 command */
#define ST7789_CMD_PARCTRL         0xB5        /**< partial mode control command */
#define ST7789_CMD_GCTRL           0xB7        /**< gate control command */
#define ST7789_CMD_GTADJ           0xB8        /**< gate on timing adjustment command */
#define ST7789_CMD_DGMEN           0xBA        /**< digital gamma enable command */
#define ST7789_CMD_VCOMS           0xBB        /**< vcoms setting command */
#define ST7789_CMD_LCMCTRL         0xC0        /**< lcm control command */
#define ST7789_CMD_IDSET           0xC1        /**< id setting command */
#define ST7789_CMD_VDVVRHEN        0xC2        /**< vdv and vrh command enable command */
#define ST7789_CMD_VRHS            0xC3        /**< vrh set command */
#define ST7789_CMD_VDVSET          0xC4        /**< vdv setting command */
#define ST7789_CMD_VCMOFSET        0xC5        /**< vcoms offset set command */
#define ST7789_CMD_FRCTR2          0xC6        /**< fr control 2 command */
#define ST7789_CMD_CABCCTRL        0xC7        /**< cabc control command */
#define ST7789_CMD_REGSEL1         0xC8        /**< register value selection1 command */
#define ST7789_CMD_REGSEL2         0xCA        /**< register value selection2 command */
#define ST7789_CMD_PWMFRSEL        0xCC        /**< pwm frequency selection command */
#define ST7789_CMD_PWCTRL1         0xD0        /**< power control 1 command */
#define ST7789_CMD_VAPVANEN        0xD2        /**< enable vap/van signal output command */
#define ST7789_CMD_CMD2EN          0xDF        /**< command 2 enable command */
#define ST7789_CMD_PVGAMCTRL       0xE0        /**< positive voltage gamma control command */
#define ST7789_CMD_NVGAMCTRL       0xE1        /**< negative voltage gamma control command */
#define ST7789_CMD_DGMLUTR         0xE2        /**< digital gamma look-up table for red command */
#define ST7789_CMD_DGMLUTB         0xE3        /**< digital gamma look-up table for blue command */
#define ST7789_CMD_GATECTRL        0xE4        /**< gate control command */
#define ST7789_CMD_SPI2EN          0xE7        /**< spi2 command */
#define ST7789_CMD_PWCTRL2         0xE8        /**< power control 2 command */
#define ST7789_CMD_EQCTRL          0xE9        /**< equalize time control command */
#define ST7789_CMD_PROMCTRL        0xEC        /**< program control command */
#define ST7789_CMD_PROMEN          0xFA        /**< program mode enable command */
#define ST7789_CMD_NVMSET          0xFC        /**< nvm setting command */
#define ST7789_CMD_PROMACT         0xFE        /**< program action command */

#define ST7789_BASIC_DEFAULT_COLUMN                             240                                             /**< 240 */
#define ST7789_BASIC_DEFAULT_ROW                                320                                             /**< 320 */
#define ST7789_BASIC_DEFAULT_GAMMA_CURVE                        ST7789_GAMMA_CURVE_1
#define ST7789_BASIC_DEFAULT_ACCESS                            (ST7789_ORDER_PAGE_TOP_TO_BOTTOM | \
                                                                ST7789_ORDER_COLUMN_LEFT_TO_RIGHT | \
                                                                ST7789_ORDER_PAGE_COLUMN_NORMAL | \
                                                                ST7789_ORDER_LINE_TOP_TO_BOTTOM | \
                                                                ST7789_ORDER_COLOR_RGB | \
                                                                ST7789_ORDER_REFRESH_LEFT_TO_RIGHT)             /**< access */
#define ST7789_BASIC_DEFAULT_RGB_INTERFACE_COLOR_FORMAT         ST7789_RGB_INTERFACE_COLOR_FORMAT_262K          /**< 262K color format */
#define ST7789_BASIC_DEFAULT_CONTROL_INTERFACE_COLOR_FORMAT     ST7789_CONTROL_INTERFACE_COLOR_FORMAT_16_BIT    /**< 16bit color format */
#define ST7789_BASIC_DEFAULT_BRIGHTNESS                         0xFF                                            /**< 0xFF brightness */
#define ST7789_BASIC_DEFAULT_BRIGHTNESS_BLOCK                   ST7789_BOOL_FALSE                               /**< disable brightness block */
#define ST7789_BASIC_DEFAULT_DISPLAY_DIMMING                    ST7789_BOOL_FALSE                               /**< disable display dimming */
#define ST7789_BASIC_DEFAULT_BACKLIGHT                          ST7789_BOOL_FALSE                               /**< disable backlight */
#define ST7789_BASIC_DEFAULT_COLOR_ENHANCEMENT                  ST7789_BOOL_TRUE                                /**< enable color enhancement */
#define ST7789_BASIC_DEFAULT_COLOR_ENHANCEMENT_MODE             ST7789_COLOR_ENHANCEMENT_MODE_USER_INTERFACE    /**< user interface */
#define ST7789_BASIC_DEFAULT_COLOR_ENHANCEMENT_LEVEL            ST7789_COLOR_ENHANCEMENT_LEVEL_HIGH             /**< high level */
#define ST7789_BASIC_DEFAULT_CABC_MINIMUM_BRIGHTNESS            0x00                                            /**< 0x00 */
#define ST7789_BASIC_DEFAULT_RAM_ACCESS                         ST7789_RAM_ACCESS_MCU                           /**< mcu access */
#define ST7789_BASIC_DEFAULT_DISPLAY_MODE                       ST7789_DISPLAY_MODE_MCU                         /**< mcu display mode */
#define ST7789_BASIC_DEFAULT_FRAME_TYPE                         ST7789_FRAME_TYPE_0                             /**< frame type 0 */
#define ST7789_BASIC_DEFAULT_DATA_MODE                          ST7789_DATA_MODE_MSB                            /**< data mode msb */
#define ST7789_BASIC_DEFAULT_RGB_BUS_WIDTH                      ST7789_RGB_BUS_WIDTH_18_BIT                     /**< 18 bits */
#define ST7789_BASIC_DEFAULT_PIXEL_TYPE                         ST7789_PIXEL_TYPE_0                             /**< pixel type 0 */
#define ST7789_BASIC_DEFAULT_DIRECT_RGB_MODE                    ST7789_DIRECT_RGB_MODE_MEM                      /**< rgb mode mem */
#define ST7789_BASIC_DEFAULT_RGB_IF_ENABLE_MODE                 ST7789_RGB_IF_ENABLE_MODE_MCU                   /**< enable mode mcu */
#define ST7789_BASIC_DEFAULT_VSPL                               ST7789_PIN_LEVEL_LOW                            /**< level low */
#define ST7789_BASIC_DEFAULT_HSPL                               ST7789_PIN_LEVEL_LOW                            /**< level low */
#define ST7789_BASIC_DEFAULT_DPL                                ST7789_PIN_LEVEL_LOW                            /**< level low */
#define ST7789_BASIC_DEFAULT_EPL                                ST7789_PIN_LEVEL_LOW                            /**< level low */
#define ST7789_BASIC_DEFAULT_VBP                                0x02                                            /**< 0x02 */
#define ST7789_BASIC_DEFAULT_HBP                                0x14                                            /**< 0x14 */
#define ST7789_BASIC_DEFAULT_PORCH_NORMAL_BACK                  0x0C                                            /**< 0x0C */
#define ST7789_BASIC_DEFAULT_PORCH_NORMAL_FRONT                 0x0C                                            /**< 0x0C */
#define ST7789_BASIC_DEFAULT_PORCH_ENABLE                       ST7789_BOOL_FALSE                               /**< disable porch */
#define ST7789_BASIC_DEFAULT_PORCH_IDEL_BACK                    0x03                                            /**< 0x03 */
#define ST7789_BASIC_DEFAULT_PORCH_IDEL_FRONT                   0x03                                            /**< 0x03 */
#define ST7789_BASIC_DEFAULT_PORCH_PART_BACK                    0x03                                            /**< 0x03 */
#define ST7789_BASIC_DEFAULT_PORCH_PART_FRONT                   0x03                                            /**< 0x03 */
#define ST7789_BASIC_DEFAULT_SEPARATE_FR                        ST7789_BOOL_FALSE                               /**< disable fr */
#define ST7789_BASIC_DEFAULT_FRAME_RATE_DIVIDED                 ST7789_FRAME_RATE_DIVIDED_CONTROL_DIV_1         /**< div 1 */
#define ST7789_BASIC_DEFAULT_INVERSION_IDLE_MODE                ST7789_INVERSION_IDLE_MODE_DOT                  /**< dot mode */
#define ST7789_BASIC_DEFAULT_IDLE_FRAME_RATE                    0x0F                                            /**< 0x0F */
#define ST7789_BASIC_DEFAULT_INVERSION_PARTIAL_MODE             ST7789_INVERSION_PARTIAL_MODE_DOT               /**< dot mode */
#define ST7789_BASIC_DEFAULT_IDLE_PARTIAL_RATE                  0x0F                                            /**< 0x0F */
#define ST7789_BASIC_DEFAULT_NON_DISPLAY_SOURCE_OUTPUT_LEVEL    ST7789_NON_DISPLAY_SOURCE_OUTPUT_LEVEL_V63      /**< v63 */
#define ST7789_BASIC_DEFAULT_NON_DISPLAY_AREA_SCAN_MODE         ST7789_NON_DISPLAY_AREA_SCAN_MODE_NORMAL        /**< normal scan mode */
#define ST7789_BASIC_DEFAULT_NON_DISPLAY_FRAME_FREQUENCY        ST7789_NON_DISPLAY_FRAME_FREQUENCY_EVERY        /**< every frame */
#define ST7789_BASIC_DEFAULT_VGHS                               ST7789_VGHS_14P97_V                             /**< 14.97V */
#define ST7789_BASIC_DEFAULT_VGLS_NEGATIVE                      ST7789_VGLS_NEGATIVE_8P23                       /**< -8.23 */
#define ST7789_BASIC_DEFAULT_GATE_ON_TIMING                     0x22                                            /**< 0x22 */
#define ST7789_BASIC_DEFAULT_GATE_OFF_TIMING_RGB                0x07                                            /**< 0x07 */
#define ST7789_BASIC_DEFAULT_GATE_OFF_TIMING                    0x05                                            /**< 0x05 */
#define ST7789_BASIC_DEFAULT_DIGITAL_GAMMA                      ST7789_BOOL_TRUE                                /**< enable digital gamma */
#define ST7789_BASIC_DEFAULT_VCOMS                              1.625f                                          /**< 1.625 vcoms */
#define ST7789_BASIC_DEFAULT_XMY                                ST7789_BOOL_FALSE                               /**< disable xmy */
#define ST7789_BASIC_DEFAULT_XBGR                               ST7789_BOOL_TRUE                                /**< enable xbgr */
#define ST7789_BASIC_DEFAULT_XINV                               ST7789_BOOL_FALSE                               /**< disable xinv */
#define ST7789_BASIC_DEFAULT_XMX                                ST7789_BOOL_TRUE                                /**< enable xmx */
#define ST7789_BASIC_DEFAULT_XMH                                ST7789_BOOL_TRUE                                /**< enable xmh */
#define ST7789_BASIC_DEFAULT_XMV                                ST7789_BOOL_FALSE                               /**< disable xmv */
#define ST7789_BASIC_DEFAULT_XGS                                ST7789_BOOL_FALSE                               /**< disable xgs */
#define ST7789_BASIC_DEFAULT_VDV_VRH_FROM                       ST7789_VDV_VRH_FROM_CMD                         /**< from cmd */
#define ST7789_BASIC_DEFAULT_VRHS                               4.8f                                            /**< 4.8 */
#define ST7789_BASIC_DEFAULT_VDV                                0.0f                                            /**< 0.0 */
#define ST7789_BASIC_DEFAULT_VCOMS_OFFSET                       0.0f                                            /**< 0.0 */
#define ST7789_BASIC_DEFAULT_INVERSION_SELECTION                ST7789_INVERSION_SELECTION_DOT                  /**< dot */
#define ST7789_BASIC_DEFAULT_FRAME_RATE                         ST7789_FRAME_RATE_60_HZ                         /**< frame rate 60Hz */
#define ST7789_BASIC_DEFAULT_LED_ON                             ST7789_BOOL_FALSE                               /**< disable led on */
#define ST7789_BASIC_DEFAULT_LED_PWM_INIT                       ST7789_BOOL_FALSE                               /**< disable led pwm init */
#define ST7789_BASIC_DEFAULT_LED_PWM_FIX                        ST7789_BOOL_FALSE                               /**< disable led pwm fix */
#define ST7789_BASIC_DEFAULT_LED_PWM_POLARITY                   ST7789_BOOL_FALSE                               /**< disable led pwm polarity */
#define ST7789_BASIC_DEFAULT_PWM_FREQUENCY                      ST7789_PWM_FREQUENCY_9P8_KHZ                    /**< pwm 9.8KHz */
#define ST7789_BASIC_DEFAULT_AVDD                               ST7789_AVDD_6P8_V                               /**< 6.8V */
#define ST7789_BASIC_DEFAULT_AVCL_NEGTIVE                       ST7789_AVCL_NEGTIVE_4P8_V                       /**< -4.8V */
#define ST7789_BASIC_DEFAULT_VDS                                ST7789_VDS_2P3_V                                /**< 2.3V */
#define ST7789_BASIC_DEFAULT_COMMAND_2_ENABLE                   ST7789_BOOL_FALSE                               /**< disable command 2 */
#define ST7789_BASIC_DEFAULT_POSITIVE_VOLTAGE_GAMMA            {0xD0, 0x04, 0x0D, 0x11, 0x13, 0x2B, 0x3F, \
                                                                0x54, 0x4C, 0x18, 0x0D, 0x0B, 0x1F, 0x23}       /**< gamma */
#define ST7789_BASIC_DEFAULT_NEGATIVA_VOLTAGE_GAMMA            {0xD0, 0x04, 0x0C, 0x11, 0x13, 0x2C, 0x3F, \
                                                                0x44, 0x51, 0x2F, 0x1F, 0x1F, 0x20, 0x23}       /**< gamma */
#define ST7789_BASIC_DEFAULT_GATE_LINE                          320                                             /**< 320 */
#define ST7789_BASIC_DEFAULT_FIRST_SCAN_LINE                    0x00                                            /**< 0x00 */
#define ST7789_BASIC_DEFAULT_GATE_SCAN_MODE                     ST7789_GATE_SCAN_MODE_INTERLACE                 /**< interlace */
#define ST7789_BASIC_DEFAULT_GATE_SCAN_DIRECTION                ST7789_GATE_SCAN_DIRECTION_0_319                /**< 320 */
#define ST7789_BASIC_DEFAULT_SPI2_LANE                          ST7789_BOOL_FALSE                               /**< disable */
#define ST7789_BASIC_DEFAULT_COMMAND_TABLE_2                    ST7789_BOOL_FALSE                               /**< disable command table2 */
#define ST7789_BASIC_DEFAULT_SBCLK_DIV                          ST7789_SBCLK_DIV_3                              /**< div3 */
#define ST7789_BASIC_DEFAULT_STP14CK_DIV                        ST7789_STP14CK_DIV_6                            /**< div6 */
#define ST7789_BASIC_DEFAULT_SOURCE_EQUALIZE_TIME               0x11                                            /**< 0x11 */
#define ST7789_BASIC_DEFAULT_SOURCE_PRE_DRIVE_TIME              0x11                                            /**< 0x11 */
#define ST7789_BASIC_DEFAULT_GATE_EQUALIZE_TIME                 0x08                                            /**< 0x08 */
#define ST7789_BASIC_DEFAULT_PROGRAM_MODE                       ST7789_BOOL_FALSE                               /**< disable program mode */

#endif