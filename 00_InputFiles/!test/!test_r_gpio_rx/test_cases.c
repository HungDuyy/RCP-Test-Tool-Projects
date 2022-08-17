/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2019 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : test_cases.c
* Description  : Unity unit tests for GPIO module
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 04.24.2019 1.00     Supported RX72M
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "platform.h"
#include "r_gpio_rx_if.h"

#include "unity.h"
#include "unity_fixture.h"
#include <stdio.h>

/* Port test for GPIO write or GPIO Read functions */
#define PORT_TEST GPIO_PORT_1
/* Pin test for GPIO write or GPIO Read functions  */
#define PIN_TEST  GPIO_PORT_1_PIN_0

/* Mask test for PortDirectionSet
 * Must be match port to PORT_TEST */
#define MASK_TEST  GPIO_PORT1_PIN_MASK

/* Value input for test case TG002_001 and TG003_001
 * Value depend on PORT_TEST */
#define VALUE_ADDR_PORT   0x03

/* Value input for test case TG006_001
 * Value depend on PIN_TEST */
#define VALUE_HIGH_PIN   0x01

/* Value input for test case TG006_001
 * Value depend on PIN_TEST */
#define VALUE_LOW_PIN   0x00

/* Pin test no support DSCR function  */
#define PIN_NO_DSCR   GPIO_PORT_4_PIN_0

/* Pin test  support DSCR function  */
#define PIN_DSCR   GPIO_PORT_7_PIN_1

#if defined (GPIO_DSCR2_IS_SUPPORTED)
/* Pin test no support DSCR2 function  */
#define PIN_NO_DSCR2   GPIO_PORT_4_PIN_0

/* Pin test  support DSCR2 function  */
#define PIN_DSCR2   GPIO_PORT_7_PIN_1
#endif

/* Pin test no support Pull-up function  */
#define PIN_NO_PULLUP   GPIO_PORT_E_PIN_2

/* Pin test support Pull-up  function  */
#define PIN_PULLUP   GPIO_PORT_7_PIN_2

/* Pin test support CMOS output  */
#define PIN_CMOS  GPIO_PORT_2_PIN_2

/* Pin test no support CMOS output  */
#define PIN_NO_CMOS  GPIO_PORT_4_PIN_2

/* Pin test support N-chanel Open Drain output  */
#define PIN_N_OPEN  GPIO_PORT_7_PIN_6

/* Address check port support Open Drain output
 * Value depend on port define in PIN_N_OPEN  */
#define ADDR_OD  &PORT7.ODR1.BYTE

/* Pin test support P-chanel Open Drain output  */
#define PIN_P_OPEN  GPIO_PORT_B_PIN_0

/* Pin test no support P-chanel Open Drain output  */
#define PIN_NO_P_OPEN  GPIO_PORT_D_PIN_3

/* Get port address */
static uint8_t * gpio_port_addr(uint8_t volatile * base_addr, uint16_t index)
{
    return (uint8_t *)((((uint32_t)index >> 8) & 0x000000FFuL) + (uint32_t)base_addr);
}

TEST_GROUP(GPIO_UT);

TEST_SETUP(GPIO_UT)
{
	/* Do some thing */
}

TEST_TEAR_DOWN(GPIO_UT)
{
	/* Do some thing */
}

/* Test cases of R_GPIO_GetVersion() */
TEST(GPIO_UT, TG001_001)
{
	printf("[TG001_001_GetVersion]===");
	
	uint32_t ver = ((((uint32_t)GPIO_RX_VERSION_MAJOR) << 16) | (uint32_t)GPIO_RX_VERSION_MINOR);

	uint32_t ret = R_GPIO_GetVersion();
	TEST_ASSERT_EQUAL(ver, ret);

	printf("Version of GPIO is %d.%d\n", GPIO_RX_VERSION_MAJOR, GPIO_RX_VERSION_MINOR);
}

/* Test cases of R_GPIO_PortWrite() */
TEST(GPIO_UT, TG002_001)
{
	printf("[TG002_001_PortWrite]===");

	gpio_port_t port = PORT_TEST;
	uint8_t value = VALUE_ADDR_PORT;
	uint8_t *addr;
    addr = gpio_port_addr(GPIO_PRV_BASE_ADDR_OUTPUT, port);

	R_GPIO_PortWrite(port, value);
	TEST_ASSERT_EQUAL(value, (*addr));

	printf("Success writing to port\n");
}

