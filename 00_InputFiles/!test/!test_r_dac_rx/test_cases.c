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
* File Name	   : test_cases.c
* Description  : Unity unit tests for RX R12DA module
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 07.12.2018 1.00			First release.
*         : 19.04.2019 1.10         Test on RX72M
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/

#include <stdio.h>

#include "platform.h"
#include "r_dac_rx_if.h"
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
Imported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
/* Declare all test groups */
TEST_GROUP(R_DAC_GetVersion_Test);
TEST_GROUP(R_DAC_Open_Test);
TEST_GROUP(R_DAC_Control_Test);
TEST_GROUP(R_DAC_Write_Test);
TEST_GROUP(R_DAC_Close_Test);
TEST_GROUP(dac_set_options_Test);
TEST_GROUP(power_on_Test);
TEST_GROUP(power_off_Test);

/***********************************************************************************************************************
* Function Name: TEST_SETUP
* Description  : Setup for these unit tests. This will be run before every test case.
***********************************************************************************************************************/
TEST_SETUP(R_DAC_GetVersion_Test)
{

}

TEST_SETUP(R_DAC_Open_Test)
{
	R_DAC_Close();
}

TEST_SETUP(R_DAC_Control_Test)
{
	R_DAC_Close();
}

TEST_SETUP(R_DAC_Write_Test)
{
	R_DAC_Close();
}

TEST_SETUP(R_DAC_Close_Test)
{

}

TEST_SETUP(dac_set_options_Test)
{
	R_DAC_Close();
}

TEST_SETUP(power_on_Test)
{
	R_DAC_Close();
}

TEST_SETUP(power_off_Test)
{

}

/***********************************************************************************************************************
* Function Name: TEST_TEAR_DOWN
* Description  : Tear down for these unit tests. This will be run after each test case.
***********************************************************************************************************************/
TEST_TEAR_DOWN(R_DAC_GetVersion_Test)
{

}

TEST_TEAR_DOWN(R_DAC_Open_Test)
{

}

TEST_TEAR_DOWN(R_DAC_Control_Test)
{

}

TEST_TEAR_DOWN(R_DAC_Write_Test)
{

}

TEST_TEAR_DOWN(R_DAC_Close_Test)
{

}

TEST_TEAR_DOWN(dac_set_options_Test)
{

}

TEST_TEAR_DOWN(power_on_Test)
{

}

TEST_TEAR_DOWN(power_off_Test)
{

}

/***********************************************************************************************************************
* Group 1: R_DAC_Open_Test
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG002_001
* Description  : RX65N: Unable to configure DAC successfully
*                RX66T: Setup DAC successfully so that channel 0 and channel 1 can controlled individually.
***********************************************************************************************************************/
TEST(R_DAC_Open_Test, TG002_001)
{
	dac_cfg_t config;
	dac_err_t err;
#if defined(BSP_MCU_RX13T)
	config.fmt_flush_right = true;
#else
	config.sync_with_adc   = true;
	config.fmt_flush_right = true;
#endif

#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
	config.sync_unit = 0;
#endif

#ifndef BSP_MCU_RX13T
    config.ch_conv_off_when_output_off = true;
#endif

#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T) || defined(BSP_MCU_RX72T)
    SYSTEM.MSTPCRA.BIT.MSTPA23 = 0;
    S12AD2.ADCSR.BIT.ADST       = 0;
#elif defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
    SYSTEM.MSTPCRA.BIT.MSTPA17 = 0;
    S12AD1.ADCSR.BIT.ADST       = 0;
#endif

	err = R_DAC_Open(&config);
#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
	TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
#elif defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
	TEST_ASSERT_EQUAL_INT(DAC_ERR_INVALID_ARG, err);
#endif
	TEST_ASSERT_EQUAL_INT(0x1F, DA.DACR.BYTE);
	TEST_ASSERT_EQUAL_INT(0,    DA.DADR0);
#ifndef BSP_MCU_RX13T
    TEST_ASSERT_EQUAL_INT(0,    DA.DADR1);
#endif
}

/***********************************************************************************************************************
* Function Name: TG002_002
* Description  : Setup DAC successfully so that channel 0 and channel 1 can controlled individually.
***********************************************************************************************************************/
/*TEST(R_DAC_Open_Test, TG002_002)
{
    dac_cfg_t config;
    dac_err_t err;

    config.sync_with_adc   = false;
    config.fmt_flush_right = true;
#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
	config.sync_unit = 0;
#endif
    config.ch_conv_off_when_output_off = true;

#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
	SYSTEM.MSTPCRA.BIT.MSTPA23 = 0;
	S12AD2.ADCSR.BIT.ADST       = 0;
#endif

    err = R_DAC_Open(&config);

    TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
    TEST_ASSERT_EQUAL_INT(0x1F, DA.DACR.BYTE);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADR0);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADR1);
}*/

