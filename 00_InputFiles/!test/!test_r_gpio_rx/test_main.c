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
* File Name    : test_main.c
* Description  : Unity unit tests for GPIO module
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 04.18.2019 1.00     Supported RX72M
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/

#include "platform.h"
#include "r_gpio_rx_if.h"

#include "unity_fixture.h"
#include <stdio.h>


TEST_GROUP_RUNNER(GPIO_UT)
{
	/* Test cases of R_GPIO_GetVersion() */
	RUN_TEST_CASE(GPIO_UT, TG001_001);

	/* Test cases of R_GPIO_PortWrite() */
	RUN_TEST_CASE(GPIO_UT, TG002_001);

	/* Test cases of R_GPIO_PortRead() */
	RUN_TEST_CASE(GPIO_UT, TG003_001);

	/* Test cases of R_GPIO_PortDirectionSet() */
	RUN_TEST_CASE(GPIO_UT, TG004_001);
	RUN_TEST_CASE(GPIO_UT, TG004_002);

	/* Test cases of R_GPIO_PinWrite() */
	RUN_TEST_CASE(GPIO_UT, TG005_001);
	RUN_TEST_CASE(GPIO_UT, TG005_002);

	/* Test cases of R_GPIO_PinRead() */
	RUN_TEST_CASE(GPIO_UT, TG006_001);
	RUN_TEST_CASE(GPIO_UT, TG006_002);

    /* Test cases of R_GPIO_PinDirectionSet() */
	RUN_TEST_CASE(GPIO_UT, TG007_001);
	RUN_TEST_CASE(GPIO_UT, TG007_002);
    
	/* Test cases of R_GPIO_PinControl() */
	RUN_TEST_CASE(GPIO_UT, TG008_001);
	RUN_TEST_CASE(GPIO_UT, TG008_002);
	RUN_TEST_CASE(GPIO_UT, TG008_003);
	RUN_TEST_CASE(GPIO_UT, TG008_004);
	RUN_TEST_CASE(GPIO_UT, TG008_005);
	RUN_TEST_CASE(GPIO_UT, TG008_006);
	RUN_TEST_CASE(GPIO_UT, TG008_007);
	RUN_TEST_CASE(GPIO_UT, TG008_008);
	RUN_TEST_CASE(GPIO_UT, TG008_009);
	RUN_TEST_CASE(GPIO_UT, TG008_010);
	RUN_TEST_CASE(GPIO_UT, TG008_011);
	RUN_TEST_CASE(GPIO_UT, TG008_012);
	RUN_TEST_CASE(GPIO_UT, TG008_013);
	RUN_TEST_CASE(GPIO_UT, TG008_014);
	RUN_TEST_CASE(GPIO_UT, TG008_015);
	RUN_TEST_CASE(GPIO_UT, TG008_016);
	RUN_TEST_CASE(GPIO_UT, TG008_017);
	RUN_TEST_CASE(GPIO_UT, TG008_018);
	RUN_TEST_CASE(GPIO_UT, TG008_019);
	RUN_TEST_CASE(GPIO_UT, TG008_020);
	RUN_TEST_CASE(GPIO_UT, TG008_021);
}

static void RunTest()
{
	printf("GPIO Unit Test...\n");
	RUN_TEST_GROUP(GPIO_UT);
}

void main()
{
	UnityMain(0, 0, RunTest);
	printf("TEST DONE !!!\n");
}
