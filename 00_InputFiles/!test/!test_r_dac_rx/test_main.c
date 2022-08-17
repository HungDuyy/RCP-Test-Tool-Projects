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
* Copyright (C) 2018 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name	   : test_main.c
* Description  : Unity unit tests for R12DA on RX66N
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 07.12.2018 1.00     First Release. 
*         : 19.04.2019 1.10     Test on RX72M
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "platform.h"

#include "unity_fixture.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/
 
/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
static void RunAllTests(void);

TEST_GROUP_RUNNER(R_DAC_GetVersion_Test)
{
    RUN_TEST_CASE(R_DAC_GetVersion_Test, TG001_001);
}

/***********************************************************************************************************************
* Function Name: TEST_SETUP
* Description  : Setup for these unit tests
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
TEST_GROUP_RUNNER(R_DAC_Open_Test)
{
    RUN_TEST_CASE(R_DAC_Open_Test, TG002_001);
#ifndef BSP_MCU_RX13T
    RUN_TEST_CASE(R_DAC_Open_Test, TG002_002);
#endif
    RUN_TEST_CASE(R_DAC_Open_Test, TG002_003);
#ifndef BSP_MCU_RX13T
    RUN_TEST_CASE(R_DAC_Open_Test, TG002_004);
    RUN_TEST_CASE(R_DAC_Open_Test, TG002_005);
#endif
#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    RUN_TEST_CASE(R_DAC_Open_Test, TG002_006);
    RUN_TEST_CASE(R_DAC_Open_Test, TG002_007);
    RUN_TEST_CASE(R_DAC_Open_Test, TG002_008);
    RUN_TEST_CASE(R_DAC_Open_Test, TG002_009);
#endif
#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
    RUN_TEST_CASE(R_DAC_Open_Test, TG002_010);
#endif
    RUN_TEST_CASE(R_DAC_Open_Test, TG002_011);
    RUN_TEST_CASE(R_DAC_Open_Test, TG002_012);
#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
    RUN_TEST_CASE(R_DAC_Open_Test, TG002_013);
#endif
#ifndef BSP_MCU_RX13T
    RUN_TEST_CASE(R_DAC_Open_Test, TG002_014);
    RUN_TEST_CASE(R_DAC_Open_Test, TG002_015);
    RUN_TEST_CASE(R_DAC_Open_Test, TG002_016);
#endif
}

TEST_GROUP_RUNNER(R_DAC_Control_Test)
{
	RUN_TEST_CASE(R_DAC_Control_Test, TG003_001);
#ifndef BSP_MCU_RX13T
	RUN_TEST_CASE(R_DAC_Control_Test, TG003_002);
	RUN_TEST_CASE(R_DAC_Control_Test, TG003_004);
#endif
	RUN_TEST_CASE(R_DAC_Control_Test, TG003_003);
	RUN_TEST_CASE(R_DAC_Control_Test, TG003_005);
	RUN_TEST_CASE(R_DAC_Control_Test, TG003_006);
}

TEST_GROUP_RUNNER(R_DAC_Write_Test)
{
	RUN_TEST_CASE(R_DAC_Write_Test, TG004_001);
	RUN_TEST_CASE(R_DAC_Write_Test, TG004_002);
	RUN_TEST_CASE(R_DAC_Write_Test, TG004_003);
#ifndef BSP_MCU_RX13T
	RUN_TEST_CASE(R_DAC_Write_Test, TG004_004);
	RUN_TEST_CASE(R_DAC_Write_Test, TG004_005);
	RUN_TEST_CASE(R_DAC_Write_Test, TG004_006);
#endif
	RUN_TEST_CASE(R_DAC_Write_Test, TG004_007);
	RUN_TEST_CASE(R_DAC_Write_Test, TG004_008);
}

TEST_GROUP_RUNNER(R_DAC_Close_Test)
{
	RUN_TEST_CASE(R_DAC_Close_Test, TG005_001);
}

TEST_GROUP_RUNNER(dac_set_options_Test)
{
#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T) || defined(BSP_MCU_RX72M)
    RUN_TEST_CASE(dac_set_options_Test, TG006_001);
    RUN_TEST_CASE(dac_set_options_Test, TG006_002);
    RUN_TEST_CASE(dac_set_options_Test, TG006_003);
    RUN_TEST_CASE(dac_set_options_Test, TG006_004);
    RUN_TEST_CASE(dac_set_options_Test, TG006_005);
    RUN_TEST_CASE(dac_set_options_Test, TG006_006);
    RUN_TEST_CASE(dac_set_options_Test, TG006_007);
#endif
}

TEST_GROUP_RUNNER(power_on_Test)
{
#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)|| defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M) || defined(BSP_MCU_RX13T)
    RUN_TEST_CASE(power_on_Test, TG007_001);
#endif
}

TEST_GROUP_RUNNER(power_off_Test)
{
    RUN_TEST_CASE(power_off_Test, TG008_001);
}

/***********************************************************************************************************************
* Function Name: RunAllTests
* Description  : Call test groups
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
static void RunAllTests(void)
{
	RUN_TEST_GROUP(R_DAC_GetVersion_Test);
    RUN_TEST_GROUP(R_DAC_Open_Test);
    RUN_TEST_GROUP(R_DAC_Control_Test);
    RUN_TEST_GROUP(R_DAC_Write_Test);
    RUN_TEST_GROUP(R_DAC_Close_Test);
    RUN_TEST_GROUP(dac_set_options_Test);
    RUN_TEST_GROUP(power_on_Test);
    RUN_TEST_GROUP(power_off_Test);
}

/***********************************************************************************************************************
* Function Name: TEST_SETUP
* Description  : Tear down for these unit tests
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void main(void *pvParameters)
{
    UnityMain(0, 0, RunAllTests);
    
    while(1)
    {
        /* Infinite loop. */
    }
}

