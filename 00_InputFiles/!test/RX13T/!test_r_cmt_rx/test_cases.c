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
* Description  : Unity unit tests for RX CMT module
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 28.06.2019 1.00     First Release
***********************************************************************************************************************/

/* Check the flag to enable test scrips for unit test */
//#if __RUN_UNIT_TEST__

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "platform.h"
#include "r_cmt_rx_if.h"
#include "unity_fixture.h"

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
/* Declare test groups. */

uint32_t    cmt_channel[4];
uint32_t    ch_group1;

void cmt_callback(void *pdata);
static void stop_all_channel();


TEST_GROUP(R_CMT_CreatePeriodic_Test);

TEST_SETUP(R_CMT_CreatePeriodic_Test)
{
}

/***********************************************************************************************************************
* Function Name: TEST_TEAR_DOWN
* Description  : Tear down for these unit tests. This will be run after each test case.
***********************************************************************************************************************/
TEST_TEAR_DOWN(R_CMT_CreatePeriodic_Test)
{
    printf("-------------------------------------------\r\n");
}
/***********************************************************************************************************************
End of function TEST_R_CMT_CreatePeriodic_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG001_1
* Description  : Test CMT API function R_CMT_CreatePeriodic()
***********************************************************************************************************************/
TEST(R_CMT_CreatePeriodic_Test, TG001_1)
{
    printf("\n*TG001_1: Test CMT_CreatePeriodic: ");
    bool ret;

    /* Open and Start the timer0 */
    ret = R_CMT_CreatePeriodic(0, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG001_1: Can't create CMT channel\r\n");
    }
    else
    {
        printf("\n*TG001_1: CMT Channel created: %d\r\n", ch_group1);
    }

    TEST_ASSERT_FALSE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_CreatePeriodic_Test_TG001_1
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG001_2
* Description  : Test CMT API function R_CMT_CreatePeriodic()
***********************************************************************************************************************/
TEST(R_CMT_CreatePeriodic_Test, TG001_2)
{
    printf("\n*TG001_2: Test CMT_CreatePeriodic: ");
    bool ret;

    /* Open and Start the timer0 */
    ret = R_CMT_CreatePeriodic(4000005, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG001_2: Can't create CMT channel\r\n");
    }
    else
    {
        printf("\n*TG001_2: CMT Channel created: %d\r\n", ch_group1);
    }

    TEST_ASSERT_FALSE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_CreatePeriodic_Test_TG001_2
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG001_3
* Description  : Test CMT API function R_CMT_CreatePeriodic()
***********************************************************************************************************************/
TEST(R_CMT_CreatePeriodic_Test, TG001_3)
{
    printf("\n*TG001_3: Test CMT_CreatePeriodic: ");
    bool ret;

    /* Open and Start the timer0 */
    ret = R_CMT_CreatePeriodic(1, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG001_3: Can't create CMT channel\r\n");
    }
    else
    {
        printf("\n*TG001_3: CMT Channel created: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1,0);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_CreatePeriodic_Test_TG001_3
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG001_4
* Description  : Test CMT API function R_CMT_CreatePeriodic()
***********************************************************************************************************************/
TEST(R_CMT_CreatePeriodic_Test, TG001_4)
{
    printf("\n*TG001_4: Test CMT_CreatePeriodic: ");
    bool ret;

    /* Open and Start the timer0 */
    ret = R_CMT_CreatePeriodic(4, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG001_4: Can't create CMT channel\r\n");
    }
    else
    {
        printf("\n*TG001_4: CMT Channel created: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1,1);
    R_CMT_Stop(ch_group1);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_CreatePeriodic_Test_TG001_4
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG001_5
* Description  : Test CMT API function R_CMT_CreatePeriodic()
***********************************************************************************************************************/
TEST(R_CMT_CreatePeriodic_Test, TG001_5)
{
    printf("\n*TG001_5: Test CMT_CreatePeriodic: ");
    bool ret;

    /* Open and Start the timer0 */
    ret = R_CMT_CreatePeriodic(16, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG001_5: Can't create CMT channel\r\n");
    }
    else
    {
        printf("\n*TG001_5: CMT Channel created: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1,1);
    R_CMT_Stop(ch_group1);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_CreatePeriodic_Test_TG001_5
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG001_6
* Description  : Test CMT API function R_CMT_CreatePeriodic()
***********************************************************************************************************************/
TEST(R_CMT_CreatePeriodic_Test, TG001_6)
{
    printf("\n*TG001_6: Test CMT_CreatePeriodic: ");
    bool ret;

    /* Open and Start the timer0 */
    ret = R_CMT_CreatePeriodic(65, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG001_6: Can't create CMT channel\r\n");
    }
    else
    {
        printf("\n*TG001_6: CMT Channel created: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1,1);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_CreatePeriodic_Test_TG001_6
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: TG001_6
* Description  : Test CMT API function R_CMT_CreatePeriodic()
***********************************************************************************************************************/
TEST(R_CMT_CreatePeriodic_Test, TG001_7)
{
    printf("\n*TG001_7: Test CMT_CreatePeriodic: ");
    bool ret;

    /* Lock BSP_LOCK_CMT and this function return FALSE if call again */
    ret = R_BSP_HardwareLock(BSP_LOCK_CMT);

    /* Open and Start the timer */
    ret = R_CMT_CreatePeriodic(1, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG001_7: Can't create CMT channel\r\n");
    }
    else
    {
        printf("\n*TG001_7: CMT Channel created: %d\r\n", ch_group1);
    }

    R_BSP_HardwareUnlock(BSP_LOCK_CMT);

    TEST_ASSERT_FALSE(ret);

    stop_all_channel();
}
/***********************************************************************************************************************
End of function TEST_R_CMT_CreatePeriodic_Test_TG001_7
***********************************************************************************************************************/

//#####################################################################################################################

TEST_GROUP(R_CMT_CreateOneShot_Test);

TEST_SETUP(R_CMT_CreateOneShot_Test)
{
}

/***********************************************************************************************************************
* Function Name: TEST_TEAR_DOWN
* Description  : Tear down for these unit tests. This will be run after each test case.
***********************************************************************************************************************/
TEST_TEAR_DOWN(R_CMT_CreateOneShot_Test)
{
    printf("-------------------------------------------\r\n");
}
/***********************************************************************************************************************
End of function TEST_R_CMT_CreateOneShot_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG002_1
* Description  : Test CMT API function R_CMT_CreateOneShot()
***********************************************************************************************************************/
TEST(R_CMT_CreateOneShot_Test, TG002_1)
{
    printf("\n*TG002_1: Test R_CMT_CreateOneShot: ");
    bool ret;

    /* Open and Start the timer0 */
    ret = R_CMT_CreateOneShot(2000000, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG002_1: Can't create CMT channel\r\n");
    }
    else
    {
        printf("\n*TG002_1: CMT Channel created: %d\r\n", ch_group1);
    }

    TEST_ASSERT_FALSE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_CreateOneShot_Test_TG002_1
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG002_2
* Description  : Test CMT API function R_CMT_CreateOneShot()
***********************************************************************************************************************/
TEST(R_CMT_CreateOneShot_Test, TG002_2)
{
    printf("\n*TG002_2: Test R_CMT_CreateOneShot: ");
    bool ret;

    /* Open and Start the timer0 */
    ret = R_CMT_CreateOneShot(50000, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG002_2: Can't create CMT channel\r\n");
    }
    else
    {
        printf("\n*TG002_2: CMT Channel created: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1,0);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_CreateOneShot_Test_TG002_2
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG002_3
* Description  : Test CMT API function R_CMT_CreateOneShot()
***********************************************************************************************************************/
TEST(R_CMT_CreateOneShot_Test, TG002_3)
{
    printf("\n*TG002_3: Test R_CMT_CreateOneShot: ");
    bool ret;

    /* Open and Start the timer0 */
    ret = R_CMT_CreateOneShot(250000, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG002_3: Can't create CMT channel\r\n");
    }
    else
    {
        printf("\n*TG002_3: CMT Channel created: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1,1);
    R_CMT_Stop(ch_group1);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_CreateOneShot_Test_TG002_3
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG002_4
* Description  : Test CMT API function R_CMT_CreateOneShot()
***********************************************************************************************************************/
TEST(R_CMT_CreateOneShot_Test, TG002_4)
{
    printf("\n*TG002_4: Test R_CMT_CreateOneShot: ");
    bool ret;

    /* Open and Start the timer0 */
    ret = R_CMT_CreateOneShot(62500, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG002_4: Can't create CMT channel\r\n");
    }
    else
    {
        printf("\n*TG002_4: CMT Channel created: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1,1);
    R_CMT_Stop(ch_group1);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_CreateOneShot_Test_TG002_4
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG002_5
* Description  : Test CMT API function R_CMT_CreateOneShot()
***********************************************************************************************************************/
TEST(R_CMT_CreateOneShot_Test, TG002_5)
{
    printf("\n*TG002_5: Test R_CMT_CreateOneShot: ");
    bool ret;

    /* Open and Start the timer0 */
    ret = R_CMT_CreateOneShot(10000, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG002_5: Can't create CMT channel\r\n");
    }
    else
    {
        printf("\n*TG002_5: CMT Channel created: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1,1);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_CreateOneShot_Test_TG002_5
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG002_6
* Description  : Test CMT API function R_CMT_CreateOneShot()
***********************************************************************************************************************/
TEST(R_CMT_CreateOneShot_Test, TG002_6)
{
    printf("\n*TG002_6: Test R_CMT_CreateOneShot: ");
    bool ret;

    /* Open and Start the timer0 */
    ret = R_CMT_CreateOneShot(10000, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG002_6: Can't create CMT channel\r\n");
    }
    else
    {
        printf("\n*TG002_6: CMT Channel created: %d\r\n", ch_group1);
    }

    TEST_ASSERT_FALSE(ret);

    stop_all_channel();
}
/***********************************************************************************************************************
End of function TEST_R_CMT_CreateOneShot_Test_TG002_6
***********************************************************************************************************************/

//#####################################################################################################################

TEST_GROUP(R_CMT_Stop_Test);

TEST_SETUP(R_CMT_Stop_Test)
{
    R_CMT_CreatePeriodic(2, cmt_callback, &ch_group1);
    R_CMT_CreatePeriodic(2, cmt_callback, &ch_group1);
//    R_CMT_CreatePeriodic(2, cmt_callback, &ch_group1);
//    R_CMT_CreatePeriodic(2, cmt_callback, &ch_group1);

}

/***********************************************************************************************************************
* Function Name: TEST_TEAR_DOWN
* Description  : Tear down for these unit tests. This will be run after each test case.
***********************************************************************************************************************/
TEST_TEAR_DOWN(R_CMT_Stop_Test)
{
    printf("-------------------------------------------\r\n");

    /* Stop the timer */
    R_CMT_Stop(0);
    R_CMT_Stop(1);
//    R_CMT_Stop(2);
//    R_CMT_Stop(3);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_Stop_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG003_1
* Description  : Test CMT API function R_CMT_Stop()
***********************************************************************************************************************/
TEST(R_CMT_Stop_Test, TG003_1)
{
    printf("\n*TG003_1: Test CMT_Stop: ");
    bool ret;

    /* Open and Start the timer0 */
    ret = R_CMT_Stop(2);

    if(0 == ret)
    {
        printf("\n*TG003_1: Can't stop CMT Channel: %d\r\n", 0);
    }
    else
    {
        printf("\n*TG003_1: Stopped CMT Channel: %d\r\n", 0);
    }

    TEST_ASSERT_FALSE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_CreateStop_Test_TG003_1
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG003_2
* Description  : Test CMT API function R_CMT_Stop()
***********************************************************************************************************************/
TEST(R_CMT_Stop_Test, TG003_2)
{
    printf("\n*TG003_2: Test CMT_Stop: ");
    bool ret;

    ret = R_CMT_Stop(0);

    if(0 == ret)
    {
        printf("\n*TG003_2: Can't stop CMT Channel: %d\r\n", 0);
    }
    else
    {
        printf("\n*TG003_2: Stopped CMT Channel: %d\r\n", 0);
    }

    TEST_ASSERT_TRUE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_CreateStop_Test_TG003_2
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG003_3
* Description  : Test CMT API function R_CMT_Stop()
***********************************************************************************************************************/
TEST(R_CMT_Stop_Test, TG003_3)
{
    printf("\n*TG003_3: Test CMT_Stop: ");
    bool ret;

    ret = R_CMT_Stop(1);

    if(0 == ret)
    {
        printf("\n*TG003_3: Can't stop CMT Channel: %d\r\n", 1);
    }
    else
    {
        printf("\n*TG003_3: Stopped CMT Channel: %d\r\n", 1);
    }

    TEST_ASSERT_TRUE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_CreateStop_Test_TG003_3
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: TG003_4
* Description  : Test CMT API function R_CMT_Stop()
***********************************************************************************************************************/
//TEST(R_CMT_Stop_Test, TG003_4)
//{
//    printf("\n*TG003_4: Test CMT_Stop: ");
//    bool ret;
//
//    ret = R_CMT_Stop(2);
//
//    if(0 == ret)
//    {
//        printf("\n*TG003_4: Can't stop CMT Channel: %d\r\n", 2);
//    }
//    else
//    {
//        printf("\n*TG003_4: Stopped CMT Channel: %d\r\n", 2);
//    }
//
//    TEST_ASSERT_TRUE(ret);
//}
/***********************************************************************************************************************
End of function TEST_R_CMT_CreateStop_Test_TG003_4
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: TG003_5
* Description  : Test CMT API function R_CMT_Stop()
***********************************************************************************************************************/
//TEST(R_CMT_Stop_Test, TG003_5)
//{
//    printf("\n*TG003_5: Test CMT_Stop: ");
//    bool ret;
//
//    ret = R_CMT_Stop(3);
//
//    if(0 == ret)
//    {
//        printf("\n*TG003_5: Can't stop CMT Channel: %d\r\n", 3);
//    }
//    else
//    {
//        printf("\n*TG003_5: Stopped CMT Channel: %d\r\n", 3);
//    }
//
//    TEST_ASSERT_TRUE(ret);
//}
/***********************************************************************************************************************
End of function TEST_R_CMT_CreateStop_Test_TG003_5
***********************************************************************************************************************/

//#####################################################################################################################

uint32_t    pdata;

TEST_GROUP(R_CMT_Control_Test);

TEST_SETUP(R_CMT_Control_Test)
{
    R_CMT_CreatePeriodic(2, cmt_callback, &ch_group1);
    R_CMT_CreatePeriodic(2, cmt_callback, &ch_group1);
//    R_CMT_CreatePeriodic(2, cmt_callback, &ch_group1);
//    R_CMT_CreatePeriodic(2, cmt_callback, &ch_group1);

}

/***********************************************************************************************************************
* Function Name: TEST_TEAR_DOWN
* Description  : Tear down for these unit tests. This will be run after each test case.
***********************************************************************************************************************/
TEST_TEAR_DOWN(R_CMT_Control_Test)
{
    printf("-------------------------------------------\r\n");

    /* Stop the timer */
    R_CMT_Stop(0);
    R_CMT_Stop(1);
//    R_CMT_Stop(2);
//    R_CMT_Stop(3);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_1
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
TEST(R_CMT_Control_Test, TG004_1)
{
    printf("\n*TG004_1: Test CMT_Control\r\n ");
    bool ret;

    ret = R_CMT_Control(0, CMT_RX_CMD_IS_CHANNEL_COUNTING, &pdata);


    TEST_ASSERT_EQUAL(pdata, 1);

    TEST_ASSERT_TRUE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_1
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_2
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
TEST(R_CMT_Control_Test, TG004_2)
{
    printf("\n*TG004_2: Test CMT_Control\r\n ");
    bool ret;

    ret = R_CMT_Control(0, CMT_RX_CMD_GET_NUM_CHANNELS, &pdata);

    printf("Number of channel: %d\r\n", pdata);

    TEST_ASSERT_EQUAL(2, pdata);

    TEST_ASSERT_TRUE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_2
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_3
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
TEST(R_CMT_Control_Test, TG004_3)
{
    printf("\n*TG004_3: Test CMT_Control\r\n ");
    bool ret;

    ret = R_CMT_Control(0, CMT_RX_CMD_PAUSE, &pdata);

    TEST_ASSERT_TRUE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_3
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_4
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
TEST(R_CMT_Control_Test, TG004_4)
{
    printf("\n*TG004_4: Test CMT_Control\r\n ");
    bool ret;

    ret = R_CMT_Control(0, CMT_RX_CMD_PAUSE, &pdata);

    ret = R_CMT_Control(0, CMT_RX_CMD_RESTART, &pdata);

    TEST_ASSERT_TRUE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_4
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_5
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
TEST(R_CMT_Control_Test, TG004_5)
{
    printf("\n*TG004_5: Test CMT_Control\r\n ");
    bool ret;

    ret = R_CMT_Control(0, CMT_RX_CMD_PAUSE, &pdata);

    ret = R_CMT_Control(0, CMT_RX_CMD_RESUME, &pdata);

    TEST_ASSERT_TRUE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_5
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_6
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
TEST(R_CMT_Control_Test, TG004_6)
{
    printf("\n*TG004_6: Test CMT_Control\r\n ");
    bool ret;

    ret = R_CMT_Control(1, CMT_RX_CMD_IS_CHANNEL_COUNTING, &pdata);


    TEST_ASSERT_EQUAL(pdata, 1);

    TEST_ASSERT_TRUE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_6
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_7
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
TEST(R_CMT_Control_Test, TG004_7)
{
    printf("\n*TG004_7: Test CMT_Control\r\n ");
    bool ret;

    ret = R_CMT_Control(1, CMT_RX_CMD_GET_NUM_CHANNELS, &pdata);

    printf("Number of channel: %d\r\n", pdata);

    TEST_ASSERT_EQUAL(2, pdata);

    TEST_ASSERT_TRUE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_7
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_8
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
TEST(R_CMT_Control_Test, TG004_8)
{
    printf("\n*TG004_8: Test CMT_Control\r\n ");
    bool ret;

    ret = R_CMT_Control(1, CMT_RX_CMD_PAUSE, &pdata);

    TEST_ASSERT_TRUE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_8
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_9
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
TEST(R_CMT_Control_Test, TG004_9)
{
    printf("\n*TG004_9: Test CMT_Control\r\n ");
    bool ret;

    ret = R_CMT_Control(1, CMT_RX_CMD_PAUSE, &pdata);

    ret = R_CMT_Control(1, CMT_RX_CMD_RESTART, &pdata);

    TEST_ASSERT_TRUE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_9
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_10
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
TEST(R_CMT_Control_Test, TG004_10)
{
    printf("\n*TG004_10: Test CMT_Control\r\n ");
    bool ret;

    ret = R_CMT_Control(1, CMT_RX_CMD_PAUSE, &pdata);

    ret = R_CMT_Control(1, CMT_RX_CMD_RESUME, &pdata);

    TEST_ASSERT_TRUE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_10
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_11
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
//TEST(R_CMT_Control_Test, TG004_11)
//{
//    printf("\n*TG004_11: Test CMT_Control\r\n ");
//    bool ret;
//
//    ret = R_CMT_Control(2, CMT_RX_CMD_IS_CHANNEL_COUNTING, &pdata);
//
//
//    TEST_ASSERT_EQUAL(pdata, 1);
//
//    TEST_ASSERT_TRUE(ret);
//}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_11
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_12
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
//TEST(R_CMT_Control_Test, TG004_12)
//{
//    printf("\n*TG004_12: Test CMT_Control\r\n ");
//    bool ret;
//
//    ret = R_CMT_Control(2, CMT_RX_CMD_GET_NUM_CHANNELS, &pdata);
//
//    printf("Number of channel: %d\r\n", pdata);
//
//    TEST_ASSERT_EQUAL(4, pdata);
//
//    TEST_ASSERT_TRUE(ret);
//}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_12
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_13
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
//TEST(R_CMT_Control_Test, TG004_13)
//{
//    printf("\n*TG004_13: Test CMT_Control\r\n ");
//    bool ret;
//
//    ret = R_CMT_Control(2, CMT_RX_CMD_PAUSE, &pdata);
//
//    TEST_ASSERT_TRUE(ret);
//}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_13
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_14
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
//TEST(R_CMT_Control_Test, TG004_14)
//{
//    printf("\n*TG004_14: Test CMT_Control\r\n ");
//    bool ret;
//
//    ret = R_CMT_Control(2, CMT_RX_CMD_PAUSE, &pdata);
//
//    ret = R_CMT_Control(2, CMT_RX_CMD_RESTART, &pdata);
//
//    TEST_ASSERT_TRUE(ret);
//}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_14
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_15
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
//TEST(R_CMT_Control_Test, TG004_15)
//{
//    printf("\n*TG004_15: Test CMT_Control\r\n ");
//    bool ret;
//
//    ret = R_CMT_Control(2, CMT_RX_CMD_PAUSE, &pdata);
//
//    ret = R_CMT_Control(2, CMT_RX_CMD_RESUME, &pdata);
//
//    TEST_ASSERT_TRUE(ret);
//}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_15
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_16
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
//TEST(R_CMT_Control_Test, TG004_16)
//{
//    printf("\n*TG004_16: Test CMT_Control\r\n ");
//    bool ret;
//
//    ret = R_CMT_Control(3, CMT_RX_CMD_IS_CHANNEL_COUNTING, &pdata);
//
//
//    TEST_ASSERT_EQUAL(pdata, 1);
//
//    TEST_ASSERT_TRUE(ret);
//}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_16
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_17
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
//TEST(R_CMT_Control_Test, TG004_17)
//{
//    printf("\n*TG004_17: Test CMT_Control\r\n ");
//    bool ret;
//
//    ret = R_CMT_Control(3, CMT_RX_CMD_GET_NUM_CHANNELS, &pdata);
//
//    printf("Number of channel: %d\r\n", pdata);
//
//    TEST_ASSERT_EQUAL(4, pdata);
//
//    TEST_ASSERT_TRUE(ret);
//}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_17
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_18
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
//TEST(R_CMT_Control_Test, TG004_18)
//{
//    printf("\n*TG004_18: Test CMT_Control\r\n ");
//    bool ret;
//
//    ret = R_CMT_Control(3, CMT_RX_CMD_PAUSE, &pdata);
//
//    TEST_ASSERT_TRUE(ret);
//}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_18
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_19
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
//TEST(R_CMT_Control_Test, TG004_19)
//{
//    printf("\n*TG004_19: Test CMT_Control\r\n ");
//    bool ret;
//
//    ret = R_CMT_Control(3, CMT_RX_CMD_PAUSE, &pdata);
//
//    ret = R_CMT_Control(3, CMT_RX_CMD_RESTART, &pdata);
//
//    TEST_ASSERT_TRUE(ret);
//}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_19
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_20
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
//TEST(R_CMT_Control_Test, TG004_20)
//{
//    printf("\n*TG004_20: Test CMT_Control\r\n ");
//    bool ret;
//
//    ret = R_CMT_Control(3, CMT_RX_CMD_PAUSE, &pdata);
//
//    ret = R_CMT_Control(3, CMT_RX_CMD_RESUME, &pdata);
//
//    TEST_ASSERT_TRUE(ret);
//}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_20
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_21
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
TEST(R_CMT_Control_Test, TG004_21)
{
    printf("\n*TG004_21: Test CMT_Control\r\n ");
    bool ret;

    ret = R_CMT_Control(4, CMT_RX_CMD_IS_CHANNEL_COUNTING, &pdata);


    TEST_ASSERT_FALSE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_21
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_22
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
TEST(R_CMT_Control_Test, TG004_22)
{
    printf("\n*TG004_22: Test CMT_Control\r\n ");
    bool ret;

    ret = R_CMT_Stop(0);
    ret = R_CMT_Stop(1);
//    ret = R_CMT_Stop(2);
//    ret = R_CMT_Stop(3);

    ret = R_CMT_Control(0, CMT_RX_CMD_IS_CHANNEL_COUNTING, &pdata);

    TEST_ASSERT_EQUAL(pdata, 0);

    TEST_ASSERT_TRUE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_22
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_23
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
TEST(R_CMT_Control_Test, TG004_23)
{
    printf("\n*TG004_23: Test CMT_Control\r\n ");
    bool ret;

    ret = R_CMT_Stop(0);
    ret = R_CMT_Stop(1);
//    ret = R_CMT_Stop(2);
//    ret = R_CMT_Stop(3);

    ret = R_CMT_Control(1, CMT_RX_CMD_IS_CHANNEL_COUNTING, &pdata);


    TEST_ASSERT_EQUAL(pdata, 0);

    TEST_ASSERT_TRUE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_23
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_24
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
//TEST(R_CMT_Control_Test, TG004_24)
//{
//    printf("\n*TG004_24: Test CMT_Control\r\n ");
//    bool ret;
//
//    ret = R_CMT_Stop(0);
//    ret = R_CMT_Stop(1);
//    ret = R_CMT_Stop(2);
//    ret = R_CMT_Stop(3);
//
//    ret = R_CMT_Control(2, CMT_RX_CMD_IS_CHANNEL_COUNTING, &pdata);
//
//
//    TEST_ASSERT_EQUAL(pdata, 0);
//
//    TEST_ASSERT_TRUE(ret);
//}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_24
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_25
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
//TEST(R_CMT_Control_Test, TG004_25)
//{
//    printf("\n*TG004_25: Test CMT_Control\r\n ");
//    bool ret;
//
//    ret = R_CMT_Stop(0);
//    ret = R_CMT_Stop(1);
//    ret = R_CMT_Stop(2);
//    ret = R_CMT_Stop(3);
//
//    ret = R_CMT_Control(3, CMT_RX_CMD_IS_CHANNEL_COUNTING, &pdata);
//
//
//    TEST_ASSERT_EQUAL(pdata, 0);
//
//    TEST_ASSERT_TRUE(ret);
//}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_25
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_26
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
TEST(R_CMT_Control_Test, TG004_26)
{
    printf("\n*TG004_26: Test CMT_Control\r\n ");
    bool ret;

    ret = R_CMT_Control(4, CMT_RX_CMD_PAUSE, &pdata);

    TEST_ASSERT_FALSE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_26
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_27
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
TEST(R_CMT_Control_Test, TG004_27)
{
    printf("\n*TG004_27: Test CMT_Control\r\n ");
    bool ret;

    ret = R_CMT_Control(4, CMT_RX_CMD_RESTART, &pdata);

    TEST_ASSERT_FALSE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_27
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_28
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
TEST(R_CMT_Control_Test, TG004_28)
{
    printf("\n*TG004_28: Test CMT_Control\r\n ");
    bool ret;

    ret = R_CMT_Control(4, CMT_RX_CMD_RESUME, &pdata);

    TEST_ASSERT_FALSE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_28
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG004_29
* Description  : Test CMT API function R_CMT_Control()
***********************************************************************************************************************/
TEST(R_CMT_Control_Test, TG004_29)
{
    printf("\n*TG004_29: Test CMT_Control\r\n ");
    bool ret;

    ret = R_CMT_Control(1, (cmt_commands_t)99, &pdata);

    TEST_ASSERT_FALSE(ret);
}
/***********************************************************************************************************************
End of function TEST_R_CMT_Control_Test_TG004_29
***********************************************************************************************************************/


TEST(R_CMT_Control_Test, TG004_30)
{
    printf("\n*TG004_30...");
    bool ret;
    uint32_t channel = 0;
    cmt_commands_t command = CMT_RX_CMD_SET_PRIORITY;
    cmt_priority_t priority = (cmt_priority_t)(CMT_PRIORITY_0 - 1);

    ret = R_CMT_Control(channel, command, &priority);
    TEST_ASSERT_EQUAL(false, ret);

    printf("OK\n");
}

TEST(R_CMT_Control_Test, TG004_31)
{
    printf("\n*TG004_31...");
    bool ret;
    uint32_t channel = 0;
    cmt_commands_t command = CMT_RX_CMD_SET_PRIORITY;
    cmt_priority_t priority = (cmt_priority_t)(CMT_PRIORITY_MAX + 1);

    ret = R_CMT_Control(channel, command, &priority);
    TEST_ASSERT_EQUAL(false, ret);

    printf("OK\n");
}

TEST(R_CMT_Control_Test, TG004_32)
{
    printf("\n*TG004_32...");
    bool ret;
    uint32_t channel = 4;
    cmt_commands_t command = CMT_RX_CMD_SET_PRIORITY;
    cmt_priority_t priority = CMT_PRIORITY_7;

    ret = R_CMT_Control(channel, command, &priority);
    TEST_ASSERT_EQUAL(false, ret);

    printf("OK\n");
}

TEST(R_CMT_Control_Test, TG004_33)
{
    printf("\n*TG004_33...");
    bool ret;
    uint32_t channel = 0;
    cmt_commands_t command = CMT_RX_CMD_SET_PRIORITY;
    cmt_priority_t priority = CMT_PRIORITY_7;
    R_CMT_Stop(channel);

    ret = R_CMT_Control(channel, command, &priority);
    TEST_ASSERT_EQUAL(false, ret);

    printf("OK\n");
}

TEST(R_CMT_Control_Test, TG004_34)
{
    printf("\n*TG004_34...");
    bool ret;
    uint32_t channel = 0;
    cmt_commands_t command = CMT_RX_CMD_SET_PRIORITY;
    cmt_priority_t priority = CMT_PRIORITY_7;
    R_CMT_Stop(channel);
    R_CMT_CreatePeriodicAssignChannelPriority(100, cmt_callback, channel, CMT_PRIORITY_6);
    TEST_ASSERT_EQUAL(CMT_PRIORITY_6, IPR(CMT0, CMI0));

    ret = R_CMT_Control(channel, command, &priority);
    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(priority, IPR(CMT0, CMI0));

    printf("OK\n");
    R_CMT_Stop(channel);
}

TEST(R_CMT_Control_Test, TG004_35)
{
    printf("\n*TG004_35...");
    bool ret;
    uint32_t channel = 1;
    cmt_commands_t command = CMT_RX_CMD_SET_PRIORITY;
    cmt_priority_t priority = CMT_PRIORITY_7;
    R_CMT_Stop(channel);
    R_CMT_CreatePeriodicAssignChannelPriority(100, cmt_callback, channel, CMT_PRIORITY_6);
    TEST_ASSERT_EQUAL(CMT_PRIORITY_6, IPR(CMT1, CMI1));

    ret = R_CMT_Control(channel, command, &priority);
    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(priority, IPR(CMT1, CMI1));

    printf("OK\n");
    R_CMT_Stop(channel);
}

//TEST(R_CMT_Control_Test, TG004_36)
//{
//    printf("\n*TG004_36...");
//    bool ret;
//    uint32_t channel = 2;
//    cmt_commands_t command = CMT_RX_CMD_SET_PRIORITY;
//    cmt_priority_t priority = CMT_PRIORITY_7;
//    R_CMT_Stop(channel);
//    R_CMT_CreatePeriodicAssignChannelPriority(100, cmt_callback, channel, CMT_PRIORITY_6);
//    TEST_ASSERT_EQUAL(CMT_PRIORITY_6, IPR(CMT2, CMI2));
//
//    ret = R_CMT_Control(channel, command, &priority);
//    TEST_ASSERT_EQUAL(true, ret);
//    TEST_ASSERT_EQUAL(priority, IPR(CMT2, CMI2));
//
//    printf("OK\n");
//    R_CMT_Stop(channel);
//}

//TEST(R_CMT_Control_Test, TG004_37)
//{
//    printf("\n*TG004_37...");
//    bool ret;
//    uint32_t channel = 3;
//    cmt_commands_t command = CMT_RX_CMD_SET_PRIORITY;
//    cmt_priority_t priority = CMT_PRIORITY_7;
//    R_CMT_Stop(channel);
//    R_CMT_CreatePeriodicAssignChannelPriority(100, cmt_callback, channel, CMT_PRIORITY_6);
//    TEST_ASSERT_EQUAL(CMT_PRIORITY_6, IPR(CMT3, CMI3));
//
//    ret = R_CMT_Control(channel, command, &priority);
//    TEST_ASSERT_EQUAL(true, ret);
//    TEST_ASSERT_EQUAL(priority, IPR(CMT3, CMI3));
//
//    printf("OK\n");
//    R_CMT_Stop(channel);
//}

TEST(R_CMT_Control_Test, TG004_38)
{
    printf("\n*TG004_38...");
    bool ret;
    uint32_t channel = 4;
    cmt_commands_t command = CMT_RX_CMD_GET_PRIORITY;
    cmt_priority_t prior_ret = CMT_PRIORITY_0;
    R_CMT_Stop(channel);

    ret = R_CMT_Control(channel, command, &prior_ret);
    TEST_ASSERT_EQUAL(false, ret);

    printf("OK\n");
    R_CMT_Stop(channel);
}

TEST(R_CMT_Control_Test, TG004_39)
{
    printf("\n*TG004_39...");
    bool ret;
    uint32_t channel = 0;
    cmt_commands_t command = CMT_RX_CMD_GET_PRIORITY;
    cmt_priority_t priority = CMT_PRIORITY_7;
    cmt_priority_t prior_ret = CMT_PRIORITY_0;
    R_CMT_Stop(channel);
    R_CMT_CreatePeriodicAssignChannelPriority(100, cmt_callback, channel, CMT_PRIORITY_6);
    TEST_ASSERT_EQUAL(CMT_PRIORITY_6, IPR(CMT0, CMI0));

    CMT.CMSTR0.BIT.STR0 = 0;
    IPR(CMT0, CMI0) = priority;
    CMT.CMSTR0.BIT.STR0 = 1;

    ret = R_CMT_Control(channel, command, &prior_ret);
    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(prior_ret, priority);

    printf("OK\n");
    R_CMT_Stop(channel);
}

TEST(R_CMT_Control_Test, TG004_40)
{
    printf("\n*TG004_40...");
    bool ret;
    uint32_t channel = 1;
    cmt_commands_t command = CMT_RX_CMD_GET_PRIORITY;
    cmt_priority_t priority = CMT_PRIORITY_7;
    cmt_priority_t prior_ret = CMT_PRIORITY_0;
    R_CMT_Stop(channel);
    R_CMT_CreatePeriodicAssignChannelPriority(100, cmt_callback, channel, CMT_PRIORITY_6);
    TEST_ASSERT_EQUAL(CMT_PRIORITY_6, IPR(CMT1, CMI1));

    CMT.CMSTR0.BIT.STR1 = 0;
    IPR(CMT1, CMI1) = priority;
    CMT.CMSTR0.BIT.STR1 = 1;

    ret = R_CMT_Control(channel, command, &prior_ret);
    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(prior_ret, priority);

    printf("OK\n");
    R_CMT_Stop(channel);
}

//TEST(R_CMT_Control_Test, TG004_41)
//{
//    printf("\n*TG004_41...");
//    bool ret;
//    uint32_t channel = 2;
//    cmt_commands_t command = CMT_RX_CMD_GET_PRIORITY;
//    cmt_priority_t priority = CMT_PRIORITY_7;
//    cmt_priority_t prior_ret = CMT_PRIORITY_0;
//    R_CMT_Stop(channel);
//    R_CMT_CreatePeriodicAssignChannelPriority(100, cmt_callback, channel, CMT_PRIORITY_6);
//    TEST_ASSERT_EQUAL(CMT_PRIORITY_6, IPR(CMT2, CMI2));
//
//    CMT.CMSTR1.BIT.STR2 = 0;
//    IPR(CMT2, CMI2) = priority;
//    CMT.CMSTR1.BIT.STR2 = 1;
//
//    ret = R_CMT_Control(channel, command, &prior_ret);
//    TEST_ASSERT_EQUAL(true, ret);
//    TEST_ASSERT_EQUAL(prior_ret, priority);
//
//    printf("OK\n");
//    R_CMT_Stop(channel);
//}

//TEST(R_CMT_Control_Test, TG004_42)
//{
//    printf("\n*TG004_42...");
//    bool ret;
//    uint32_t channel = 3;
//    cmt_commands_t command = CMT_RX_CMD_GET_PRIORITY;
//    cmt_priority_t priority = CMT_PRIORITY_7;
//    cmt_priority_t prior_ret = CMT_PRIORITY_0;
//    R_CMT_Stop(channel);
//    R_CMT_CreatePeriodicAssignChannelPriority(100, cmt_callback, channel, CMT_PRIORITY_6);
//    TEST_ASSERT_EQUAL(CMT_PRIORITY_6, IPR(CMT3, CMI3));
//
//    CMT.CMSTR1.BIT.STR3 = 0;
//    IPR(CMT3, CMI3) = priority;
//    CMT.CMSTR1.BIT.STR3 = 1;
//
//    ret = R_CMT_Control(channel, command, &prior_ret);
//    TEST_ASSERT_EQUAL(true, ret);
//    TEST_ASSERT_EQUAL(prior_ret, priority);
//
//    printf("OK\n");
//    R_CMT_Stop(channel);
//}

//TEST(R_CMT_Control_Test, TG004_43)
//{
//    printf("\n*TG004_43...");
//    bool ret;
//    uint32_t channel = 3;
//    cmt_commands_t command = CMT_RX_CMD_SET_PRIORITY;
//    R_CMT_Stop(channel);
//    R_CMT_CreatePeriodicAssignChannelPriority(100, cmt_callback, channel, CMT_PRIORITY_6);
//    TEST_ASSERT_EQUAL(CMT_PRIORITY_6, IPR(CMT3, CMI3));
//
//    ret = R_CMT_Control(channel, command, NULL);
//    TEST_ASSERT_EQUAL(false, ret);
//
//    printf("OK\n");
//    R_CMT_Stop(channel);
//}

//TEST(R_CMT_Control_Test, TG004_44)
//{
//    printf("\n*TG004_44...");
//    bool ret;
//    uint32_t channel = 3;
//    cmt_commands_t command = CMT_RX_CMD_GET_PRIORITY;
//    R_CMT_Stop(channel);
//    R_CMT_CreatePeriodicAssignChannelPriority(100, cmt_callback, channel, CMT_PRIORITY_6);
//    TEST_ASSERT_EQUAL(CMT_PRIORITY_6, IPR(CMT3, CMI3));
//
//    ret = R_CMT_Control(channel, command, NULL);
//    TEST_ASSERT_EQUAL(false, ret);
//
//    printf("OK\n");
//    R_CMT_Stop(channel);
//}

//#####################################################################################################################

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
/* Declare test groups. */
TEST_GROUP(R_CMT_GetVersion_Test);

 TEST_SETUP(R_CMT_GetVersion_Test)
{
}
/***********************************************************************************************************************
End of function TEST_R_CMT_GetVersion_Test_SETUP
***********************************************************************************************************************/


TEST_TEAR_DOWN(R_CMT_GetVersion_Test)
{
    printf("-------------------------------------------\r\n");
}
/***********************************************************************************************************************
End of function TEST_R_CMT_GetVersion_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG005_1
* Description  : Test CMT API function R_CMT_GetVersion()
***********************************************************************************************************************/
TEST(R_CMT_GetVersion_Test, TG005_1)
{
    printf("\n*TG005_1: Test CMT version: ");

    /* Retrieve the version number and convert it to a string. */
    uint32_t version;
    uint32_t version_high;
    uint32_t version_low;

    version = R_CMT_GetVersion();
    version_high = (version >> 16)&0xf;
    version_low = version & 0xff;

    printf("CMT v%1.1hu.%2.2hu\n", version_high, version_low);
    TEST_ASSERT_EQUAL(0x0004001E, R_CMT_GetVersion());
}
/********************************************************************************
End of function TEST_R_CMT_GetVersion_Test_TG005_1
********************************************************************************/


//#####################################################################################################################

/***********************************************************************************************************************
Private static variables and functions
***********************************************************************************************************************/
/* Declare test groups. */
TEST_GROUP(cmt_create);

 TEST_SETUP(cmt_create)
{
}
/***********************************************************************************************************************
End of function cmt_create_Test_SETUP
***********************************************************************************************************************/


TEST_TEAR_DOWN(cmt_create)
{
    printf("-------------------------------------------\r\n");
}
/***********************************************************************************************************************
End of function cmt_create_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG006_1
* Description  : Test Static function cmt_create()
***********************************************************************************************************************/
TEST(cmt_create, TG006_1)
{
    printf("\n*TG006_1: Test cmt_create: ");
    bool ret;

    R_BSP_HardwareLock(BSP_LOCK_CMT);
    ret = R_CMT_CreatePeriodic(1, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG006_1: Can't create CMT channel\r\n");
    }
    else
    {
        printf("\n*TG006_1: CMT Channel created: %d\r\n", ch_group1);
    }

    TEST_ASSERT_FALSE(ret);
    R_BSP_HardwareUnlock(BSP_LOCK_CMT);
}
/***********************************************************************************************************************
End of function cmt_create_Test_TG006_1
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG006_2
* Description  : Test Static function cmt_create()
***********************************************************************************************************************/
TEST(cmt_create, TG006_2)
{
    printf("\n*TG006_2: Test cmt_create: ");
    bool ret;

    R_CMT_CreatePeriodic(1, cmt_callback, &ch_group1);
    R_CMT_CreatePeriodic(1, cmt_callback, &ch_group1);
//    R_CMT_CreatePeriodic(2, cmt_callback, &ch_group1);
//    R_CMT_CreatePeriodic(2, cmt_callback, &ch_group1);
    ret = R_CMT_CreatePeriodic(1, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG006_2: Can't create CMT channel\r\n");
    }
    else
    {
        printf("\n*TG006_2: CMT Channel created: %d\r\n", ch_group1);
    }

    TEST_ASSERT_FALSE(ret);
    stop_all_channel();
}
/***********************************************************************************************************************
End of function cmt_create_Test_TG006_2
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG006_3
* Description  : Test Static function cmt_create()
***********************************************************************************************************************/
TEST(cmt_create, TG006_3)
{
    printf("\n*TG006_3: Test cmt_create: ");
    bool ret;

    ret = R_CMT_CreatePeriodic(0, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG006_3: Can't create CMT channel\r\n");
    }
    else
    {
        printf("\n*TG006_3: CMT Channel created: %d\r\n", ch_group1);
    }

    TEST_ASSERT_FALSE(ret);
}
/***********************************************************************************************************************
End of function cmt_create_Test_TG006_3
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG006_4
* Description  : Test Static function cmt_create()
***********************************************************************************************************************/
TEST(cmt_create, TG006_4)
{
    printf("\n*TG006_4: Test cmt_create: ");
    bool ret;

    ret = R_CMT_CreatePeriodic(4000001, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG006_4: Can't create CMT channel\r\n");
    }
    else
    {
        printf("\n*TG006_4: CMT Channel created: %d\r\n", ch_group1);
    }

    TEST_ASSERT_FALSE(ret);
}
/***********************************************************************************************************************
End of function cmt_create_Test_TG006_4
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG006_5
* Description  : Test Static function cmt_create()
***********************************************************************************************************************/
TEST(cmt_create, TG006_5)
{
    printf("\n*TG006_5: Test cmt_create: ");
    bool ret;

    ret = R_CMT_CreatePeriodic(1, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG006_5: Can't create CMT channel\r\n");
    }
    else
    {
        printf("\n*TG006_5: CMT Channel created: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1,0);
}
/***********************************************************************************************************************
End of function cmt_create_Test_TG006_5
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG006_6
* Description  : Test Static function cmt_create()
***********************************************************************************************************************/
TEST(cmt_create, TG006_6)
{
    printf("\n*TG006_6: Test cmt_create: ");
    bool ret;

    ret = R_CMT_CreatePeriodic(4, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG006_6: Can't create CMT channel\r\n");
    }
    else
    {
        printf("\n*TG006_6: CMT Channel created: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1,1);
    R_CMT_Stop(ch_group1);
}
/***********************************************************************************************************************
End of function cmt_create_Test_TG006_6
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG006_7
* Description  : Test Static function cmt_create()
***********************************************************************************************************************/
TEST(cmt_create, TG006_7)
{
    printf("\n*TG006_7: Test cmt_create: ");
    bool ret;

    ret = R_CMT_CreatePeriodic(16, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG006_7: Can't create CMT channel\r\n");
    }
    else
    {
        printf("\n*TG006_7: CMT Channel created: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1,1);
    R_CMT_Stop(ch_group1);
}
/***********************************************************************************************************************
End of function cmt_create_Test_TG006_7
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG006_8
* Description  : Test Static function cmt_create()
***********************************************************************************************************************/
TEST(cmt_create, TG006_8)
{
    printf("\n*TG006_8: Test cmt_create: ");
    bool ret;

    ret = R_CMT_CreatePeriodic(65, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG006_8: Can't create CMT channel\r\n");
    }
    else
    {
        printf("\n*TG006_8: CMT Channel created: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1,1);

    stop_all_channel();
}
/***********************************************************************************************************************
End of function cmt_create_Test_TG006_8
***********************************************************************************************************************/

//#####################################################################################################################

/***********************************************************************************************************************
Private static variables and functions
***********************************************************************************************************************/
/* Declare test groups. */
TEST_GROUP(cmt_lock_state);

 TEST_SETUP(cmt_lock_state)
{
}
/***********************************************************************************************************************
End of function cmt_lock_state_Test_SETUP
***********************************************************************************************************************/


TEST_TEAR_DOWN(cmt_lock_state)
{
    printf("-------------------------------------------\r\n");
}
/***********************************************************************************************************************
End of function cmt_lock_state_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_1
* Description  : Test Static function cmt_lock_state()
***********************************************************************************************************************/
TEST(cmt_lock_state, TG007_1)
{
    printf("\n*TG007_1: Test cmt_lock_state: ");
    bool ret;

    ret = R_CMT_CreatePeriodic(1, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG007_1: Can't lock BSP_LOCK_CMT\r\n");
    }
    else
    {
        printf("\n*TG007_1: BSP_LOCK_CMT locked\r\n");
    }

    TEST_ASSERT_TRUE(ret);
}
/***********************************************************************************************************************
End of function cmt_lock_state_Test_TG007_1
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG007_2
* Description  : Test Static function cmt_lock_state()
***********************************************************************************************************************/
TEST(cmt_lock_state, TG007_2)
{
    printf("\n*TG007_2: Test cmt_lock_state: ");
    bool ret;

    R_BSP_HardwareLock(BSP_LOCK_CMT);

    ret = R_CMT_CreatePeriodic(1, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG007_2: Can't lock BSP_LOCK_CMT\r\n");
    }
    else
    {
        printf("\n*TG007_2: BSP_LOCK_CMT locked\r\n");
    }

    TEST_ASSERT_FALSE(ret);

    R_BSP_HardwareUnlock(BSP_LOCK_CMT);
    stop_all_channel();
}
/***********************************************************************************************************************
End of function cmt_lock_state_Test_TG007_1
***********************************************************************************************************************/

//#####################################################################################################################

/***********************************************************************************************************************
Private static variables and functions
***********************************************************************************************************************/
/* Declare test groups. */
TEST_GROUP(cmt_unlock_state);

 TEST_SETUP(cmt_unlock_state)
{
}
/***********************************************************************************************************************
End of function cmt_unlock_state_Test_SETUP
***********************************************************************************************************************/


TEST_TEAR_DOWN(cmt_unlock_state)
{
    printf("-------------------------------------------\r\n");
}
/***********************************************************************************************************************
End of function cmt_unlock_state_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG008_1
* Description  : Test Static function cmt_unlock_state()
***********************************************************************************************************************/
TEST(cmt_unlock_state, TG008_1)
{
    printf("\n*TG008_1: Test cmt_unlock_state\r\n ");

    R_CMT_CreatePeriodic(1, cmt_callback, &ch_group1);

    stop_all_channel();

}
/***********************************************************************************************************************
End of function cmt_unlock_state_Test_TG008_1
***********************************************************************************************************************/

//#####################################################################################################################

/***********************************************************************************************************************
Private static variables and functions
***********************************************************************************************************************/
/* Declare test groups. */
TEST_GROUP(cmt_find_channel);

 TEST_SETUP(cmt_find_channel)
{

}
/***********************************************************************************************************************
End of function cmt_find_channel_Test_SETUP
***********************************************************************************************************************/

TEST_TEAR_DOWN(cmt_find_channel)
{
    printf("-------------------------------------------\r\n");
}
/***********************************************************************************************************************
End of function cmt_find_channel_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG009_1
* Description  : Test Static function cmt_find_channel()
***********************************************************************************************************************/
TEST(cmt_find_channel, TG009_1)
{
    printf("\n*TG009_1: Test cmt_find_channel: ");
    bool ret;

    ret = R_CMT_CreatePeriodic(1, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG009_1: CMT Channel not found\r\n");
    }
    else
    {
        printf("\n*TG009_1: CMT Channel found: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1,0);
}
/***********************************************************************************************************************
End of function cmt_find_channel_Test_TG009_1
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG009_2
* Description  : Test Static function cmt_find_channel()
***********************************************************************************************************************/
TEST(cmt_find_channel, TG009_2)
{
    printf("\n*TG009_2: Test cmt_find_channel: ");
    bool ret;

    ret = R_CMT_CreatePeriodic(1, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG009_2: CMT Channel not found\r\n");
    }
    else
    {
        printf("\n*TG009_2: CMT Channel found: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1,1);
    R_CMT_Stop(ch_group1);
}
/***********************************************************************************************************************
End of function cmt_find_channel_Test_TG009_2
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG009_3
* Description  : Test Static function cmt_find_channel()
***********************************************************************************************************************/
TEST(cmt_find_channel, TG009_3)
{
    printf("\n*TG009_3: Test cmt_find_channel: ");
    bool ret;

    ret = R_CMT_CreatePeriodic(1, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG009_3: CMT Channel not found\r\n");
    }
    else
    {
        printf("\n*TG009_3: CMT Channel found: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1,1);
    R_CMT_Stop(ch_group1);
}
/***********************************************************************************************************************
End of function cmt_find_channel_Test_TG009_3
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG009_4
* Description  : Test Static function cmt_find_channel()
***********************************************************************************************************************/
TEST(cmt_find_channel, TG009_4)
{
    printf("\n*TG009_4: Test cmt_find_channel: ");
    bool ret;

    ret = R_CMT_CreatePeriodic(1, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG009_4: CMT Channel not found\r\n");
    }
    else
    {
        printf("\n*TG009_4: CMT Channel found: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1,1);
}
/***********************************************************************************************************************
End of function cmt_find_channel_Test_TG009_4
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG009_5
* Description  : Test Static function cmt_find_channel()
***********************************************************************************************************************/
TEST(cmt_find_channel, TG009_5)
{
    printf("\n*TG009_5: Test cmt_find_channel: ");
    bool ret;

    ret = R_CMT_CreatePeriodic(1, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG009_5: CMT Channel not found\r\n");
    }
    else
    {
        printf("\n*TG009_5: CMT Channel found: %d\r\n", ch_group1);
    }

    TEST_ASSERT_FALSE(ret);

    stop_all_channel();
}
/***********************************************************************************************************************
End of function cmt_find_channel_Test_TG009_5
***********************************************************************************************************************/

//#####################################################################################################################

/***********************************************************************************************************************
Private static variables and functions
***********************************************************************************************************************/
/* Declare test groups. */
TEST_GROUP(cmt_setup_channel);

 TEST_SETUP(cmt_setup_channel)
{
}
/***********************************************************************************************************************
End of function cmt_setup_channel_Test_SETUP
***********************************************************************************************************************/

TEST_TEAR_DOWN(cmt_setup_channel)
{
    printf("-------------------------------------------\r\n");
}
/***********************************************************************************************************************
End of function cmt_setup_channel_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG010_1
* Description  : Test Static function cmt_setup_channel()
***********************************************************************************************************************/
TEST(cmt_setup_channel, TG010_1)
{
    printf("\n*TG010_1: Test cmt_setup_channel: ");
    bool ret;

    /* Open and Start the timer0 */
    ret = R_CMT_CreatePeriodic(4000001, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG010_1: CMT Channel not found\r\n");
    }
    else
    {
        printf("\n*TG010_1: CMT Channel found: %d\r\n", ch_group1);
    }

    TEST_ASSERT_FALSE(ret);
}
/***********************************************************************************************************************
End of function cmt_setup_channel_Test_TG010_1
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG010_2
* Description  : Test Static function cmt_setup_channel()
***********************************************************************************************************************/
TEST(cmt_setup_channel, TG010_2)
{
    printf("\n*TG010_2: Test cmt_setup_channel: ");
    bool ret;

    /* Open and Start the timer0 */
    ret = R_CMT_CreatePeriodic(1, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG010_2: CMT Channel not found\r\n");
    }
    else
    {
        printf("\n*TG010_2: CMT Channel found: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1,0);
}
/***********************************************************************************************************************
End of function cmt_setup_channel_Test_TG010_2
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG010_3
* Description  : Test Static function cmt_setup_channel()
***********************************************************************************************************************/
TEST(cmt_setup_channel, TG010_3)
{
    printf("\n*TG010_3: Test cmt_setup_channel: ");
    bool ret;

    ret = R_CMT_CreatePeriodic(4, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG010_3: CMT Channel not found\r\n");
    }
    else
    {
        printf("\n*TG010_3: CMT Channel found: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1,1);
    R_CMT_Stop(ch_group1);
}
/***********************************************************************************************************************
End of function cmt_setup_channel_Test_TG010_3
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG010_4
* Description  : Test Static function cmt_setup_channel()
***********************************************************************************************************************/
TEST(cmt_setup_channel, TG010_4)
{
    printf("\n*TG010_4: Test cmt_setup_channel: ");
    bool ret;

    ret = R_CMT_CreatePeriodic(16, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG010_4: CMT Channel not found\r\n");
    }
    else
    {
        printf("\n*TG010_4: CMT Channel found: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1,1);
    R_CMT_Stop(ch_group1);
}
/***********************************************************************************************************************
End of function cmt_setup_channel_Test_TG010_4
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG010_5
* Description  : Test Static function cmt_setup_channel()
***********************************************************************************************************************/
TEST(cmt_setup_channel, TG010_5)
{
    printf("\n*TG010_5: Test cmt_setup_channel: ");
    bool ret;

    ret = R_CMT_CreatePeriodic(65, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG010_5: CMT Channel not found\r\n");
    }
    else
    {
        printf("\n*TG010_5: CMT Channel found: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1,1);

    stop_all_channel();
}
/***********************************************************************************************************************
End of function cmt_setup_channel_Test_TG010_5
***********************************************************************************************************************/

//#####################################################################################################################

/***********************************************************************************************************************
Private static variables and functions
***********************************************************************************************************************/
/* Declare test groups. */
TEST_GROUP(cmt_counter_start);

 TEST_SETUP(cmt_counter_start)
{
}
/***********************************************************************************************************************
End of function cmt_counter_start_Test_SETUP
***********************************************************************************************************************/

TEST_TEAR_DOWN(cmt_counter_start)
{
    printf("-------------------------------------------\r\n");
}
/***********************************************************************************************************************
End of function cmt_counter_start_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG011_1
* Description  : Test Static function cmt_counter_start()
***********************************************************************************************************************/
TEST(cmt_counter_start, TG011_1)
{
    printf("\n*TG011_1: Test cmt_counter_start: ");
    bool ret;

    ret = R_CMT_CreatePeriodic(1, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG011_1: CMT Channel can not start\r\n");
    }
    else
    {
        printf("\n*TG011_1: CMT Channel started: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1,0);

    TEST_ASSERT_EQUAL(IR(CMT0, CMI0), 0);
//    TEST_ASSERT_EQUAL(IPR(CMT0, CMI0), CMT_RX_CFG_IPR);
    TEST_ASSERT_EQUAL(IEN(CMT0, CMI0), 1);
    TEST_ASSERT_EQUAL(CMT.CMSTR0.BIT.STR0, 1);
}
/***********************************************************************************************************************
End of function cmt_counter_start_Test_TG011_1
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG011_2
* Description  : Test Static function cmt_counter_start()
***********************************************************************************************************************/
TEST(cmt_counter_start, TG011_2)
{
    printf("\n*TG011_2: Test cmt_counter_start: ");
    bool ret;

    ret = R_CMT_CreatePeriodic(1, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG011_2: CMT Channel can not start\r\n");
    }
    else
    {
        printf("\n*TG011_2: CMT Channel started: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1,1);

    TEST_ASSERT_EQUAL(IR(CMT1, CMI1), 0);
    //TEST_ASSERT_EQUAL(IPR(CMT1, CMI1), CMT_RX_CFG_IPR);
    TEST_ASSERT_EQUAL(IEN(CMT1, CMI1), 1);
    TEST_ASSERT_EQUAL(CMT.CMSTR0.BIT.STR1, 1);
}
/***********************************************************************************************************************
End of function cmt_counter_start_Test_TG011_2
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG011_3
* Description  : Test Static function cmt_counter_start()
***********************************************************************************************************************/
//TEST(cmt_counter_start, TG011_3)
//{
//    printf("\n*TG011_3: Test cmt_counter_start: ");
//    bool ret;
//
//    ret = R_CMT_CreatePeriodic(2, cmt_callback, &ch_group1);
//
//    if(0 == ret)
//    {
//        printf("\n*TG011_3: CMT Channel can not start\r\n");
//    }
//    else
//    {
//        printf("\n*TG011_3: CMT Channel started: %d\r\n", ch_group1);
//    }
//
//    TEST_ASSERT_TRUE(ret);
//    TEST_ASSERT_EQUAL(ch_group1,2);
//
//    TEST_ASSERT_EQUAL(IR(CMT2, CMI2), 0);
//    //TEST_ASSERT_EQUAL(IPR(CMT2, CMI2), CMT_RX_CFG_IPR);
//    TEST_ASSERT_EQUAL(IEN(CMT2, CMI2), 1);
//    TEST_ASSERT_EQUAL(CMT.CMSTR1.BIT.STR2, 1);
//}
/***********************************************************************************************************************
End of function cmt_counter_start_Test_TG011_3
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG011_4
* Description  : Test Static function cmt_counter_start()
***********************************************************************************************************************/
//TEST(cmt_counter_start, TG011_4)
//{
//    printf("\n*TG011_4: Test cmt_counter_start: ");
//    bool ret;
//
//    ret = R_CMT_CreatePeriodic(2, cmt_callback, &ch_group1);
//
//    if(0 == ret)
//    {
//        printf("\n*TG011_4: CMT Channel can not start\r\n");
//    }
//    else
//    {
//        printf("\n*TG011_4: CMT Channel started: %d\r\n", ch_group1);
//    }
//
//    TEST_ASSERT_TRUE(ret);
//    TEST_ASSERT_EQUAL(ch_group1,3);
//
//    TEST_ASSERT_EQUAL(IR(CMT3, CMI3), 0);
//    //TEST_ASSERT_EQUAL(IPR(CMT3, CMI3), CMT_RX_CFG_IPR);
//    TEST_ASSERT_EQUAL(IEN(CMT3, CMI3), 1);
//    TEST_ASSERT_EQUAL(CMT.CMSTR1.BIT.STR3, 1);
//
//    stop_all_channel();
//}
/***********************************************************************************************************************
End of function cmt_counter_start_Test_TG011_4
***********************************************************************************************************************/

//#####################################################################################################################

/***********************************************************************************************************************
Private static variables and functions
***********************************************************************************************************************/
/* Declare test groups. */
TEST_GROUP(cmt_counter_stop);

 TEST_SETUP(cmt_counter_stop)
{
    R_CMT_CreatePeriodic(1, cmt_callback, &ch_group1);
    R_CMT_CreatePeriodic(1, cmt_callback, &ch_group1);
//    R_CMT_CreatePeriodic(2, cmt_callback, &ch_group1);
//    R_CMT_CreatePeriodic(2, cmt_callback, &ch_group1);
}
/***********************************************************************************************************************
End of function cmt_counter_stop_Test_SETUP
***********************************************************************************************************************/

TEST_TEAR_DOWN(cmt_counter_stop)
{
    printf("-------------------------------------------\r\n");

    /* Stop the timer */
    R_CMT_Stop(0);
    R_CMT_Stop(1);
//    R_CMT_Stop(2);
//    R_CMT_Stop(3);
}
/***********************************************************************************************************************
End of function cmt_counter_stop_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG012_1
* Description  : Test Static function cmt_counter_stop()
***********************************************************************************************************************/
TEST(cmt_counter_stop, TG012_1)
{
    printf("\n*TG012_1: Test cmt_counter_stop: ");
    bool ret;

    ret = R_CMT_Stop(0);

    if(0 == ret)
    {
        printf("\n*TG012_1: Can't stop CMT Channel: %d\r\n", 0);
    }
    else
    {
        printf("\n*TG012_1: CMT Channel stopped: %d\r\n", 0);
    }

    TEST_ASSERT_TRUE(ret);

    TEST_ASSERT_EQUAL(CMT.CMSTR0.BIT.STR0, 0);
    TEST_ASSERT_EQUAL(IEN(CMT0, CMI0), 0);
    TEST_ASSERT_EQUAL(IPR(CMT0, CMI0), 0);
    TEST_ASSERT_EQUAL(IR(CMT0, CMI0), 0);

}
/***********************************************************************************************************************
End of function cmt_counter_stop_Test_TG012_1
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG012_2
* Description  : Test Static function cmt_counter_stop()
***********************************************************************************************************************/
TEST(cmt_counter_stop, TG012_2)
{
    printf("\n*TG012_2: Test cmt_counter_stop: ");
    bool ret;

    ret = R_CMT_Stop(1);

    if(0 == ret)
    {
        printf("\n*TG012_2: Can't stop CMT Channel: %d\r\n", 1);
    }
    else
    {
        printf("\n*TG012_2: CMT Channel stopped: %d\r\n", 1);
    }

    TEST_ASSERT_TRUE(ret);

    TEST_ASSERT_EQUAL(CMT.CMSTR0.BIT.STR1, 0);
    TEST_ASSERT_EQUAL(IEN(CMT1, CMI1), 0);
    TEST_ASSERT_EQUAL(IPR(CMT1, CMI1), 0);
    TEST_ASSERT_EQUAL(IR(CMT1, CMI1), 0);
}
/***********************************************************************************************************************
End of function cmt_counter_stop_Test_TG012_2
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG012_3
* Description  : Test Static function cmt_counter_stop()
***********************************************************************************************************************/
//TEST(cmt_counter_stop, TG012_3)
//{
//    printf("\n*TG012_3: Test cmt_counter_stop: ");
//    bool ret;
//
//    ret = R_CMT_Stop(2);
//
//    if(0 == ret)
//    {
//        printf("\n*TG012_3: Can't stop CMT Channel: %d\r\n", 2);
//    }
//    else
//    {
//        printf("\n*TG012_3: CMT Channel stopped: %d\r\n", 2);
//    }
//
//    TEST_ASSERT_TRUE(ret);
//
//    TEST_ASSERT_EQUAL(CMT.CMSTR1.BIT.STR2, 0);
//    TEST_ASSERT_EQUAL(IEN(CMT2, CMI2), 0);
//    TEST_ASSERT_EQUAL(IPR(CMT2, CMI2), 0);
//    TEST_ASSERT_EQUAL(IR(CMT2, CMI2), 0);
//}
/***********************************************************************************************************************
End of function cmt_counter_stop_Test_TG012_3
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG012_4
* Description  : Test Static function cmt_counter_stop()
***********************************************************************************************************************/
//TEST(cmt_counter_stop, TG012_4)
//{
//    printf("\n*TG012_4: Test cmt_counter_stop: ");
//    bool ret;
//
//    ret = R_CMT_Stop(3);
//
//    if(0 == ret)
//    {
//        printf("\n*TG012_4: Can't stop CMT Channel: %d\r\n", 3);
//    }
//    else
//    {
//        printf("\n*TG012_4: CMT Channel stopped: %d\r\n", 3);
//    }
//
//    TEST_ASSERT_TRUE(ret);
//
//    TEST_ASSERT_EQUAL(CMT.CMSTR1.BIT.STR3, 0);
//    TEST_ASSERT_EQUAL(IEN(CMT3, CMI3), 0);
//    TEST_ASSERT_EQUAL(IPR(CMT3, CMI3), 0);
//    TEST_ASSERT_EQUAL(IR(CMT3, CMI3), 0);
//}
/***********************************************************************************************************************
End of function cmt_counter_stop_Test_TG012_4
***********************************************************************************************************************/

//#####################################################################################################################

/***********************************************************************************************************************
Private static variables and functions
***********************************************************************************************************************/
/* Declare test groups. */
TEST_GROUP(power_on);

 TEST_SETUP(power_on)
{
}
/***********************************************************************************************************************
End of function power_on_Test_SETUP
***********************************************************************************************************************/

TEST_TEAR_DOWN(power_on)
{
    printf("-------------------------------------------\r\n");
}
/***********************************************************************************************************************
End of function power_on_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG013_1
* Description  : Test Static function power_on()
***********************************************************************************************************************/
TEST(power_on, TG013_1)
{
    printf("\n*TG013_1: Test power_on: ");
    bool ret;

    ret = R_CMT_CreatePeriodic(1, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG013_1: Can't turn on CMT Channel: %d\r\n", ch_group1);
    }
    else
    {
        printf("\n*TG013_1: Power on CMT Channel: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1, 0);

    TEST_ASSERT_EQUAL(MSTP(CMT0), 0);
//    TEST_ASSERT_EQUAL(CMT.CMSTR0.BIT.STR0, 0);
}
/***********************************************************************************************************************
End of function power_on_Test_TG013_1
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG013_2
* Description  : Test Static function power_on()
***********************************************************************************************************************/
TEST(power_on, TG013_2)
{
    printf("\n*TG013_2: Test power_on: ");
    bool ret;

    ret = R_CMT_CreatePeriodic(2, cmt_callback, &ch_group1);

    if(0 == ret)
    {
        printf("\n*TG013_2: Can't turn on CMT Channel: %d\r\n", ch_group1);
    }
    else
    {
        printf("\n*TG013_2: Power on CMT Channel: %d\r\n", ch_group1);
    }

    TEST_ASSERT_TRUE(ret);
    TEST_ASSERT_EQUAL(ch_group1, 1);

    TEST_ASSERT_EQUAL(MSTP(CMT1), 0);
//    TEST_ASSERT_EQUAL(CMT.CMSTR0.BIT.STR1, 0);
}
/***********************************************************************************************************************
End of function power_on_Test_TG013_2
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG013_3
* Description  : Test Static function power_on()
***********************************************************************************************************************/
//TEST(power_on, TG013_3)
//{
//    printf("\n*TG013_3: Test power_on: ");
//    bool ret;
//
//    ret = R_CMT_CreatePeriodic(2, cmt_callback, &ch_group1);
//
//    if(0 == ret)
//    {
//        printf("\n*TG013_3: Can't turn on CMT Channel: %d\r\n", ch_group1);
//    }
//    else
//    {
//        printf("\n*TG013_3: Power on CMT Channel: %d\r\n", ch_group1);
//    }
//
//    TEST_ASSERT_TRUE(ret);
//    TEST_ASSERT_EQUAL(ch_group1, 2);
//
//    TEST_ASSERT_EQUAL(MSTP(CMT2), 0);
//    //TEST_ASSERT_EQUAL(CMT.CMSTR1.BIT.STR2, 0);
//}
/***********************************************************************************************************************
End of function power_on_Test_TG013_3
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG013_4
* Description  : Test Static function power_on()
***********************************************************************************************************************/
//TEST(power_on, TG013_4)
//{
//    printf("\n*TG013_4: Test power_on: ");
//    bool ret;
//
//    ret = R_CMT_CreatePeriodic(2, cmt_callback, &ch_group1);
//
//    if(0 == ret)
//    {
//        printf("\n*TG013_4: Can't turn on CMT Channel: %d\r\n", ch_group1);
//    }
//    else
//    {
//        printf("\n*TG013_4: Power on CMT Channel: %d\r\n", ch_group1);
//    }
//
//    TEST_ASSERT_TRUE(ret);
//    TEST_ASSERT_EQUAL(ch_group1, 3);
//
//    TEST_ASSERT_EQUAL(MSTP(CMT3), 0);
//    //TEST_ASSERT_EQUAL(CMT.CMSTR1.BIT.STR3, 0);
//
//    stop_all_channel();
//}
/***********************************************************************************************************************
End of function power_on_Test_TG013_4
***********************************************************************************************************************/

//#####################################################################################################################

/***********************************************************************************************************************
Private static variables and functions
***********************************************************************************************************************/
/* Declare test groups. */
TEST_GROUP(power_off);

 TEST_SETUP(power_off)
{
    R_CMT_CreatePeriodic(2, cmt_callback, &ch_group1);
    R_CMT_CreatePeriodic(2, cmt_callback, &ch_group1);
//    R_CMT_CreatePeriodic(2, cmt_callback, &ch_group1);
//    R_CMT_CreatePeriodic(2, cmt_callback, &ch_group1);
}
/***********************************************************************************************************************
End of function power_off
***********************************************************************************************************************/

TEST_TEAR_DOWN(power_off)
{
    printf("-------------------------------------------\r\n");

    /* Stop the timer */
    R_CMT_Stop(0);
    R_CMT_Stop(1);
//    R_CMT_Stop(2);
//    R_CMT_Stop(3);
}
/***********************************************************************************************************************
End of function power_off_Test_TEAR_DOWN
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG014_1
* Description  : Test Static function power_off()
***********************************************************************************************************************/
TEST(power_off, TG014_1)
{
    printf("\n*TG014_1: Test power_off: ");
    bool ret;

    ret = R_CMT_Stop(0);

    if(0 == ret)
    {
        printf("\n*TG014_1: Can't turn off CMT Channel: %d\r\n", 0);
    }
    else
    {
        printf("\n*TG014_1: Power off CMT Channel: %d\r\n", 0);
    }

    TEST_ASSERT_TRUE(ret);

    TEST_ASSERT_EQUAL(CMT.CMSTR0.BIT.STR0, 0);
    TEST_ASSERT_EQUAL(MSTP(CMT0), 0);
}
/***********************************************************************************************************************
End of function power_off_Test_TG014_1
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG014_2
* Description  : Test Static function power_off()
***********************************************************************************************************************/
TEST(power_off, TG014_2)
{
    printf("\n*TG014_2: Test power_off: ");
    bool ret;

    ret = R_CMT_Stop(1);

    if(0 == ret)
    {
        printf("\n*TG014_2: Can't turn off CMT Channel: %d\r\n", 1);
    }
    else
    {
        printf("\n*TG014_2: Power off CMT Channel: %d\r\n", 1);
    }

    TEST_ASSERT_TRUE(ret);

    TEST_ASSERT_EQUAL(CMT.CMSTR0.BIT.STR1, 0);
    TEST_ASSERT_EQUAL(MSTP(CMT1), 0);
}
/***********************************************************************************************************************
End of function power_off_Test_TG014_2
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG014_3
* Description  : Test Static function power_off()
***********************************************************************************************************************/
//TEST(power_off, TG014_3)
//{
//    printf("\n*TG014_3: Test power_off: ");
//    bool ret;
//
//    ret = R_CMT_Stop(2);
//
//    if(0 == ret)
//    {
//        printf("\n*TG014_3: Can't turn off CMT Channel: %d\r\n", 2);
//    }
//    else
//    {
//        printf("\n*TG014_3: Power off CMT Channel: %d\r\n", 2);
//    }
//
//    TEST_ASSERT_TRUE(ret);
//
//    TEST_ASSERT_EQUAL(CMT.CMSTR1.BIT.STR2, 0);
//    TEST_ASSERT_EQUAL(MSTP(CMT2), 0);
//}
/***********************************************************************************************************************
End of function power_off_Test_TG014_3
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: TG014_4
* Description  : Test Static function power_off()
***********************************************************************************************************************/
//TEST(power_off, TG014_4)
//{
//    printf("\n*TG014_4: Test power_off: ");
//    bool ret;
//
//    ret = R_CMT_Stop(3);
//
//    if(0 == ret)
//    {
//        printf("\n*TG014_4: Can't turn off CMT Channel: %d\r\n", 3);
//    }
//    else
//    {
//        printf("\n*TG014_4: Power off CMT Channel: %d\r\n", 3);
//    }
//
//    TEST_ASSERT_TRUE(ret);
//
//    TEST_ASSERT_EQUAL(CMT.CMSTR1.BIT.STR3, 0);
//    TEST_ASSERT_EQUAL(MSTP(CMT3), 0);
//}
/***********************************************************************************************************************
End of function power_off_Test_TG014_4
***********************************************************************************************************************/
//#####################################################################################################################

TEST_GROUP(R_CMT_CreatePeriodicAssignChannelPriority_Test);

TEST_SETUP(R_CMT_CreatePeriodicAssignChannelPriority_Test)
{

}

TEST_TEAR_DOWN(R_CMT_CreatePeriodicAssignChannelPriority_Test)
{
    printf("-------------------------------------------\r\n");
}

TEST(R_CMT_CreatePeriodicAssignChannelPriority_Test, TG015_1)
{
    printf("\n*TG015_1...");
    bool ret;
    uint32_t frequency_hz = 100;
    uint32_t channel = 0;
    cmt_priority_t priority =  (cmt_priority_t)(CMT_PRIORITY_0 - 1);

    ret = R_CMT_CreatePeriodicAssignChannelPriority(frequency_hz, cmt_callback, channel, priority);
    TEST_ASSERT_EQUAL(false, ret);

    printf("OK\n");
}

TEST(R_CMT_CreatePeriodicAssignChannelPriority_Test, TG015_2)
{
    printf("\n*TG015_2...");
    bool ret;
    uint32_t frequency_hz = 100;
    uint32_t channel = 0;
    cmt_priority_t priority =  (cmt_priority_t)(CMT_PRIORITY_MAX + 1);

    ret = R_CMT_CreatePeriodicAssignChannelPriority(frequency_hz, cmt_callback, channel, priority);
    TEST_ASSERT_EQUAL(false, ret);

    printf("OK\n");
}

TEST(R_CMT_CreatePeriodicAssignChannelPriority_Test, TG015_3)
{
    printf("\n*TG015_3...");
    bool ret;
    uint32_t frequency_hz = 100;
    uint32_t channel = 4;
    cmt_priority_t priority =  CMT_PRIORITY_7;

    ret = R_CMT_CreatePeriodicAssignChannelPriority(frequency_hz, cmt_callback, channel, priority);
    TEST_ASSERT_EQUAL(false, ret);

    printf("OK\n");
}

TEST(R_CMT_CreatePeriodicAssignChannelPriority_Test, TG015_4)
{
    printf("\n*TG015_4...");
    bool ret;
    uint32_t frequency_hz = 100;
    uint32_t channel = 0;
    cmt_priority_t priority =  CMT_PRIORITY_7;
    R_BSP_HardwareLock(BSP_LOCK_CMT);

    ret = R_CMT_CreatePeriodicAssignChannelPriority(frequency_hz, cmt_callback, channel, priority);
    TEST_ASSERT_EQUAL(false, ret);

    R_BSP_HardwareUnlock(BSP_LOCK_CMT);
    printf("OK\n");
}

TEST(R_CMT_CreatePeriodicAssignChannelPriority_Test, TG015_5)
{
    printf("\n*TG015_5...");
    bool ret;
    uint32_t frequency_hz = 100;
    uint32_t channel = 0;
    cmt_priority_t priority =  CMT_PRIORITY_7;
    R_BSP_HardwareLock(BSP_LOCK_CMT0);

    ret = R_CMT_CreatePeriodicAssignChannelPriority(frequency_hz, cmt_callback, channel, priority);
    TEST_ASSERT_EQUAL(false, ret);

    R_BSP_HardwareUnlock(BSP_LOCK_CMT0);
    printf("OK\n");
}

TEST(R_CMT_CreatePeriodicAssignChannelPriority_Test, TG015_6)
{
    printf("\n*TG015_6...");
    bool ret;
    uint32_t frequency_hz = (uint32_t)((BSP_PCLKB_HZ / 8) + 10);
    uint32_t channel = 0;
    cmt_priority_t priority =  CMT_PRIORITY_7;

    ret = R_CMT_CreatePeriodicAssignChannelPriority(frequency_hz, cmt_callback, channel, priority);
    TEST_ASSERT_EQUAL(false, ret);

    printf("OK\n");
}

TEST(R_CMT_CreatePeriodicAssignChannelPriority_Test, TG015_7)
{
    printf("\n*TG015_7...");
    bool ret;
    uint32_t frequency_hz = 100;
    uint32_t channel = 0;
    cmt_priority_t priority =  CMT_PRIORITY_7;

    ret = R_CMT_CreatePeriodicAssignChannelPriority(frequency_hz, cmt_callback, channel, priority);
    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(0, IR(CMT0, CMI0));
    TEST_ASSERT_EQUAL(priority, IPR(CMT0, CMI0));
    TEST_ASSERT_EQUAL(1, IEN(CMT0, CMI0));
    TEST_ASSERT_EQUAL(1, CMT.CMSTR0.BIT.STR0);

    printf("OK\n");
    R_CMT_Stop(channel);
}

TEST(R_CMT_CreatePeriodicAssignChannelPriority_Test, TG015_8)
{
    printf("\n*TG015_8...");
    bool ret;
    uint32_t frequency_hz = 100;
    uint32_t channel = 1;
    cmt_priority_t priority =  CMT_PRIORITY_7;

    ret = R_CMT_CreatePeriodicAssignChannelPriority(frequency_hz, cmt_callback, channel, priority);
    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(0, IR(CMT1, CMI1));
    TEST_ASSERT_EQUAL(priority, IPR(CMT1, CMI1));
    TEST_ASSERT_EQUAL(1, IEN(CMT1, CMI1));
    TEST_ASSERT_EQUAL(1, CMT.CMSTR0.BIT.STR1);

    printf("OK\n");
    R_CMT_Stop(channel);
}

//TEST(R_CMT_CreatePeriodicAssignChannelPriority_Test, TG015_9)
//{
//    printf("\n*TG015_9...");
//    bool ret;
//    uint32_t frequency_hz = 100;
//    uint32_t channel = 2;
//    cmt_priority_t priority =  CMT_PRIORITY_7;
//
//    ret = R_CMT_CreatePeriodicAssignChannelPriority(frequency_hz, cmt_callback, channel, priority);
//    TEST_ASSERT_EQUAL(true, ret);
//    TEST_ASSERT_EQUAL(0, IR(CMT2, CMI2));
//    TEST_ASSERT_EQUAL(priority, IPR(CMT2, CMI2));
//    TEST_ASSERT_EQUAL(1, IEN(CMT2, CMI2));
//    TEST_ASSERT_EQUAL(1, CMT.CMSTR1.BIT.STR2);
//
//    printf("OK\n");
//    R_CMT_Stop(channel);
//}

//TEST(R_CMT_CreatePeriodicAssignChannelPriority_Test, TG015_10)
//{
//    printf("\n*TG015_10...");
//    bool ret;
//    uint32_t frequency_hz = 100;
//    uint32_t channel = 3;
//    cmt_priority_t priority =  CMT_PRIORITY_7;
//
//    ret = R_CMT_CreatePeriodicAssignChannelPriority(frequency_hz, cmt_callback, channel, priority);
//    TEST_ASSERT_EQUAL(true, ret);
//    TEST_ASSERT_EQUAL(0, IR(CMT3, CMI3));
//    TEST_ASSERT_EQUAL(priority, IPR(CMT3, CMI3));
//    TEST_ASSERT_EQUAL(1, IEN(CMT3, CMI3));
//    TEST_ASSERT_EQUAL(1, CMT.CMSTR1.BIT.STR3);
//
//    printf("OK\n");
//    R_CMT_Stop(channel);
//}

//#####################################################################################################################

TEST_GROUP(R_CMT_CreateOneShotAssignChannelPriority_Test);

TEST_SETUP(R_CMT_CreateOneShotAssignChannelPriority_Test)
{

}

TEST_TEAR_DOWN(R_CMT_CreateOneShotAssignChannelPriority_Test)
{
    printf("-------------------------------------------\r\n");
}

TEST(R_CMT_CreateOneShotAssignChannelPriority_Test, TG016_1)
{
    printf("\n*TG016_1...");
    bool ret;
    uint32_t period_us = 10000;
    uint32_t channel = 0;
    cmt_priority_t priority =  (cmt_priority_t)(CMT_PRIORITY_0 - 1);

    ret = R_CMT_CreateOneShotAssignChannelPriority(period_us, cmt_callback, channel, priority);
    TEST_ASSERT_EQUAL(false, ret);

    printf("OK\n");
}

TEST(R_CMT_CreateOneShotAssignChannelPriority_Test, TG016_2)
{
    printf("\n*TG016_2...");
    bool ret;
    uint32_t period_us = 10000;
    uint32_t channel = 0;
    cmt_priority_t priority =  (cmt_priority_t)(CMT_PRIORITY_MAX + 1);

    ret = R_CMT_CreateOneShotAssignChannelPriority(period_us, cmt_callback, channel, priority);
    TEST_ASSERT_EQUAL(false, ret);

    printf("OK\n");
}

TEST(R_CMT_CreateOneShotAssignChannelPriority_Test, TG016_3)
{
    printf("\n*TG016_3...");
    bool ret;
    uint32_t period_us = 10000;
    uint32_t channel = 4;
    cmt_priority_t priority =  CMT_PRIORITY_7;

    ret = R_CMT_CreateOneShotAssignChannelPriority(period_us, cmt_callback, channel, priority);
    TEST_ASSERT_EQUAL(false, ret);

    printf("OK\n");
}

TEST(R_CMT_CreateOneShotAssignChannelPriority_Test, TG016_4)
{
    printf("\n*TG016_4...");
    bool ret;
    uint32_t period_us = 10000;
    uint32_t channel = 0;
    cmt_priority_t priority =  CMT_PRIORITY_7;
    R_BSP_HardwareLock(BSP_LOCK_CMT);

    ret = R_CMT_CreateOneShotAssignChannelPriority(period_us, cmt_callback, channel, priority);
    TEST_ASSERT_EQUAL(false, ret);

    R_BSP_HardwareUnlock(BSP_LOCK_CMT);
    printf("OK\n");
}

TEST(R_CMT_CreateOneShotAssignChannelPriority_Test, TG016_5)
{
    printf("\n*TG016_5...");
    bool ret;
    uint32_t period_us = 10000;
    uint32_t channel = 0;
    cmt_priority_t priority =  CMT_PRIORITY_7;
    R_BSP_HardwareLock(BSP_LOCK_CMT0);

    ret = R_CMT_CreateOneShotAssignChannelPriority(period_us, cmt_callback, channel, priority);
    TEST_ASSERT_EQUAL(false, ret);

    R_BSP_HardwareUnlock(BSP_LOCK_CMT0);
    printf("OK\n");
}

TEST(R_CMT_CreateOneShotAssignChannelPriority_Test, TG016_6)
{
    printf("\n*TG016_6...");
    bool ret;
    uint32_t period_us = 10000;
    uint32_t channel = 0;
    cmt_priority_t priority =  CMT_PRIORITY_7;

    ret = R_CMT_CreateOneShotAssignChannelPriority(period_us, cmt_callback, channel, priority);
    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(0, IR(CMT0, CMI0));
    TEST_ASSERT_EQUAL(priority, IPR(CMT0, CMI0));
    TEST_ASSERT_EQUAL(1, IEN(CMT0, CMI0));
    TEST_ASSERT_EQUAL(1, CMT.CMSTR0.BIT.STR0);

    printf("OK\n");
    R_CMT_Stop(channel);
}

TEST(R_CMT_CreateOneShotAssignChannelPriority_Test, TG016_7)
{
    printf("\n*TG016_7...");
    bool ret;
    uint32_t period_us = 10000;
    uint32_t channel = 1;
    cmt_priority_t priority =  CMT_PRIORITY_7;

    ret = R_CMT_CreateOneShotAssignChannelPriority(period_us, cmt_callback, channel, priority);
    TEST_ASSERT_EQUAL(true, ret);
    TEST_ASSERT_EQUAL(0, IR(CMT1, CMI1));
    TEST_ASSERT_EQUAL(priority, IPR(CMT1, CMI1));
    TEST_ASSERT_EQUAL(1, IEN(CMT1, CMI1));
    TEST_ASSERT_EQUAL(1, CMT.CMSTR0.BIT.STR1);

    printf("OK\n");
    R_CMT_Stop(channel);
}

//TEST(R_CMT_CreateOneShotAssignChannelPriority_Test, TG016_8)
//{
//    printf("\n*TG016_8...");
//    bool ret;
//    uint32_t period_us = 10000;
//    uint32_t channel = 2;
//    cmt_priority_t priority =  CMT_PRIORITY_7;
//
//    ret = R_CMT_CreateOneShotAssignChannelPriority(period_us, cmt_callback, channel, priority);
//    TEST_ASSERT_EQUAL(true, ret);
//    TEST_ASSERT_EQUAL(0, IR(CMT2, CMI2));
//    TEST_ASSERT_EQUAL(priority, IPR(CMT2, CMI2));
//    TEST_ASSERT_EQUAL(1, IEN(CMT2, CMI2));
//    TEST_ASSERT_EQUAL(1, CMT.CMSTR1.BIT.STR2);
//
//    printf("OK\n");
//    R_CMT_Stop(channel);
//}

//TEST(R_CMT_CreateOneShotAssignChannelPriority_Test, TG016_9)
//{
//    printf("\n*TG016_9...");
//    bool ret;
//    uint32_t period_us = 10000;
//    uint32_t channel = 3;
//    cmt_priority_t priority =  CMT_PRIORITY_7;
//
//    ret = R_CMT_CreateOneShotAssignChannelPriority(period_us, cmt_callback, channel, priority);
//    TEST_ASSERT_EQUAL(true, ret);
//    TEST_ASSERT_EQUAL(0, IR(CMT3, CMI3));
//    TEST_ASSERT_EQUAL(priority, IPR(CMT3, CMI3));
//    TEST_ASSERT_EQUAL(1, IEN(CMT3, CMI3));
//    TEST_ASSERT_EQUAL(1, CMT.CMSTR1.BIT.STR3);
//
//    printf("OK\n");
//    R_CMT_Stop(channel);
//}

//#####################################################################################################################

/******************************************************************************
* Function Name : cmt_callbacks
* Description   : This is the callback function for R_CMT_CreatePeriodic_TestGroup1()
*                   that was assigned to the CMT driver in main. It is called by
*                   all the CMT driver at a 10 Hz rate and toggles LED0,1,2,3 with each call
*                   generating 10Hz blink rate.
* Arguments     : pdata - pointer to void
* Return value  : none
*******************************************************************************/
void cmt_callback(void *pdata)
{
    uint32_t channel_num;

    /* This is an example of how to dereference the channel number when more than
     * one channel is used.  Channel numbers can be 0 to 3. */
    channel_num = *((uint32_t *)pdata);
    switch(channel_num)
    {
    case 0:
        printf("Start Timer0!\n");
        break;

    case 1:
        printf("Start Timer1!\n");
        break;

//    case 2:
//        printf("Start Timer2!\n");
//        break;
//
//    case 3:
//        printf("Start Timer3!\n");
//        break;

    default:
        printf("Timer channels are busy!\n");
        break;
    }
}
/***********************************************************************************************************************
End of function cmt_callback
***********************************************************************************************************************/

static void stop_all_channel()
{
    R_CMT_Stop(0);
    R_CMT_Stop(1);
//    R_CMT_Stop(2);
//    R_CMT_Stop(3);
}

