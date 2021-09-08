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

#include "battery_module.h"
#include "battery_impl.h"

namespace OHOS {
namespace ACELite {
namespace {


static char *g_chargingState[] = {
    "CHARGE_STATE_NONE", 
    "CHARGE_STATE_ENABLE", 
    "CHARGE_STATE_DISABLE", 
    "CHARGE_STATE_FULL",
    "CHARGE_STATE_BUTT"
};

static char *g_pluggedType[] = {
    "PLUGGED_TYPE_NONE", 
    "PLUGGED_TYPE_AC", 
    "PLUGGED_TYPE_USB", 
    "PLUGGED_TYPE_WIRELESS",
    "CHARGE_STATE_BUTT"
};
static char *g_healthState[] = {
    "HEALTH_STATE_UNKNOWN", 
    "HEALTH_STATE_GOOD", 
    "HEALTH_STATE_OVERHEAT", 
    "HEALTH_STATE_OVERVOLTAGE", 
    "HEALTH_STATE_COLD", 
    "HEALTH_STATE_DEAD",
    "CHARGE_STATE_BUTT"
};  

static JSIValue BatterySOC(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    return JSI::CreateNumber(GetChargingStatusImpl());
}
static JSIValue GetChargingState(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    int32_t value = GetChargingStatusImpl();
    return (value < BatteryChargeState::CHARGE_STATE_NONE 
    || value > BatteryChargeState::CHARGE_STATE_BUTT) ? JSI::CreateUndefined() : JSI::CreateString(g_chargingState[value]);
}
static JSIValue GetHealthState(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    int32_t value = GetHealthStatusImpl();
    return (value < BatteryHealthState::HEALTH_STATE_UNKNOWN 
    || value > BatteryHealthState::HEALTH_STATE_BUTT) ? JSI::CreateUndefined() : JSI::CreateString(g_healthState[value]);
}
static JSIValue GetPluggedType(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    int32_t value = GetPluggedTypeImpl();
    return (value < BatteryPluggedType::PLUGGED_TYPE_NONE 
    || value > BatteryPluggedType::PLUGGED_TYPE_BUTT) ? JSI::CreateUndefined() : JSI::CreateString(g_pluggedType[value]);
    //return JSI::CreateNumber(GetPluggedTypeImpl());
}
static JSIValue GetVoltage(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    return JSI::CreateNumber(GetBatVoltageImpl());
}
static JSIValue GetTechnology(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    char *src = GetBatTechnologyImpl();
    return (src == NULL) ? JSI::CreateUndefined() : JSI::CreateString(src);
}
static JSIValue GetBatteryTemperature(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    return JSI::CreateNumber(GetBatTemperatureImpl());
}

void InitBatteryModule(JSIValue exports)
{
    JSI::SetModuleAPI(exports, "getStatus", BatteryModule::BatterySOC);
    JSI::SetModuleAPI(exports, "batterySOC", BatteryModule::BatterySOC);
    JSI::SetModuleAPI(exports, "chargingStatus", BatteryModule::GetChargingState);
    JSI::SetModuleAPI(exports, "healthStatus", BatteryModule::GetHealthState);
    JSI::SetModuleAPI(exports, "pluggedType", BatteryModule::GetPluggedType);
    JSI::SetModuleAPI(exports, "voltage", BatteryModule::GetVoltage);
    JSI::SetModuleAPI(exports, "technology", BatteryModule::GetTechnology);
    JSI::SetModuleAPI(exports, "batteryTemperature", BatteryModule::GetBatteryTemperature);
}

}
} // ACELite
} // OHOS