/***********************************************************************************************************************
* Function Name: TG002_003
* Description  : Setup DAC successfully so that channel 0 and channel 1 can controlled individually.
***********************************************************************************************************************/
TEST(R_DAC_Open_Test, TG002_003)
{
    dac_cfg_t config;
    dac_err_t err;

#if defined(BSP_MCU_RX13T)
	config.fmt_flush_right = false;
#else
    config.sync_with_adc   = true;
    config.fmt_flush_right = false;
#endif

#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
	config.sync_unit = 1;
#endif
#ifndef BSP_MCU_RX13T
    config.ch_conv_off_when_output_off = true;
#endif

#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
	SYSTEM.MSTPCRA.BIT.MSTPA23 = 0;
	S12AD2.ADCSR.BIT.ADST       = 0;
#elif defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
    SYSTEM.MSTPCRA.BIT.MSTPA16 = 0;
    S12AD1.ADCSR.BIT.ADST       = 0;
#endif

    err = R_DAC_Open(&config);
    TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
    TEST_ASSERT_EQUAL_INT(0x1F, DA.DACR.BYTE);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADR0);
#ifndef BSP_MCU_RX13T
    TEST_ASSERT_EQUAL_INT(0,    DA.DADR1);
#endif
}

/***********************************************************************************************************************
* Function Name: TG002_004
* Description  : Setup DAC successfully so that channel 0 and channel 1 can controlled individually.
**********************************************************************************************************************
TEST(R_DAC_Open_Test, TG002_004)
{
    dac_cfg_t config;
    dac_err_t err;

    config.sync_with_adc   = true;
    config.fmt_flush_right = true;
#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
	config.sync_unit = 1;
#endif
    config.ch_conv_off_when_output_off = true;

#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    SYSTEM.MSTPCRA.BIT.MSTPA23 = 0;
    S12AD2.ADCSR.BIT.ADST       = 0;
#elif defined(BSP_MCU_RX65N)
    S12AD1.ADCSR.BIT.ADST       = 0;
#endif

    err = R_DAC_Open(&config);
    TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
    TEST_ASSERT_EQUAL_INT(0x1F, DA.DACR.BYTE);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADR0);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADR1);
}

**********************************************************************************************************************
* Function Name: TG002_005
* Description  : RX65N: Unable to configure DAC successfully
*                RX66T: Setup DAC successfully so that channel 0 and channel 1 can controlled individually.
**********************************************************************************************************************
TEST(R_DAC_Open_Test, TG002_005)
{
    dac_cfg_t config;
    dac_err_t err;

    config.sync_with_adc   = true;
    config.fmt_flush_right = true;
#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
	config.sync_unit = 0;
#endif
    config.ch_conv_off_when_output_off = false;


#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    SYSTEM.MSTPCRA.BIT.MSTPA23 = 0;
    S12AD2.ADCSR.BIT.ADST       = 0;
#elif defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
    S12AD1.ADCSR.BIT.ADST       = 0;
#endif

    err = R_DAC_Open(&config);
#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
	TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
#elif defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
	TEST_ASSERT_EQUAL_INT(DAC_ERR_INVALID_ARG, err);
#endif
    TEST_ASSERT_EQUAL_INT(0x3F, DA.DACR.BYTE);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADR0);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADR1);
}

**********************************************************************************************************************
* Function Name: TG002_006
* Description  : Disable the analog output.
**********************************************************************************************************************
TEST(R_DAC_Open_Test, TG002_006)
{
    dac_cfg_t config;
    dac_err_t err;

    config.sync_with_adc   = true;
    config.fmt_flush_right = true;
    config.ch_conv_off_when_output_off = true;
#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    config.out_sel_da      = DAC_OUT_DA_OFF;
    config.out_sel_ref     = DAC_OUT_REF_OFF;

    SYSTEM.MSTPCRA.BIT.MSTPA23 = 0;
    S12AD2.ADCSR.BIT.ADST       = 0;
#endif
    err = R_DAC_Open(&config);

    TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    TEST_ASSERT_EQUAL_INT(0,    DA.DADSELR.BIT.OUTDA0);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADSELR.BIT.OUTDA1);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADSELR.BIT.OUTREF0);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADSELR.BIT.OUTREF1);
#endif
    TEST_ASSERT_EQUAL_INT(0x1F, DA.DACR.BYTE);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADR0);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADR1);
}

**********************************************************************************************************************
* Function Name: TG002_007
* Description  : Enable the analog output DA0 and use it as the reference voltage.
**********************************************************************************************************************
TEST(R_DAC_Open_Test, TG002_007)
{
    dac_cfg_t config;
    dac_err_t err;

    config.sync_with_adc   = true;
    config.fmt_flush_right = true;
    config.ch_conv_off_when_output_off = true;
#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    config.out_sel_da      = DAC_OUT_SEL_DA0;
    config.out_sel_ref     = DAC_OUT_SEL_REF0;

    SYSTEM.MSTPCRA.BIT.MSTPA23 = 0;
    S12AD2.ADCSR.BIT.ADST       = 0;
#endif
    err = R_DAC_Open(&config);

    TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    TEST_ASSERT_EQUAL_INT(1,    DA.DADSELR.BIT.OUTDA0);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADSELR.BIT.OUTDA1);
    TEST_ASSERT_EQUAL_INT(1,    DA.DADSELR.BIT.OUTREF0);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADSELR.BIT.OUTREF1);
#endif
    TEST_ASSERT_EQUAL_INT(0x1F, DA.DACR.BYTE);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADR0);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADR1);
}

**********************************************************************************************************************
* Function Name: TG002_008
* Description  : Enable the analog output DA1 and use it as the reference voltage.
**********************************************************************************************************************
TEST(R_DAC_Open_Test, TG002_008)
{
    dac_cfg_t config;
    dac_err_t err;

    config.sync_with_adc   = true;
    config.fmt_flush_right = true;
    config.ch_conv_off_when_output_off = true;
#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    config.out_sel_da      = DAC_OUT_SEL_DA1;
    config.out_sel_ref     = DAC_OUT_SEL_REF1;

    SYSTEM.MSTPCRA.BIT.MSTPA23 = 0;
    S12AD2.ADCSR.BIT.ADST       = 0;
#endif
    err = R_DAC_Open(&config);

    TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    TEST_ASSERT_EQUAL_INT(0,    DA.DADSELR.BIT.OUTDA0);
    TEST_ASSERT_EQUAL_INT(1,    DA.DADSELR.BIT.OUTDA1);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADSELR.BIT.OUTREF0);
    TEST_ASSERT_EQUAL_INT(1,    DA.DADSELR.BIT.OUTREF1);
#endif
    TEST_ASSERT_EQUAL_INT(0x1F, DA.DACR.BYTE);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADR0);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADR1);
}

**********************************************************************************************************************
* Function Name: TG002_009
* Description  : Disable the analog output DA1, but use it as the reference voltage.
**********************************************************************************************************************
TEST(R_DAC_Open_Test, TG002_009)
{
    dac_cfg_t config;
    dac_err_t err;

    config.sync_with_adc   = true;
    config.fmt_flush_right = true;
    config.ch_conv_off_when_output_off = true;
#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    config.out_sel_da      = DAC_OUT_DA_OFF;
    config.out_sel_ref     = DAC_OUT_SEL_REF1;

    SYSTEM.MSTPCRA.BIT.MSTPA23 = 0;
    S12AD2.ADCSR.BIT.ADST       = 0;
#endif
    err = R_DAC_Open(&config);
    TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    TEST_ASSERT_EQUAL_INT(0,    DA.DADSELR.BIT.OUTDA0);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADSELR.BIT.OUTDA1);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADSELR.BIT.OUTREF0);
    TEST_ASSERT_EQUAL_INT(1,    DA.DADSELR.BIT.OUTREF1);
#endif
    TEST_ASSERT_EQUAL_INT(0x1F, DA.DACR.BYTE);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADR0);
    TEST_ASSERT_EQUAL_INT(0,    DA.DADR1);
}*/

