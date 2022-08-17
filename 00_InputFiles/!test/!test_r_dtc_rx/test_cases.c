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
* File Name       : test_cases.c
* Description     : Unity unit tests for DTC module
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

extern uint8_t var_T004_002, var_T011_001, var_T012_001;

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/
extern uint32_t * g_dtc_table_work[2];
extern const dtc_activation_source_t g_source_array[];

/***********************************************************************************************************************
Imported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
/* Declare test groups. */
TEST_GROUP(R_DTC_Open_Test);
TEST_GROUP(R_DTC_Create_Test);
TEST_GROUP(R_DTC_CreateSeq_Test);
TEST_GROUP(R_DTC_Close_Test);
TEST_GROUP(R_DTC_Control_Test);
TEST_GROUP(R_DTC_GetVersion_Test);
TEST_GROUP(r_dtc_set_transfer_data_Test);
TEST_GROUP(r_dtc_clear_all_dtce_bits_Test);
TEST_GROUP(r_dtc_abort_chain_transfer_Test);
TEST_GROUP(r_dtc_acquire_hw_lock_Test);
TEST_GROUP(r_dtc_release_hw_lock_Test);
TEST_GROUP(r_dtc_check_dmac_locking_sw_Test);
TEST_GROUP(r_dtc_check_DMAC_locking_byUSER_Test);
TEST_GROUP(r_dtc_check_create_param_Test);
TEST_GROUP(r_dtc_module_enable_Test);
TEST_GROUP(r_dtc_module_disable_Test);

uint32_t                   test_dest_buff[256];
uint16_t                   test_dest_buff16[256];
bool                       dtc_end_chk[8];
dtc_transfer_data_t        transfer_data[8];
dtc_transfer_data_cfg_t    data_cfg[8];

const uint32_t test_src_buff32[256] = 
{
0x00000000, 0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000005, 0x00000006, 0x00000007, 0x00000008, 0x00000009, 0x0000000A, 0x0000000B, 0x0000000C, 0x0000000D, 0x0000000E, 0x0000000F,
0x11000000, 0x11000001, 0x11000002, 0x11000003, 0x11000004, 0x11000005, 0x11000006, 0x11000007, 0x11000008, 0x11000009, 0x1100000A, 0x1100000B, 0x1100000C, 0x1100000D, 0x1100000E, 0x1100000F,
0x22000000, 0x22000001, 0x22000002, 0x22000003, 0x22000004, 0x22000005, 0x22000006, 0x22000007, 0x22000008, 0x22000009, 0x2200000A, 0x2200000B, 0x2200000C, 0x2200000D, 0x2200000E, 0x2200000F,
0x33000000, 0x33000001, 0x33000002, 0x33000003, 0x33000004, 0x33000005, 0x33000006, 0x33000007, 0x33000008, 0x33000009, 0x3300000A, 0x3300000B, 0x3300000C, 0x3300000D, 0x3300000E, 0x3300000F,
0x44000000, 0x44000001, 0x44000002, 0x44000003, 0x44000004, 0x44000005, 0x44000006, 0x44000007, 0x44000008, 0x44000009, 0x4400000A, 0x4400000B, 0x4400000C, 0x4400000D, 0x4400000E, 0x4400000F,
0x55000000, 0x55000001, 0x55000002, 0x55000003, 0x55000004, 0x55000005, 0x55000006, 0x55000007, 0x55000008, 0x55000009, 0x5500000A, 0x5500000B, 0x5500000C, 0x5500000D, 0x5500000E, 0x5500000F,
0x66000000, 0x66000001, 0x66000002, 0x66000003, 0x66000004, 0x66000005, 0x66000006, 0x66000007, 0x66000008, 0x66000009, 0x6600000A, 0x6600000B, 0x6600000C, 0x6600000D, 0x6600000E, 0x6600000F,
0x77000000, 0x77000001, 0x77000002, 0x77000003, 0x77000004, 0x77000005, 0x77000006, 0x77000007, 0x77000008, 0x77000009, 0x7700000A, 0x7700000B, 0x7700000C, 0x7700000D, 0x7700000E, 0x7700000F,
0x88000000, 0x88000001, 0x88000002, 0x88000003, 0x88000004, 0x88000005, 0x88000006, 0x88000007, 0x88000008, 0x88000009, 0x8800000A, 0x8800000B, 0x8800000C, 0x8800000D, 0x8800000E, 0x8800000F,
0x99000000, 0x99000001, 0x99000002, 0x99000003, 0x99000004, 0x99000005, 0x99000006, 0x99000007, 0x99000008, 0x99000009, 0x9900000A, 0x9900000B, 0x9900000C, 0x9900000D, 0x9900000E, 0x9900000F,
0xAA000000, 0xAA000001, 0xAA000002, 0xAA000003, 0xAA000004, 0xAA000005, 0xAA000006, 0xAA000007, 0xAA000008, 0xAA000009, 0xAA00000A, 0xAA00000B, 0xAA00000C, 0xAA00000D, 0xAA00000E, 0xAA00000F,
0xBB000000, 0xBB000001, 0xBB000002, 0xBB000003, 0xBB000004, 0xBB000005, 0xBB000006, 0xBB000007, 0xBB000008, 0xBB000009, 0xBB00000A, 0xBB00000B, 0xBB00000C, 0xBB00000D, 0xBB00000E, 0xBB00000F,
0xCC000000, 0xCC000001, 0xCC000002, 0xCC000003, 0xCC000004, 0xCC000005, 0xCC000006, 0xCC000007, 0xCC000008, 0xCC000009, 0xCC00000A, 0xCC00000B, 0xCC00000C, 0xCC00000D, 0xCC00000E, 0xCC00000F,
0xDD000000, 0xDD000001, 0xDD000002, 0xDD000003, 0xDD000004, 0xDD000005, 0xDD000006, 0xDD000007, 0xDD000008, 0xDD000009, 0xDD00000A, 0xDD00000B, 0xDD00000C, 0xDD00000D, 0xDD00000E, 0xDD00000F,
0xEE000000, 0xEE000001, 0xEE000002, 0xEE000003, 0xEE000004, 0xEE000005, 0xEE000006, 0xEE000007, 0xEE000008, 0xEE000009, 0xEE00000A, 0xEE00000B, 0xEE00000C, 0xEE00000D, 0xEE00000E, 0xEE00000F,
0xFF000000, 0xFF000001, 0xFF000002, 0xFF000003, 0xFF000004, 0xFF000005, 0xFF000006, 0xFF000007, 0xFF000008, 0xFF000009, 0xFF00000A, 0xFF00000B, 0xFF00000C, 0xFF00000D, 0xFF00000E, 0xFF00000F
};

/***********************************************************************************************************************
* Function Name: TEST_R_DTC_Open_Test_SETUP
* Description  :
***********************************************************************************************************************/
TEST_SETUP(R_DTC_Open_Test)
{
    
}
/***********************************************************************************************************************
End of function TEST_R_DTC_Open_Test_SETUP
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TEST_R_DTC_Open_Test_TEAR_DOWN
* Description  :
***********************************************************************************************************************/
TEST_TEAR_DOWN(R_DTC_Open_Test)
{
    R_DTC_Close();
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
}
/***********************************************************************************************************************
End of function TEST_R_DTC_Open_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG001_001
* Description  : Test API function R_DTC_Open()
***********************************************************************************************************************/
TEST(R_DTC_Open_Test, TG001_001)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_DISABLE)
    dtc_err_t    ret_dtc = DTC_SUCCESS;
    uint8_t *    dtc_table_work2 = 0;

    R_DTC_Close();

    R_BSP_HardwareLock(BSP_LOCK_DTC);

    ret_dtc = R_DTC_Open();

    TEST_ASSERT_EQUAL(DTC_ERR_BUSY, ret_dtc);
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
    TEST_ASSERT_EQUAL(DTC_SUCCESS, R_DTC_Open());

#endif
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Open_Test_TG001_001
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG001_002
* Description  : Test API function R_DTC_Open()
***********************************************************************************************************************/
TEST(R_DTC_Open_Test, TG001_002)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_DISABLE)
    dtc_err_t    ret_dtc = DTC_SUCCESS;
    uint8_t *    dtc_table_work2 = 0;

    R_DTC_Open();

    R_BSP_HardwareUnlock(BSP_LOCK_DTC);

    ret_dtc = R_DTC_Open();

    TEST_ASSERT_EQUAL(DTC_ERR_OPENED, ret_dtc);
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
    TEST_ASSERT_EQUAL(DTC_ERR_OPENED, R_DTC_Open());

#endif
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Open_Test_TG001_002
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG001_003
* Description  : Test API function R_DTC_Open()
***********************************************************************************************************************/
TEST(R_DTC_Open_Test, TG001_003)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_DISABLE)
    dtc_err_t    ret_dtc = DTC_SUCCESS;
    uint8_t *    dtc_table_work2 = 0;

    R_DTC_Close();

    R_BSP_HardwareUnlock(BSP_LOCK_DTC);

    ret_dtc = R_DTC_Open();

    dtc_table_work2 = (uint8_t *)g_dtc_table_work[1];
    dtc_table_work2 = (dtc_table_work2 + 0x400);
    dtc_table_work2 = (uint8_t *)((uint32_t)dtc_table_work2 & 0xfffffc00);
    TEST_ASSERT_EQUAL(dtc_table_work2, DTC.DTCVBR);

    TEST_ASSERT_EQUAL(0, DTC.DTCADMOD.BIT.SHORT);

    TEST_ASSERT_EQUAL(1, DTC.DTCCR.BIT.RRS);

    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
    TEST_ASSERT_EQUAL(DTC_ERR_OPENED, R_DTC_Open());

#endif
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Open_Test_TG001_003
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG001_004
* Description  : Test API function R_DTC_Open()
***********************************************************************************************************************/
TEST(R_DTC_Open_Test, TG001_004)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_ENABLE)
    dtc_err_t    ret_dtc = DTC_SUCCESS;
    uint8_t *    dtc_table_work2 = 0;

    R_DTC_Close();

    R_BSP_HardwareUnlock(BSP_LOCK_DTC);

    ret_dtc = R_DTC_Open();

    dtc_table_work2 = (uint8_t *)g_dtc_table_work[1];
    dtc_table_work2 = (dtc_table_work2 + 0x400);
    dtc_table_work2 = (uint8_t *)((uint32_t)dtc_table_work2 & 0xfffffc00);
    TEST_ASSERT_EQUAL(dtc_table_work2, DTC.DTCVBR);

    TEST_ASSERT_EQUAL(1, DTC.DTCCR.BIT.RRS);

    TEST_ASSERT_EQUAL(1, DTC.DTCADMOD.BIT.SHORT);

    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
    TEST_ASSERT_EQUAL(DTC_ERR_OPENED, R_DTC_Open());

