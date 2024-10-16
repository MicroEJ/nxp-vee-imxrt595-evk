/**
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file
 * @brief NXP GPIO low level API
 * @author Julien Jouan
 * @version 1.0.0
 */

#include <LLGPIO_impl.h>
#include "LLGPIO_mux.h"
#include "sni.h"
#include "fsl_iopctl.h"
#include "board.h"

static int8_t check_port_and_pin(uint32_t port, uint32_t pin)
{
    int8_t ret = kPinError;

    switch (port)
    {
        case GPIO00:
        case GPIO01:
        case GPIO02:
        case GPIO03:
        case GPIO04:
        case GPIO05:
            ret = kSuccess;
            break;
        case GPIO06:
            if (pin <= GPIO06_MAX_PIN) ret = kSuccess;
            break;
        default:
            ret = kPortError;
            break;
    }
    return ret;
}

int32_t LLGPIO_IMPL_init_gpio_pin(uint32_t pin, uint32_t direction, uint32_t pullConfig)
{
    uint32_t port = pin / GPIO_BANK_SIZE;
    pin %= GPIO_BANK_SIZE;
    gpio_pin_config_t sw_config = {(gpio_pin_direction_t)direction, 0};

    /* Check that GPIO port and pin used is existing */
    int8_t portPinStatus = check_port_and_pin(port, pin);
    if (portPinStatus == kSuccess)
    {
        const uint32_t portx_piny_config = (/* Pin is configured as PIO{port}_{pin} */
            IOPCTL_PIO_FUNC0 |
            /* Disable pull-up / pull-down function */
            ((pullConfig > 0) ? IOPCTL_PIO_PUPD_EN : IOPCTL_PIO_PUPD_DI) |
            /* Enable pull-up/down function */
            ((pullConfig == 1) ? IOPCTL_PIO_PULLUP_EN : IOPCTL_PIO_PULLDOWN_EN) |
            /* Enables input buffer function */
            IOPCTL_PIO_INBUF_EN |
            /* Normal mode */
            IOPCTL_PIO_SLEW_RATE_NORMAL |
            /* Normal drive */
            IOPCTL_PIO_FULLDRIVE_DI |
            /* Analog mux is disabled */
            IOPCTL_PIO_ANAMUX_DI |
            /* Pseudo Output Drain is disabled */
            IOPCTL_PIO_PSEDRAIN_DI |
            /* Input function is not inverted */
            IOPCTL_PIO_INV_DI);
        IOPCTL_PinMuxSet(IOPCTL, port, pin, portx_piny_config);

        GPIO_PortInit_noreset(GPIO, port);
        GPIO_PinInit(GPIO, port, pin, &sw_config);
    }
    return portPinStatus;
}

int32_t LLGPIO_IMPL_read_gpio_pin(uint32_t pin)
{
    uint32_t port = pin / GPIO_BANK_SIZE;
    pin %= GPIO_BANK_SIZE;

    /* Check that GPIO port and pin used is existing */
    int8_t portPinStatus = check_port_and_pin(port, pin);
    int8_t ret;

    if (portPinStatus == kSuccess)
    {
        ret = GPIO_PinRead(GPIO, port, pin);
    }
    else
    {
        ret = portPinStatus;
    }

    return ret;
}

int32_t LLGPIO_IMPL_write_gpio_pin(uint32_t pin, uint32_t level)
{
    uint32_t port = pin / GPIO_BANK_SIZE;
    pin %= GPIO_BANK_SIZE;

    /* Check that GPIO port and pin used is existing */
    int8_t portPinStatus = check_port_and_pin(port, pin);
    int8_t ret;

    if (portPinStatus == kSuccess)
    {
        GPIO_PinWrite(GPIO, port, pin, level);
        ret = GPIO_PinRead(GPIO, port, pin);
    }
    else
    {
        ret = portPinStatus;
    }

    return ret;
}

int32_t LLGPIO_IMPL_toggle_gpio_pin(uint32_t pin)
{
    uint32_t port = pin / GPIO_BANK_SIZE;
    pin %= GPIO_BANK_SIZE;

    /* Check that GPIO port and pin used is existing */
    int8_t portPinStatus = check_port_and_pin(port, pin);
    int8_t ret;

    if (portPinStatus == kSuccess)
    {
        GPIO_PortToggle(GPIO, port, (uint32_t) (1 << pin));
        ret = GPIO_PinRead(GPIO, port, pin);
    }
    else
    {
        ret = portPinStatus;
    }

    return ret;
}