/***********************************************************************************************************************
* Function Name: TG002_010
* Description  : Unable to configure DAC when Synchronous Unit is invalid (Synchronous Unit is greater than 1).
**********************************************************************************************************************
TEST(R_DAC_Open_Test, TG002_010)
{
    dac_cfg_t config;
    dac_err_t err;

    config.sync_with_adc   = true;
    config.fmt_flush_right = true;
#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
	config.sync_unit = 2;
#endif
    config.ch_conv_off_when_output_off = true;

    err = R_DAC_Open(&config);
    TEST_ASSERT_EQUAL_INT(DAC_ERR_INVALID_ARG, err);
}*/

/***********************************************************************************************************************
* Function Name: TG002_011
* Description  : Unable to configure DAC when input configuration is invalid (NULL).
***********************************************************************************************************************/
TEST(R_DAC_Open_Test, TG002_011)
{
    dac_cfg_t *pConfig;
    dac_err_t err;

    pConfig = NULL;

    err = R_DAC_Open(pConfig);
    TEST_ASSERT_EQUAL_INT(DAC_ERR_NULL_PTR, err);
}

/***********************************************************************************************************************
* Function Name: TG002_012
* Description  : Unable to configure DAC when DAC hardware has already been locked.
***********************************************************************************************************************/
TEST(R_DAC_Open_Test, TG002_012)
{
    dac_cfg_t config;
    dac_err_t err;

#if defined(BSP_MCU_RX13T)
	config.fmt_flush_right = true;
#else
	config.sync_with_adc   = true;
	config.fmt_flush_right = true;
#endif
#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
	config.sync_unit = 1;
#endif

#ifndef BSP_MCU_RX13T
    config.ch_conv_off_when_output_off = true;
#endif

#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    SYSTEM.MSTPCRA.BIT.MSTPA23 = 0;
    S12AD2.ADCSR.BIT.ADST       = 0;
#endif

    /* DAC hardware has already been locked */
    R_BSP_HardwareLock(BSP_LOCK_DA);

    err = R_DAC_Open(&config);
    TEST_ASSERT_EQUAL_INT(DAC_ERR_LOCK_FAILED, err);

    /* Release lock for DAC */
    R_BSP_HardwareUnlock(BSP_LOCK_DA);
}