#endif
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Open_Test_TG001_004
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: TEST_R_DTC_Create_Test_SETUP
* Description  :
***********************************************************************************************************************/
TEST_SETUP(R_DTC_Create_Test)
{
    
}
/***********************************************************************************************************************
End of function TEST_R_DTC_Create_Test_SETUP
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TEST_R_DTC_Create_Test_TEAR_DOWN
* Description  :
***********************************************************************************************************************/
TEST_TEAR_DOWN(R_DTC_Create_Test)
{
    R_DTC_Close();
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
}
/***********************************************************************************************************************
End of function TEST_R_DTC_Create_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG002_001
* Description  : Test API function R_DTC_Create()
***********************************************************************************************************************/
TEST(R_DTC_Create_Test, TG002_001)
{
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;

    R_DTC_Open();

    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_NOT_EQUAL(DTC_SUCCESS, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Create_Test_TG002_001
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG002_002
* Description  : Test API function R_DTC_Create()
***********************************************************************************************************************/
TEST(R_DTC_Create_Test, TG002_002)
{
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;

    R_DTC_Close();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];

    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(DTC_ERR_NOT_OPEN, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Create_Test_TG002_002
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG002_003
* Description  : Test API function R_DTC_Create()
***********************************************************************************************************************/
TEST(R_DTC_Create_Test, TG002_003)
{
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = (3 << 6);

    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];

    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_ARG, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Create_Test_TG002_003
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG002_004
* Description  : Test API function R_DTC_Create()
***********************************************************************************************************************/
TEST(R_DTC_Create_Test, TG002_004)
{
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];

    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);

}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Create_Test_TG002_004
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG002_005
* Description  : Test API function R_DTC_Create()
***********************************************************************************************************************/
TEST(R_DTC_Create_Test, TG002_005)
{
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];

    uint32_t *ptr = (uint32_t *)((uint32_t)DTC.DTCVBR + (4 * act_source));

    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(*ptr, (uint32_t)p_transfer_data);

    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);

}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Create_Test_TG002_005
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG002_006
* Description  : Test API function R_DTC_Create()
***********************************************************************************************************************/
TEST(R_DTC_Create_Test, TG002_006)
{
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];

    for (int i = 0; i < DTC_NUM_INTERRUPT_SRC; i++) {
        act_source = g_source_array[i];
        uint32_t *ptr = (uint32_t *)((uint32_t)DTC.DTCVBR + (4 * act_source));
        ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);
        TEST_ASSERT_EQUAL(*ptr, (uint32_t)p_transfer_data);
        TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
    }

}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Create_Test_TG002_006
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: TEST_R_DTC_CreateSeq_Test_SETUP
* Description  :
***********************************************************************************************************************/
TEST_SETUP(R_DTC_CreateSeq_Test)
{
    
}
/***********************************************************************************************************************
End of function TEST_R_DTC_CreateSeq_Test_SETUP
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TEST_R_DTC_CreateSeq_Test_TEAR_DOWN
* Description  :
***********************************************************************************************************************/
TEST_TEAR_DOWN(R_DTC_CreateSeq_Test)
{
    R_DTC_Close();
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
}
/***********************************************************************************************************************
End of function TEST_R_DTC_CreateSeq_Test_TEAR_DOWN
***********************************************************************************************************************/

#if (DTC_IP_VER_DTCb <= DTC_IP) // RX65N

/***********************************************************************************************************************
 * Function Name: TG003_001
 * Description  : Test API function R_DTC_CreateSeq()
 ***********************************************************************************************************************/
TEST(R_DTC_CreateSeq_Test, TG003_001)
{
    dtc_err_t ret_dtc = DTC_SUCCESS;
    dtc_activation_source_t act_source = DTCE_ICU_SWINT;
    dtc_transfer_data_t *p_transfer_data = NULL;
    dtc_transfer_data_cfg_t *p_data_cfg = NULL;

    uint32_t sequence_transfer_nr = 1;
    uint8_t sequence_no = 0;

    R_DTC_Open();

    ret_dtc = R_DTC_CreateSeq(act_source, p_transfer_data, p_data_cfg, sequence_transfer_nr, sequence_no);

    R_DTC_Close();

#if (DTC_DISABLE == DTC_CFG_USE_SEQUENCE_TRANSFER)
    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_ARG, ret_dtc);
#else
    TEST_ASSERT_NOT_EQUAL(DTC_SUCCESS, ret_dtc);
#endif /* (DTC_DISABLE == DTC_CFG_USE_SEQUENCE_TRANSFER) */
}
/***********************************************************************************************************************
 * End of function TEST_R_DTC_CreateSeq_Test_TG003_001
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: TG003_002
 * Description  : Test API function R_DTC_CreateSeq()
 ***********************************************************************************************************************/
TEST(R_DTC_CreateSeq_Test, TG003_002)
{
    dtc_err_t ret_dtc = DTC_SUCCESS;
    dtc_activation_source_t act_source = DTCE_ICU_SWINT;

    dtc_transfer_data_t transfer_data;
    dtc_transfer_data_t *p_transfer_data = &transfer_data;

    dtc_transfer_data_cfg_t data_cfg;
    data_cfg.transfer_count = 256;          //DTC_MAX_8BITS_COUNT_VAL
    dtc_transfer_data_cfg_t *p_data_cfg = &data_cfg;
    uint32_t sequence_transfer_nr = 1;
    uint8_t sequence_no = 0;

    R_DTC_Close();

    ret_dtc = R_DTC_CreateSeq(act_source, p_transfer_data, p_data_cfg, sequence_transfer_nr, sequence_no);

    #if (DTC_DISABLE == DTC_CFG_USE_SEQUENCE_TRANSFER)
        TEST_ASSERT_EQUAL(DTC_ERR_INVALID_ARG, ret_dtc);
    #else
        TEST_ASSERT_EQUAL(DTC_ERR_NOT_OPEN, ret_dtc);
    #endif /* (DTC_DISABLE == DTC_CFG_USE_SEQUENCE_TRANSFER) */
}
/***********************************************************************************************************************
 * End of function TEST_R_DTC_CreateSeq_Test_TG003_002
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: TG003_003
 * Description  : Test API function R_DTC_CreateSeq()
 ***********************************************************************************************************************/
TEST(R_DTC_CreateSeq_Test, TG003_003)
{
    dtc_err_t ret_dtc = DTC_SUCCESS;
    dtc_activation_source_t act_source = DTCE_ICU_SWINT;

    dtc_transfer_data_t transfer_data;
    dtc_transfer_data_t *p_transfer_data = &transfer_data;

    dtc_transfer_data_cfg_t data_cfg;
    data_cfg.transfer_mode = (3 << 6);
    data_cfg.transfer_count = 65536;

    dtc_transfer_data_cfg_t *p_data_cfg = &data_cfg;
    uint32_t sequence_transfer_nr = 1;
    uint8_t sequence_no = 0;

    R_DTC_Open();

    ret_dtc = R_DTC_CreateSeq(act_source, p_transfer_data, p_data_cfg, sequence_transfer_nr, sequence_no);

    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_ARG, ret_dtc);
}
/***********************************************************************************************************************
 * End of function TEST_R_DTC_CreateSeq_Test_TG003_003
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: TG003_004
 * Description  : Test API function R_DTC_CreateSeq()
 ***********************************************************************************************************************/
TEST(R_DTC_CreateSeq_Test, TG003_004)
{
    dtc_err_t ret_dtc = DTC_SUCCESS;
    dtc_activation_source_t act_source = DTCE_ICU_SWINT;

    dtc_transfer_data_t transfer_data;
    dtc_transfer_data_t *p_transfer_data = &transfer_data;

    dtc_transfer_data_cfg_t data_cfg;
    data_cfg.transfer_mode = DTC_TRANSFER_MODE_NORMAL;
    data_cfg.transfer_count = 65536;

    dtc_transfer_data_cfg_t *p_data_cfg = &data_cfg;
    uint32_t sequence_transfer_nr = 0;
    uint8_t sequence_no = 0;

    R_DTC_Open();

    ret_dtc = R_DTC_CreateSeq(act_source, p_transfer_data, p_data_cfg, sequence_transfer_nr, sequence_no);

#if (DTC_DISABLE == DTC_CFG_USE_SEQUENCE_TRANSFER)
    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_ARG, ret_dtc);
#else
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
#endif /* (DTC_DISABLE == DTC_CFG_USE_SEQUENCE_TRANSFER) */
}
/***********************************************************************************************************************
 * End of function TEST_R_DTC_CreateSeq_Test_TG003_004
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: TG003_005
 * Description  : Test API function R_DTC_CreateSeq()
 ***********************************************************************************************************************/
TEST(R_DTC_CreateSeq_Test, TG003_005)
{
    dtc_err_t ret_dtc = DTC_SUCCESS;
    dtc_activation_source_t act_source = DTCE_ICU_SWINT;

    dtc_transfer_data_t transfer_data;
    dtc_transfer_data_t *p_transfer_data = &transfer_data;
    dtc_transfer_data_cfg_t data_cfg;

    data_cfg.writeback_disable = DTC_WRITEBACK_DISABLE;
    data_cfg.source_addr = (uint32_t)&test_src_buff32[0];
    data_cfg.src_addr_mode = DTC_SRC_ADDR_INCR;
    data_cfg.data_size = DTC_DATA_SIZE_LWORD;
    data_cfg.transfer_mode = DTC_TRANSFER_MODE_NORMAL;
    data_cfg.sequence_end = DTC_SEQUENCE_TRANSFER_END;
    data_cfg.refer_index_table_enable = DTC_REFER_INDEX_TABLE_DISABLE;
    data_cfg.dest_addr = (uint32_t)&test_dest_buff[0];
    data_cfg.dest_addr_mode = DTC_DES_ADDR_FIXED;
    data_cfg.repeat_block_side = DTC_REPEAT_BLOCK_SOURCE;
    data_cfg.response_interrupt = DTC_INTERRUPT_AFTER_ALL_COMPLETE;
    data_cfg.chain_transfer_enable = DTC_CHAIN_TRANSFER_DISABLE;
    data_cfg.chain_transfer_mode = DTC_CHAIN_TRANSFER_NORMAL;
    data_cfg.transfer_count = 65536;
    data_cfg.disp_add_enable = DTC_SRC_ADDR_DISP_ADD_DISABLE;

    dtc_transfer_data_cfg_t *p_data_cfg = &data_cfg;
    uint32_t sequence_transfer_nr = 1;
    uint8_t sequence_no = 0;

    R_DTC_Open();

    ret_dtc = R_DTC_CreateSeq(act_source, p_transfer_data, p_data_cfg, sequence_transfer_nr, sequence_no);

#if (DTC_DISABLE == DTC_CFG_USE_SEQUENCE_TRANSFER)
    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_ARG, ret_dtc);
#else
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
#endif /* (DTC_DISABLE == DTC_CFG_USE_SEQUENCE_TRANSFER) */

    R_DTC_Close();
}
/***********************************************************************************************************************
 * End of function TEST_R_DTC_CreateSeq_Test_TG003_005
 ***********************************************************************************************************************/


#else // RX66T

/***********************************************************************************************************************
 * Function Name: TG003_001
 * Description  : Test API function R_DTC_CreateSeq()
 ***********************************************************************************************************************/
TEST(R_DTC_CreateSeq_Test, TG003_001)
{
    dtc_err_t ret_dtc = DTC_SUCCESS;

    ret_dtc = R_DTC_CreateSeq(DTCE_ICU_SWINT, NULL, NULL, 0, 0);

    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_ARG, ret_dtc);

}
/***********************************************************************************************************************
 * End of function TEST_R_DTC_CreateSeq_Test_TG003_001
 ***********************************************************************************************************************/