/* Test cases of R_GPIO_PortRead() */
TEST(GPIO_UT, TG003_001)
{
	printf("[TG003_001_PortRead]===");

	gpio_port_t port = PORT_TEST;
	uint8_t *addr;
    addr = gpio_port_addr(GPIO_PRV_BASE_ADDR_INPUT, port);
	*addr = VALUE_ADDR_PORT;

	uint8_t ret = R_GPIO_PortRead(port);
	TEST_ASSERT_EQUAL((*addr), ret);

	printf("Success reading from port\n");
}

/* Test cases of R_GPIO_PortDirectionSet() */
TEST(GPIO_UT, TG004_001)
{
	printf("[TG004_001_PortDirectionSet]===");
	gpio_port_t port = PORT_TEST;
	gpio_dir_t dir = GPIO_DIRECTION_INPUT;
	uint8_t mask = MASK_TEST;

	uint8_t *addr;
	addr = gpio_port_addr(GPIO_PRV_BASE_ADDR_DIRECTION, port);
	uint8_t value = (*addr) & (~((uint8_t)mask));

	R_GPIO_PortDirectionSet(port, dir, mask);
	TEST_ASSERT_EQUAL(value, (*addr));

	printf("Success set port direction\n");
}

TEST(GPIO_UT, TG004_002)
{
	printf("[TG004_002_PortDirectionSet]===");
	gpio_port_t port = PORT_TEST;
	gpio_dir_t dir = GPIO_DIRECTION_OUTPUT;
	uint8_t mask = MASK_TEST;

	uint8_t *addr;
	addr = gpio_port_addr(GPIO_PRV_BASE_ADDR_DIRECTION, port);
	uint8_t value = (*addr) | ((uint8_t)mask);

	R_GPIO_PortDirectionSet(port, dir, mask);
	TEST_ASSERT_EQUAL(value, (*addr));

	printf("Success set port direction\n");
}

/* Test cases of R_GPIO_PinWrite() */
TEST(GPIO_UT, TG005_001)
{
	printf("[TG005_001_PinWrite]===");

	gpio_port_pin_t pin = PIN_TEST;
	gpio_level_t level = GPIO_LEVEL_LOW;
	uint8_t *addr;
	addr = gpio_port_addr(GPIO_PRV_BASE_ADDR_OUTPUT, pin);

	R_GPIO_PinWrite(pin, level);
	uint8_t value = ((*addr) & (1 << (pin & 0x00FF))) >> (pin & 0x00FF);
	TEST_ASSERT_EQUAL(GPIO_LEVEL_LOW, value);

	printf("Success writing to pin\n");
}

TEST(GPIO_UT, TG005_002)
{
	printf("[TG005_002_PinWrite]===");

	gpio_port_pin_t pin = PIN_TEST;
	gpio_level_t level = GPIO_LEVEL_HIGH;
	uint8_t *addr;
	addr = gpio_port_addr(GPIO_PRV_BASE_ADDR_OUTPUT, pin);

	R_GPIO_PinWrite(pin, level);
	uint8_t value = ((*addr) & (1 << (pin & 0x00FF))) >> (pin & 0x00FF);
	TEST_ASSERT_EQUAL(GPIO_LEVEL_HIGH, value);

	printf("Success writing to pin\n");
}

/* Test cases of R_GPIO_PinRead() */
TEST(GPIO_UT, TG006_001)
{
	printf("[TG006_001_PinRead]===");

	gpio_port_pin_t pin = PIN_TEST;
	uint8_t *addr;
	addr = gpio_port_addr(GPIO_PRV_BASE_ADDR_INPUT, pin);
	*addr = VALUE_HIGH_PIN; //GPIO_LEVEL_HIGH

	gpio_level_t level = R_GPIO_PinRead(pin);
	TEST_ASSERT_EQUAL(GPIO_LEVEL_HIGH, level);

	printf("Success reading from pin\n");
}

TEST(GPIO_UT, TG006_002)
{
	printf("[TG006_002_PinRead]===");

	gpio_port_pin_t pin = PIN_TEST;
	uint8_t *addr;
	addr = gpio_port_addr(GPIO_PRV_BASE_ADDR_INPUT, pin);
	*addr = VALUE_LOW_PIN; //GPIO_LEVEL_LOW

	gpio_level_t level = R_GPIO_PinRead(pin);
	TEST_ASSERT_EQUAL(GPIO_LEVEL_LOW, level);

	printf("Success reading from pin\n");
}