/***********************************************************************************************************************
* Function Name: TG002_013
* Description  : Unable to configure DAC when it is set to synchronize with ADC (Unit0), but ADC module is processing.
**********************************************************************************************************************
TEST(R_DAC_Open_Test, TG002_013)
{
    dac_cfg_t config;
    dac_err_t err;

    config.sync_with_adc   = true;
    config.fmt_flush_right = true;
#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
	config.sync_unit = 1;
#endif
    config.ch_conv_off_when_output_off = true;

#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
     ADC module is processing.
    SYSTEM.MSTPCRA.BIT.MSTPA23 = 0;
    S12AD2.ADCSR.BIT.ADST       = 1;
#elif defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
    SYSTEM.MSTPCRA.BIT.MSTPA16 = 0;
    S12AD1.ADCSR.BIT.ADST = 1;
#endif

    err = R_DAC_Open(&config);
    TEST_ASSERT_EQUAL_INT(DAC_ERR_ADC_CONVERTING, err);
}

**********************************************************************************************************************
* Function Name: TG002_014
* Description  : Unable to configure DAC when it is set to synchronize with ADC (Unit0), but ADC module is not working.
**********************************************************************************************************************
TEST(R_DAC_Open_Test, TG002_014)
{
    dac_cfg_t config;
    dac_err_t err;

    config.sync_with_adc   = true;
    config.fmt_flush_right = true;
#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
	config.sync_unit = 0;
#endif
    config.ch_conv_off_when_output_off = true;

#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    SYSTEM.MSTPCRA.BIT.MSTPA23 = 0;
    S12AD2.ADCSR.BIT.ADST = 0;

     ADC (Unit0) is within module-stop state.
    SYSTEM.MSTPCRA.BIT.MSTPA23 = 1;
#elif defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
    SYSTEM.MSTPCRA.BIT.MSTPA17 = 1;
#endif

    err = R_DAC_Open(&config);
    TEST_ASSERT_EQUAL_INT(DAC_ERR_ADC_NOT_POWERED, err);
}

**********************************************************************************************************************
* Function Name: TG002_015
* Description  : Unable to configure DAC when it is set to synchronize with ADC  (Unit1), but ADC module is processing.
**********************************************************************************************************************
TEST(R_DAC_Open_Test, TG002_015)
{
    dac_cfg_t config;
    dac_err_t err;

    config.sync_with_adc   = true;
    config.fmt_flush_right = true;
#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
	config.sync_unit = 0;
#endif
    config.ch_conv_off_when_output_off = true;

#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    SYSTEM.MSTPCRA.BIT.MSTPA23 = 0;
    S12AD2.ADCSR.BIT.ADST      = 0;

     ADC module is processing.
    SYSTEM.MSTPCRA.BIT.MSTPA23 = 0;
    S12AD2.ADCSR.BIT.ADST      = 1;
#elif defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
    SYSTEM.MSTPCRA.BIT.MSTPA17 = 0;
    S12AD.ADCSR.BIT.ADST      = 1;
#endif

    err = R_DAC_Open(&config);
    TEST_ASSERT_EQUAL_INT(DAC_ERR_ADC_CONVERTING, err);
}

**********************************************************************************************************************
* Function Name: TG002_016
* Description  : Unable to configure DAC when it is set to synchronize with ADC (Unit1), but ADC module is not working.
**********************************************************************************************************************
TEST(R_DAC_Open_Test, TG002_016)
{
    dac_cfg_t config;
    dac_err_t err;

    config.sync_with_adc   = true;
    config.fmt_flush_right = true;
#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
	config.sync_unit = 1;
#endif
    config.ch_conv_off_when_output_off = true;

#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    SYSTEM.MSTPCRA.BIT.MSTPA23 = 0;
    S12AD2.ADCSR.BIT.ADST       = 0;

     ADC (Unit1) is within module-stop state.
    SYSTEM.MSTPCRA.BIT.MSTPA23 = 1;
#elif defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
    SYSTEM.MSTPCRA.BIT.MSTPA16 = 1;
#endif

    err = R_DAC_Open(&config);
    TEST_ASSERT_EQUAL_INT(DAC_ERR_ADC_NOT_POWERED, err);
}*/

