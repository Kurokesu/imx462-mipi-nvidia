/*
 * IMX462 sensor header file
 * Developed by UAB Kurokesu
 */

#ifndef __IMX462_H__
#define __IMX462_H__

#include <media/tegracam_core.h>

/* IMX462 sensor register definitions */
#define IMX462_MODEL_ID_ADDR_MSB			0x0000
#define IMX462_MODEL_ID_ADDR_LSB			0x0001
#define IMX462_FRAME_LENGTH_ADDR_MSB			0x0340
#define IMX462_FRAME_LENGTH_ADDR_LSB			0x0341
#define IMX462_COARSE_INTEG_TIME_ADDR_MSB		0x0202
#define IMX462_COARSE_INTEG_TIME_ADDR_LSB		0x0203
#define IMX462_FINE_INTEG_TIME_ADDR_MSB		0x0200
#define IMX462_FINE_INTEG_TIME_ADDR_LSB		0x0201
#define IMX462_ANALOG_GAIN_ADDR_MSB			0x0204
#define IMX462_ANALOG_GAIN_ADDR_LSB			0x0205
#define IMX462_GROUP_HOLD_ADDR				0x0104

/* IMX462 sensor constants */
#define IMX462_SENSOR_INTERNAL_CLK_FREQ		840000000
#define IMX462_ANALOG_GAIN_C0				0x10
#define IMX462_MIN_GAIN					0x10
#define IMX462_MAX_GAIN					0x78
#define IMX462_MIN_FRAME_LENGTH				0x0008
#define IMX462_MAX_FRAME_LENGTH				0xffff
#define IMX462_MIN_COARSE_EXPOSURE			0x0001
#define IMX462_MAX_COARSE_DIFF				0x0008
#define IMX462_SHIFT_8_BITS				8
#define IMX462_MASK_LSB_2_BITS				0x03
#define IMX462_MASK_LSB_8_BITS				0xff
#define IMX462_TABLE_WAIT_MS				0
#define IMX462_TABLE_END				1

/* IMX462 mode table indices */
#define IMX462_MODE_COMMON				0
#define IMX462_START_STREAM				1
#define IMX462_STOP_STREAM				2

/* IMX462 register structure */
struct imx462_reg {
	u16 addr;
	u8 val;
};

/* IMX462 frame format structure */
struct imx462_frmfmt {
	u32 width;
	u32 height;
	u32 max_framerate;
	u8 lanes;
	u8 bitsperpixel;
	u32 flags;
	u8 version;
};

/* IMX462 mode table type */
typedef struct imx462_reg imx462_reg;

/* External declarations */
extern const struct imx462_reg mode_table[];
extern const struct imx462_frmfmt imx462_frmfmt[];

#endif /* __IMX462_H__ */ 