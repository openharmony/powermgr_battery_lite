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

JSIValue PrintHello(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    JSIValue undefValue = JSI::CreateUndefined();
    (void)PrintBatHello(void);
    return undefValue;
}

void InitBatteryModule(JSIValue exports)
{
    JSI::SetModuleAPI(exports, "printHellow", BatteryModule::PrintHello);
}

}

battery.printHellow()

