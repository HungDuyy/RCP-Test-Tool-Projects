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
* Description     : Unity unit tests for DTC Module
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 07.12.2018 1.00     First Release
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "platform.h"
#include "r_dtc_rx_if.h"        // The DTC module API interface file.
#include "r_dtc_rx_config.h"    // User configurable options for the DTC module
#include "r_dtc_rx_private.h"
#include "r_dtc_rx_target.h"
#include "../!test/unity/unity_fixture.h"

#include <stdio.h>


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

/***********************************************************************************************************************
* Function Name: TEST_SETUP
* Description  : Setup for these unit tests
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/

TEST_GROUP_RUNNER(R_DTC_Open_Test)
{
    RUN_TEST_CASE(R_DTC_Open_Test, TG001_001);
    RUN_TEST_CASE(R_DTC_Open_Test, TG001_002);
    RUN_TEST_CASE(R_DTC_Open_Test, TG001_003);
    RUN_TEST_CASE(R_DTC_Open_Test, TG001_004);
}

TEST_GROUP_RUNNER(R_DTC_Create_Test)
{
    RUN_TEST_CASE(R_DTC_Create_Test, TG002_001);
    RUN_TEST_CASE(R_DTC_Create_Test, TG002_002);
    RUN_TEST_CASE(R_DTC_Create_Test, TG002_003);
    RUN_TEST_CASE(R_DTC_Create_Test, TG002_004);
    RUN_TEST_CASE(R_DTC_Create_Test, TG002_005);
    RUN_TEST_CASE(R_DTC_Create_Test, TG002_006);
}

TEST_GROUP_RUNNER(R_DTC_CreateSeq_Test)
{
#if (DTC_IP_VER_DTCb <= DTC_IP) // RX65N
    RUN_TEST_CASE(R_DTC_CreateSeq_Test, TG003_001);
    RUN_TEST_CASE(R_DTC_CreateSeq_Test, TG003_002);
    RUN_TEST_CASE(R_DTC_CreateSeq_Test, TG003_003);
    RUN_TEST_CASE(R_DTC_CreateSeq_Test, TG003_004);
    RUN_TEST_CASE(R_DTC_CreateSeq_Test, TG003_005);
#else // RX66T, RX72T
    RUN_TEST_CASE(R_DTC_CreateSeq_Test, TG003_001);
#endif /* (DTC_IP_VER_DTCb <= DTC_IP) */
}

TEST_GROUP_RUNNER(R_DTC_Close_Test)
{
    RUN_TEST_CASE(R_DTC_Close_Test, TG004_001);
    RUN_TEST_CASE(R_DTC_Close_Test, TG004_002);
}

TEST_GROUP_RUNNER(R_DTC_Control_Test)
{
    RUN_TEST_CASE(R_DTC_Control_Test, TG005_001);
    RUN_TEST_CASE(R_DTC_Control_Test, TG005_002);
    RUN_TEST_CASE(R_DTC_Control_Test, TG005_003);
    RUN_TEST_CASE(R_DTC_Control_Test, TG005_004);

    RUN_TEST_CASE(R_DTC_Control_Test, TG005_005);
    RUN_TEST_CASE(R_DTC_Control_Test, TG005_006);
    RUN_TEST_CASE(R_DTC_Control_Test, TG005_007);

    RUN_TEST_CASE(R_DTC_Control_Test, TG005_008);
    RUN_TEST_CASE(R_DTC_Control_Test, TG005_009);
    RUN_TEST_CASE(R_DTC_Control_Test, TG005_010);
    RUN_TEST_CASE(R_DTC_Control_Test, TG005_011);
    RUN_TEST_CASE(R_DTC_Control_Test, TG005_012);
    RUN_TEST_CASE(R_DTC_Control_Test, TG005_013);
    RUN_TEST_CASE(R_DTC_Control_Test, TG005_014);
    RUN_TEST_CASE(R_DTC_Control_Test, TG005_015);
    RUN_TEST_CASE(R_DTC_Control_Test, TG005_016);
    RUN_TEST_CASE(R_DTC_Control_Test, TG005_017);
    RUN_TEST_CASE(R_DTC_Control_Test, TG005_018);
    RUN_TEST_CASE(R_DTC_Control_Test, TG005_019);
    RUN_TEST_CASE(R_DTC_Control_Test, TG005_020);
    RUN_TEST_CASE(R_DTC_Control_Test, TG005_021);
    RUN_TEST_CASE(R_DTC_Control_Test, TG005_022);
    RUN_TEST_CASE(R_DTC_Control_Test, TG005_023);
    RUN_TEST_CASE(R_DTC_Control_Test, TG005_024);
}

TEST_GROUP_RUNNER(R_DTC_GetVersion_Test)
{
    RUN_TEST_CASE(R_DTC_GetVersion_Test, TG006_001);
}

