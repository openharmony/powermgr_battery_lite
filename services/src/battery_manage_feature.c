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

#include <feature.h>
#include <ohos_init.h>
#include <samgr_lite.h>
#include "ibattery.h"
#include "hilog_wrapper.h"
#include "battery_manage_feature.h"
#include "battery_device.h"

static const int BATT_ERROR = -1;
static const int BATT_INT_VALUE = 0;
static const int BS_INVOKE_SUCCESS = 1;


typedef int32 (*InvokeFunc)(const void *origin, IpcIo *req);
static InvokeFunc invokeFuncList[4];


const char *GetFeatureName(Feature *feature);
void OnFeatureStop(Feature *feature, Identity identity);
BOOL OnFeatureMessage(Feature *feature, Request *request);
void OnFeatureInitialize(Feature *feature, Service *parent, Identity identity);

uint16 BatterySOCImpl()
{
    uint16 soc = BATT_INT_VALUE;
    g_batteryDevice = NewBatterInterfaceInstance();
    if (g_batteryDevice == NULL) {
        POWER_HILOGI("BatteryService::BatterySOCImpl error.");
        return soc;
    }
    soc = g_batteryDevice->GetSoc();
    POWER_HILOGI("BatteryService::BatterySOCImpl ok.");
    return soc;
}
BatteryChargeState ChargingStatusImpl()
{
    BatteryChargeState chargingstate = CHARGE_STATE_BUTT;
    g_batteryDevice = NewBatterInterfaceInstance();
    if (g_batteryDevice == NULL) {
        POWER_HILOGI("BatteryService::ChargingStatusImpl error.");
        return chargingstate;
    }
    chargingstate = g_batteryDevice->GetChargingStatus();
    POWER_HILOGI("BatteryService::ChargingStatusImpl ok.");
    return chargingstate;
}
BatteryHealthState HealthStatusImpl()
{
    BatteryHealthState healthState = HEALTH_STATE_BUTT;
    g_batteryDevice = NewBatterInterfaceInstance();
    if (g_batteryDevice == NULL) {
        POWER_HILOGI("BatteryService::HealthStatus error.");
        return healthState;
    }
    healthState = g_batteryDevice->GetHealthStatus();
    POWER_HILOGI("BatteryService::HealthStatus ok.");
    return healthState;
}
BatteryPluggedType PluggedTypeImpl()
{
    BatteryPluggedType pluggedType = PLUGGED_TYPE_BUTT;
    g_batteryDevice = NewBatterInterfaceInstance();
    if (g_batteryDevice == NULL) {
        POWER_HILOGI("BatteryService::PluggedType error.");
        return pluggedType;
    }
    pluggedType = g_batteryDevice->GetPluggedType();
    POWER_HILOGI("BatteryService::PluggedType ok.");
    return pluggedType;
}
uint16 VoltageImpl()
{
    uint16 voltage = BATT_INT_VALUE;
    g_batteryDevice = NewBatterInterfaceInstance();
    if (g_batteryDevice == NULL) {
        POWER_HILOGI("NewBatterInterfaceInstance():g_BatterDevice is NULL");
    }

    if (g_batteryDevice == NULL) {
        POWER_HILOGI("BatteryService::Voltage error.");
        return voltage;
    }
    voltage = g_batteryDevice->GetVoltage();
    POWER_HILOGI("BatteryService::Voltage ok.");
    return voltage;
}
char* TechnologyImpl()
{
    char* technology = NULL;
    g_batteryDevice = NewBatterInterfaceInstance();
     if (g_batteryDevice == NULL) {
        POWER_HILOGI("NewBatterInterfaceInstance():g_BatterDevice is NULL");
    }

    if (g_batteryDevice == NULL) {
        POWER_HILOGI("BatteryService::Technology error.");
        return technology;
    }
    technology = g_batteryDevice->GetTechnology();
    POWER_HILOGI("BatteryService::Technology ok.");
    return technology;
}
uint16 BatteryTemperatureImpl()
{
    uint16 temperature = BATT_INT_VALUE;
    g_batteryDevice = NewBatterInterfaceInstance();
     if (g_batteryDevice == NULL) {
        POWER_HILOGI("NewBatterInterfaceInstance():g_BatterDevice is NULL");
    }

    if (g_batteryDevice == NULL) {
        POWER_HILOGI("BatteryService::BatteryTemperature error.");
        return temperature;
    }
    temperature = g_batteryDevice->GetTemperature();
    POWER_HILOGI("BatteryService::BatteryTemperature ok.");
    return temperature;
}

int32 Invoke(IServerProxy *iProxy, int funcId, void *origin, IpcIo *req, IpcIo *reply)
{
    POWER_HILOGI("IPC Invoke called.");
}



static BatteryServiceApi g_battserviceImpl = {
    .GetName = GetFeatureName,
    .OnInitialize = OnFeatureInitialize,
    .OnStop = OnFeatureStop,
    .OnMessage = OnFeatureMessage,
    DEFAULT_IUNKNOWN_ENTRY_BEGIN,
    .BatterySOC = BatterySOCImpl,
    .ChargingStatus = ChargingStatusImpl,
    .HealthStatus = HealthStatusImpl,
    .PluggedType = PluggedTypeImpl,
    .Voltage = VoltageImpl,
    .Technology = TechnologyImpl,
    .BatteryTemperature = BatteryTemperatureImpl,
    DEFAULT_IUNKNOWN_ENTRY_END,
    .identity_ = { -1, -1, NULL },
};


const char *GetFeatureName(Feature *feature)
{
    POWER_HILOGI("BatteryServiceFeature::GetFeatureName called.");
    return BATTERY_INNER;
}

void OnFeatureStop(Feature *feature, Identity identity)
{
    POWER_HILOGI("BatteryServiceFeature::OnFeatureStop called.");
    (void)feature;
    (void)identity;
}

BOOL OnFeatureMessage(Feature *feature, Request *request)
{
    POWER_HILOGI("BatteryServiceFeature::OnFeatureMessage called.");
    return ((feature != NULL) && (request != NULL));
}

void OnFeatureInitialize(Feature *feature, Service *parent, Identity identity)
{
    g_battserviceImpl.identity_ = identity;
    POWER_HILOGI("BatteryServiceFeature::OnFeatureInitialize called.");
}

static void GInit()
{
    POWER_HILOGI("SYS_FEATURE_INIT called.");
    BOOL result = SAMGR_GetInstance()->RegisterFeature(BATTERY_SERVICE, (Feature *)&g_battserviceImpl);
    if (result == FALSE) {
        POWER_HILOGI("RegisterFeature failed.");
        return;
    }
    BOOL apiResult = SAMGR_GetInstance()->RegisterFeatureApi(BATTERY_SERVICE, BATTERY_INNER, GET_IUNKNOWN(g_battserviceImpl));
    if (apiResult == FALSE) {
        POWER_HILOGI("RegisterFeatureApi failed.");
        return;
    }

    //BatteryFeatureTimeerInit();
    POWER_HILOGI("SAMGR_GetInstance()->RegisterFeature ok...");
    POWER_HILOGI("SAMGR_GetInstance()->RegisterFeatureApi ok...");

}
SYSEX_FEATURE_INIT(GInit);