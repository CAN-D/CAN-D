#include "can.h"
#include <cgreen/cgreen.h>

extern hcan;

Describe(can);
BeforeEach(can)
{
    APP_CAN_Init();
    APP_CAN_InitTasks();
    HAL_CAN_MspInit(hcan);
}
AfterEach(can)
{
    HAL_CAN_MspDeInit(hcan);
}

Ensure(can, canConfigure)
{
    APP_ConfigType config = {
        .SDStorage = Enable,
        .USBStream = Enable,
        .USBTransfer = Enable,
        .CANTransmit = Enable
    } APP_CAN_SetConfiguration(config);
    assert_that(mAppConfiguration.SDStorage, is_equal_to(Enable));
    assert_that(mAppConfiguration.USBStream, is_equal_to(Enable));
    assert_that(mAppConfiguration.USBTransfer, is_equal_to(Enable));
    assert_that(mAppConfiguration.CANTransmit, is_equal_to(Enable));
}

Ensure(can, dataCanBeBuffered)
{
    uint8_t txData[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    CAN_TxHeaderTypeDef header = {
        .StdId = 1,
        .ExtId = 1,
        .IDE = CAN_ID_STD,
        .RTR = CAN_RTR_DATA,
        .DLC = 8,
        .TransmitGlobalTime = DISABLE
    };
    APP_CAN_TransmitData(txData, header);
    event = osMessageGet(CANTxQueueHandle, 0);
    assert_that(event.status, is_equal_to(osEventMessage));
    osDelay(5000);
}

Ensure(can, canToggleOn)
{
    APP_CAN_StartStop();
    assert_that(hcan.State, is_equal_to(HAL_CAN_STATE_LISTENING));
}

Ensure(can, canToggleOff)
{
    APP_CAN_StartStop();
    APP_CAN_StartStop();
    assert_that(hcan.State, is_equal_to(HAL_CAN_STATE_READY));
}

TestSuite* can_tests()
{
    TestSuite* suite = create_test_suite();
    add_test_with_context(suite, can, dataCanBeBuffered);
    add_test_with_context(suite, can, canConfigure);
    add_test_with_context(suite, can, canToggleOn);
    add_test_with_context(suite, can, canToggleOff);
    return suite;
}

int main(int argc, char** argv)
{
    return run_test_suite(BufferData(), create_text_reporter());
}