#endif /* (DTC_IP_VER_DTCb <= DTC_IP) */


/***********************************************************************************************************************
* Function Name: TEST_R_DTC_Close_Test_SETUP
* Description  :
***********************************************************************************************************************/
TEST_SETUP(R_DTC_Close_Test)
{
    
}
/***********************************************************************************************************************
End of function TEST_R_DTC_Close_Test_SETUP
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TEST_R_DTC_Close_Test_TEAR_DOWN
* Description  :
***********************************************************************************************************************/
TEST_TEAR_DOWN(R_DTC_Close_Test)
{
    R_DTC_Close();
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
}
/***********************************************************************************************************************
End of function TEST_R_DTC_Close_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_001
* Description  : Test API function R_DTC_Close()
***********************************************************************************************************************/
TEST(R_DTC_Close_Test, TG004_001)
{
    dtc_err_t ret_dtc = DTC_SUCCESS;

    R_BSP_HardwareUnlock((mcu_lock_t)(BSP_LOCK_DTC));

    ret_dtc = R_DTC_Close();

    TEST_ASSERT_EQUAL(NULL, g_dtc_table_work[1]);
    TEST_ASSERT_EQUAL(0, DTC.DTCST.BIT.DTCST);
    TEST_ASSERT_EQUAL(DTC_SUCCESS, R_DTC_Open());
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);

}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Close_Test_TG004_001
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_002
* Description  : Test API function R_DTC_Close()
***********************************************************************************************************************/
TEST(R_DTC_Close_Test, TG004_002)
{
    dtc_err_t ret_dtc = DTC_SUCCESS;
    var_T004_002 = 1;

    R_BSP_HardwareLock(BSP_LOCK_DTC);

    ret_dtc = R_DTC_Close();

    TEST_ASSERT_EQUAL(NULL, g_dtc_table_work[1]);
    TEST_ASSERT_EQUAL(0, DTC.DTCST.BIT.DTCST);
    TEST_ASSERT_EQUAL(DTC_SUCCESS, R_DTC_Open());
    TEST_ASSERT_EQUAL(DTC_SUCCESS_DMAC_BUSY, ret_dtc);

    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
    var_T004_002 = 0;

}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Close_Test_TG004_002
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: TEST_R_DTC_Control_Test_SETUP
* Description  :
***********************************************************************************************************************/
TEST_SETUP(R_DTC_Control_Test)
{
    
}
/***********************************************************************************************************************
End of function TEST_R_DTC_Control_Test_SETUP
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TEST_R_DTC_Control_Test_TEAR_DOWN
* Description  :
***********************************************************************************************************************/
TEST_TEAR_DOWN(R_DTC_Control_Test)
{
    R_DTC_Close();
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
}
/***********************************************************************************************************************
End of function TEST_R_DTC_Control_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_001
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_001)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_STATUS_GET;
    p_stat = NULL;
    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];
    args.p_transfer_data       = &transfer_data[0];

    p_args = &args;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(DTC_ERR_NULL_PTR, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_001
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_002
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_002)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_ACT_SRC_ENABLE;
    p_stat = &stat;
    p_args = NULL;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(DTC_ERR_NULL_PTR, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_002
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_003
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_003)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_ACT_SRC_DISABLE;
    p_stat = &stat;
    p_args = NULL;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(DTC_ERR_NULL_PTR, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_003
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_004
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_004)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_CHAIN_TRANSFER_ABORT;
    p_stat = &stat;
    p_args = NULL;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(DTC_ERR_NULL_PTR, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_004
***********************************************************************************************************************/


#if (DTC_IP_VER_DTCb <= DTC_IP) // RX65N

/***********************************************************************************************************************
* Function Name: TG005_005
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_005)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_SEQUENCE_TRANSFER_ENABLE;
    p_stat = &stat;
    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];
    args.p_transfer_data       = &transfer_data[0];

    p_args = &args;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_005
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_006
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_006)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_SEQUENCE_TRANSFER_DISABLE;
    p_stat = &stat;
    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];
    args.p_transfer_data       = &transfer_data[0];

    p_args = &args;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_006
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_007
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_007)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_SEQUENCE_TRANSFER_ABORT;
    p_stat = &stat;
    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];
    args.p_transfer_data       = &transfer_data[0];

    p_args = &args;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_007
***********************************************************************************************************************/

#else // RX66T

/***********************************************************************************************************************
* Function Name: TG005_005
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_005)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_SEQUENCE_TRANSFER_ENABLE;
    p_stat = &stat;
    p_args = NULL;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(DTC_ERR_NULL_PTR, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_005
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: TG005_006
 * Description  : Test API function R_DTC_Control()
 ***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_006)
{
    dtc_err_t ret_dtc = DTC_SUCCESS;
    dtc_command_t command;
    dtc_stat_t *p_stat;
    dtc_cmd_arg_t *p_args;
    dtc_stat_t stat;
    dtc_cmd_arg_t args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_SEQUENCE_TRANSFER_DISABLE;
    p_stat = &stat;
    p_args = NULL;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_COMMAND, ret_dtc);
}
/***********************************************************************************************************************
 * End of function TEST_R_DTC_Control_Test_TG005_006
 ***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_007
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_007)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_SEQUENCE_TRANSFER_ABORT;
    p_stat = &stat;
    p_args = NULL;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_COMMAND, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_007
***********************************************************************************************************************/

#endif /* (DTC_IP_VER_DTCb <= DTC_IP) */