/***********************************************************************************************************************
* Group 3: R_DAC_Control_Test
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG003_001
* Description  : Enable D/A Output of channel 0
***********************************************************************************************************************/
TEST(R_DAC_Control_Test, TG003_001)
{
	uint8_t   channel;
	dac_cmd_t command;
	dac_err_t err;

	channel = DAC_CH0;
	command = DAC_CMD_OUTPUT_ON;

	err = R_DAC_Control(channel, command);
	TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
	TEST_ASSERT_EQUAL_INT(1, DA.DACR.BIT.DAOE0);
}

/***********************************************************************************************************************
* Function Name: TG003_002
* Description  : Enable D/A Output of channel 1
**********************************************************************************************************************
TEST(R_DAC_Control_Test, TG003_002)
{
    uint8_t   channel;
    dac_cmd_t command;
    dac_err_t err;

    channel = DAC_CH1;
    command = DAC_CMD_OUTPUT_ON;

    err = R_DAC_Control(channel, command);
    TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
    TEST_ASSERT_EQUAL_INT(1, DA.DACR.BIT.DAOE1);
}*/

/***********************************************************************************************************************
* Function Name: TG003_003
* Description  : Disable D/A Output of channel 0
***********************************************************************************************************************/
TEST(R_DAC_Control_Test, TG003_003)
{
    uint8_t   channel;
    dac_cmd_t command;
    dac_err_t err;

    channel = DAC_CH0;
    command = DAC_CMD_OUTPUT_OFF;

    err = R_DAC_Control(channel, command);
    TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
    TEST_ASSERT_EQUAL_INT(0, DA.DACR.BIT.DAOE0);
}

/***********************************************************************************************************************
* Function Name: TG003_004
* Description  : Disable D/A Output of channel 1
**********************************************************************************************************************
TEST(R_DAC_Control_Test, TG003_004)
{
    uint8_t   channel;
    dac_cmd_t command;
    dac_err_t err;

    channel = DAC_CH1;
    command = DAC_CMD_OUTPUT_OFF;

    err = R_DAC_Control(channel, command);
    TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
    TEST_ASSERT_EQUAL_INT(0, DA.DACR.BIT.DAOE1);
}*/

/***********************************************************************************************************************
* Function Name: TG003_005
* Description  : Unable to configure DAC when channel is invalid.
***********************************************************************************************************************/
TEST(R_DAC_Control_Test, TG003_005)
{
    uint8_t   channel;
    dac_cmd_t command;
    dac_err_t err;

    channel = DAC_NUM_CH;
    command = DAC_CMD_OUTPUT_OFF;

    err = R_DAC_Control(channel, command);
    TEST_ASSERT_EQUAL_INT(DAC_ERR_BAD_CHAN, err);
}

/***********************************************************************************************************************
* Function Name: TG003_006
* Description  : Unable to configure DAC when channel is invalid.
***********************************************************************************************************************/
TEST(R_DAC_Control_Test, TG003_006)
{
    uint8_t   channel;
    dac_cmd_t command;
    dac_err_t err;

    channel = DAC_CH0;
    command = DAC_CMD_END_ENUM;

    err = R_DAC_Control(channel, command);
    TEST_ASSERT_EQUAL_INT(DAC_ERR_INVALID_CMD, err);
}

/***********************************************************************************************************************
* Group 3: R_DAC_Write
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_001
* Description  : Write data into D/A Data register (Channel 0)
***********************************************************************************************************************/
TEST(R_DAC_Write_Test, TG004_001)
{
	dac_err_t err;
	uint16_t  data;
	uint8_t   channel;

	channel = DAC_CH0;
	data    = 0x0000;

	err = R_DAC_Write(channel, data);
	TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
	TEST_ASSERT_EQUAL_INT16(data, DA.DADR0);
}

