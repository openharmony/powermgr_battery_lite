/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ohos_init.h>
#include <samgr_lite.h>
#include <service.h>

#include <unistd.h>
#include <pthread.h>
#include "iunknown.h"
#include "ibattery.h"
#include "battery_manage_feature.h"
#include "battery_manage_service.h"
#include "battery_mgr.h"
#include "hilog_wrapper.h"
#include "iproxy_server.h"
#include "feature.h"
#include "power_mgr_time_util.h"
#include "power_mgr_timer_util.h"

#define BATTERY_STACK_SIZE      0x800
#define BATTERY_QUEUE_SIZE      20

typedef enum {
    /* add new msg */
    BATT_SRV_MSG_UPDATE,
    BATT_SRV_MSG_ID_MAX,
} BatteryServiceMsgID;

static int64_t DEFAULT_INTERVAL_MSECS = 5000;
static PowerTimer *time_ = NULL;
static BatInfo battpoint;

static void BatteryFeatureTimeerInit(void);
static BatteryService *BatteryGetInstance(void);

static BOOL Initialize(Service *service, Identity identity)
{

    POWER_HILOGI("BatteryInitialize begin");
    BatteryService *batterService = BatteryGetInstance();
    batterService->identity = identity;
    
    BatteryFeatureTimeerInit();
    return TRUE;
}

static const char *BatteryGetName(Service *service)
{
    POWER_HILOGI("BatteryGetName begin");
    return BATTERY_SERVICE;
}

void UpdateBatteryMsg(BatInfo* battery)
{
    POWER_HILOGI("UpdateBatteryMsg() start.");
    g_batteryDevice = NewBatterInterfaceInstance();
    if (g_batteryDevice == NULL) {
        POWER_HILOGI("UpdateBatteryMsg() error.");
        return;
    }
    g_batteryDevice->UpdateBatInfo(battery);
    POWER_HILOGI("UpdateBatteryMsg():succeed");
    return;
}

static BOOL MessageHandle(Service *service, Request *request)
{
    (void)service;
    if ((request == NULL) ||
        ((BatteryServiceMsgID)(request->msgId) >= BATT_SRV_MSG_ID_MAX)) {
        return false;
    }
    switch (request->msgId) {
        case BATT_SRV_MSG_UPDATE:
            UpdateBatteryMsg(&battpoint);
            break;
        default:
            break;
    }
    POWER_HILOGI("BatteryMessageHandle begin");
    return true;
}
static TaskConfig GetTaskConfig(Service *service)
{
    POWER_HILOGI("BatteryGetTaskConfig begin");
    TaskConfig config = {LEVEL_HIGH, PRI_BELOW_NORMAL, BATTERY_STACK_SIZE, BATTERY_QUEUE_SIZE, SHARED_TASK};
    return config;
}

static BatteryService g_batteryService = {
    .GetName = BatteryGetName,
    .Initialize = Initialize,
    .MessageHandle = MessageHandle,
    .GetTaskConfig = GetTaskConfig,
    { -1, -1, NULL },
};

static BatteryService *BatteryGetInstance(void)
{
    return &g_batteryService;
}

void BatteryMonitorHandle(void *arg)
{
    Request request = {
        .msgId = BATT_SRV_MSG_UPDATE,
        .data = NULL,
        .len = 0,
        .msgValue = 0
    };
    SAMGR_SendRequest(&(g_batteryService.identity),&request,NULL);
}

static void BatteryFeatureTimeerInit(void)
{
    if( time_ == NULL )
    {
        time_  =  PowerMgrCreateTimer(DEFAULT_INTERVAL_MSECS, DEFAULT_INTERVAL_MSECS , BatteryMonitorHandle);
        if (time_ == NULL) {
            POWER_HILOGI("BatteryFeatureTimeerInit failed.");
            return;
        }
        if (PowerMgrStartTimer(time_, NULL) == FALSE) {

            POWER_HILOGI("Failed to start timer.");
            return;
        }

        POWER_HILOGI("BatteryFeatureTimeerInit()...ok.");
    }
}

static void Init(void)
{
    POWER_HILOGI("Succeed to init battery manager service begin");
    BOOL result = SAMGR_GetInstance()->RegisterService((Service *)&g_batteryService);
    if (result == FALSE) {
        POWER_HILOGI("RegisterService failed.");
        return;
    }
    POWER_HILOGI("Succeed to init battery manager service");
    POWER_HILOGI("Succeed to init battery manager service end");
}
SYSEX_SERVICE_INIT(Init);