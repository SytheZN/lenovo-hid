// SPDX-License-Identifier: GPL-2.0+
/*
 *  HID driver for Lenovo Legion Go
 *
 *  Copyright (c) 2024 Trevor Heslop <sythe.zn@gmail.com>
 *  Based on original work by Antheas Kapenekakis for HHD
 *  <https://github.com/hhd-dev/hhd>
 *
 *  Provides RGB LED control via led_class_multicolor sysfs interface and
 *  Controller support.
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/hid.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include "lenovo-hid.h"

/*
 *  Control packets are generally formatted as
 *
 *  [HEADER][LENGTH][COMMAND][CONTROLLER]([PARAM]...[PARAM])[FOOTER]
 *
 *  Length includes the length byte and footer byte, but excludes header.
 */

static u8* lenovo_get_packet_rgb_store_profile(void)
{
  u8 ret[] = {
    LENOVO_HEADER_START,
    12,
    LENOVO_CMD_RGB_PROFILE_STORE,
    LENOVO_CONTROLLER_ID_LEFT,
    LENOVO_VAL_RGB_MODE_SOLID,
    0x00, // red (0-255)
    0x00, // green (0-255)
    0x00, // blue (0-255)
    0x00, // brightness (0-63)
    0x00, // period (0-63)
    LENOVO_VAL_RGB_PROFILE_ID_1,
    LENOVO_FOOTER_END
  };

  return ret;
}

static u8* lenovo_get_packet_rgb_load_profile(void)
{
  u8 ret[] = {
    LENOVO_HEADER_START,
    6,
    LENOVO_CMD_RGB_PROFILE_LOAD,
    LENOVO_CONTROLLER_ID_LEFT,
    LENOVO_VAL_RGB_PROFILE_ID_1,
    LENOVO_FOOTER_END
  };

  return ret;
}

static u8* lenovo_get_packet_rgb_enable(void)
{
  u8 ret[] = {
    LENOVO_HEADER_START,
    6,
    LENOVO_CMD_RGB_ENABLE,
    LENOVO_CONTROLLER_ID_LEFT,
    LENOVO_VAL_RGB_ENABLE_OFF,
    LENOVO_FOOTER_END
  };

  return ret;
}

static u8* lenovo_get_packet_gyro_enable(void)
{
  u8 ret[] = {
    LENOVO_HEADER_START,
    6,
    LENOVO_CMD_GYRO_ENABLE,
    LENOVO_CONTROLLER_ID_LEFT,
    LENOVO_VAL_GYRO_ENABLE_ON,
    LENOVO_FOOTER_END
  };

  return ret;
}

static u8* lenovo_get_packet_gyro_report(void)
{
  u8 ret[] = {
    LENOVO_HEADER_START,
    6,
    LENOVO_CMD_GYRO_REPORT,
    LENOVO_CONTROLLER_ID_LEFT,
    LENOVO_VAL_GYRO_REPORT_OFF,
    LENOVO_FOOTER_END
  };

  return ret;
}

static u8* lenovo_get_packet_factory_reset(void)
{
  u8 ret[] = {
    LENOVO_HEADER_FACTORYRESET,
    5,
    LENOVO_CMD_FACTORYRESET,
    LENOVO_CONTROLLER_ID_RX,
    LENOVO_FOOTER_END,

    LENOVO_HEADER_FACTORYRESET,
    5,
    LENOVO_CMD_FACTORYRESET,
    LENOVO_CONTROLLER_ID_DONGLE,
    LENOVO_FOOTER_END,

    LENOVO_HEADER_FACTORYRESET,
    5,
    LENOVO_CMD_FACTORYRESET,
    LENOVO_CONTROLLER_ID_LEFT,
    LENOVO_FOOTER_END,

    LENOVO_HEADER_FACTORYRESET,
    5,
    LENOVO_CMD_FACTORYRESET,
    LENOVO_CONTROLLER_ID_RIGHT,
    LENOVO_FOOTER_END
  };

  return ret;
}

static u8* lenovo_get_packet_legion_swap(void)
{
  u8 ret[] = {
    LENOVO_HEADER_START,
    6,
    LENOVO_CMD_LEGION_SWAP,
    LENOVO_CONTROLLER_ID_RX,
    LENOVO_VAL_LEGION_SWAP_OFF,
    LENOVO_FOOTER_END
  };

  return ret;
}


static int lenovo_hid_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
  int ret;

  ret = hid_parse(hdev);
  if (ret) {
    hid_err(hdev, "hid_parse failed\n");
    goto err;
  }

  ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
  if (ret) {
    hid_err(hdev, "hid_hw_start failed\n");
    goto err;
  }

  switch (hdev->product) {
  case USB_DEVICE_ID_LEGION_GO_CONTROLLER_XINPUT:
  case USB_DEVICE_ID_LEGION_GO_CONTROLLER_DIRECTINPUT:
  case USB_DEVICE_ID_LEGION_GO_CONTROLLER_DUALDIRECTINPUT:
  case USB_DEVICE_ID_LEGION_GO_CONTROLLER_FPS:
  default:
    ret = 0;
    break;
  };

  if (ret)
    goto err_hid;

  return 0;

err_hid:
  hid_hw_stop(hdev);
err:
  return ret;
}

static int lenovo_hid_suspend(struct hid_device *hdev, pm_message_t message)
{
  return 0;
}

static int lenovo_hid_resume(struct hid_device *hdev)
{
  return 0;
}


static const struct hid_device_id lenovo_hid_devices[] = {
  { HID_USB_DEVICE(USB_VENDOR_ID_LENOVO, USB_DEVICE_ID_LEGION_GO_CONTROLLER_XINPUT) },
  { HID_USB_DEVICE(USB_VENDOR_ID_LENOVO, USB_DEVICE_ID_LEGION_GO_CONTROLLER_DIRECTINPUT) },
  { HID_USB_DEVICE(USB_VENDOR_ID_LENOVO, USB_DEVICE_ID_LEGION_GO_CONTROLLER_DUALDIRECTINPUT) },
  { HID_USB_DEVICE(USB_VENDOR_ID_LENOVO, USB_DEVICE_ID_LEGION_GO_CONTROLLER_FPS) },
  { },
};

MODULE_DEVICE_TABLE(hid, lenovo_hid_devices);

static struct hid_driver lenovo_hid_driver = {
  .name = "lenovo-hid",
  .id_table = lenovo_hid_devices,
  .probe = lenovo_hid_probe,
  .suspend = lenovo_hid_suspend,
  .resume = lenovo_hid_resume,
};
module_hid_driver(lenovo_hid_driver);

MODULE_AUTHOR("Trevor Heslop <sythe.zn@gmail.com>");
MODULE_DESCRIPTION("HID driver for Lenovo Legion Go");
MODULE_LICENSE("GPL");
