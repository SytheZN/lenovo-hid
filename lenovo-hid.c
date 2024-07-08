// SPDX-License-Identifier: GPL-2.0+
/*
 * HID driver for Lenovo Legion Go
 *
 * Copyright (c) 2024 Trevor Heslop <sythe.zn@gmail.com>
 * Based on original work by Antheas Kapenekakis for HHD
 * <https://github.com/hhd-dev/hhd>
 *
 * Provides RGB LED control via led_class_multicolor sysfs interface and
 * Controller support.
 */
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/hid.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>



MODULE_AUTHOR("Trevor Heslop <sythe.zn@gmail.com>");
MODULE_DESCRIPTION("HID driver for Lenovo Legion Go");
MODULE_LICENSE("GPL");