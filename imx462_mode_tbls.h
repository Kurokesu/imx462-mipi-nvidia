#ifndef __IMX462_MODE_TBLS_H__
#define __IMX462_MODE_TBLS_H__

#include <media/camera_common.h>
#include <linux/miscdevice.h>

#define IMX462_TABLE_WAIT_MS	0
#define IMX462_TABLE_END	1
#define IMX462_MAX_RETRIES	3
#define IMX462_WAIT_MS 1

#define IMX462_STANDBY 0x3000
#define IMX462_XMSTA   0x3002

#define IMX462_WINWV_OB	 0x303a
#define IMX462_WINPH_LSB 0x3040
#define IMX462_WINPH_MSB 0x3041
#define IMX462_WINPV_LSB 0x303c
#define IMX462_WINPV_MSB 0x303d
#define IMX462_WINWH_LSB 0x3042
#define IMX462_WINWH_MSB 0x3043
#define IMX462_WINWV_LSB 0x303e
#define IMX462_WINWV_MSB 0x303f
#define IMX462_XSOUTSEL	 0x304b

#define IMX462_EXTCK_FREQ_LSB 0x3444
#define IMX462_EXTCK_FREQ_MSB 0x3445
#define IMX462_INCKSEL7       0x3480

#define IMX462_INCKSEL1 0x305c
#define IMX462_INCKSEL2 0x305d
#define IMX462_INCKSEL3 0x305e
#define IMX462_INCKSEL4 0x305f
#define IMX462_INCKSEL5 0x315e
#define IMX462_INCKSEL6 0x3164

#define IMX462_PHY_LANE_NUM  0x3407
#define IMX462_CSI_LANE_MODE 0x3443
#define IMX462_FR_FDG_SEL    0x3009

#define IMX462_REPETITION    0x3405
#define IMX462_TCLKPOST		 0x3446
#define IMX462_THSZERO		 0x3448
#define IMX462_THSPREPARE	 0x344a
#define IMX462_TCLKTRAIL	 0x344c
#define IMX462_THSTRAIL		 0x344e
#define IMX462_TCLKZERO		 0x3450
#define IMX462_TCLKPREPARE	 0x3452
#define IMX462_TLPX			 0x3454

#define IMX462_ADBIT      0x3005
#define IMX462_OUT_CTRL   0x3046
#define IMX462_ADBIT1     0x3129
#define IMX462_ADBIT2     0x317c
#define IMX462_ADBIT3     0x31ec
#define IMX462_CSI_DT_FMT_LSB 0x3441
#define IMX462_CSI_DT_FMT_MSB 0x3442
#define IMX462_BLKLEVEL   0x300a
#define IMX462_OPB_SIZE_V 0x3414
#define IMX462_X_OUT_SIZE_LSB 0x3472
#define IMX462_X_OUT_SIZE_MSB 0x3473
#define IMX462_Y_OUT_SIZE_LSB 0x3418
#define IMX462_Y_OUT_SIZE_MSB 0x3419

#define IMX462_GAIN 0x3014
// #define IMX462_VMAX					CCI_REG24_LE(0x3018)
#define IMX462_SHS1_LSB 0x3020
#define IMX462_HMAX_LSB 0x301c
#define IMX462_HMAX_MSB 0x301d

#define imx462_reg struct reg_8

/* IMX462 Start Streaming */
static imx462_reg imx462_start[] = {
	{IMX462_STANDBY, 0x00}, /* Operating */
	{IMX462_TABLE_WAIT_MS, IMX462_WAIT_MS*30},
	{IMX462_XMSTA, 0x00}, /* Start master mode operation */
	{IMX462_TABLE_END, 0x00}
};

/* IMX462 Stop Streaming */
static imx462_reg imx462_stop[] = {
	{IMX462_STANDBY, 0x01}, /* Software Standby */
	{IMX462_TABLE_WAIT_MS, IMX462_WAIT_MS*30},
	{IMX462_XMSTA, 0x01}, /* Stop master mode operation */
	{IMX462_TABLE_END, 0x00},
};