/***********************************************************************************************************************
* Function Name: TG005_008
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_008)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_CHANGING_DATA_FORCIBLY_SET;
    p_stat = &stat;
    p_args = NULL;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_COMMAND, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_008
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_009
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_009)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_CHANGING_DATA_FORCIBLY_SET;
    p_stat = &stat;
    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];

    p_args = &args;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_COMMAND, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_009
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_010
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_010)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_CHANGING_DATA_FORCIBLY_SET;
    p_stat = &stat;
    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];
    args.p_transfer_data       = &transfer_data[0];

    p_args = &args;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_010
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_011
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_011)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_CHANGING_DATA_FORCIBLY_SET;
    p_stat = &stat;
    data_cfg[0].transfer_mode  = (3<<6);
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];
    args.p_transfer_data       = &transfer_data[0];

    p_args = &args;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_COMMAND, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_011
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_012
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_012)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Close();

    command = DTC_CMD_DTC_START;

    p_stat = &stat;
    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];
    args.p_transfer_data       = &transfer_data[0];

    p_args = &args;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(DTC_ERR_NOT_OPEN, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_012
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_013
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_013)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = 0xFF;
    p_stat = &stat;
    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];
    args.p_transfer_data       = &transfer_data[0];

    p_args = &args;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_COMMAND, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_013
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_014
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_014)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_DTC_START;

    p_stat = &stat;
    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];
    args.p_transfer_data       = &transfer_data[0];

    p_args = &args;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(1, DTC.DTCST.BIT.DTCST);
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_014
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_015
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_015)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_DTC_STOP;
    p_stat = &stat;
    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];
    args.p_transfer_data       = &transfer_data[0];

    p_args = &args;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(0, DTC.DTCST.BIT.DTCST);
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_015
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_016
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_016)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_DATA_READ_SKIP_ENABLE;
    p_stat = &stat;
    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];
    args.p_transfer_data       = &transfer_data[0];

    p_args = &args;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(1, DTC.DTCCR.BIT.RRS);
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_016
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_017
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_017)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_DATA_READ_SKIP_DISABLE;
    p_stat = &stat;
    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];
    args.p_transfer_data       = &transfer_data[0];

    p_args = &args;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(0, DTC.DTCCR.BIT.RRS);
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_017
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_018
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_018)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_ACT_SRC_ENABLE;
    p_stat = &stat;
    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];
    args.p_transfer_data       = &transfer_data[0];

    p_args = &args;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(1, ICU.DTCER[p_args->act_src].BIT.DTCE);
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_018
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_019
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_019)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_ACT_SRC_DISABLE;
    p_stat = &stat;
    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];
    args.p_transfer_data       = &transfer_data[0];

    p_args = &args;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(0, ICU.DTCER[p_args->act_src].BIT.DTCE);
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_019
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_020
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_020)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    DTC.DTCSTS.WORD &= ~(0x8000); //DTC_ACT_BIT_MASK

    command = DTC_CMD_STATUS_GET;
    p_stat = &stat;
    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];
    args.p_transfer_data       = &transfer_data[0];

    p_args = &args;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(false, p_stat->in_progress);
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_020
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_021
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_021)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    DTC.DTCSTS.WORD |= 0x8000; //DTC_ACT_BIT_MASK

    command = DTC_CMD_STATUS_GET;
    p_stat = &stat;
    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];
    args.p_transfer_data       = &transfer_data[0];

    p_args = &args;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(true, p_stat->in_progress);
    TEST_ASSERT_EQUAL((uint8_t)(DTC.DTCSTS.WORD & 0x00FF), p_stat->vect_nr); //DTC_VECT_NR_MASK
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_021
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_022
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_022)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_CHAIN_TRANSFER_ABORT;
    p_stat = &stat;
    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];
    args.p_transfer_data       = &transfer_data[0];

    p_args = &args;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_022
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_023
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_023)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_CHANGING_DATA_FORCIBLY_SET;
    p_stat = &stat;
    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];

    p_args = &args;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_COMMAND, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_023
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_024
* Description  : Test API function R_DTC_Control()
***********************************************************************************************************************/
TEST(R_DTC_Control_Test, TG005_024)
{
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 0;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_CHANGING_DATA_FORCIBLY_SET;
    p_stat = &stat;
    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];
    args.p_transfer_data       = &transfer_data[0];

    p_args = &args;
    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    dtc_transfer_data_t *ptrandata = &transfer_data[0];
    ptrandata += p_args->chain_transfer_nr + 1;
    TEST_ASSERT_EQUAL(ptrandata, p_args->p_transfer_data);

    dtc_transfer_data_cfg_t *pdatcfg = &data_cfg[0];
    pdatcfg += p_args->chain_transfer_nr + 1;
    TEST_ASSERT_EQUAL(pdatcfg, p_args->p_data_cfg);

    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_Control_Test_TG005_024
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: TEST_R_DTC_GetVersion_Test_SETUP
* Description  :
***********************************************************************************************************************/
TEST_SETUP(R_DTC_GetVersion_Test)
{
    
}
/***********************************************************************************************************************
End of function TEST_R_DTC_GetVersion_Test_SETUP
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TEST_R_DTC_GetVersion_Test_TEAR_DOWN
* Description  :
***********************************************************************************************************************/
TEST_TEAR_DOWN(R_DTC_GetVersion_Test)
{
    R_DTC_Close();
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
}
/***********************************************************************************************************************
End of function TEST_R_DTC_GetVersion_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG006_001
* Description  : Test API function R_DTC_GetVersion()
***********************************************************************************************************************/
TEST(R_DTC_GetVersion_Test, TG006_001)
{
    TEST_ASSERT_EQUAL(0x0003001e, R_DTC_GetVersion());
}
/***********************************************************************************************************************
* End of function TEST_R_DTC_GetVersion_Test_TG006_001
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: TEST_r_dtc_set_transfer_data_Test_SETUP
* Description  :
***********************************************************************************************************************/
TEST_SETUP(r_dtc_set_transfer_data_Test)
{
    
}
/***********************************************************************************************************************
End of function TEST_r_dtc_set_transfer_data_Test_SETUP
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TEST_r_dtc_set_transfer_data_Test_TEAR_DOWN
* Description  :
***********************************************************************************************************************/
TEST_TEAR_DOWN(r_dtc_set_transfer_data_Test)
{
    R_DTC_Close();
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
}
/***********************************************************************************************************************
End of function TEST_r_dtc_set_transfer_data_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_001
* Description  : Test API function r_dtc_set_transfer_data()
***********************************************************************************************************************/
TEST(r_dtc_set_transfer_data_Test, TG007_001)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_DISABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    p_data_cfg->transfer_count = 65536; // DTC_MAX_16BITS_COUNT_VAL;
    t_mra.BYTE = (uint8_t)(p_data_cfg->src_addr_mode | p_data_cfg->data_size | p_data_cfg->transfer_mode);
    t_mrb.BYTE = (uint8_t)(p_data_cfg->dest_addr_mode | p_data_cfg->repeat_block_side | p_data_cfg->response_interrupt |
                           p_data_cfg->chain_transfer_enable | p_data_cfg->chain_transfer_mode);


    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(0x0000, td_ptr->FOURTH_LWORD.REG.CRA.WORD);
    /* settings for fist long word: MRA & MRB */
    TEST_ASSERT_EQUAL(t_mra.BYTE, td_ptr->FIRST_LWORD.REG.MRA.BYTE); /* 1 byte MRA */
    TEST_ASSERT_EQUAL(t_mrb.BYTE, td_ptr->FIRST_LWORD.REG.MRB.BYTE); /* 1 byte MRB */
    /* settings for second long word: SAR */
    TEST_ASSERT_EQUAL(p_data_cfg->source_addr, td_ptr->SECOND_LWORD.SAR); /* 4 byte SAR */
    /* settings for third long word: DAR */
    TEST_ASSERT_EQUAL(p_data_cfg->dest_addr, td_ptr->THIRD_LWORD.DAR); /* 4 byte DAR */
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_set_transfer_data_Test_TG007_001
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_002
* Description  : Test API function r_dtc_set_transfer_data()
***********************************************************************************************************************/
TEST(r_dtc_set_transfer_data_Test, TG007_002)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_DISABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    p_data_cfg->transfer_count = 1;
    t_mra.BYTE = (uint8_t)(p_data_cfg->src_addr_mode | p_data_cfg->data_size | p_data_cfg->transfer_mode);
    t_mrb.BYTE = (uint8_t)(p_data_cfg->dest_addr_mode | p_data_cfg->repeat_block_side | p_data_cfg->response_interrupt |
                           p_data_cfg->chain_transfer_enable | p_data_cfg->chain_transfer_mode);


    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL((uint16_t)p_data_cfg->transfer_count, td_ptr->FOURTH_LWORD.REG.CRA.WORD);
    /* settings for fist long word: MRA & MRB */
    TEST_ASSERT_EQUAL(t_mra.BYTE, td_ptr->FIRST_LWORD.REG.MRA.BYTE); /* 1 byte MRA */
    TEST_ASSERT_EQUAL(t_mrb.BYTE, td_ptr->FIRST_LWORD.REG.MRB.BYTE); /* 1 byte MRB */
    /* settings for second long word: SAR */
    TEST_ASSERT_EQUAL(p_data_cfg->source_addr, td_ptr->SECOND_LWORD.SAR); /* 4 byte SAR */
    /* settings for third long word: DAR */
    TEST_ASSERT_EQUAL(p_data_cfg->dest_addr, td_ptr->THIRD_LWORD.DAR); /* 4 byte DAR */
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_set_transfer_data_Test_TG007_002
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_003
* Description  : Test API function r_dtc_set_transfer_data()
***********************************************************************************************************************/
TEST(r_dtc_set_transfer_data_Test, TG007_003)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_DISABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    p_data_cfg->transfer_mode = DTC_TRANSFER_MODE_REPEAT;
    p_data_cfg->transfer_count = 1;
    t_mra.BYTE = (uint8_t)(p_data_cfg->src_addr_mode | p_data_cfg->data_size | p_data_cfg->transfer_mode);
    t_mrb.BYTE = (uint8_t)(p_data_cfg->dest_addr_mode | p_data_cfg->repeat_block_side | p_data_cfg->response_interrupt |
                           p_data_cfg->chain_transfer_enable | p_data_cfg->chain_transfer_mode);


    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL((uint8_t)p_data_cfg->transfer_count, td_ptr->FOURTH_LWORD.REG.CRA.BYTE.CRA_H);
    TEST_ASSERT_EQUAL((uint8_t)p_data_cfg->transfer_count, td_ptr->FOURTH_LWORD.REG.CRA.BYTE.CRA_L);
    /* settings for fist long word: MRA & MRB */
    TEST_ASSERT_EQUAL(t_mra.BYTE, td_ptr->FIRST_LWORD.REG.MRA.BYTE); /* 1 byte MRA */
    TEST_ASSERT_EQUAL(t_mrb.BYTE, td_ptr->FIRST_LWORD.REG.MRB.BYTE); /* 1 byte MRB */
    /* settings for second long word: SAR */
    TEST_ASSERT_EQUAL(p_data_cfg->source_addr, td_ptr->SECOND_LWORD.SAR); /* 4 byte SAR */
    /* settings for third long word: DAR */
    TEST_ASSERT_EQUAL(p_data_cfg->dest_addr, td_ptr->THIRD_LWORD.DAR); /* 4 byte DAR */
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_set_transfer_data_Test_TG007_003
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_004
* Description  : Test API function r_dtc_set_transfer_data()
***********************************************************************************************************************/
TEST(r_dtc_set_transfer_data_Test, TG007_004)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_DISABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    p_data_cfg->transfer_mode = DTC_TRANSFER_MODE_REPEAT;
    p_data_cfg->transfer_count = 256; // DTC_MAX_8BITS_COUNT_VAL
    t_mra.BYTE = (uint8_t)(p_data_cfg->src_addr_mode | p_data_cfg->data_size | p_data_cfg->transfer_mode);
    t_mrb.BYTE = (uint8_t)(p_data_cfg->dest_addr_mode | p_data_cfg->repeat_block_side | p_data_cfg->response_interrupt |
                           p_data_cfg->chain_transfer_enable | p_data_cfg->chain_transfer_mode);


    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(0x00, td_ptr->FOURTH_LWORD.REG.CRA.BYTE.CRA_H);
    TEST_ASSERT_EQUAL(0x00, td_ptr->FOURTH_LWORD.REG.CRA.BYTE.CRA_L);
    /* settings for fist long word: MRA & MRB */
    TEST_ASSERT_EQUAL(t_mra.BYTE, td_ptr->FIRST_LWORD.REG.MRA.BYTE); /* 1 byte MRA */
    TEST_ASSERT_EQUAL(t_mrb.BYTE, td_ptr->FIRST_LWORD.REG.MRB.BYTE); /* 1 byte MRB */
    /* settings for second long word: SAR */
    TEST_ASSERT_EQUAL(p_data_cfg->source_addr, td_ptr->SECOND_LWORD.SAR); /* 4 byte SAR */
    /* settings for third long word: DAR */
    TEST_ASSERT_EQUAL(p_data_cfg->dest_addr, td_ptr->THIRD_LWORD.DAR); /* 4 byte DAR */
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_set_transfer_data_Test_TG007_004
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_005
* Description  : Test API function r_dtc_set_transfer_data()
***********************************************************************************************************************/
TEST(r_dtc_set_transfer_data_Test, TG007_005)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_DISABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    p_data_cfg->transfer_mode = DTC_TRANSFER_MODE_REPEAT;
    p_data_cfg->transfer_count = 257;
    t_mra.BYTE = (uint8_t)(p_data_cfg->src_addr_mode | p_data_cfg->data_size | p_data_cfg->transfer_mode);
    t_mrb.BYTE = (uint8_t)(p_data_cfg->dest_addr_mode | p_data_cfg->repeat_block_side | p_data_cfg->response_interrupt |
                           p_data_cfg->chain_transfer_enable | p_data_cfg->chain_transfer_mode);


    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    /* settings for fist long word: MRA & MRB */
    TEST_ASSERT_EQUAL(t_mra.BYTE, td_ptr->FIRST_LWORD.REG.MRA.BYTE); /* 1 byte MRA */
    TEST_ASSERT_EQUAL(t_mrb.BYTE, td_ptr->FIRST_LWORD.REG.MRB.BYTE); /* 1 byte MRB */
    /* settings for second long word: SAR */
    TEST_ASSERT_EQUAL(p_data_cfg->source_addr, td_ptr->SECOND_LWORD.SAR); /* 4 byte SAR */
    /* settings for third long word: DAR */
    TEST_ASSERT_EQUAL(p_data_cfg->dest_addr, td_ptr->THIRD_LWORD.DAR); /* 4 byte DAR */
    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_ARG, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_set_transfer_data_Test_TG007_005
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_006
* Description  : Test API function r_dtc_set_transfer_data()
***********************************************************************************************************************/
TEST(r_dtc_set_transfer_data_Test, TG007_006)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_DISABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    p_data_cfg->transfer_mode = DTC_TRANSFER_MODE_BLOCK;
    p_data_cfg->transfer_count = 65536; // DTC_MAX_16BITS_COUNT_VAL;
    t_mra.BYTE = (uint8_t)(p_data_cfg->src_addr_mode | p_data_cfg->data_size | p_data_cfg->transfer_mode);
    t_mrb.BYTE = (uint8_t)(p_data_cfg->dest_addr_mode | p_data_cfg->repeat_block_side | p_data_cfg->response_interrupt |
                           p_data_cfg->chain_transfer_enable | p_data_cfg->chain_transfer_mode);


    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(0x0000, td_ptr->FOURTH_LWORD.REG.CRB.WORD);
    /* settings for fist long word: MRA & MRB */
    TEST_ASSERT_EQUAL(t_mra.BYTE, td_ptr->FIRST_LWORD.REG.MRA.BYTE); /* 1 byte MRA */
    TEST_ASSERT_EQUAL(t_mrb.BYTE, td_ptr->FIRST_LWORD.REG.MRB.BYTE); /* 1 byte MRB */
    /* settings for second long word: SAR */
    TEST_ASSERT_EQUAL(p_data_cfg->source_addr, td_ptr->SECOND_LWORD.SAR); /* 4 byte SAR */
    /* settings for third long word: DAR */
    TEST_ASSERT_EQUAL(p_data_cfg->dest_addr, td_ptr->THIRD_LWORD.DAR); /* 4 byte DAR */
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_set_transfer_data_Test_TG007_006
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_007
* Description  : Test API function r_dtc_set_transfer_data()
***********************************************************************************************************************/
TEST(r_dtc_set_transfer_data_Test, TG007_007)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_DISABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    p_data_cfg->transfer_mode = DTC_TRANSFER_MODE_BLOCK;
    p_data_cfg->transfer_count = 1;
    t_mra.BYTE = (uint8_t)(p_data_cfg->src_addr_mode | p_data_cfg->data_size | p_data_cfg->transfer_mode);
    t_mrb.BYTE = (uint8_t)(p_data_cfg->dest_addr_mode | p_data_cfg->repeat_block_side | p_data_cfg->response_interrupt |
                           p_data_cfg->chain_transfer_enable | p_data_cfg->chain_transfer_mode);


    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL((uint16_t)p_data_cfg->transfer_count, td_ptr->FOURTH_LWORD.REG.CRB.WORD);
    /* settings for fist long word: MRA & MRB */
    TEST_ASSERT_EQUAL(t_mra.BYTE, td_ptr->FIRST_LWORD.REG.MRA.BYTE); /* 1 byte MRA */
    TEST_ASSERT_EQUAL(t_mrb.BYTE, td_ptr->FIRST_LWORD.REG.MRB.BYTE); /* 1 byte MRB */
    /* settings for second long word: SAR */
    TEST_ASSERT_EQUAL(p_data_cfg->source_addr, td_ptr->SECOND_LWORD.SAR); /* 4 byte SAR */
    /* settings for third long word: DAR */
    TEST_ASSERT_EQUAL(p_data_cfg->dest_addr, td_ptr->THIRD_LWORD.DAR); /* 4 byte DAR */
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_set_transfer_data_Test_TG007_007
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_008
* Description  : Test API function r_dtc_set_transfer_data()
***********************************************************************************************************************/
TEST(r_dtc_set_transfer_data_Test, TG007_008)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_DISABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    p_data_cfg->transfer_mode = DTC_TRANSFER_MODE_BLOCK;
    p_data_cfg->block_size = 1;
    t_mra.BYTE = (uint8_t)(p_data_cfg->src_addr_mode | p_data_cfg->data_size | p_data_cfg->transfer_mode);
    t_mrb.BYTE = (uint8_t)(p_data_cfg->dest_addr_mode | p_data_cfg->repeat_block_side | p_data_cfg->response_interrupt |
                           p_data_cfg->chain_transfer_enable | p_data_cfg->chain_transfer_mode);


    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL((uint8_t)p_data_cfg->block_size, td_ptr->FOURTH_LWORD.REG.CRA.BYTE.CRA_H);
    TEST_ASSERT_EQUAL((uint8_t)p_data_cfg->block_size, td_ptr->FOURTH_LWORD.REG.CRA.BYTE.CRA_L);
    /* settings for fist long word: MRA & MRB */
    TEST_ASSERT_EQUAL(t_mra.BYTE, td_ptr->FIRST_LWORD.REG.MRA.BYTE); /* 1 byte MRA */
    TEST_ASSERT_EQUAL(t_mrb.BYTE, td_ptr->FIRST_LWORD.REG.MRB.BYTE); /* 1 byte MRB */
    /* settings for second long word: SAR */
    TEST_ASSERT_EQUAL(p_data_cfg->source_addr, td_ptr->SECOND_LWORD.SAR); /* 4 byte SAR */
    /* settings for third long word: DAR */
    TEST_ASSERT_EQUAL(p_data_cfg->dest_addr, td_ptr->THIRD_LWORD.DAR); /* 4 byte DAR */
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_set_transfer_data_Test_TG007_008
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_009
* Description  : Test API function r_dtc_set_transfer_data()
***********************************************************************************************************************/
TEST(r_dtc_set_transfer_data_Test, TG007_009)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_DISABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    p_data_cfg->transfer_mode = DTC_TRANSFER_MODE_BLOCK;
    p_data_cfg->block_size = 256;
    t_mra.BYTE = (uint8_t)(p_data_cfg->src_addr_mode | p_data_cfg->data_size | p_data_cfg->transfer_mode);
    t_mrb.BYTE = (uint8_t)(p_data_cfg->dest_addr_mode | p_data_cfg->repeat_block_side | p_data_cfg->response_interrupt |
                           p_data_cfg->chain_transfer_enable | p_data_cfg->chain_transfer_mode);


    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(0x00, td_ptr->FOURTH_LWORD.REG.CRA.BYTE.CRA_H);
    TEST_ASSERT_EQUAL(0x00, td_ptr->FOURTH_LWORD.REG.CRA.BYTE.CRA_L);
    /* settings for fist long word: MRA & MRB */
    TEST_ASSERT_EQUAL(t_mra.BYTE, td_ptr->FIRST_LWORD.REG.MRA.BYTE); /* 1 byte MRA */
    TEST_ASSERT_EQUAL(t_mrb.BYTE, td_ptr->FIRST_LWORD.REG.MRB.BYTE); /* 1 byte MRB */
    /* settings for second long word: SAR */
    TEST_ASSERT_EQUAL(p_data_cfg->source_addr, td_ptr->SECOND_LWORD.SAR); /* 4 byte SAR */
    /* settings for third long word: DAR */
    TEST_ASSERT_EQUAL(p_data_cfg->dest_addr, td_ptr->THIRD_LWORD.DAR); /* 4 byte DAR */
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_set_transfer_data_Test_TG007_009
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_010
* Description  : Test API function r_dtc_set_transfer_data()
***********************************************************************************************************************/
TEST(r_dtc_set_transfer_data_Test, TG007_010)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_DISABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    p_data_cfg->transfer_mode = DTC_TRANSFER_MODE_BLOCK;
    p_data_cfg->block_size = 257;
    t_mra.BYTE = (uint8_t)(p_data_cfg->src_addr_mode | p_data_cfg->data_size | p_data_cfg->transfer_mode);
    t_mrb.BYTE = (uint8_t)(p_data_cfg->dest_addr_mode | p_data_cfg->repeat_block_side | p_data_cfg->response_interrupt |
                           p_data_cfg->chain_transfer_enable | p_data_cfg->chain_transfer_mode);


    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    /* settings for fist long word: MRA & MRB */
    TEST_ASSERT_EQUAL(t_mra.BYTE, td_ptr->FIRST_LWORD.REG.MRA.BYTE); /* 1 byte MRA */
    TEST_ASSERT_EQUAL(t_mrb.BYTE, td_ptr->FIRST_LWORD.REG.MRB.BYTE); /* 1 byte MRB */
    /* settings for second long word: SAR */
    TEST_ASSERT_EQUAL(p_data_cfg->source_addr, td_ptr->SECOND_LWORD.SAR); /* 4 byte SAR */
    /* settings for third long word: DAR */
    TEST_ASSERT_EQUAL(p_data_cfg->dest_addr, td_ptr->THIRD_LWORD.DAR); /* 4 byte DAR */
    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_ARG, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_set_transfer_data_Test_TG007_010
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_011
* Description  : Test API function r_dtc_set_transfer_data()
***********************************************************************************************************************/
TEST(r_dtc_set_transfer_data_Test, TG007_011)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_DISABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    p_data_cfg->transfer_mode = (3<<6);

    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_ARG, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_set_transfer_data_Test_TG007_011
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_012
* Description  : Test API function r_dtc_set_transfer_data()
***********************************************************************************************************************/
TEST(r_dtc_set_transfer_data_Test, TG007_012)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_ENABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    p_data_cfg->transfer_count = 65536; // DTC_MAX_16BITS_COUNT_VAL;
    t_mra.BYTE = (uint8_t)(p_data_cfg->src_addr_mode | p_data_cfg->data_size | p_data_cfg->transfer_mode);
    t_mrb.BYTE = (uint8_t)(p_data_cfg->dest_addr_mode | p_data_cfg->repeat_block_side | p_data_cfg->response_interrupt |
                           p_data_cfg->chain_transfer_enable | p_data_cfg->chain_transfer_mode);


    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(0x0000, td_ptr->THIRD_LWORD.REG.CRA.WORD);
    /* settings for fist long word: MRA & SAR */
    TEST_ASSERT_EQUAL(t_mra.BYTE, td_ptr->FIRST_LWORD.REG.MRA.BYTE); /* 1 byte MRA */
    TEST_ASSERT_EQUAL((p_data_cfg->source_addr & 0x00FFFFFF), (td_ptr->FIRST_LWORD.LWORD & 0x00FFFFFF));
    /* settings for second long word: MRB & DAR */
    TEST_ASSERT_EQUAL(t_mrb.BYTE, td_ptr->SECOND_LWORD.REG.MRB.BYTE); /* 1 byte MRB */
    TEST_ASSERT_EQUAL((p_data_cfg->dest_addr & 0x00FFFFFF), (td_ptr->SECOND_LWORD.LWORD & 0x00FFFFFF)); /* 3 byte DAR */
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_set_transfer_data_Test_TG007_012
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_013
* Description  : Test API function r_dtc_set_transfer_data()
***********************************************************************************************************************/
TEST(r_dtc_set_transfer_data_Test, TG007_013)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_ENABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    p_data_cfg->transfer_count = 1;
    t_mra.BYTE = (uint8_t)(p_data_cfg->src_addr_mode | p_data_cfg->data_size | p_data_cfg->transfer_mode);
    t_mrb.BYTE = (uint8_t)(p_data_cfg->dest_addr_mode | p_data_cfg->repeat_block_side | p_data_cfg->response_interrupt |
                           p_data_cfg->chain_transfer_enable | p_data_cfg->chain_transfer_mode);


    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL((uint16_t)p_data_cfg->transfer_count, td_ptr->THIRD_LWORD.REG.CRA.WORD);
    /* settings for fist long word: MRA & SAR */
    TEST_ASSERT_EQUAL(t_mra.BYTE, td_ptr->FIRST_LWORD.REG.MRA.BYTE); /* 1 byte MRA */
    TEST_ASSERT_EQUAL((p_data_cfg->source_addr & 0x00FFFFFF), (td_ptr->FIRST_LWORD.LWORD & 0x00FFFFFF));
    /* settings for second long word: MRB & DAR */
    TEST_ASSERT_EQUAL(t_mrb.BYTE, td_ptr->SECOND_LWORD.REG.MRB.BYTE); /* 1 byte MRB */
    TEST_ASSERT_EQUAL((p_data_cfg->dest_addr & 0x00FFFFFF), (td_ptr->SECOND_LWORD.LWORD & 0x00FFFFFF)); /* 3 byte DAR */
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_set_transfer_data_Test_TG007_013
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_014
* Description  : Test API function r_dtc_set_transfer_data()
***********************************************************************************************************************/
TEST(r_dtc_set_transfer_data_Test, TG007_014)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_ENABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    p_data_cfg->transfer_mode = DTC_TRANSFER_MODE_REPEAT;
    p_data_cfg->transfer_count = 1;
    t_mra.BYTE = (uint8_t)(p_data_cfg->src_addr_mode | p_data_cfg->data_size | p_data_cfg->transfer_mode);
    t_mrb.BYTE = (uint8_t)(p_data_cfg->dest_addr_mode | p_data_cfg->repeat_block_side | p_data_cfg->response_interrupt |
                           p_data_cfg->chain_transfer_enable | p_data_cfg->chain_transfer_mode);


    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL((uint8_t)p_data_cfg->transfer_count, td_ptr->THIRD_LWORD.REG.CRA.BYTE.CRA_H);
    TEST_ASSERT_EQUAL((uint8_t)p_data_cfg->transfer_count, td_ptr->THIRD_LWORD.REG.CRA.BYTE.CRA_L);
    /* settings for fist long word: MRA & SAR */
    TEST_ASSERT_EQUAL(t_mra.BYTE, td_ptr->FIRST_LWORD.REG.MRA.BYTE); /* 1 byte MRA */
    TEST_ASSERT_EQUAL((p_data_cfg->source_addr & 0x00FFFFFF), (td_ptr->FIRST_LWORD.LWORD & 0x00FFFFFF));
    /* settings for second long word: MRB & DAR */
    TEST_ASSERT_EQUAL(t_mrb.BYTE, td_ptr->SECOND_LWORD.REG.MRB.BYTE); /* 1 byte MRB */
    TEST_ASSERT_EQUAL((p_data_cfg->dest_addr & 0x00FFFFFF), (td_ptr->SECOND_LWORD.LWORD & 0x00FFFFFF)); /* 3 byte DAR */
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_set_transfer_data_Test_TG007_014
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_015
* Description  : Test API function r_dtc_set_transfer_data()
***********************************************************************************************************************/
TEST(r_dtc_set_transfer_data_Test, TG007_015)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_ENABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    p_data_cfg->transfer_mode = DTC_TRANSFER_MODE_REPEAT;
    p_data_cfg->transfer_count = 256; // DTC_MAX_8BITS_COUNT_VAL
    t_mra.BYTE = (uint8_t)(p_data_cfg->src_addr_mode | p_data_cfg->data_size | p_data_cfg->transfer_mode);
    t_mrb.BYTE = (uint8_t)(p_data_cfg->dest_addr_mode | p_data_cfg->repeat_block_side | p_data_cfg->response_interrupt |
                           p_data_cfg->chain_transfer_enable | p_data_cfg->chain_transfer_mode);


    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(0x00, td_ptr->THIRD_LWORD.REG.CRA.BYTE.CRA_H);
    TEST_ASSERT_EQUAL(0x00, td_ptr->THIRD_LWORD.REG.CRA.BYTE.CRA_L);
    /* settings for fist long word: MRA & SAR */
    TEST_ASSERT_EQUAL(t_mra.BYTE, td_ptr->FIRST_LWORD.REG.MRA.BYTE); /* 1 byte MRA */
    TEST_ASSERT_EQUAL((p_data_cfg->source_addr & 0x00FFFFFF), (td_ptr->FIRST_LWORD.LWORD & 0x00FFFFFF));
    /* settings for second long word: MRB & DAR */
    TEST_ASSERT_EQUAL(t_mrb.BYTE, td_ptr->SECOND_LWORD.REG.MRB.BYTE); /* 1 byte MRB */
    TEST_ASSERT_EQUAL((p_data_cfg->dest_addr & 0x00FFFFFF), (td_ptr->SECOND_LWORD.LWORD & 0x00FFFFFF)); /* 3 byte DAR */
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_set_transfer_data_Test_TG007_015
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_016
* Description  : Test API function r_dtc_set_transfer_data()
***********************************************************************************************************************/
TEST(r_dtc_set_transfer_data_Test, TG007_016)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_ENABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    p_data_cfg->transfer_mode = DTC_TRANSFER_MODE_REPEAT;
    p_data_cfg->transfer_count = 257;
    t_mra.BYTE = (uint8_t)(p_data_cfg->src_addr_mode | p_data_cfg->data_size | p_data_cfg->transfer_mode);
    t_mrb.BYTE = (uint8_t)(p_data_cfg->dest_addr_mode | p_data_cfg->repeat_block_side | p_data_cfg->response_interrupt |
                           p_data_cfg->chain_transfer_enable | p_data_cfg->chain_transfer_mode);


    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    /* settings for fist long word: MRA & SAR */
    TEST_ASSERT_EQUAL(t_mra.BYTE, td_ptr->FIRST_LWORD.REG.MRA.BYTE); /* 1 byte MRA */
    TEST_ASSERT_EQUAL((p_data_cfg->source_addr & 0x00FFFFFF), (td_ptr->FIRST_LWORD.LWORD & 0x00FFFFFF));
    /* settings for second long word: MRB & DAR */
    TEST_ASSERT_EQUAL(t_mrb.BYTE, td_ptr->SECOND_LWORD.REG.MRB.BYTE); /* 1 byte MRB */
    TEST_ASSERT_EQUAL((p_data_cfg->dest_addr & 0x00FFFFFF), (td_ptr->SECOND_LWORD.LWORD & 0x00FFFFFF)); /* 3 byte DAR */
    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_ARG, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_set_transfer_data_Test_TG007_016
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_017
* Description  : Test API function r_dtc_set_transfer_data()
***********************************************************************************************************************/
TEST(r_dtc_set_transfer_data_Test, TG007_017)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_ENABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    p_data_cfg->transfer_mode = DTC_TRANSFER_MODE_BLOCK;
    p_data_cfg->transfer_count = 65536; // DTC_MAX_16BITS_COUNT_VAL;
    t_mra.BYTE = (uint8_t)(p_data_cfg->src_addr_mode | p_data_cfg->data_size | p_data_cfg->transfer_mode);
    t_mrb.BYTE = (uint8_t)(p_data_cfg->dest_addr_mode | p_data_cfg->repeat_block_side | p_data_cfg->response_interrupt |
                           p_data_cfg->chain_transfer_enable | p_data_cfg->chain_transfer_mode);


    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(0x0000, td_ptr->THIRD_LWORD.REG.CRB.WORD);
    /* settings for fist long word: MRA & SAR */
    TEST_ASSERT_EQUAL(t_mra.BYTE, td_ptr->FIRST_LWORD.REG.MRA.BYTE); /* 1 byte MRA */
    TEST_ASSERT_EQUAL((p_data_cfg->source_addr & 0x00FFFFFF), (td_ptr->FIRST_LWORD.LWORD & 0x00FFFFFF));
    /* settings for second long word: MRB & DAR */
    TEST_ASSERT_EQUAL(t_mrb.BYTE, td_ptr->SECOND_LWORD.REG.MRB.BYTE); /* 1 byte MRB */
    TEST_ASSERT_EQUAL((p_data_cfg->dest_addr & 0x00FFFFFF), (td_ptr->SECOND_LWORD.LWORD & 0x00FFFFFF)); /* 3 byte DAR */
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_set_transfer_data_Test_TG007_017
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_018
* Description  : Test API function r_dtc_set_transfer_data()
***********************************************************************************************************************/
TEST(r_dtc_set_transfer_data_Test, TG007_018)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_ENABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    p_data_cfg->transfer_mode = DTC_TRANSFER_MODE_BLOCK;
    p_data_cfg->transfer_count = 1;
    t_mra.BYTE = (uint8_t)(p_data_cfg->src_addr_mode | p_data_cfg->data_size | p_data_cfg->transfer_mode);
    t_mrb.BYTE = (uint8_t)(p_data_cfg->dest_addr_mode | p_data_cfg->repeat_block_side | p_data_cfg->response_interrupt |
                           p_data_cfg->chain_transfer_enable | p_data_cfg->chain_transfer_mode);


    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL((uint16_t)p_data_cfg->transfer_count, td_ptr->THIRD_LWORD.REG.CRB.WORD);
    /* settings for fist long word: MRA & SAR */
    TEST_ASSERT_EQUAL(t_mra.BYTE, td_ptr->FIRST_LWORD.REG.MRA.BYTE); /* 1 byte MRA */
    TEST_ASSERT_EQUAL((p_data_cfg->source_addr & 0x00FFFFFF), (td_ptr->FIRST_LWORD.LWORD & 0x00FFFFFF));
    /* settings for second long word: MRB & DAR */
    TEST_ASSERT_EQUAL(t_mrb.BYTE, td_ptr->SECOND_LWORD.REG.MRB.BYTE); /* 1 byte MRB */
    TEST_ASSERT_EQUAL((p_data_cfg->dest_addr & 0x00FFFFFF), (td_ptr->SECOND_LWORD.LWORD & 0x00FFFFFF)); /* 3 byte DAR */
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_set_transfer_data_Test_TG007_018
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_019
* Description  : Test API function r_dtc_set_transfer_data()
***********************************************************************************************************************/
TEST(r_dtc_set_transfer_data_Test, TG007_019)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_ENABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    p_data_cfg->transfer_mode = DTC_TRANSFER_MODE_BLOCK;
    p_data_cfg->block_size = 1;
    t_mra.BYTE = (uint8_t)(p_data_cfg->src_addr_mode | p_data_cfg->data_size | p_data_cfg->transfer_mode);
    t_mrb.BYTE = (uint8_t)(p_data_cfg->dest_addr_mode | p_data_cfg->repeat_block_side | p_data_cfg->response_interrupt |
                           p_data_cfg->chain_transfer_enable | p_data_cfg->chain_transfer_mode);


    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL((uint8_t)p_data_cfg->block_size, td_ptr->THIRD_LWORD.REG.CRA.BYTE.CRA_H);
    TEST_ASSERT_EQUAL((uint8_t)p_data_cfg->block_size, td_ptr->THIRD_LWORD.REG.CRA.BYTE.CRA_L);
    /* settings for fist long word: MRA & SAR */
    TEST_ASSERT_EQUAL(t_mra.BYTE, td_ptr->FIRST_LWORD.REG.MRA.BYTE); /* 1 byte MRA */
    TEST_ASSERT_EQUAL((p_data_cfg->source_addr & 0x00FFFFFF), (td_ptr->FIRST_LWORD.LWORD & 0x00FFFFFF));
    /* settings for second long word: MRB & DAR */
    TEST_ASSERT_EQUAL(t_mrb.BYTE, td_ptr->SECOND_LWORD.REG.MRB.BYTE); /* 1 byte MRB */
    TEST_ASSERT_EQUAL((p_data_cfg->dest_addr & 0x00FFFFFF), (td_ptr->SECOND_LWORD.LWORD & 0x00FFFFFF)); /* 3 byte DAR */
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_set_transfer_data_Test_TG007_019
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_020
* Description  : Test API function r_dtc_set_transfer_data()
***********************************************************************************************************************/
TEST(r_dtc_set_transfer_data_Test, TG007_020)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_ENABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    p_data_cfg->transfer_mode = DTC_TRANSFER_MODE_BLOCK;
    p_data_cfg->block_size = 256;
    t_mra.BYTE = (uint8_t)(p_data_cfg->src_addr_mode | p_data_cfg->data_size | p_data_cfg->transfer_mode);
    t_mrb.BYTE = (uint8_t)(p_data_cfg->dest_addr_mode | p_data_cfg->repeat_block_side | p_data_cfg->response_interrupt |
                           p_data_cfg->chain_transfer_enable | p_data_cfg->chain_transfer_mode);


    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(0x00, td_ptr->THIRD_LWORD.REG.CRA.BYTE.CRA_H);
    TEST_ASSERT_EQUAL(0x00, td_ptr->THIRD_LWORD.REG.CRA.BYTE.CRA_L);
    /* settings for fist long word: MRA & SAR */
    TEST_ASSERT_EQUAL(t_mra.BYTE, td_ptr->FIRST_LWORD.REG.MRA.BYTE); /* 1 byte MRA */
    TEST_ASSERT_EQUAL((p_data_cfg->source_addr & 0x00FFFFFF), (td_ptr->FIRST_LWORD.LWORD & 0x00FFFFFF));
    /* settings for second long word: MRB & DAR */
    TEST_ASSERT_EQUAL(t_mrb.BYTE, td_ptr->SECOND_LWORD.REG.MRB.BYTE); /* 1 byte MRB */
    TEST_ASSERT_EQUAL((p_data_cfg->dest_addr & 0x00FFFFFF), (td_ptr->SECOND_LWORD.LWORD & 0x00FFFFFF)); /* 3 byte DAR */
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_set_transfer_data_Test_TG007_020
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_021
* Description  : Test API function r_dtc_set_transfer_data()
***********************************************************************************************************************/
TEST(r_dtc_set_transfer_data_Test, TG007_021)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_ENABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    p_data_cfg->transfer_mode = DTC_TRANSFER_MODE_BLOCK;
    p_data_cfg->block_size = 257;
    t_mra.BYTE = (uint8_t)(p_data_cfg->src_addr_mode | p_data_cfg->data_size | p_data_cfg->transfer_mode);
    t_mrb.BYTE = (uint8_t)(p_data_cfg->dest_addr_mode | p_data_cfg->repeat_block_side | p_data_cfg->response_interrupt |
                           p_data_cfg->chain_transfer_enable | p_data_cfg->chain_transfer_mode);


    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    /* settings for fist long word: MRA & SAR */
    TEST_ASSERT_EQUAL(t_mra.BYTE, td_ptr->FIRST_LWORD.REG.MRA.BYTE); /* 1 byte MRA */
    TEST_ASSERT_EQUAL((p_data_cfg->source_addr & 0x00FFFFFF), (td_ptr->FIRST_LWORD.LWORD & 0x00FFFFFF));
    /* settings for second long word: MRB & DAR */
    TEST_ASSERT_EQUAL(t_mrb.BYTE, td_ptr->SECOND_LWORD.REG.MRB.BYTE); /* 1 byte MRB */
    TEST_ASSERT_EQUAL((p_data_cfg->dest_addr & 0x00FFFFFF), (td_ptr->SECOND_LWORD.LWORD & 0x00FFFFFF)); /* 3 byte DAR */
    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_ARG, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_set_transfer_data_Test_TG007_021
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_022
* Description  : Test API function r_dtc_set_transfer_data()
***********************************************************************************************************************/
TEST(r_dtc_set_transfer_data_Test, TG007_022)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_ENABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];
    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    p_data_cfg->transfer_mode = (3<<6);

    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_ARG, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_set_transfer_data_Test_TG007_022
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: TEST_r_dtc_clear_all_dtce_bits_Test_SETUP
* Description  :
***********************************************************************************************************************/
TEST_SETUP(r_dtc_clear_all_dtce_bits_Test)
{
    
}
/***********************************************************************************************************************
End of function TEST_r_dtc_clear_all_dtce_bits_Test_SETUP
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TEST_r_dtc_clear_all_dtce_bits_Test_TEAR_DOWN
* Description  :
***********************************************************************************************************************/
TEST_TEAR_DOWN(r_dtc_clear_all_dtce_bits_Test)
{
    R_DTC_Close();
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
}
/***********************************************************************************************************************
End of function TEST_r_dtc_clear_all_dtce_bits_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG008_001
* Description  : Test API function r_dtc_clear_all_dtce_bits()
***********************************************************************************************************************/
TEST(r_dtc_clear_all_dtce_bits_Test, TG008_001)
{
    dtc_err_t ret_dtc = DTC_SUCCESS;
    volatile uint32_t dtce_cnt = 0;
    ret_dtc = R_DTC_Open();

    while (dtce_cnt < DTC_NUM_INTERRUPT_SRC)
    {
        TEST_ASSERT_EQUAL(0, ICU.DTCER[g_source_array[dtce_cnt]].BIT.DTCE);
        dtce_cnt++;
    }

    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);

}
/***********************************************************************************************************************
* End of function TEST_r_dtc_clear_all_dtce_bits_Test_TG008_001
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: TEST_r_dtc_abort_chain_transfer_Test_SETUP
* Description  :
***********************************************************************************************************************/
TEST_SETUP(r_dtc_abort_chain_transfer_Test)
{
    
}
/***********************************************************************************************************************
End of function TEST_r_dtc_abort_chain_transfer_Test_SETUP
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TEST_r_dtc_abort_chain_transfer_Test_TEAR_DOWN
* Description  :
***********************************************************************************************************************/
TEST_TEAR_DOWN(r_dtc_abort_chain_transfer_Test)
{
    R_DTC_Close();
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
}
/***********************************************************************************************************************
End of function TEST_r_dtc_abort_chain_transfer_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG009_001
* Description  : Test API function r_dtc_abort_chain_transfer()
***********************************************************************************************************************/
TEST(r_dtc_abort_chain_transfer_Test, TG009_001)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_DISABLE)
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;
    uint16_t         status_reg = 0;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 1;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_CHAIN_TRANSFER_ABORT;
    p_stat = &stat;
    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];
    args.p_transfer_data       = &transfer_data[0];
    p_args = &args;

    DTC.DTCSTS.WORD &= ~0x8000;

    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);