/***********************************************************************************************************************
* Function Name: TG004_002
* Description  : Write data into D/A Data register (Channel 0)
***********************************************************************************************************************/
TEST(R_DAC_Write_Test, TG004_002)
{
    dac_err_t err;
    uint16_t  data;
    uint8_t   channel;

    channel = DAC_CH0;
    data    = 0x7FF;

    err = R_DAC_Write(channel, data);
    TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
    TEST_ASSERT_EQUAL_INT16(data, DA.DADR0);
}

/***********************************************************************************************************************
* Function Name: TG004_003
* Description  : Write data into D/A Data register (Channel 0)
***********************************************************************************************************************/
TEST(R_DAC_Write_Test, TG004_003)
{
    dac_err_t err;
    uint16_t  data;
    uint8_t   channel;

    channel = DAC_CH0;
    data    = 0xFFF;

    err = R_DAC_Write(channel, data);
    TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
    TEST_ASSERT_EQUAL_INT16(data, DA.DADR0);
}


/***********************************************************************************************************************
* Function Name: TG004_001
* Description  : Write data into D/A Data register (Channel 1)
**********************************************************************************************************************
TEST(R_DAC_Write_Test, TG004_004)
{
    dac_err_t err;
    uint16_t  data;
    uint8_t   channel;

    channel = DAC_CH1;
    data    = 0x0000;

    err = R_DAC_Write(channel, data);
    TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
    TEST_ASSERT_EQUAL_INT16(data, DA.DADR1);
}

**********************************************************************************************************************
* Function Name: TG004_005
* Description  : Write data into D/A Data register (Channel 1)
**********************************************************************************************************************
TEST(R_DAC_Write_Test, TG004_005)
{
    dac_err_t err;
    uint16_t  data;
    uint8_t   channel;

    channel = DAC_CH1;
    data    = 0x7FF;

    err = R_DAC_Write(channel, data);
    TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
    TEST_ASSERT_EQUAL_INT16(data, DA.DADR1);
}

**********************************************************************************************************************
* Function Name: TG004_006
* Description  : Write data into D/A Data register (Channel 1)
**********************************************************************************************************************
TEST(R_DAC_Write_Test, TG004_006)
{
    dac_err_t err;
    uint16_t  data;
    uint8_t   channel;

    channel = DAC_CH1;
    data    = 0xFFF;

    err = R_DAC_Write(channel, data);
    TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
    TEST_ASSERT_EQUAL_INT16(data, DA.DADR1);
}*/

/***********************************************************************************************************************
* Function Name: TG004_007
* Description  : Write data into D/A Data register when input is invalid.
***********************************************************************************************************************/
TEST(R_DAC_Write_Test, TG004_007)
{
    dac_err_t err;
    uint16_t  data;
    uint8_t   channel;

    channel = DAC_NUM_CH;
    data    = 0x0000;

    err = R_DAC_Write(channel, data);
    TEST_ASSERT_EQUAL_INT(DAC_ERR_BAD_CHAN, err);
}

/***********************************************************************************************************************
* Function Name: TG004_008
* Description  : Write data into D/A Data register when input is invalid.
***********************************************************************************************************************/
TEST(R_DAC_Write_Test, TG004_008)
{
    dac_err_t err;
    uint16_t  data;
    uint8_t   channel;

    channel = DAC_CH0;
    data    = 0xFFFF;

    err = R_DAC_Write(channel, data);
    TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
    TEST_ASSERT_EQUAL_INT16(0xFFF, 0x0FFF & DA.DADR0);
}

/***********************************************************************************************************************
* Group 5: R_DAC_Close_Test
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_001
* Description  : Confirm return value and register value when closing DAC module
***********************************************************************************************************************/
TEST(R_DAC_Close_Test, TG005_001)
{
	dac_cfg_t config;
    dac_err_t err;
#ifndef BSP_MCU_RX13T
    config.sync_with_adc   = false;
#endif

    config.fmt_flush_right = true;

#ifndef BSP_MCU_RX13T
    config.ch_conv_off_when_output_off = true;
#endif
    /* Open DAC */
    err = R_DAC_Open(&config);

    /* Close DAC */
	err = R_DAC_Close();

	TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
    TEST_ASSERT_EQUAL_INT8(0x1F, DA.DACR.BYTE);
	TEST_ASSERT_EQUAL_INT16(0x0000, DA.DADR0);
#ifndef BSP_MCU_RX13T
	TEST_ASSERT_EQUAL_INT16(0x0000, DA.DADR1);
#endif

	TEST_ASSERT_EQUAL_INT(0, DA.DADPR.BIT.DPSEL);
#ifndef BSP_MCU_RX13T
	TEST_ASSERT_EQUAL_INT(0, DA.DAADSCR.BIT.DAADST);
#endif
	TEST_ASSERT_EQUAL_INT(1, SYSTEM.MSTPCRA.BIT.MSTPA19);
#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
	TEST_ASSERT_EQUAL_INT(0, DA.DADSELR.BYTE);
#endif
}

