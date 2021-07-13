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

const char *GetFeatureName(Feature *feature)
{
    (void)feature;
    return BATTERY_INNER;
}

void OnFeatureInitialize(Feature *feature, Service *parent, Identity identity)
{
    POWER_HILOGI("Init batterymgr feature done");
}

void OnFeatureStop(Feature *feature, Identity identity)
{
    (void)feature;
    (void)identity;
    POWER_HILOGI("Init batterymgr feature stop");
}

BOOL OnFeatureMessage(Feature *feature, Request *request)
{
    return ((feature != NULL) && (request != NULL)) ? TRUE : FALSE;
}



int32_t BatterySOCImpl(IUnknown *iUnknown)
{
    int32_t soc = BATT_INT_VALUE;
    g_batteryDevice = NewBatterInterfaceInstance();
    if (g_batteryDevice == NULL) {
        POWER_HILOGI("BatteryService::BatterySOCImpl error.");
        return soc;
    }
    soc = g_batteryDevice->GetSoc();
    POWER_HILOGI("BatteryService::BatterySOCImpl ok.");
    return soc;
}
BatteryChargeState ChargingStatusImpl(IUnknown *iUnknown)
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
BatteryHealthState HealthStatusImpl(IUnknown *iUnknown)
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
BatteryPluggedType PluggedTypeImpl(IUnknown *iUnknown)
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
int32_t VoltageImpl(IUnknown *iUnknown)
{
    int32_t voltage = BATT_INT_VALUE;
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
char* TechnologyImpl(IUnknown *iUnknown)
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
int32_t BatteryTemperatureImpl(IUnknown *iUnknown)
{
    int32_t temperature = BATT_INT_VALUE;
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



static void GInit()
{

    BatteryFeatureApi *feature = GetBatteryFeatureImpl();
	if(feature == NULL) {
		POWER_HILOGI("SYS_FEATURE_INIT called err. g_battFeatureImpl");
		return;
	}

    POWER_HILOGI("SYS_FEATURE_INIT called.");
    BOOL result = SAMGR_GetInstance()->RegisterFeature(BATTERY_SERVICE, (Feature *)feature);
    if (result == FALSE) {
        POWER_HILOGI("RegisterFeature failed.");
        return;
    }
    BOOL apiResult = SAMGR_GetInstance()->RegisterFeatureApi(BATTERY_SERVICE, BATTERY_INNER, GET_IUNKNOWN(*feature));
    if (apiResult == FALSE) {
        POWER_HILOGI("RegisterFeatureApi failed.");
        return;
    }


    POWER_HILOGI("SAMGR_GetInstance()->RegisterFeature ok...");
    POWER_HILOGI("SAMGR_GetInstance()->RegisterFeatureApi ok...");

}
SYSEX_FEATURE_INIT(GInit);