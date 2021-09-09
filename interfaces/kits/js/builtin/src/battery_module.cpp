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
#include "hilog_wrapper.h"

namespace OHOS {
namespace ACELite {
namespace {

/*
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
*/


void SuccessCallBack(const JSIValue thisVal, const JSIValue args, JSIValue jsiValue)
{
    if (JSI::ValueIsUndefined(args)) {
        return;
    }
    JSIValue success = JSI::GetNamedProperty(args, CB_SUCCESS);
    JSIValue complete = JSI::GetNamedProperty(args, CB_COMPLETE);
    if (!JSI::ValueIsUndefined(success)) {
        if (JSI::ValueIsUndefined(jsiValue)) {
            JSI::CallFunction(success, thisVal, nullptr, 0);
        } else {
            JSI::CallFunction(success, thisVal, &jsiValue, ARGC_ONE);
        }
    }
    if (!JSI::ValueIsUndefined(complete)) {
        JSI::CallFunction(complete, thisVal, nullptr, 0);
    }
    JSI::ReleaseValueList(success, complete, ARGS_END);
}



static JSIValue BatterySOC(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if ((args == nullptr) || (argsNum == 0) || JSI::ValueIsUndefined(args[0])) {
        return undefValue;
    }

    int32_t batterysoc = 0;
    batterysoc = GetBatSocImpl();
    JSIValue result = JSI::CreateObject();
    JSI::SetNumberProperty(result, "batterysoc", batterysoc);
    SuccessCallBack(thisVal, args[0], result);
    JSI::ReleaseValue(result);
    return undefValue;


    //return JSI::CreateNumber(GetChargingStatusImpl());
}
/*
static JSIValue GetChargingState(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    int32_t value = GetChargingStatusImpl();
    return (value < BatteryChargeState::CHARGE_STATE_NONE 
    || value > BatteryChargeState::CHARGE_STATE_BUTT) ? JSI::CreateUndefined() : JSI::CreateString(g_chargingState[value]);
}
*/
static JSIValue GetChargingState(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    int32_t value = GetChargingStatusImpl();
    return (value < BatteryChargeState::CHARGE_STATE_NONE 
    || value > BatteryChargeState::CHARGE_STATE_BUTT) ? JSI::CreateUndefined() : JSI::CreateNumber(GetChargingStatusImpl());
}
/*
static JSIValue GetHealthState(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    int32_t value = GetHealthStatusImpl();
    return (value < BatteryHealthState::HEALTH_STATE_UNKNOWN 
    || value > BatteryHealthState::HEALTH_STATE_BUTT) ? JSI::CreateUndefined() : JSI::CreateString(g_healthState[value]);
}
*/
static JSIValue GetHealthState(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    int32_t value = GetHealthStatusImpl();
    return (value < BatteryHealthState::HEALTH_STATE_UNKNOWN 
    || value > BatteryHealthState::HEALTH_STATE_BUTT) ? JSI::CreateUndefined() : JSI::CreateNumber(GetHealthStatusImpl());
}
/*
static JSIValue GetPluggedType(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    int32_t value = GetPluggedTypeImpl();
    return (value < BatteryPluggedType::PLUGGED_TYPE_NONE 
    || value > BatteryPluggedType::PLUGGED_TYPE_BUTT) ? JSI::CreateUndefined() : JSI::CreateString(g_pluggedType[value]);
    //return JSI::CreateNumber(GetPluggedTypeImpl());
}
*/
static JSIValue GetPluggedType(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    int32_t value = GetPluggedTypeImpl();
    return (value < BatteryPluggedType::PLUGGED_TYPE_NONE 
    || value > BatteryPluggedType::PLUGGED_TYPE_BUTT) ? JSI::CreateUndefined() : JSI::CreateNumber(GetPluggedTypeImpl());
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
    POWER_HILOGE("InitBatteryModule start");
    JSI::SetModuleAPI(exports, "batterySOC", BatteryModule::BatterySOC);
    JSI::SetModuleAPI(exports, "chargingStatus", BatteryModule::GetChargingState);
    JSI::SetModuleAPI(exports, "healthStatus", BatteryModule::GetHealthState);
    JSI::SetModuleAPI(exports, "pluggedType", BatteryModule::GetPluggedType);
    JSI::SetModuleAPI(exports, "voltage", BatteryModule::GetVoltage);
    JSI::SetModuleAPI(exports, "technology", BatteryModule::GetTechnology);
    JSI::SetModuleAPI(exports, "batteryTemperature", BatteryModule::GetBatteryTemperature);
    POWER_HILOGE("InitBatteryModule end");
}

}
} // ACELite
} // OHOS