/***********************************************************************************************************************
* Function Name: TG006_001
* Description  : Unable to configure DAC when it is set to synchronize with ADC (Unit0), but ADC module is processing.
**********************************************************************************************************************
TEST(dac_set_options_Test, TG006_001)
{
    dac_cfg_t config;
    dac_err_t err;

    config.sync_with_adc   = true;
    config.sync_unit       = 0;
    config.fmt_flush_right = true;
    config.ch_conv_off_when_output_off = true;

#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    SYSTEM.MSTPCRA.BIT.MSTPA23 = 0;
    S12AD2.ADCSR.BIT.ADST       = 1;
#elif defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
    S12AD1.ADCSR.BIT.ADST       = 1;
#endif

     Open DAC
    err = R_DAC_Open(&config);

    TEST_ASSERT_EQUAL_INT(DAC_ERR_ADC_CONVERTING, err);
}

**********************************************************************************************************************
* Function Name: TG006_002
* Description  : Unable to configure DAC when it is set to synchronize with ADC (Unit0), but ADC module is processing.
**********************************************************************************************************************
TEST(dac_set_options_Test, TG006_002)
{
    dac_cfg_t config;
    dac_err_t err;

    config.sync_with_adc   = true;
    config.sync_unit       = 0;
    config.fmt_flush_right = true;
    config.ch_conv_off_when_output_off = true;

#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    SYSTEM.MSTPCRA.BIT.MSTPA23 = 1;
#elif defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
    SYSTEM.MSTPCRA.BIT.MSTPA17 = 1;
#endif

     Open DAC
    err = R_DAC_Open(&config);

    TEST_ASSERT_EQUAL_INT(DAC_ERR_ADC_NOT_POWERED, err);
}

**********************************************************************************************************************
* Function Name: TG006_003
* Description  : Unable to configure DAC when it is set to synchronize with ADC  (Unit1), but ADC module is processing.
**********************************************************************************************************************
TEST(dac_set_options_Test, TG006_003)
{
    dac_cfg_t config;
    dac_err_t err;

    config.sync_with_adc   = true;
    config.sync_unit       = 0;
    config.fmt_flush_right = true;
    config.ch_conv_off_when_output_off = true;

#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    S12AD2.ADCSR.BIT.ADST       = 1;
    SYSTEM.MSTPCRA.BIT.MSTPA23 = 0;
#elif defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
    S12AD1.ADCSR.BIT.ADST       = 1;
    SYSTEM.MSTPCRA.BIT.MSTPA17 = 0;
#endif

     Open DAC
    err = R_DAC_Open(&config);

    TEST_ASSERT_EQUAL_INT(DAC_ERR_ADC_CONVERTING, err);
}

**********************************************************************************************************************
* Function Name: TG006_004
* Description  : Unable to configure DAC when it is set to synchronize with ADC (Unit1), but ADC module is not working.
**********************************************************************************************************************
TEST(dac_set_options_Test, TG006_004)
{
    dac_cfg_t config;
    dac_err_t err;

    config.sync_with_adc   = true;
    config.sync_unit       = 0;
    config.fmt_flush_right = true;
    config.ch_conv_off_when_output_off = true;

#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    SYSTEM.MSTPCRA.BIT.MSTPA23 = 1;
#elif defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
    SYSTEM.MSTPCRA.BIT.MSTPA17 = 1;
#endif

     Open DAC
    err = R_DAC_Open(&config);

    TEST_ASSERT_EQUAL_INT(DAC_ERR_ADC_NOT_POWERED, err);
}

**********************************************************************************************************************
* Function Name: TG006_005
* Description  : Setup DAC module to work independently with ADC module.
**********************************************************************************************************************
TEST(dac_set_options_Test, TG006_005)
{
    dac_cfg_t config;
    dac_err_t err;

    config.sync_with_adc   = false;
    config.sync_unit       = 0;
    config.fmt_flush_right = true;
    config.ch_conv_off_when_output_off = true;

#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    SYSTEM.MSTPCRA.BIT.MSTPA23 = 1;
#elif defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
    SYSTEM.MSTPCRA.BIT.MSTPA17 = 1;
#endif

     Open DAC
    err = R_DAC_Open(&config);

    TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
    TEST_ASSERT_EQUAL_INT(0, DA.DAADSCR.BIT.DAADST);
}

**********************************************************************************************************************
* Function Name: TG006_006
* Description  : Setup DAC module to work synchronously with ADC module.
**********************************************************************************************************************
TEST(dac_set_options_Test, TG006_006)
{
    dac_cfg_t config;
    dac_err_t err;

    config.sync_with_adc   = true;
    config.sync_unit       = 1;
    config.fmt_flush_right = true;
    config.ch_conv_off_when_output_off = true;

#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    SYSTEM.MSTPCRA.BIT.MSTPA23 = 0;
    S12AD2.ADCSR.BIT.ADST       = 0;
#elif defined(BSP_MCU_RX72M)
    SYSTEM.MSTPCRA.BIT.MSTPA16 = 0;
    S12AD1.ADCSR.BIT.ADST       = 0;
#endif

     Open DAC
    err = R_DAC_Open(&config);

    TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
    TEST_ASSERT_EQUAL_INT(0, DA.DACR.BIT.DAE);
}

**********************************************************************************************************************
* Function Name: TG006_007
* Description  : Setup DAC module to work synchronously with ADC module.
**********************************************************************************************************************
TEST(dac_set_options_Test, TG006_007)
{
    dac_cfg_t config;
    dac_err_t err;

    config.sync_with_adc   = true;
    config.sync_unit       = 1;
    config.fmt_flush_right = true;
    config.ch_conv_off_when_output_off = false;

#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    SYSTEM.MSTPCRA.BIT.MSTPA23 =  0;
    S12AD2.ADCSR.BIT.ADST       = 0;
#elif defined(BSP_MCU_RX72M)
    SYSTEM.MSTPCRA.BIT.MSTPA16 = 0;
    S12AD1.ADCSR.BIT.ADST       = 0;
#endif

     Open DAC
    err = R_DAC_Open(&config);

    TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
    TEST_ASSERT_EQUAL_INT(1, DA.DACR.BIT.DAE);
}*/

