/**
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef LLGPIO_MUX
#define LLGPIO_MUX

#ifdef __cplusplus
extern "C" {
#endif

#define IOPCTL_PIO_FUNC0            0x0000u     /*!<@brief Selects pin function 0 */
#define IOPCTL_PIO_PUPD_DI          0x0000u     /*!<@brief Disable pull-up / pull-down function */
#define IOPCTL_PIO_PUPD_EN          0x0010u     /*!<@brief Enable pull-up / pull-down function */
#define IOPCTL_PIO_PULLDOWN_EN      0x0000u     /*!<@brief Enable pull-down function */
#define IOPCTL_PIO_PULLUP_EN        0x0020u     /*!<@brief Enable pull-up function */
#define IOPCTL_PIO_INBUF_DI         0x0000u     /*!<@brief Disable input buffer function */
#define IOPCTL_PIO_INBUF_EN         0x0040u     /*!<@brief Enables input buffer function */
#define IOPCTL_PIO_SLEW_RATE_NORMAL 0x0000u     /*!<@brief Normal mode */
#define IOPCTL_PIO_SLEW_RATE_SLOW   0x0080u     /*!<@brief Slow mode */
#define IOPCTL_PIO_FULLDRIVE_DI     0x0000u     /*!<@brief Normal drive */
#define IOPCTL_PIO_FULLDRIVE_EN     0x0100u     /*!<@brief Full drive enable */
#define IOPCTL_PIO_ANAMUX_DI        0x0000u     /*!<@brief Analog mux is disabled */
#define IOPCTL_PIO_ANAMUX_EN        0x0200u     /*!<@brief Analog mux is enabled */
#define IOPCTL_PIO_PSEDRAIN_DI      0x0000u     /*!<@brief Pseudo Output Drain is disabled */
#define IOPCTL_PIO_PSEDRAIN_EN      0x0400u     /*!<@brief Pseudo Output Drain is enabled */
#define IOPCTL_PIO_INV_DI           0x0000u     /*!<@brief Input function is not inverted */
#define IOPCTL_PIO_INV_EN           0x0800u     /*!<@brief Input function is inverted */

#define MAX_PORT_NUMBER             6
#define GPIO_BANK_SIZE              32
#define GPIO00                      0
#define GPIO01                      1
#define GPIO02                      2
#define GPIO03                      3
#define GPIO04                      4
#define GPIO05                      5
#define GPIO06                      6
#define GPIO06_MAX_PIN              27

typedef enum
{
    kSuccess = 0,
    kPortError = -1,
    kPinError = -2,
} gpio_init_status;

#ifdef __cplusplus
}
#endif
#endif
