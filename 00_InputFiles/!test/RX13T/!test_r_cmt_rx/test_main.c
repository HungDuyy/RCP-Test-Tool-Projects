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
* File Name       : test_main.c
* Description  : Unity unit tests for CMT Module
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 28.06.2019 1.00     First Release
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "platform.h"
#include "r_cmt_rx_if.h"
#include "unity_fixture.h"


/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
static void RunAllTests(void);

/***********************************************************************************************************************
* Function Name: TEST_SETUP
* Description  : Setup for these unit tests
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/


TEST_GROUP_RUNNER(R_CMT_CreatePeriodic_Test)
{
    RUN_TEST_CASE(R_CMT_CreatePeriodic_Test, TG001_1);
    RUN_TEST_CASE(R_CMT_CreatePeriodic_Test, TG001_2);
    RUN_TEST_CASE(R_CMT_CreatePeriodic_Test, TG001_3);
    RUN_TEST_CASE(R_CMT_CreatePeriodic_Test, TG001_4);
    RUN_TEST_CASE(R_CMT_CreatePeriodic_Test, TG001_5);
    RUN_TEST_CASE(R_CMT_CreatePeriodic_Test, TG001_6);
    RUN_TEST_CASE(R_CMT_CreatePeriodic_Test, TG001_7);
}

TEST_GROUP_RUNNER(R_CMT_CreateOneShot_Test)
{
    RUN_TEST_CASE(R_CMT_CreateOneShot_Test, TG002_1);
    RUN_TEST_CASE(R_CMT_CreateOneShot_Test, TG002_2);
    RUN_TEST_CASE(R_CMT_CreateOneShot_Test, TG002_3);
    RUN_TEST_CASE(R_CMT_CreateOneShot_Test, TG002_4);
    RUN_TEST_CASE(R_CMT_CreateOneShot_Test, TG002_5);
    RUN_TEST_CASE(R_CMT_CreateOneShot_Test, TG002_6);
}

TEST_GROUP_RUNNER(R_CMT_Stop_Test)
{
    RUN_TEST_CASE(R_CMT_Stop_Test, TG003_1);
    RUN_TEST_CASE(R_CMT_Stop_Test, TG003_2);
    RUN_TEST_CASE(R_CMT_Stop_Test, TG003_3);
//    RUN_TEST_CASE(R_CMT_Stop_Test, TG003_4);
//    RUN_TEST_CASE(R_CMT_Stop_Test, TG003_5);
}

#if    !defined(__RUN_CONBINATION_TEST__)

TEST_GROUP_RUNNER(R_CMT_Control_Test)
{
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_1);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_2);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_3);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_4);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_5);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_6);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_7);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_8);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_9);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_10);
//    RUN_TEST_CASE(R_CMT_Control_Test, TG004_11);
//    RUN_TEST_CASE(R_CMT_Control_Test, TG004_12);
//    RUN_TEST_CASE(R_CMT_Control_Test, TG004_13);
//    RUN_TEST_CASE(R_CMT_Control_Test, TG004_14);
//    RUN_TEST_CASE(R_CMT_Control_Test, TG004_15);
//    RUN_TEST_CASE(R_CMT_Control_Test, TG004_16);
//    RUN_TEST_CASE(R_CMT_Control_Test, TG004_17);
//    RUN_TEST_CASE(R_CMT_Control_Test, TG004_18);
//    RUN_TEST_CASE(R_CMT_Control_Test, TG004_19);
//    RUN_TEST_CASE(R_CMT_Control_Test, TG004_20);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_21);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_22);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_23);
//    RUN_TEST_CASE(R_CMT_Control_Test, TG004_24);
//    RUN_TEST_CASE(R_CMT_Control_Test, TG004_25);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_26);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_27);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_28);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_29);

    /* New command */
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_30);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_31);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_32);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_33);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_34);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_35);
//    RUN_TEST_CASE(R_CMT_Control_Test, TG004_36);
//    RUN_TEST_CASE(R_CMT_Control_Test, TG004_37);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_38);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_39);
    RUN_TEST_CASE(R_CMT_Control_Test, TG004_40);