/***********************************************************************************************************************
* Function Name: TG007_001
* Description  : Release DAC module from module-stop state.
***********************************************************************************************************************/
TEST(power_on_Test, TG007_001)
{
    dac_cfg_t config;
    dac_err_t err;
#ifndef BSP_MCU_RX13T
    config.sync_unit = 0;
    config.sync_with_adc   = false;
#endif

    config.fmt_flush_right = true;
#ifndef BSP_MCU_RX13T
    config.ch_conv_off_when_output_off = true;
#endif


#if defined(BSP_MCU_RX66_ALL) || defined(BSP_MCU_RX72T)
    SYSTEM.MSTPCRA.BIT.MSTPA23 = 0;
    S12AD2.ADCSR.BIT.ADST       = 0;
#elif defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX72M)
    S12AD1.ADCSR.BIT.ADST       = 0;
#endif

    /* Open DAC */
    err = R_DAC_Open(&config);

    TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
    TEST_ASSERT_EQUAL_INT(0, SYSTEM.MSTPCRA.BIT.MSTPA19);
}

/***********************************************************************************************************************
* Function Name: TG008_001
* Description  : Set DAC module to be within module-stop state.
***********************************************************************************************************************/
TEST(power_off_Test, TG008_001)
{
    dac_cfg_t config;
    dac_err_t err;
#ifndef BSP_MCU_RX13T
    config.sync_unit	= 0;
    config.sync_with_adc   = false;
#endif

    config.fmt_flush_right = true;
#ifndef BSP_MCU_RX13T
    config.ch_conv_off_when_output_off = true;
#endif


    /* Open DAC */
    err = R_DAC_Open(&config);

    /* Close DAC */
    err = R_DAC_Close();

    TEST_ASSERT_EQUAL_INT(DAC_SUCCESS, err);
    TEST_ASSERT_EQUAL_INT(1, SYSTEM.MSTPCRA.BIT.MSTPA19);
}

/***********************************************************************************************************************
* Group 5: R_DAC_GetVersion_Test
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG001_001
* Description  : Confirm DAC module version
***********************************************************************************************************************/
TEST(R_DAC_GetVersion_Test, TG001_001)
{
	uint32_t ver;

	ver = R_DAC_GetVersion();
	TEST_ASSERT_EQUAL_INT32(0x0004001e, ver); //v4.30
	printf("DAC v%1u.%2u\n", ((ver >> 16) & 0xf), (ver & 0xff));
}