/* Test cases of R_GPIO_PinDirectionSet() */
TEST(GPIO_UT, TG007_001)
{
	printf("[TG007_001_PinDirectionSet]===");

	gpio_port_pin_t pin = PIN_TEST;
	gpio_dir_t dir = GPIO_DIRECTION_INPUT;
	uint8_t *addr;
	addr = gpio_port_addr(GPIO_PRV_BASE_ADDR_DIRECTION, pin);

	R_GPIO_PinDirectionSet(pin, dir);
	uint8_t value = ((*addr) & (1 << (pin & 0x00FF))) >> (pin & 0x00FF);
	TEST_ASSERT_EQUAL(GPIO_LEVEL_LOW, value);

	printf("Success set pin direction\n");
}

TEST(GPIO_UT, TG007_002)
{
	printf("[TG007_002_PinDirectionSet]===");

	gpio_port_pin_t pin = PIN_TEST;
	gpio_dir_t dir = GPIO_DIRECTION_OUTPUT;
	uint8_t *addr;
	addr = gpio_port_addr(GPIO_PRV_BASE_ADDR_DIRECTION, pin);

	R_GPIO_PinDirectionSet(pin, dir);
	uint8_t value = ((*addr) & (1 << (pin & 0x00FF))) >> (pin & 0x00FF);
	TEST_ASSERT_EQUAL(GPIO_LEVEL_HIGH, value);

	printf("Success set pin direction\n");
}

/* Test cases of R_GPIO_PinControl() */
TEST(GPIO_UT, TG008_001)
{
	printf("[TG008_001_PinControl]===");

	gpio_port_pin_t pin = PIN_TEST;
	gpio_cmd_t cmd = GPIO_CMD_DSCR_ENABLE;
	uint8_t *addr;
	addr = gpio_port_addr(GPIO_PRV_BASE_ADDR_DSCR, pin);

	gpio_err_t ret = R_GPIO_PinControl(pin, cmd);
	uint8_t value = ((*addr) & (1 << (pin & 0x00FF))) >> (pin & 0x00FF);
	TEST_ASSERT_EQUAL(GPIO_SUCCESS, ret);
	TEST_ASSERT_EQUAL(GPIO_LEVEL_HIGH, value);

	printf("DSCR function is enabled\n");
}

TEST(GPIO_UT, TG008_002)
{
	printf("[TG008_002_PinControl]===");

	gpio_port_pin_t pin = PIN_NO_DSCR;
	gpio_cmd_t cmd = GPIO_CMD_DSCR_ENABLE;

	gpio_err_t ret = R_GPIO_PinControl(pin, cmd);
	TEST_ASSERT_EQUAL(GPIO_ERR_INVALID_MODE, ret);

	printf("Pin is not supported DSCR function\n");
}

TEST(GPIO_UT, TG008_003)
{
	printf("[TG008_003_PinControl]===");

	gpio_port_pin_t pin = PIN_DSCR;
	gpio_cmd_t cmd = GPIO_CMD_DSCR_DISABLE;
	uint8_t *addr;
	addr = gpio_port_addr(GPIO_PRV_BASE_ADDR_DSCR, pin);

	gpio_err_t ret = R_GPIO_PinControl(pin, cmd);
	uint8_t value = ((*addr) & (1 << (pin & 0x00FF))) >> (pin & 0x00FF);
	TEST_ASSERT_EQUAL(GPIO_SUCCESS, ret);
	TEST_ASSERT_EQUAL(GPIO_LEVEL_LOW, value);

	printf("DSCR function is disabled\n");
}

TEST(GPIO_UT, TG008_004)
{
	printf("[TG008_004_PinControl]===");

	gpio_port_pin_t pin = PIN_NO_DSCR;
	gpio_cmd_t cmd = GPIO_CMD_DSCR_DISABLE;

	gpio_err_t ret = R_GPIO_PinControl(pin, cmd);
	TEST_ASSERT_EQUAL(GPIO_ERR_INVALID_MODE, ret);

	printf("Pin is not supported DSCR function\n");
}

TEST(GPIO_UT, TG008_005)
{
	printf("[TG008_005_PinControl]===");
#if defined (GPIO_DSCR2_IS_SUPPORTED)
	gpio_port_pin_t pin = PIN_DSCR2;
	gpio_cmd_t cmd = GPIO_CMD_DSCR2_ENABLE;
	uint8_t *addr;
	addr = gpio_port_addr(GPIO_PRV_BASE_ADDR_DSCR, pin);

	gpio_err_t ret = R_GPIO_PinControl(pin, cmd);
	uint8_t value = ((*addr) & (1 << (pin & 0x00FF))) >> (pin & 0x00FF);
	TEST_ASSERT_EQUAL(GPIO_SUCCESS, ret);
	TEST_ASSERT_EQUAL(GPIO_LEVEL_HIGH, value);

	printf("DSCR2 function is enabled\n");
#else
	printf("DSCR2 unavailable on this MCU\n");
#endif
}

