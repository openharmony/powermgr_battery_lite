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

#ifndef BATTERY_CLIENT_H
#define BATTERY_CLIENT_H

#include "battery_info.h"
#include "iostream"
#include <samgr_lite.h>
#include <service.h>
#include "battery_mgr.h"
#include "battery_manage_feature.h"

namespace OHOS {
class BatteryClient {
public:
    BatteryClient();
    ~BatteryClient();
    const uint16 GetBatSoc();
    const BatteryChargeState GetChargingStatus();
    const BatteryHealthState GetHealthStatus();
    const BatteryPluggedType GetPluggedType();
    const uint16 GetBatVoltage();
    const std::string GetBatTechnology();
    const uint16 GetBatTemperature();

private:
    BatteryInterface *ChargingApiGet(void);
    BatteryInterface *batteryInterface;
};
}

#endif // BATTERY_SRV_CLIENT_H