#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_abort_chain_transfer_Test_TG009_001
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG009_002
* Description  : Test API function r_dtc_abort_chain_transfer()
***********************************************************************************************************************/
TEST(r_dtc_abort_chain_transfer_Test, TG009_002)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_DISABLE)
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;
    uint16_t         status_reg = 0;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 1;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_CHAIN_TRANSFER_ABORT;
    p_stat = &stat;
    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];
    args.p_transfer_data       = &transfer_data[0];
    p_args = &args;

    DTC.DTCSTS.WORD |= 0x8000;
    status_reg = DTC.DTCSTS.WORD;
    volatile dtc_internal_registers_t *td_ptr = NULL;
    status_reg &= 0xFF;
    td_ptr = (((volatile dtc_internal_registers_t *)*((uint32_t *)DTC.DTCVBR + status_reg)) + args.chain_transfer_nr) - 1;

    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(0, td_ptr->FIRST_LWORD.REG.MRB.BIT.CHNE);

    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);

#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_abort_chain_transfer_Test_TG009_002
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG009_003
* Description  : Test API function r_dtc_abort_chain_transfer()
***********************************************************************************************************************/
TEST(r_dtc_abort_chain_transfer_Test, TG009_003)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_ENABLE)
    dtc_err_t        ret_dtc = DTC_SUCCESS;
    dtc_command_t    command;
    dtc_stat_t       *p_stat;
    dtc_cmd_arg_t    *p_args;
    dtc_stat_t       stat;
    dtc_cmd_arg_t    args;
    uint16_t         status_reg = 0;

    args.act_src = DTCE_ICU_SWINT;
    args.chain_transfer_nr = 1;
    args.p_data_cfg = NULL;
    args.p_transfer_data = NULL;

    R_DTC_Open();

    command = DTC_CMD_CHAIN_TRANSFER_ABORT;
    p_stat = &stat;
    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    args.p_data_cfg            = &data_cfg[0];
    args.p_transfer_data       = &transfer_data[0];
    p_args = &args;

    DTC.DTCSTS.WORD |= 0x8000;
    status_reg = DTC.DTCSTS.WORD;
    volatile dtc_internal_registers_t *td_ptr = NULL;
    status_reg &= 0xFF;
    td_ptr = (((volatile dtc_internal_registers_t *)*((uint32_t *)DTC.DTCVBR + status_reg)) + args.chain_transfer_nr) - 1;

    ret_dtc = R_DTC_Control(command, p_stat, p_args);

    TEST_ASSERT_EQUAL(0, td_ptr->SECOND_LWORD.REG.MRB.BIT.CHNE);

    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);