TEST(GPIO_UT, TG008_006)
{
	printf("[TG008_006_PinControl]===");
#if defined (GPIO_DSCR2_IS_SUPPORTED)
	gpio_port_pin_t pin = PIN_NO_DSCR2;
	gpio_cmd_t cmd = GPIO_CMD_DSCR2_ENABLE;

	gpio_err_t ret = R_GPIO_PinControl(pin, cmd);
	TEST_ASSERT_EQUAL(GPIO_ERR_INVALID_MODE, ret);
	
	printf("Pin is not supported DSCR2 function\n");
#else
	printf("DSCR2 unavailable on this MCU\n");
#endif
}


TEST(GPIO_UT, TG008_007)
{
	printf("[TG008_007_PinControl]===");

	gpio_port_pin_t pin = PIN_DSCR;
	gpio_cmd_t cmd = GPIO_CMD_DSCR_DISABLE;
	uint8_t *addr;
	addr = gpio_port_addr(GPIO_PRV_BASE_ADDR_DSCR, pin);

	gpio_err_t ret = R_GPIO_PinControl(pin, cmd);
	uint8_t value = ((*addr) & (1 << (pin & 0x00FF))) >> (pin & 0x00FF);
	TEST_ASSERT_EQUAL(GPIO_SUCCESS, ret);
	TEST_ASSERT_EQUAL(GPIO_LEVEL_LOW, value);

	printf("DSCR function is disabled\n");
}

TEST(GPIO_UT, TG008_008)
{
	printf("[TG008_008_PinControl]===");
#if defined (GPIO_DSCR2_IS_SUPPORTED)
	gpio_port_pin_t pin = PIN_NO_DSCR2;
	gpio_cmd_t cmd = GPIO_CMD_DSCR2_DISABLE;

	gpio_err_t ret = R_GPIO_PinControl(pin, cmd);
	TEST_ASSERT_EQUAL(GPIO_ERR_INVALID_MODE, ret);

	printf("Pin is not supported DSCR2 function\n");
#else
	printf("DSCR2 unavailable on this MCU\n");
#endif
}

TEST(GPIO_UT, TG008_009)
{
	printf("[TG008_009_PinControl]===");

	gpio_port_pin_t pin = PIN_TEST;
	gpio_cmd_t cmd = GPIO_CMD_ASSIGN_TO_GPIO;
	uint8_t *addr;
	addr = gpio_port_addr(GPIO_PRV_BASE_ADDR_MODE, pin);

	gpio_err_t ret = R_GPIO_PinControl(pin, cmd);
	uint8_t value = ((*addr) & (1 << (pin & 0x00FF))) >> (pin & 0x00FF);
	TEST_ASSERT_EQUAL(GPIO_SUCCESS, ret);
	TEST_ASSERT_EQUAL(GPIO_LEVEL_LOW, value);

	printf("GPIO function is assigned\n");
}

TEST(GPIO_UT, TG008_010)
{
	printf("[TG008_010_PinControl]===");

	gpio_port_pin_t pin = PIN_TEST;
	gpio_cmd_t cmd = GPIO_CMD_ASSIGN_TO_PERIPHERAL;
	uint8_t *addr;
	addr = gpio_port_addr(GPIO_PRV_BASE_ADDR_MODE, pin);

	gpio_err_t ret = R_GPIO_PinControl(pin, cmd);
	uint8_t value = ((*addr) & (1 << (pin & 0x00FF))) >> (pin & 0x00FF);
	TEST_ASSERT_EQUAL(GPIO_SUCCESS, ret);
	TEST_ASSERT_EQUAL(GPIO_LEVEL_HIGH, value);

	printf("PERIPHERAL function is assigned\n");
}