//    RUN_TEST_CASE(R_CMT_Control_Test, TG004_41);
//    RUN_TEST_CASE(R_CMT_Control_Test, TG004_42);
//    RUN_TEST_CASE(R_CMT_Control_Test, TG004_43);
//    RUN_TEST_CASE(R_CMT_Control_Test, TG004_44);
}

TEST_GROUP_RUNNER(R_CMT_GetVersion_Test)
{
    RUN_TEST_CASE(R_CMT_GetVersion_Test, TG005_1);
}

/* Testing static function */
TEST_GROUP_RUNNER(cmt_create)
{
    RUN_TEST_CASE(cmt_create, TG006_1);
    RUN_TEST_CASE(cmt_create, TG006_2);
    RUN_TEST_CASE(cmt_create, TG006_3);
    RUN_TEST_CASE(cmt_create, TG006_4);
    RUN_TEST_CASE(cmt_create, TG006_5);
    RUN_TEST_CASE(cmt_create, TG006_6);
    RUN_TEST_CASE(cmt_create, TG006_7);
    RUN_TEST_CASE(cmt_create, TG006_8);
}

TEST_GROUP_RUNNER(cmt_lock_state)
{
    RUN_TEST_CASE(cmt_lock_state, TG007_1);
    RUN_TEST_CASE(cmt_lock_state, TG007_2);
}

TEST_GROUP_RUNNER(cmt_unlock_state)
{
    RUN_TEST_CASE(cmt_unlock_state, TG008_1);
}

TEST_GROUP_RUNNER(cmt_find_channel)
{
    RUN_TEST_CASE(cmt_find_channel, TG009_1);
    RUN_TEST_CASE(cmt_find_channel, TG009_2);
    RUN_TEST_CASE(cmt_find_channel, TG009_3);
    RUN_TEST_CASE(cmt_find_channel, TG009_4);
    RUN_TEST_CASE(cmt_find_channel, TG009_5);
}

TEST_GROUP_RUNNER(cmt_setup_channel)
{
    RUN_TEST_CASE(cmt_setup_channel, TG010_1);
    RUN_TEST_CASE(cmt_setup_channel, TG010_2);
    RUN_TEST_CASE(cmt_setup_channel, TG010_3);
    RUN_TEST_CASE(cmt_setup_channel, TG010_4);
    RUN_TEST_CASE(cmt_setup_channel, TG010_5);
}

TEST_GROUP_RUNNER(cmt_counter_start)
{
    RUN_TEST_CASE(cmt_counter_start, TG011_1);
    RUN_TEST_CASE(cmt_counter_start, TG011_2);
//    RUN_TEST_CASE(cmt_counter_start, TG011_3);
//    RUN_TEST_CASE(cmt_counter_start, TG011_4);
}

TEST_GROUP_RUNNER(cmt_counter_stop)
{
    RUN_TEST_CASE(cmt_counter_stop, TG012_1);
    RUN_TEST_CASE(cmt_counter_stop, TG012_2);
//    RUN_TEST_CASE(cmt_counter_stop, TG012_3);
//    RUN_TEST_CASE(cmt_counter_stop, TG012_4);
}

TEST_GROUP_RUNNER(power_on)
{
    RUN_TEST_CASE(power_on, TG013_1);
    RUN_TEST_CASE(power_on, TG013_2);
//    RUN_TEST_CASE(power_on, TG013_3);
//    RUN_TEST_CASE(power_on, TG013_4);
}

TEST_GROUP_RUNNER(power_off)
{
    RUN_TEST_CASE(power_off, TG014_1);
    RUN_TEST_CASE(power_off, TG014_2);
//    RUN_TEST_CASE(power_off, TG014_3);
//    RUN_TEST_CASE(power_off, TG014_4);
}