/* IMX462 Common Mode */
static imx462_reg imx462_mode_common[] = {
	/* imx290_global_init_settings */
	{IMX462_WINWV_OB, 12},
	{IMX462_WINPH_LSB, 0},
	{IMX462_WINPH_MSB, 0},
	{IMX462_WINPV_LSB, 0},
	{IMX462_WINPV_MSB, 0},
	{IMX462_WINWH_LSB, 1948 & 0xFF},
	{IMX462_WINWH_MSB, (1948 >> 8) & 0x07},
	{IMX462_WINWV_LSB, 1097 & 0xFF},
	{IMX462_WINWV_MSB, (1097 >> 8) & 0x07},
	{IMX462_XSOUTSEL, 0}, /* HSYNC output enabled in original */
	{0x3012, 0x64},
	{0x3013, 0x00},
	/* imx290->model->init_regs */
	{0x300f, 0x00},
	{0x3010, 0x21},
	{0x3011, 0x02},
	{0x3016, 0x09},
	{0x3070, 0x02},
	{0x3071, 0x11},
	{0x309b, 0x10},
	{0x309c, 0x22},
	{0x30a2, 0x02},
	{0x30a6, 0x20},
	{0x30a8, 0x20},
	{0x30aa, 0x20},
	{0x30ac, 0x20},
	{0x30b0, 0x43},
	{0x3119, 0x9e},
	{0x311c, 0x1e},
	{0x311e, 0x08},
	{0x3128, 0x05},
	{0x313d, 0x83},
	{0x3150, 0x03},
	{0x317e, 0x00},
	{0x32b8, 0x50},
	{0x32b9, 0x10},
	{0x32ba, 0x00},
	{0x32bb, 0x04},
	{0x32c8, 0x50},
	{0x32c9, 0x10},
	{0x32ca, 0x00},
	{0x32cb, 0x04},
	{0x332c, 0xd3},
	{0x332d, 0x10},
	{0x332e, 0x0d},
	{0x3358, 0x06},
	{0x3359, 0xe1},
	{0x335a, 0x11},
	{0x3360, 0x1e},
	{0x3361, 0x61},
	{0x3362, 0x10},
	{0x33b0, 0x50},
	{0x33b2, 0x1a},
	{0x33b3, 0x04},
	/* imx290_set_clock */
	{IMX462_EXTCK_FREQ_LSB, 0x20}, /* 37.125MHz */
	{IMX462_EXTCK_FREQ_MSB, 0x25},
	{IMX462_INCKSEL7, 0x49},
    {IMX462_INCKSEL1, 0x18},
	{IMX462_INCKSEL2, 0x03},
	{IMX462_INCKSEL3, 0x20},
	{IMX462_INCKSEL4, 0x01},
	{IMX462_INCKSEL5, 0x1a},
	{IMX462_INCKSEL6, 0x1a},
	/* imx290_set_data_lanes */
	{IMX462_PHY_LANE_NUM, 1}, /* 2 lanes */
    {IMX462_CSI_LANE_MODE, 1}, /* 2 lanes */
    {IMX462_FR_FDG_SEL, 0}, /* hcg disabled, TODO: check */
    /* imx290_set_csi_config */
	{IMX462_REPETITION, 0x00},
    {IMX462_TCLKPOST, 103},
    {IMX462_THSZERO, 87},
    {IMX462_THSPREPARE, 47},
    {IMX462_TCLKTRAIL, 39},
    {IMX462_THSTRAIL, 47},
    {IMX462_TCLKZERO, 191},
    {IMX462_TCLKPREPARE, 47},
	{IMX462_TLPX, 39},
	{IMX462_TABLE_END, 0x00},
};

/* IMX462 1920x1080 2-lane mode */
static imx462_reg imx462_mode_1920x1080[] = {
	/* imx290_setup_format */
	{IMX462_ADBIT, 0},
	{IMX462_OUT_CTRL, 0},
	{IMX462_ADBIT1, 0x1D},
	{IMX462_ADBIT2, 0x12},
	{IMX462_ADBIT3, 0x37},
	{IMX462_CSI_DT_FMT_LSB, 0x0A},
	{IMX462_CSI_DT_FMT_MSB, 0x0A},
	/* imx290_set_black_level*/
	{IMX462_BLKLEVEL, 0x3C},
	/* imx290->current_mode->data */
	{IMX462_WINWV_OB, 12},
	{IMX462_OPB_SIZE_V, 10},
	{IMX462_X_OUT_SIZE_LSB, 1920 & 0xFF},
	{IMX462_X_OUT_SIZE_MSB, (1920 >> 8) & 0x1F},
	{IMX462_Y_OUT_SIZE_LSB, 1080 & 0xFF},
	{IMX462_Y_OUT_SIZE_MSB, (1080 >> 8) & 0x1F},
	/* v4l2_ctrl_handler_setup */
	{IMX462_GAIN, 0x00},
	// { IMX462_VMAX, 1125 },
	{IMX462_SHS1_LSB, 11},
	{IMX462_HMAX_LSB, 2200 & 0xFF},
	{IMX462_HMAX_MSB, (2200 >> 8) & 0xFF},
	{IMX462_TABLE_END, 0x0},
};

/* IMX462 1920x1080 4-lane mode */
static imx462_reg imx462_mode_1920x1080_4lane[] = {
	{0x0104, 0x01}, /* Grouped Parameter Hold */
	{0x0220, 0x00}, /* Data Format Select */
	{0x0222, 0x10}, /* 10-bit Output */
	{0x0340, 0x0C}, /* Frame Length MSB */
	{0x0341, 0x30}, /* Frame Length LSB */
	{0x0342, 0x13}, /* Line Length MSB */
	{0x0343, 0x20}, /* Line Length LSB */
	{0x0344, 0x00}, /* X Start MSB */
	{0x0345, 0x00}, /* X Start LSB */
	{0x0346, 0x00}, /* Y Start MSB */
	{0x0347, 0x00}, /* Y Start LSB */
	{0x0348, 0x07}, /* X End MSB */
	{0x0349, 0x7F}, /* X End LSB */
	{0x034A, 0x04}, /* Y End MSB */
	{0x034B, 0x3F}, /* Y End LSB */
	{0x0104, 0x00}, /* Grouped Parameter Hold */
	{IMX462_TABLE_END, 0x00}
};

enum {
	IMX462_MODE_1920X1080,
	IMX462_MODE_1920X1080_4LANE,
	IMX462_MODE_COMMON,
	IMX462_START_STREAM,
	IMX462_STOP_STREAM,
};

static imx462_reg *mode_table[] = {
	[IMX462_MODE_1920X1080] = imx462_mode_1920x1080,
	[IMX462_MODE_1920X1080_4LANE] = imx462_mode_1920x1080_4lane,
	[IMX462_MODE_COMMON] = imx462_mode_common,
	[IMX462_START_STREAM] = imx462_start,
	[IMX462_STOP_STREAM] = imx462_stop,
};

static const int imx462_30fps[] = {
	30,
};

/*
 * WARNING: frmfmt ordering need to match mode definition in
 * device tree!
 */
static const struct camera_common_frmfmt imx462_frmfmt[] = {
	{{1920, 1080}, imx462_30fps, 1, 0, IMX462_MODE_1920X1080},
};

#endif /* __IMX462_MODE_TBLS_H__ */ 