#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_abort_chain_transfer_Test_TG009_003
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: TEST_r_dtc_acquire_hw_lock_Test_SETUP
* Description  :
***********************************************************************************************************************/
TEST_SETUP(r_dtc_acquire_hw_lock_Test)
{
    
}
/***********************************************************************************************************************
End of function TEST_r_dtc_acquire_hw_lock_Test_SETUP
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TEST_r_dtc_acquire_hw_lock_Test_TEAR_DOWN
* Description  :
***********************************************************************************************************************/
TEST_TEAR_DOWN(r_dtc_acquire_hw_lock_Test)
{
    R_DTC_Close();
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
}
/***********************************************************************************************************************
End of function TEST_r_dtc_acquire_hw_lock_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG010_001
* Description  : Test API function r_dtc_acquire_hw_lock()
***********************************************************************************************************************/
TEST(r_dtc_acquire_hw_lock_Test, TG010_001)
{
    dtc_err_t    ret_dtc = DTC_SUCCESS;

    R_DTC_Close();
    R_BSP_HardwareLock(BSP_LOCK_DTC);

    ret_dtc = R_DTC_Open();
    TEST_ASSERT_EQUAL(DTC_ERR_BUSY, ret_dtc);

}
/***********************************************************************************************************************
* End of function TEST_r_dtc_acquire_hw_lock_Test_TG010_001
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG010_002
* Description  : Test API function r_dtc_acquire_hw_lock()
***********************************************************************************************************************/
TEST(r_dtc_acquire_hw_lock_Test, TG010_002)
{
    dtc_err_t    ret_dtc = DTC_SUCCESS;

    R_DTC_Close();
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);

    ret_dtc = R_DTC_Open();
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);

}
/***********************************************************************************************************************
* End of function TEST_r_dtc_acquire_hw_lock_Test_TG010_002
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: TEST_r_dtc_release_hw_lock_Test_SETUP
* Description  :
***********************************************************************************************************************/
TEST_SETUP(r_dtc_release_hw_lock_Test)
{
    
}
/***********************************************************************************************************************
End of function TEST_r_dtc_release_hw_lock_Test_SETUP
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TEST_r_dtc_release_hw_lock_Test_TEAR_DOWN
* Description  :
***********************************************************************************************************************/
TEST_TEAR_DOWN(r_dtc_release_hw_lock_Test)
{
    R_DTC_Close();
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
}
/***********************************************************************************************************************
End of function TEST_r_dtc_release_hw_lock_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG011_001
* Description  : Test API function r_dtc_release_hw_lock()
***********************************************************************************************************************/
TEST(r_dtc_release_hw_lock_Test, TG011_001)
{
    dtc_err_t ret_dtc = DTC_SUCCESS;
    var_T011_001 = 1;

    R_BSP_HardwareLock(BSP_LOCK_DTC);

    ret_dtc = R_DTC_Close();

    TEST_ASSERT_EQUAL(DTC_SUCCESS_DMAC_BUSY, ret_dtc);
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
    var_T011_001 = 0;
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_release_hw_lock_Test_TG011_001
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: TEST_r_dtc_check_dmac_locking_sw_Test_SETUP
* Description  :
***********************************************************************************************************************/
TEST_SETUP(r_dtc_check_dmac_locking_sw_Test)
{
    
}
/***********************************************************************************************************************
End of function TEST_r_dtc_check_dmac_locking_sw_Test_SETUP
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TEST_r_dtc_check_dmac_locking_sw_Test_TEAR_DOWN
* Description  :
***********************************************************************************************************************/
TEST_TEAR_DOWN(r_dtc_check_dmac_locking_sw_Test)
{
    R_DTC_Close();
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
}
/***********************************************************************************************************************
End of function TEST_r_dtc_check_dmac_locking_sw_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG012_001
* Description  : Test API function r_dtc_check_dmac_locking_sw()
***********************************************************************************************************************/
TEST(r_dtc_check_dmac_locking_sw_Test, TG012_001)
{
    dtc_err_t ret_dtc = DTC_SUCCESS;
    var_T012_001 = 1;

    R_BSP_HardwareLock(BSP_LOCK_DTC);

    ret_dtc = R_DTC_Close();

    TEST_ASSERT_EQUAL(DTC_SUCCESS_DMAC_BUSY, ret_dtc);

    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
    var_T012_001 = 0;

}
/***********************************************************************************************************************
* End of function TEST_r_dtc_check_dmac_locking_sw_Test_TG012_001
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG012_002
* Description  : Test API function r_dtc_check_dmac_locking_sw()
***********************************************************************************************************************/
TEST(r_dtc_check_dmac_locking_sw_Test, TG012_002)
{
    dtc_err_t ret_dtc = DTC_SUCCESS;

    R_BSP_HardwareUnlock((mcu_lock_t)(BSP_LOCK_DTC));

    ret_dtc = R_DTC_Close();

    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);

}
/***********************************************************************************************************************
* End of function TEST_r_dtc_check_dmac_locking_sw_Test_TG012_002
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: TEST_r_dtc_check_DMAC_locking_byUSER_Test_SETUP
* Description  :
***********************************************************************************************************************/
TEST_SETUP(r_dtc_check_DMAC_locking_byUSER_Test)
{
    
}
/***********************************************************************************************************************
End of function TEST_r_dtc_check_DMAC_locking_byUSER_Test_SETUP
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TEST_r_dtc_check_DMAC_locking_byUSER_Test_TEAR_DOWN
* Description  :
***********************************************************************************************************************/
TEST_TEAR_DOWN(r_dtc_check_DMAC_locking_byUSER_Test)
{
    R_DTC_Close();
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
}
/***********************************************************************************************************************
End of function TEST_r_dtc_check_DMAC_locking_byUSER_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG013_001
* Description  : Test API function r_dtc_check_DMAC_locking_byUSER()
***********************************************************************************************************************/
TEST(r_dtc_check_DMAC_locking_byUSER_Test, TG013_001)
{
#if ((0 != BSP_CFG_USER_LOCKING_ENABLED) || (bsp_lock_t != BSP_CFG_USER_LOCKING_TYPE) \
      || (DTC_ENABLE != DTC_CFG_USE_DMAC_FIT_MODULE))

    dtc_err_t ret_dtc = DTC_SUCCESS;

    ret_dtc = R_DTC_Close();
    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);