TEST(GPIO_UT, TG008_011)
{
	printf("[TG008_011_PinControl]===");

	gpio_port_pin_t pin = PIN_PULLUP;
	gpio_cmd_t cmd = GPIO_CMD_IN_PULL_UP_DISABLE;
	uint8_t *addr;
	addr = gpio_port_addr(GPIO_PRV_BASE_ADDR_PULL_UP, pin);

	gpio_err_t ret = R_GPIO_PinControl(pin, cmd);
	uint8_t value = ((*addr) & (1 << (pin & 0x00FF))) >> (pin & 0x00FF);
	TEST_ASSERT_EQUAL(GPIO_SUCCESS, ret);
	TEST_ASSERT_EQUAL(GPIO_LEVEL_LOW, value);

	printf("PULL-UP function is disabled\n");
}

TEST(GPIO_UT, TG008_012)
{
	printf("[TG008_012_PinControl]===");

	gpio_port_pin_t pin = PIN_NO_PULLUP;

	gpio_cmd_t cmd = GPIO_CMD_IN_PULL_UP_DISABLE;

	gpio_err_t ret = R_GPIO_PinControl(pin, cmd);
	TEST_ASSERT_EQUAL(GPIO_ERR_INVALID_MODE, ret);

	printf("Pin is not supported PULL-UP function\n");

}

TEST(GPIO_UT, TG008_013)
{
	printf("[TG008_013_PinControl]===");

	gpio_port_pin_t pin = PIN_PULLUP;
	gpio_cmd_t cmd = GPIO_CMD_IN_PULL_UP_ENABLE;
	uint8_t *addr;
	addr = gpio_port_addr(GPIO_PRV_BASE_ADDR_PULL_UP, pin);

	gpio_err_t ret = R_GPIO_PinControl(pin, cmd);
	uint8_t value = ((*addr) & (1 << (pin & 0x00FF))) >> (pin & 0x00FF);
	TEST_ASSERT_EQUAL(GPIO_SUCCESS, ret);
	TEST_ASSERT_EQUAL(GPIO_LEVEL_HIGH, value);

	printf("PULL-UP function is enabled\n");
}

TEST(GPIO_UT, TG008_014)
{
	printf("[TG008_014_PinControl]===");

	gpio_port_pin_t pin = PIN_NO_PULLUP;

	gpio_cmd_t cmd = GPIO_CMD_IN_PULL_UP_ENABLE;

	gpio_err_t ret = R_GPIO_PinControl(pin, cmd);
	TEST_ASSERT_EQUAL(GPIO_ERR_INVALID_MODE, ret);

	printf("Pin is not supported PULL-UP function\n");

}

TEST(GPIO_UT, TG008_015)
{
	printf("[TG008_015_PinControl]===");

	gpio_port_pin_t pin = PIN_CMOS;
	gpio_cmd_t cmd = GPIO_CMD_OUT_CMOS;
	uint8_t *addr;
	addr = gpio_port_addr(GPIO_PRV_BASE_ADDR_OUT_TYPE, (uint16_t)(pin*2));

	gpio_err_t ret = R_GPIO_PinControl(pin, cmd);
	uint8_t value = ((*addr) & (1 << ((pin & 0x00FF)*2))) >> ((pin & 0x00FF)*2);
	TEST_ASSERT_EQUAL(GPIO_SUCCESS, ret);
	TEST_ASSERT_EQUAL(GPIO_LEVEL_LOW, value);
	printf("CMOS type is assigned to output\n");
}

TEST(GPIO_UT, TG008_016)
{
	printf("[TG008_016_PinControl]===");

	gpio_port_pin_t pin = PIN_N_OPEN;
	gpio_cmd_t cmd = GPIO_CMD_OUT_OPEN_DRAIN_N_CHAN;
	uint8_t *addr;
	addr = gpio_port_addr(GPIO_PRV_BASE_ADDR_OUT_TYPE, (uint16_t)(pin*2));
	gpio_err_t ret = R_GPIO_PinControl(pin, cmd);
	// RVC
	if (((uint8_t)(pin & 0x00FFu)) > 3)
	{
		addr += 1;
		pin -= 4;
	}
	uint8_t value = ((*addr) & (1 << ((pin & 0x00FF)*2))) >> ((pin & 0x00FF)*2);
	TEST_ASSERT_EQUAL(GPIO_SUCCESS, ret);
	TEST_ASSERT_EQUAL(ADDR_OD, addr); //RVC
	TEST_ASSERT_EQUAL(GPIO_LEVEL_HIGH, value);

	printf("OPEN DRAIN N CHANEL type is assigned to output\n");
}

