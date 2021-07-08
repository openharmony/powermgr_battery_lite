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

#ifndef BATTERY_MANAGE_FEATURE_H
#define BATTERY_MANAGE_FEATURE_H
#include "battery_info.h"
#include "feature.h"
#include "iproxy_server.h"
#include "message.h"
#include "battery_mgr.h"
#include "service.h"    
#include "ibattery.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

static IBattery *g_batteryDevice = NULL;

typedef struct BatteryInterface {
    INHERIT_IUNKNOWN;
    uint16 (*BatterySOC)();
    BatteryChargeState (*ChargingStatus)();
    BatteryHealthState (*HealthStatus)();
    BatteryPluggedType (*PluggedType)();
    uint16 (*Voltage)();
    char* (*Technology)();
    uint16 (*BatteryTemperature)();
} BatteryInterface;

typedef struct {
    INHERIT_FEATURE;
    INHERIT_IUNKNOWNENTRY(BatteryInterface);
    Identity identity_;
} BatteryServiceApi;

#ifdef __cplusplus
}
#endif
#endif // BATTERY_MANAGE_FEATURE_H