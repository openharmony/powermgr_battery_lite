/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
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

export interface BatterySocResponse {

    batterySoc: number;
}

export interface GetBatterySOC {

    success?: (data: BatterySocResponse) => void;

    fail?: (data: string, code: number) => void;

    complete?: () => void;
}

export interface BatteryChargingStatusResponse {

  chargingStatus: number;
}

export interface GetChargingStatus {
   success?: (data: BatteryChargingStatusResponse) => void;

   fail?: (data: string, code: number) => void;

   complete?: () => void;
}

export interface BatteryHealthStatusResponse {

  healthStatus: number;
}

export interface GetHealthStatus {

   success?: (data: BatteryHealthStatusResponse) => void;

   fail?: (data: string, code: number) => void;

   complete?: () => void;
}

export interface BatteryGetPluggedTypeResponse {

  pluggedType: number;
}

export interface GetPluggedType {

  success?: (data: BatteryGetPluggedTypeResponse) => void;

  fail?: (data: string, code: number) => void;

  complete?: () => void;
}

export interface BatteryGetVoltageResponse {

  voltage: number;
}

export interface GetVoltage {

  success?: (data: BatteryGetVoltageResponse) => void;

  fail?: (data: string, code: number) => void;

  complete?: () => void;
}

export interface BatteryTechnologyResponse {

  technology: string;
}

export interface GetTechnology {

  success?: (data: BatteryTechnologyResponse) => void;

  fail?: (data: string, code: number) => void;

  complete?: () => void;
}

export interface BatteryTemperatureResponse {

  temperature: number;
}

export interface GetTemperature {

  success?: (data: BatteryTemperatureResponse) => void;

  fail?: (data: string, code: number) => void;

  complete?: () => void;
}
/**
 * @Syscap SysCap.ACE.UIEngineLite
 */
export default class battery {

  static BatterySOC(options?: GetBatterySOC): void;
  
  static ChargingStatus(options?: GetChargingStatus): void;
  
  static HealthStatus(options?: GetHealthStatus): void;
  
  static PluggedType(options?: GetPluggedType): void;
  
  static Voltage(options?: GetVoltage): void;
  
  static Technology(options?: GetTechnology): void;
  
  static Temperature(options?: GetTemperature): void;
}
