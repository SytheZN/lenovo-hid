/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 *  HID driver for Lenovo Legion Go definitions
 *
 *  Copyright (c) 2024 Trevor Heslop <sythe.zn@gmail.com>
 */

#ifndef LENOVO_HID__H
#define LENOVO_HID__H

#define USB_VENDOR_ID_LENOVO                                0x17EF
#define USB_DEVICE_ID_LEGION_GO_CONTROLLER_XINPUT           0x6182
#define USB_DEVICE_ID_LEGION_GO_CONTROLLER_DIRECTINPUT      0x6183
#define USB_DEVICE_ID_LEGION_GO_CONTROLLER_DUALDIRECTINPUT  0x6184
#define USB_DEVICE_ID_LEGION_GO_CONTROLLER_FPS              0x6185

#define LENOVO_HEADER_FACTORYRESET                          0x04, 0x05
#define LENOVO_HEADER_START                                 0x05
#define LENOVO_FOOTER_END                                   0x01

#define LENOVO_CMD_FACTORYRESET                             0x01, 0x01
#define LENOVO_CMD_RGB_ENABLE                               0x70, 0x02
#define LENOVO_CMD_RGB_PROFILE_STORE                        0x72, 0x01
#define LENOVO_CMD_RGB_PROFILE_LOAD                         0x73, 0x02
#define LENOVO_CMD_GYRO_ENABLE                              0x6A, 0x02
#define LENOVO_CMD_GYRO_REPORT                              0x6A, 0x07
#define LENOVO_CMD_LEGION_SWAP                              0x69, 0x04

#define LENOVO_CONTROLLER_ID_RX                             0x01
#define LENOVO_CONTROLLER_ID_DONGLE                         0x02
#define LENOVO_CONTROLLER_ID_LEFT                           0x03
#define LENOVO_CONTROLLER_ID_RIGHT                          0x04

#define LENOVO_VAL_RGB_ENABLE_OFF                           0x00
#define LENOVO_VAL_RGB_ENABLE_ON                            0x01

#define LENOVO_VAL_RGB_MODE_SOLID                           0x01
#define LENOVO_VAL_RGB_MODE_PULSE                           0x02
#define LENOVO_VAL_RGB_MODE_DYNAMIC                         0x03
#define LENOVO_VAL_RGB_MODE_SPIRAL                          0x04

#define LENOVO_VAL_RGB_PROFILE_ID_1                         0x01
#define LENOVO_VAL_RGB_PROFILE_ID_2                         0x02
#define LENOVO_VAL_RGB_PROFILE_ID_3                         0x03

#define LENOVO_VAL_GYRO_ENABLE_ON                           0x01
#define LENOVO_VAL_GYRO_REPORT_OFF                          0x01
#define LENOVO_VAL_GYRO_REPORT_ON                           0x02

#define LENOVO_VAL_LEGION_SWAP_OFF                          0x01
#define LENOVO_VAL_LEGION_SWAP_ON                           0x02

#endif
