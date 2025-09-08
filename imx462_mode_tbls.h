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

#define IMX462_WINWV_OB	 0x303A
#define IMX462_WINPH_LSB 0x3040
#define IMX462_WINPH_MSB 0x3041
#define IMX462_WINPV_LSB 0x303C
#define IMX462_WINPV_MSB 0x303D
#define IMX462_WINWH_LSB 0x3042
#define IMX462_WINWH_MSB 0x3043
#define IMX462_WINWV_LSB 0x303E
#define IMX462_WINWV_MSB 0x303F
#define IMX462_XSOUTSEL	 0x304B

#define IMX462_EXTCK_FREQ_LSB 0x3444
#define IMX462_EXTCK_FREQ_MSB 0x3445
#define IMX462_INCKSEL7       0x3480

#define IMX462_INCKSEL1 0x305C
#define IMX462_INCKSEL2 0x305D
#define IMX462_INCKSEL3 0x305E
#define IMX462_INCKSEL4 0x305F
#define IMX462_INCKSEL5 0x315E
#define IMX462_INCKSEL6 0x3164

#define IMX462_PHY_LANE_NUM  0x3407
#define IMX462_CSI_LANE_MODE 0x3443
#define IMX462_FR_FDG_SEL    0x3009

#define IMX462_REPETITION    0x3405
#define IMX462_TCLKPOST		 0x3446
#define IMX462_THSZERO		 0x3448
#define IMX462_THSPREPARE	 0x344A
#define IMX462_TCLKTRAIL	 0x344C
#define IMX462_THSTRAIL		 0x344E
#define IMX462_TCLKZERO		 0x3450
#define IMX462_TCLKPREPARE	 0x3452
#define IMX462_TLPX			 0x3454

#define IMX462_ADBIT      0x3005
#define IMX462_OUT_CTRL   0x3046
#define IMX462_ADBIT1     0x3129
#define IMX462_ADBIT2     0x317C
#define IMX462_ADBIT3     0x31EC
#define IMX462_CSI_DT_FMT_LSB 0x3441
#define IMX462_CSI_DT_FMT_MSB 0x3442
#define IMX462_BLKLEVEL   0x300A
#define IMX462_OPB_SIZE_V 0x3414
#define IMX462_X_OUT_SIZE_LSB 0x3472
#define IMX462_X_OUT_SIZE_MSB 0x3473
#define IMX462_Y_OUT_SIZE_LSB 0x3418
#define IMX462_Y_OUT_SIZE_MSB 0x3419

#define IMX462_GAIN 0x3014
// #define IMX462_VMAX					CCI_REG24_LE(0x3018)
#define IMX462_SHS1_LSB 0x3020
#define IMX462_HMAX_LSB 0x301C
#define IMX462_HMAX_MSB 0x301D

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
	{IMX462_WINWH_MSB, (1948 >> 8) & 0xFF},
	{IMX462_WINWV_LSB, 1097 & 0xFF},
	{IMX462_WINWV_MSB, (1097 >> 8) & 0xFF},
	{IMX462_XSOUTSEL, 0x0A}, /* HSYNC output enabled in original */
	{0x3012, 0x64},
	{0x3013, 0x00},
	/* imx290->model->init_regs */
	{0x300F, 0x00},
	{0x3010, 0x21},
	{0x3011, 0x02},
	{0x3016, 0x09},
	{0x3070, 0x02},
	{0x3071, 0x11},
	{0x309B, 0x10},
	{0x309C, 0x22},
	{0x30A2, 0x02},
	{0x30A6, 0x20},
	{0x30A8, 0x20},
	{0x30AA, 0x20},
	{0x30AC, 0x20},
	{0x30B0, 0x43},
	{0x3119, 0x9E},
	{0x311C, 0x1E},
	{0x311E, 0x08},
	{0x3128, 0x05},
	{0x313D, 0x83},
	{0x3150, 0x03},
	{0x317E, 0x00},
	{0x32B8, 0x50},
	{0x32B9, 0x10},
	{0x32BA, 0x00},
	{0x32BB, 0x04},
	{0x32C8, 0x50},
	{0x32C9, 0x10},
	{0x32CA, 0x00},
	{0x32CB, 0x04},
	{0x332C, 0xD3},
	{0x332D, 0x10},
	{0x332E, 0x0d},
	{0x3358, 0x06},
	{0x3359, 0xE1},
	{0x335A, 0x11},
	{0x3360, 0x1E},
	{0x3361, 0x61},
	{0x3362, 0x10},
	{0x33B0, 0x50},
	{0x33B2, 0x1A},
	{0x33B3, 0x04},
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
	{IMX462_PHY_LANE_NUM, 0x01}, /* 2 lanes */
    {IMX462_CSI_LANE_MODE, 0x01}, /* 2 lanes */
    {IMX462_FR_FDG_SEL, 0x02}, /* lcg mode 30fps */
    /* imx290_set_csi_config */
	{IMX462_REPETITION, 0x10},
    {IMX462_TCLKPOST, 0x57},
    {IMX462_THSZERO, 0x37},
    {IMX462_THSPREPARE, 0x1F},
    {IMX462_TCLKTRAIL, 0x1F},
    {IMX462_THSTRAIL, 0x1F},
    {IMX462_TCLKZERO, 0x77},
    {IMX462_TCLKPREPARE, 0x1F},
	{IMX462_TLPX, 0x17},
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
	{IMX462_OPB_SIZE_V, 0x0A},
	{IMX462_X_OUT_SIZE_LSB, 1920 & 0xFF},
	{IMX462_X_OUT_SIZE_MSB, (1920 >> 8) & 0xFF},
	{IMX462_Y_OUT_SIZE_LSB, 1080 & 0xFF},
	{IMX462_Y_OUT_SIZE_MSB, (1080 >> 8) & 0xFF},
	/* v4l2_ctrl_handler_setup */
	{IMX462_GAIN, 0x00},
	// { IMX462_VMAX, 1125 }, // TODO: Default is 1125, see if needs rewriting
	{IMX462_SHS1_LSB, 11},
	{IMX462_HMAX_LSB, 4400 & 0xFF},
	{IMX462_HMAX_MSB, (4400 >> 8) & 0xFF},
	{IMX462_TABLE_END, 0x0},
};

static imx462_reg imx462_mode_test_pattern[] = {
	{IMX462_BLKLEVEL, 0x00},
	{IMX462_TABLE_WAIT_MS, IMX462_WAIT_MS*10},
};

enum {
	IMX462_MODE_1920X1080,
	IMX462_MODE_COMMON,
	IMX462_START_STREAM,
	IMX462_STOP_STREAM,
	IMX462_MODE_TEST_PATTERN,
};

static imx462_reg *mode_table[] = {
	[IMX462_MODE_1920X1080] = imx462_mode_1920x1080,
	[IMX462_MODE_COMMON] = imx462_mode_common,
	[IMX462_START_STREAM] = imx462_start,
	[IMX462_STOP_STREAM] = imx462_stop,
	[IMX462_MODE_TEST_PATTERN] = imx462_mode_test_pattern,
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
