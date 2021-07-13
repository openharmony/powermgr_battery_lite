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

#include "battery_framework.h"
#include "battery_info.h"
#include <stdint.h>
#include <pthread.h>
#include "hilog_wrapper.h"
#include "battery_interface.h"
#include "ibattery.h"
#include "iunknown.h"


static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
static BatteryInterface *g_intf = NULL;


static BatteryInterface *GetBatteryInterface(void)
{
	if (g_intf != NULL) {
        return g_intf;
    }
    pthread_mutex_lock(&g_mutex);
    if (g_intf != NULL) {
        pthread_mutex_unlock(&g_mutex);
        return g_intf;
    }
	IUnknown *iUnknown = GetBatteryIUnknown();
    if (iUnknown == NULL) {
        POWER_HILOGE("Failed to get battery iUnknown");
        return NULL;
    }

    int ret = iUnknown->QueryInterface(iUnknown, DEFAULT_VERSION, (void **)&g_intf);
    if ((ret != EC_SUCCESS) || (g_intf == NULL)) {
        POWER_HILOGE("Failed to  get battery interface");
        pthread_mutex_unlock(&g_mutex);
        return NULL;
    }
    pthread_mutex_unlock(&g_mutex);

    return g_intf;
}

int32_t GetBatSoc()
{
	int32_t ret = EC_FAILURE;
    BatteryInterface *intf = GetBatteryInterface();
    if ((intf != NULL) && (intf->GetBatSocFunc != NULL)) {
        ret = intf->GetBatSocFunc((IUnknown *)intf);
    }
    return ret;
}
BatteryChargeState GetChargingStatus()
{
    BatteryChargeState state = CHARGE_STATE_NONE;
    BatteryInterface *intf = GetBatteryInterface();
    if ((intf != NULL) && (intf->GetBatSocFunc != NULL)) {
        state = intf->GetChargingStatusFunc((IUnknown *)intf);
    }
    return state;
}
BatteryHealthState GetHealthStatus()
{
	BatteryHealthState state = HEALTH_STATE_UNKNOWN;
    BatteryInterface *intf = GetBatteryInterface();
    if ((intf != NULL) && (intf->GetBatSocFunc != NULL)) {
        state = intf->GetHealthStatusFunc((IUnknown *)intf);
    }
    return state;
}
BatteryPluggedType GetPluggedType()
{
	BatteryPluggedType state = PLUGGED_TYPE_NONE;
    BatteryInterface *intf = GetBatteryInterface();
    if ((intf != NULL) && (intf->GetBatSocFunc != NULL)) {
        state = intf->GetPluggedTypeFunc((IUnknown *)intf);
    }
    return state;
}
int32_t GetBatVoltage()
{
	int32_t ret = EC_FAILURE;
    BatteryInterface *intf = GetBatteryInterface();
    if ((intf != NULL) && (intf->GetBatSocFunc != NULL)) {
        ret = intf->GetBatVoltageFunc((IUnknown *)intf);
    }
    return ret;
}

char strbuff[64] = {0};
char* GetBatTechnology()
{

    BatteryInterface *intf = GetBatteryInterface();
    if ((intf != NULL) && (intf->GetBatSocFunc != NULL)) {
        strcpy(strbuff, intf->GetBatTechnologyFunc((IUnknown *)intf));
    }
    return strbuff;
}
int32_t GetBatTemperature()
{
	int32_t ret = EC_FAILURE;
    BatteryInterface *intf = GetBatteryInterface();
    if ((intf != NULL) && (intf->GetBatSocFunc != NULL)) {
        ret = intf->GetBatTemperatureFunc((IUnknown *)intf);
    }
    return ret;
}
