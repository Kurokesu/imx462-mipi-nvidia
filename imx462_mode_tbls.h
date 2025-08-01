#ifndef __IMX462_MODE_TBLS_H__
#define __IMX462_MODE_TBLS_H__

#include "imx462.h"

/* IMX462 Common Mode Settings */
static const struct imx462_reg mode_table_common[] = {
	{0x0100, 0x00}, /* Software Standby */
	{0x0103, 0x01}, /* Software Reset */
	{0x0101, 0x00}, /* Output Data Format Select */
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
	{0x0348, 0x0C}, /* X End MSB */
	{0x0349, 0xCF}, /* X End LSB */
	{0x034A, 0x09}, /* Y End MSB */
	{0x034B, 0x9F}, /* Y End LSB */
	{0x0202, 0x00}, /* Coarse Integration Time MSB */
	{0x0203, 0x01}, /* Coarse Integration Time LSB */
	{0x0204, 0x00}, /* Analog Gain MSB */
	{0x0205, 0x00}, /* Analog Gain LSB */
	{0x0104, 0x00}, /* Grouped Parameter Hold */
	{0x0100, 0x01}, /* Software Standby */
	{IMX462_TABLE_END, 0x00}
};

/* IMX462 Start Streaming */
static const struct imx462_reg mode_table_start_stream[] = {
	{0x0100, 0x01}, /* Software Standby */
	{IMX462_TABLE_END, 0x00}
};

/* IMX462 Stop Streaming */
static const struct imx462_reg mode_table_stop_stream[] = {
	{0x0100, 0x00}, /* Software Standby */
	{IMX462_TABLE_END, 0x00}
};

/* IMX462 1920x1080 2-lane mode */
static const struct imx462_reg mode_table_1920x1080_2lane[] = {
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

/* IMX462 1920x1080 4-lane mode */
static const struct imx462_reg mode_table_1920x1080_4lane[] = {
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

/* IMX462 Frame Formats */
static const struct imx462_frmfmt imx462_frmfmt[] = {
	{
		.width = 1920,
		.height = 1080,
		.max_framerate = 30,
		.lanes = 2,
		.bitsperpixel = 10,
		.flags = 0,
		.version = 1,
	},
	{
		.width = 1920,
		.height = 1080,
		.max_framerate = 30,
		.lanes = 4,
		.bitsperpixel = 10,
		.flags = 0,
		.version = 1,
	},
};

/* IMX462 Mode Table Array */
static const struct imx462_reg *mode_table[] = {
	mode_table_common,
	mode_table_start_stream,
	mode_table_stop_stream,
	mode_table_1920x1080_2lane,
	mode_table_1920x1080_4lane,
};

#endif /* __IMX462_MODE_TBLS_H__ */ 