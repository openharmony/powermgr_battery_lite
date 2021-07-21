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

#include <iproxy_server.h>
#include <iunknown.h>
#include "feature.h"
#include "samgr_lite.h"
#include "battery_info.h"
#include "battery_client.h"
#include "hilog_wrapper.h"
#include "string"
#include "battery_manage_service.h"

namespace OHOS {

namespace {
static const int BATTERY_ERROR = -1;
static const int BATTERY_SUCCESS = 0;
}

BatteryClient::BatteryClient():batteryInterface(NULL){}

BatteryClient::~BatteryClient()
{
    if (batteryInterface != NULL) {
        batteryInterface = NULL;
    }
}

BatteryInterface *BatteryClient::ChargingApiGet(void)
{
    if (batteryInterface != NULL) {
        return batteryInterface;
    }
    
    IUnknown *iUnknown = SAMGR_GetInstance()->GetFeatureApi(BATTERY_SERVICE ,BATTERY_INNER);
    if (iUnknown == NULL) {
        return NULL;
    }

    int ret = iUnknown->QueryInterface(iUnknown, DEFAULT_VERSION, (void **)(&batteryInterface));
    if (ret != BATTERY_SUCCESS) {
        return NULL;
    }

    return batteryInterface;
}

const uint32_t BatteryClient::GetBatSoc()
{
    batteryInterface = ChargingApiGet();
    if (batteryInterface == NULL) {
        return BATTERY_ERROR;
    }

    return batteryInterface->BatterySOC();
}

const BatteryChargeState BatteryClient::GetChargingStatus()
{
    batteryInterface = ChargingApiGet();
    if (batteryInterface == NULL) {
        return CHARGE_STATE_NONE;
    }

    return batteryInterface->ChargingStatus();
}

const BatteryHealthState BatteryClient::GetHealthStatus()
{
    batteryInterface = ChargingApiGet();
    if (batteryInterface == NULL) {
        return HEALTH_STATE_UNKNOWN;
    }

    return batteryInterface->HealthStatus();
}

const BatteryPluggedType BatteryClient::GetPluggedType()
{
    batteryInterface = ChargingApiGet();
    if (batteryInterface == NULL) {
        return PLUGGED_TYPE_NONE;
    }

    return batteryInterface->PluggedType();
}

const uint32_t BatteryClient::GetBatVoltage()
{
    batteryInterface = ChargingApiGet();
    if (batteryInterface == NULL) {
        return BATTERY_ERROR;
    }

    return batteryInterface->Voltage();
}

const std::string BatteryClient::GetBatTechnology()
{
    std::string str;
    batteryInterface = ChargingApiGet();
    if (batteryInterface == NULL) {
        return str;
    }

    return batteryInterface->Technology();
}

const uint32_t BatteryClient::GetBatTemperature()
{
    batteryInterface = ChargingApiGet();
    if (batteryInterface == NULL) {
        return BATTERY_ERROR;
    }

    return batteryInterface->BatteryTemperature();
}
}