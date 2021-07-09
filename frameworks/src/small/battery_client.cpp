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
        POWER_HILOGE("[SERVICE:%s]:BatteryClient::ChargingApiGet iUnknown is null",BATTERY_SERVICE);
        return NULL;
    }

    int ret = iUnknown->QueryInterface(iUnknown, DEFAULT_VERSION, (void **)(&batteryInterface));
    if (ret != BATTERY_SUCCESS) {
        POWER_HILOGE("[SERVICE:%s]:BatteryClient::ChargingApiGet api is null",BATTERY_SERVICE);
        return NULL;
    }
    POWER_HILOGE("[SERVICE:%s]:BatteryClient::ChargingApiGet(void):start",BATTERY_SERVICE);

    return batteryInterface;
}

const uint16 BatteryClient::GetBatSoc()
{
    batteryInterface = ChargingApiGet();
    if (batteryInterface == NULL) {
        POWER_HILOGE("[SERVICE:%s]:BatteryClient::GetBatterySOC():this->batteryInterface is NULL",BATTERY_SERVICE);
        return BATTERY_ERROR;
    }

    POWER_HILOGE("[SERVICE:%s]:BatteryClient::GetBatterySOC(void):start",BATTERY_SERVICE);
    POWER_HILOGE("[SERVICE:%s]:BatteryClient::GetBatterySOC(void)%d",BATTERY_SERVICE ,batteryInterface->BatterySOC());
    return batteryInterface->BatterySOC();
}

const BatteryChargeState BatteryClient::GetChargingStatus()
{
    batteryInterface = ChargingApiGet();
    if (batteryInterface == NULL) {
        POWER_HILOGE("[SERVICE:%s]:BatteryClient::GetChargingStatus():this->batteryInterface is NULL",BATTERY_SERVICE);
        return CHARGE_STATE_NONE;
    }
    POWER_HILOGE("[SERVICE:%s]:BatteryClient::GetChargingStatus(void):start",BATTERY_SERVICE);
    return batteryInterface->ChargingStatus();
}

const BatteryHealthState BatteryClient::GetHealthStatus()
{
    batteryInterface = ChargingApiGet();
    if (batteryInterface == NULL) {
        POWER_HILOGE("[SERVICE:%s]:BatteryClient::GetHealthStatus():this->batteryInterface is NULL",BATTERY_SERVICE);
        return HEALTH_STATE_UNKNOWN;
    }
    POWER_HILOGE("[SERVICE:%s]:BatteryClient::GetHealthStatus(void):start",BATTERY_SERVICE);
    return batteryInterface->HealthStatus();
}

const BatteryPluggedType BatteryClient::GetPluggedType()
{
    batteryInterface = ChargingApiGet();
    if (batteryInterface == NULL) {
        POWER_HILOGE("[SERVICE:%s]:BatteryClient::GetPluggedType():this->batteryInterface is NULL",BATTERY_SERVICE);
        return PLUGGED_TYPE_NONE;
    }
    POWER_HILOGE("[SERVICE:%s]:BatteryClient::GetPluggedType(void):start",BATTERY_SERVICE);
    return batteryInterface->PluggedType();
}

const uint16 BatteryClient::GetBatVoltage()
{
    batteryInterface = ChargingApiGet();
    if (batteryInterface == NULL) {
        POWER_HILOGE("[SERVICE:%s]:BatteryClient::GetVoltage():this->batteryInterface is NULL",BATTERY_SERVICE);
        return BATTERY_ERROR;
    }
    POWER_HILOGE("[SERVICE:%s]:BatteryClient::GetVoltage(void):start",BATTERY_SERVICE);
    POWER_HILOGE("[SERVICE:%s]:BatteryClient::GetVoltage(void)%d",BATTERY_SERVICE ,batteryInterface->Voltage());
    return batteryInterface->Voltage();
}

const std::string BatteryClient::GetBatTechnology()
{
    std::string str;
    batteryInterface = ChargingApiGet();
    if (batteryInterface == NULL) {
        POWER_HILOGE("[SERVICE:%s]:BatteryClient::GetTechnology():this->batteryInterface is NULL",BATTERY_SERVICE);
        return str;
    }
    POWER_HILOGE("[SERVICE:%s]:BatteryClient::GetTechnology(void):start",BATTERY_SERVICE);
    POWER_HILOGE("[SERVICE:%s]:BatteryClient::GetTechnology(void):%s",BATTERY_SERVICE ,batteryInterface->Technology());
    return batteryInterface->Technology();
}

const uint16 BatteryClient::GetBatTemperature()
{
    batteryInterface = ChargingApiGet();
    if (batteryInterface == NULL) {
        POWER_HILOGE("[SERVICE:%s]:BatteryClient::GetVoltage(void):start",BATTERY_SERVICE);
        return BATTERY_ERROR;
    }
    POWER_HILOGE("[SERVICE:%s]:BatteryClient::GetVoltage(void):start",BATTERY_SERVICE);
    POWER_HILOGE("[SERVICE:%s]:BatteryClient::GetBatteryTemperature(void):%d",BATTERY_SERVICE ,batteryInterface->BatteryTemperature());
    return batteryInterface->BatteryTemperature();
}
}