TEST_GROUP_RUNNER(r_dtc_set_transfer_data_Test)
{
    RUN_TEST_CASE(r_dtc_set_transfer_data_Test, TG007_001);
    RUN_TEST_CASE(r_dtc_set_transfer_data_Test, TG007_002);
    RUN_TEST_CASE(r_dtc_set_transfer_data_Test, TG007_003);
    RUN_TEST_CASE(r_dtc_set_transfer_data_Test, TG007_004);
    RUN_TEST_CASE(r_dtc_set_transfer_data_Test, TG007_005);
    RUN_TEST_CASE(r_dtc_set_transfer_data_Test, TG007_006);
    RUN_TEST_CASE(r_dtc_set_transfer_data_Test, TG007_007);
    RUN_TEST_CASE(r_dtc_set_transfer_data_Test, TG007_008);
    RUN_TEST_CASE(r_dtc_set_transfer_data_Test, TG007_009);
    RUN_TEST_CASE(r_dtc_set_transfer_data_Test, TG007_010);
    RUN_TEST_CASE(r_dtc_set_transfer_data_Test, TG007_011);
    RUN_TEST_CASE(r_dtc_set_transfer_data_Test, TG007_012);
    RUN_TEST_CASE(r_dtc_set_transfer_data_Test, TG007_013);
    RUN_TEST_CASE(r_dtc_set_transfer_data_Test, TG007_014);
    RUN_TEST_CASE(r_dtc_set_transfer_data_Test, TG007_015);
    RUN_TEST_CASE(r_dtc_set_transfer_data_Test, TG007_016);
    RUN_TEST_CASE(r_dtc_set_transfer_data_Test, TG007_017);
    RUN_TEST_CASE(r_dtc_set_transfer_data_Test, TG007_018);
    RUN_TEST_CASE(r_dtc_set_transfer_data_Test, TG007_019);
    RUN_TEST_CASE(r_dtc_set_transfer_data_Test, TG007_020);
    RUN_TEST_CASE(r_dtc_set_transfer_data_Test, TG007_021);
    RUN_TEST_CASE(r_dtc_set_transfer_data_Test, TG007_022);
}

TEST_GROUP_RUNNER(r_dtc_clear_all_dtce_bits_Test)
{
    RUN_TEST_CASE(r_dtc_clear_all_dtce_bits_Test, TG008_001);
}

TEST_GROUP_RUNNER(r_dtc_abort_chain_transfer_Test)
{
    RUN_TEST_CASE(r_dtc_abort_chain_transfer_Test, TG009_001);
    RUN_TEST_CASE(r_dtc_abort_chain_transfer_Test, TG009_002);
    RUN_TEST_CASE(r_dtc_abort_chain_transfer_Test, TG009_003);
}

TEST_GROUP_RUNNER(r_dtc_acquire_hw_lock_Test)
{
    RUN_TEST_CASE(r_dtc_acquire_hw_lock_Test, TG010_001);
    RUN_TEST_CASE(r_dtc_acquire_hw_lock_Test, TG010_002);
}

TEST_GROUP_RUNNER(r_dtc_release_hw_lock_Test)
{
    RUN_TEST_CASE(r_dtc_release_hw_lock_Test, TG011_001);
}

TEST_GROUP_RUNNER(r_dtc_check_dmac_locking_sw_Test)
{
    RUN_TEST_CASE(r_dtc_check_dmac_locking_sw_Test, TG012_001);
    RUN_TEST_CASE(r_dtc_check_dmac_locking_sw_Test, TG012_002);
}

TEST_GROUP_RUNNER(r_dtc_check_DMAC_locking_byUSER_Test)
{
    RUN_TEST_CASE(r_dtc_check_DMAC_locking_byUSER_Test, TG013_001);
}

TEST_GROUP_RUNNER(r_dtc_check_create_param_Test)
{
    RUN_TEST_CASE(r_dtc_check_create_param_Test, TG014_001);
    RUN_TEST_CASE(r_dtc_check_create_param_Test, TG014_002);
    RUN_TEST_CASE(r_dtc_check_create_param_Test, TG014_003);
    RUN_TEST_CASE(r_dtc_check_create_param_Test, TG014_004);
    RUN_TEST_CASE(r_dtc_check_create_param_Test, TG014_005);
    RUN_TEST_CASE(r_dtc_check_create_param_Test, TG014_006);
    RUN_TEST_CASE(r_dtc_check_create_param_Test, TG014_007);
    RUN_TEST_CASE(r_dtc_check_create_param_Test, TG014_008);
    RUN_TEST_CASE(r_dtc_check_create_param_Test, TG014_009);
    RUN_TEST_CASE(r_dtc_check_create_param_Test, TG014_010);
    RUN_TEST_CASE(r_dtc_check_create_param_Test, TG014_011);
    RUN_TEST_CASE(r_dtc_check_create_param_Test, TG014_012);
}