TEST(GPIO_UT, TG008_017)
{
	printf("[TG008_017_PinControl]===");

	gpio_port_pin_t pin = PIN_NO_CMOS;

	gpio_cmd_t cmd = GPIO_CMD_OUT_OPEN_DRAIN_N_CHAN;

	gpio_err_t ret = R_GPIO_PinControl(pin, cmd);
	TEST_ASSERT_EQUAL(GPIO_ERR_INVALID_MODE, ret);

	printf("Pin is not supported OPEN DRAIN N CHANEL type\n");
}

TEST(GPIO_UT, TG008_018)
{
	printf("[TG008_018_PinControl]===");

	#if ((BSP_MCU_RX65N ==1) || (BSP_MCU_RX65N_2MB == 1) || (BSP_MCU_RX72M == 1)||(BSP_MCU_RX23W == 1)||(BSP_MCU_RX13T == 1))
		gpio_port_pin_t pin = PIN_P_OPEN;
		gpio_cmd_t cmd = GPIO_CMD_OUT_OPEN_DRAIN_P_CHAN;
		uint8_t *addr;
		addr = gpio_port_addr(GPIO_PRV_BASE_ADDR_OUT_TYPE, (uint16_t)(pin*2));

		gpio_err_t ret = R_GPIO_PinControl(pin, cmd);
		// RVC
		if (((uint8_t)(pin & 0x00FFu)) > 3)
		{
			addr += 1;
			pin -= 4;
		}
		uint8_t b2_value = ((*addr) & (1 << ((pin & 0x00FF)*2))) >> ((pin & 0x00FF)*2);
		uint8_t b3_value = ((*addr) & (1 << (((pin & 0x00FF)*2)+1))) >> (((pin & 0x00FF)*2)+1);

		TEST_ASSERT_EQUAL(GPIO_SUCCESS, ret);
		TEST_ASSERT_EQUAL(GPIO_LEVEL_LOW, b2_value);
		TEST_ASSERT_EQUAL(GPIO_LEVEL_HIGH, b3_value);
		TEST_ASSERT_EQUAL(&PORTB.ODR0.BYTE, addr); //RVC

		printf("OPEN DRAIN P CHANEL type is assigned to output\n");

	#else
		printf("Unavailable on this MCU\n");
	#endif
}

TEST(GPIO_UT, TG008_019)
{
	printf("[TG008_019_PinControl]===");

#if ((BSP_MCU_RX65N ==1) || (BSP_MCU_RX65N_2MB == 1) || (BSP_MCU_RX72M == 1)||(BSP_MCU_RX23W == 1)||(BSP_MCU_RX13T == 1))
	gpio_port_pin_t pin = PIN_NO_P_OPEN;
	gpio_cmd_t cmd = GPIO_CMD_OUT_OPEN_DRAIN_P_CHAN;

	gpio_err_t ret = R_GPIO_PinControl(pin, cmd);
	TEST_ASSERT_EQUAL(GPIO_ERR_INVALID_MODE, ret);
	printf("Pin is not supported OPEN DRAIN N CHANEL type\n");

#else
	printf("Not available on this MCU\n");
#endif
}

TEST(GPIO_UT, TG008_020)
{
	printf("[TG008_020_PinControl]===");

	gpio_port_pin_t pin = PIN_TEST;
	gpio_cmd_t cmd = (gpio_cmd_t)(11);

	gpio_err_t ret = R_GPIO_PinControl(pin, cmd);

	TEST_ASSERT_EQUAL(GPIO_ERR_INVALID_CMD, ret);
	printf("Command is invalid\n");
}

TEST(GPIO_UT, TG008_021)
{
	printf("[TG008_021_PinControl]===");

	gpio_port_pin_t pin = PIN_N_OPEN;
	gpio_cmd_t cmd = GPIO_CMD_OUT_OPEN_DRAIN_N_CHAN;
	uint8_t *addr;
	addr = gpio_port_addr(GPIO_PRV_BASE_ADDR_OUT_TYPE, (uint16_t)(pin*2));
	// RVC
	if (((uint8_t)(pin & 0x00FFu)) > 3)
	{
		addr += 1;
		pin -= 4;
	}

	gpio_err_t ret = R_GPIO_PinControl(pin, cmd);
	uint8_t value = ((*addr) & (1 << ((pin & 0x00FF)*2))) >> ((pin & 0x00FF)*2);
	TEST_ASSERT_EQUAL(GPIO_SUCCESS, ret);
	TEST_ASSERT_EQUAL(GPIO_LEVEL_HIGH, value);

	printf("OPEN DRAIN N CHANEL type is assigned to output\n");
}
