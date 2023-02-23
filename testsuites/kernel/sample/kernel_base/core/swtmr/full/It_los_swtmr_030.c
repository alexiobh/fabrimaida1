/*
 * Copyright (c) 2013-2019 Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "It_los_swtmr.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
static VOID SwtmrF01(UINT32 arg)
{
    ICUNIT_ASSERT_EQUAL_VOID(g_testCount, 1, g_testCount);
    LOS_AtomicInc(&g_testCount);
}

static VOID SwtmrF02(UINT32 arg)
{
    LOS_AtomicInc(&g_testCount);
}

static UINT32 Testcase(VOID)
{
    UINT32 ret;
    UINT16 swTmrID1;
    UINT16 swTmrID2;
    int value;
    g_testCount = 0;

    // 10, Timeout interval of a periodic software timer.
    ret = LOS_SwtmrCreate(10, LOS_SWTMR_MODE_PERIOD, (SWTMR_PROC_FUNC)SwtmrF02, &swTmrID1, 0xffff);
    ICUNIT_ASSERT_EQUAL(ret, LOS_OK, ret);

    // 10, Timeout interval of a periodic software timer.
    ret = LOS_SwtmrCreate(10, LOS_SWTMR_MODE_ONCE, (SWTMR_PROC_FUNC)SwtmrF01, &swTmrID2, 0xffff);
    ICUNIT_ASSERT_EQUAL(ret, LOS_OK, ret);

    ret = LOS_SwtmrStart(swTmrID1);
    ICUNIT_ASSERT_EQUAL(ret, LOS_OK, ret);

    ret = LOS_SwtmrStart(swTmrID2);
    ICUNIT_ASSERT_EQUAL(ret, LOS_OK, ret);
    HAL_READ_UINT32(&g_testCount, value);
    while (value < 4) { // 4, if value < 4, to do
        HAL_READ_UINT32(&g_testCount, value);
    }

    ret = LOS_SwtmrDelete(swTmrID1);
    ICUNIT_ASSERT_EQUAL(ret, LOS_OK, ret);

    return LOS_OK;
}

VOID ItLosSwtmr030(VOID) // IT_Layer_ModuleORFeature_No
{
    TEST_ADD_CASE("ItLosSwtmr030", Testcase, TEST_LOS, TEST_SWTMR, TEST_LEVEL2, TEST_FUNCTION);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