TEST_GROUP_RUNNER(r_dtc_module_enable_Test)
{
    RUN_TEST_CASE(r_dtc_module_enable_Test, TG015_001);
}

TEST_GROUP_RUNNER(r_dtc_module_disable_Test)
{
    RUN_TEST_CASE(r_dtc_module_disable_Test, TG016_001);
}


/***********************************************************************************************************************
* Function Name: RunAllTests
* Description  : Call test groups
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
static void RunAllTests(void)
{
    /* Run each test group. */
    printf("RUN TEST GROUP: R_DTC_Open_Test\n");
    RUN_TEST_GROUP(R_DTC_Open_Test);
    printf("END TEST GROUP: R_DTC_Open_Test\n\n");

    printf("RUN TEST GROUP: R_DTC_Create_Test\n");
    RUN_TEST_GROUP(R_DTC_Create_Test);
    printf("END TEST GROUP: R_DTC_Create_Test\n\n");

    printf("RUN TEST GROUP: R_DTC_CreateSeq_Test\n");
    RUN_TEST_GROUP(R_DTC_CreateSeq_Test);
    printf("END TEST GROUP: R_DTC_CreateSeq_Test\n\n");

    printf("RUN TEST GROUP: R_DTC_Close_Test\n");
    RUN_TEST_GROUP(R_DTC_Close_Test);
    printf("END TEST GROUP: R_DTC_Close_Test\n\n");

    printf("RUN TEST GROUP: R_DTC_Control_Test\n");
    RUN_TEST_GROUP(R_DTC_Control_Test);
    printf("END TEST GROUP: R_DTC_Control_Test\n\n");

    printf("RUN TEST GROUP: R_DTC_GetVersion_Test\n");
    RUN_TEST_GROUP(R_DTC_GetVersion_Test);
    printf("END TEST GROUP: R_DTC_GetVersion_Test\n\n");

    printf("RUN TEST GROUP: r_dtc_set_transfer_data_Test\n");
    RUN_TEST_GROUP(r_dtc_set_transfer_data_Test);
    printf("END TEST GROUP: r_dtc_set_transfer_data_Test\n\n");

    printf("RUN TEST GROUP: r_dtc_clear_all_dtce_bits_Test\n");
    RUN_TEST_GROUP(r_dtc_clear_all_dtce_bits_Test);
    printf("END TEST GROUP: r_dtc_clear_all_dtce_bits_Test\n\n");

    printf("RUN TEST GROUP: r_dtc_abort_chain_transfer_Test\n");
    RUN_TEST_GROUP(r_dtc_abort_chain_transfer_Test);
    printf("END TEST GROUP: r_dtc_abort_chain_transfer_Test\n\n");

    printf("RUN TEST GROUP: r_dtc_acquire_hw_lock_Test\n");
    RUN_TEST_GROUP(r_dtc_acquire_hw_lock_Test);
    printf("END TEST GROUP: r_dtc_acquire_hw_lock_Test\n\n");

    printf("RUN TEST GROUP: r_dtc_release_hw_lock_Test\n");
    RUN_TEST_GROUP(r_dtc_release_hw_lock_Test);
    printf("END TEST GROUP: r_dtc_release_hw_lock_Test\n\n");

    printf("RUN TEST GROUP: r_dtc_check_dmac_locking_sw_Test\n");
    RUN_TEST_GROUP(r_dtc_check_dmac_locking_sw_Test);
    printf("END TEST GROUP: r_dtc_check_dmac_locking_sw_Test\n\n");

    printf("RUN TEST GROUP: r_dtc_check_DMAC_locking_byUSER_Test\n");
    RUN_TEST_GROUP(r_dtc_check_DMAC_locking_byUSER_Test);
    printf("END TEST GROUP: r_dtc_check_DMAC_locking_byUSER_Test\n\n");

    printf("RUN TEST GROUP: r_dtc_check_create_param_Test\n");
    RUN_TEST_GROUP(r_dtc_check_create_param_Test);
    printf("END TEST GROUP: r_dtc_check_create_param_Test\n\n");

    printf("RUN TEST GROUP: r_dtc_module_enable_Test\n");
    RUN_TEST_GROUP(r_dtc_module_enable_Test);
    printf("END TEST GROUP: r_dtc_module_enable_Test\n\n");

    printf("RUN TEST GROUP: r_dtc_module_disable_Test\n");
    RUN_TEST_GROUP(r_dtc_module_disable_Test);
    printf("END TEST GROUP: r_dtc_module_disable_Test\n\n");



}
/***********************************************************************************************************************
End of function RunAllTests
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TEST_TEAR_DOWN
* Description  : Tear down for these unit tests
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/

void main()
{
    UnityMain(0, 0, RunAllTests);

    while(1)
    {
        /* Infinite loop. */
    }
}
/***********************************************************************************************************************
End of function main
***********************************************************************************************************************/