#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_check_DMAC_locking_byUSER_Test_TG013_001
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: TEST_r_dtc_check_create_param_Test_SETUP
* Description  :
***********************************************************************************************************************/
TEST_SETUP(r_dtc_check_create_param_Test)
{
    
}
/***********************************************************************************************************************
End of function TEST_r_dtc_check_create_param_Test_SETUP
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TEST_r_dtc_check_create_param_Test_TEAR_DOWN
* Description  :
***********************************************************************************************************************/
TEST_TEAR_DOWN(r_dtc_check_create_param_Test)
{
    R_DTC_Close();
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
}
/***********************************************************************************************************************
End of function TEST_r_dtc_check_create_param_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG014_001
* Description  : Test API function r_dtc_check_create_param()
***********************************************************************************************************************/
TEST(r_dtc_check_create_param_Test, TG014_001)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_ENABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];

    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(DTC_ERR_NULL_PTR, ret_dtc);

#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_check_create_param_Test_TG014_001
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG014_002
* Description  : Test API function r_dtc_check_create_param()
***********************************************************************************************************************/
TEST(r_dtc_check_create_param_Test, TG014_002)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_ENABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(DTC_ERR_NULL_PTR, ret_dtc);

#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_check_create_param_Test_TG014_002
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG014_003
* Description  : Test API function r_dtc_check_create_param()
***********************************************************************************************************************/
TEST(r_dtc_check_create_param_Test, TG014_003)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_ENABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];

    p_data_cfg->transfer_count =  0;
    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_ARG, ret_dtc);