TEST_GROUP_RUNNER(R_CMT_CreatePeriodicAssignChannelPriority_Test)
{
    RUN_TEST_CASE(R_CMT_CreatePeriodicAssignChannelPriority_Test, TG015_1);
    RUN_TEST_CASE(R_CMT_CreatePeriodicAssignChannelPriority_Test, TG015_2);
    RUN_TEST_CASE(R_CMT_CreatePeriodicAssignChannelPriority_Test, TG015_3);
    RUN_TEST_CASE(R_CMT_CreatePeriodicAssignChannelPriority_Test, TG015_4);
    RUN_TEST_CASE(R_CMT_CreatePeriodicAssignChannelPriority_Test, TG015_5);
    RUN_TEST_CASE(R_CMT_CreatePeriodicAssignChannelPriority_Test, TG015_6);
    RUN_TEST_CASE(R_CMT_CreatePeriodicAssignChannelPriority_Test, TG015_7);
    RUN_TEST_CASE(R_CMT_CreatePeriodicAssignChannelPriority_Test, TG015_8);
//    RUN_TEST_CASE(R_CMT_CreatePeriodicAssignChannelPriority_Test, TG015_9);
//    RUN_TEST_CASE(R_CMT_CreatePeriodicAssignChannelPriority_Test, TG015_10);
}

TEST_GROUP_RUNNER(R_CMT_CreateOneShotAssignChannelPriority_Test)
{
    RUN_TEST_CASE(R_CMT_CreateOneShotAssignChannelPriority_Test, TG016_1);
    RUN_TEST_CASE(R_CMT_CreateOneShotAssignChannelPriority_Test, TG016_2);
    RUN_TEST_CASE(R_CMT_CreateOneShotAssignChannelPriority_Test, TG016_3);
    RUN_TEST_CASE(R_CMT_CreateOneShotAssignChannelPriority_Test, TG016_4);
    RUN_TEST_CASE(R_CMT_CreateOneShotAssignChannelPriority_Test, TG016_5);
    RUN_TEST_CASE(R_CMT_CreateOneShotAssignChannelPriority_Test, TG016_6);
    RUN_TEST_CASE(R_CMT_CreateOneShotAssignChannelPriority_Test, TG016_7);
//    RUN_TEST_CASE(R_CMT_CreateOneShotAssignChannelPriority_Test, TG016_8);
//    RUN_TEST_CASE(R_CMT_CreateOneShotAssignChannelPriority_Test, TG016_9);
}

#endif

/***********************************************************************************************************************
* Function Name: RunAllTests
* Description  : Call test groups
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
static void RunAllTests(void)
{
    /* Run each test group. */
    RUN_TEST_GROUP(R_CMT_CreatePeriodic_Test);
    RUN_TEST_GROUP(R_CMT_CreateOneShot_Test);
    RUN_TEST_GROUP(R_CMT_Stop_Test);

    RUN_TEST_GROUP(R_CMT_Control_Test);
    RUN_TEST_GROUP(R_CMT_GetVersion_Test);

    /* Testing static function */
    RUN_TEST_GROUP(cmt_create);
    RUN_TEST_GROUP(cmt_lock_state);
    RUN_TEST_GROUP(cmt_unlock_state);
    RUN_TEST_GROUP(cmt_find_channel);
    RUN_TEST_GROUP(cmt_setup_channel);
    RUN_TEST_GROUP(cmt_counter_start);
    RUN_TEST_GROUP(cmt_counter_stop);
    RUN_TEST_GROUP(power_on);
    RUN_TEST_GROUP(power_off);

    /* Testing new APIs */
    RUN_TEST_GROUP(R_CMT_CreatePeriodicAssignChannelPriority_Test);
    RUN_TEST_GROUP(R_CMT_CreateOneShotAssignChannelPriority_Test);

}
/***********************************************************************************************************************
End of function RunAllTests
***********************************************************************************************************************/

void main()
{
    printf("\r\nUnit Test\r\n");
    UnityMain(0, 0, RunAllTests);

    printf("Unit Test completed\r\n");

    while(1)
    {
        /* Infinite loop. */
    }
}
/***********************************************************************************************************************
End of function main
***********************************************************************************************************************/