#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_check_create_param_Test_TG014_003
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG014_004
* Description  : Test API function r_dtc_check_create_param()
***********************************************************************************************************************/
TEST(r_dtc_check_create_param_Test, TG014_004)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_ENABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];

    p_data_cfg->transfer_count = 65537;

    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_ARG, ret_dtc);

#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_check_create_param_Test_TG014_004
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG014_005
* Description  : Test API function r_dtc_check_create_param()
***********************************************************************************************************************/
TEST(r_dtc_check_create_param_Test, TG014_005)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_ENABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];

    p_data_cfg->source_addr = 0xFF700000;

    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_ARG, ret_dtc);

#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_check_create_param_Test_TG014_005
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG014_006
* Description  : Test API function r_dtc_check_create_param()
***********************************************************************************************************************/
TEST(r_dtc_check_create_param_Test, TG014_006)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_ENABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];

    p_data_cfg->dest_addr = 0x008FFFFF;

    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_ARG, ret_dtc);

#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_check_create_param_Test_TG014_006
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG014_007
* Description  : Test API function r_dtc_check_create_param()
***********************************************************************************************************************/
TEST(r_dtc_check_create_param_Test, TG014_007)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_ENABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];

    p_transfer_data = 0x009FFFFF;

    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_ARG, ret_dtc);

#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_check_create_param_Test_TG014_007
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG014_008
* Description  : Test API function r_dtc_check_create_param()
***********************************************************************************************************************/
TEST(r_dtc_check_create_param_Test, TG014_008)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_ENABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];

    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);

#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_check_create_param_Test_TG014_008
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG014_009
* Description  : Test API function r_dtc_check_create_param()
***********************************************************************************************************************/
TEST(r_dtc_check_create_param_Test, TG014_009)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_DISABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];

    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(DTC_ERR_NULL_PTR, ret_dtc);

#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_check_create_param_Test_TG014_009
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG014_010
* Description  : Test API function r_dtc_check_create_param()
***********************************************************************************************************************/
TEST(r_dtc_check_create_param_Test, TG014_010)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_DISABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(DTC_ERR_NULL_PTR, ret_dtc);

#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_check_create_param_Test_TG014_010
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG014_011
* Description  : Test API function r_dtc_check_create_param()
***********************************************************************************************************************/
TEST(r_dtc_check_create_param_Test, TG014_011)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_DISABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];

    p_data_cfg->transfer_count =  0;
    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_ARG, ret_dtc);

#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_check_create_param_Test_TG014_011
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG014_012
* Description  : Test API function r_dtc_check_create_param()
***********************************************************************************************************************/
TEST(r_dtc_check_create_param_Test, TG014_012)
{
#if (DTC_CFG_SHORT_ADDRESS_MODE == DTC_DISABLE)
    dtc_err_t                ret_dtc             = DTC_SUCCESS;
    dtc_activation_source_t  act_source          = DTCE_ICU_SWINT;
    dtc_transfer_data_t      *p_transfer_data    = NULL;
    dtc_transfer_data_cfg_t  *p_data_cfg         = NULL;
    uint32_t                 chain_transfer_nr   = 0;
    dtc_mra_t                t_mra;
    dtc_mrb_t                t_mrb;
    volatile dtc_internal_registers_t *td_ptr    = NULL;

    R_DTC_Open();

    p_transfer_data            = &transfer_data[0];
    td_ptr = (volatile dtc_internal_registers_t *)p_transfer_data;

    data_cfg[0].transfer_mode  = DTC_TRANSFER_MODE_NORMAL;
    data_cfg[0].transfer_count = 1;
    data_cfg[0].source_addr    = (uint32_t)&test_src_buff32[0];
    data_cfg[0].dest_addr      = (uint32_t)&test_dest_buff[0];
    data_cfg[0].data_size      = DTC_DATA_SIZE_LWORD;              /* The size of data                 */
    data_cfg[0].src_addr_mode  = DTC_SRC_ADDR_INCR;                /* Address mode of source           */
    p_data_cfg                 = &data_cfg[0];

    p_data_cfg->transfer_count = 65537;

    ret_dtc = R_DTC_Create(act_source, p_transfer_data, p_data_cfg, chain_transfer_nr);

    TEST_ASSERT_EQUAL(DTC_ERR_INVALID_ARG, ret_dtc);

#endif
}
/***********************************************************************************************************************
* End of function TEST_r_dtc_check_create_param_Test_TG014_012
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: TEST_r_dtc_module_enable_Test_SETUP
* Description  :
***********************************************************************************************************************/
TEST_SETUP(r_dtc_module_enable_Test)
{
    
}
/***********************************************************************************************************************
End of function TEST_r_dtc_module_enable_Test_SETUP
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TEST_r_dtc_module_enable_Test_TEAR_DOWN
* Description  :
***********************************************************************************************************************/
TEST_TEAR_DOWN(r_dtc_module_enable_Test)
{
    R_DTC_Close();
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
}
/***********************************************************************************************************************
End of function TEST_r_dtc_module_enable_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG015_001
* Description  : Test API function r_dtc_module_enable()
***********************************************************************************************************************/
TEST(r_dtc_module_enable_Test, TG015_001)
{
    dtc_err_t    ret_dtc = DTC_SUCCESS;
    R_DTC_Close();
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);

    ret_dtc = R_DTC_Open();

    TEST_ASSERT_EQUAL(0, MSTP(DTC));

    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);

}
/***********************************************************************************************************************
* End of function TEST_r_dtc_module_enable_Test_TG015_001
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: TEST_r_dtc_module_disable_Test_SETUP
* Description  :
***********************************************************************************************************************/
TEST_SETUP(r_dtc_module_disable_Test)
{
    
}
/***********************************************************************************************************************
End of function TEST_r_dtc_module_disable_Test_SETUP
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TEST_r_dtc_module_disable_Test_TEAR_DOWN
* Description  :
***********************************************************************************************************************/
TEST_TEAR_DOWN(r_dtc_module_disable_Test)
{
    R_DTC_Close();
    R_BSP_HardwareUnlock(BSP_LOCK_DTC);
}
/***********************************************************************************************************************
End of function TEST_r_dtc_module_disable_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG016_001
* Description  : Test API function r_dtc_module_disable()
***********************************************************************************************************************/
TEST(r_dtc_module_disable_Test, TG016_001)
{
    dtc_err_t ret_dtc = DTC_SUCCESS;

    R_BSP_HardwareUnlock((mcu_lock_t)(BSP_LOCK_DTC));
    ret_dtc = R_DTC_Close();

    TEST_ASSERT_EQUAL(1, MSTP(DTC));

    TEST_ASSERT_EQUAL(DTC_SUCCESS, ret_dtc);

}
/***********************************************************************************************************************
* End of function TEST_r_dtc_module_disable_Test_TG016_001
***********************************************************************************************************************/

