/*
 * @Author: Li Junyan 
 * @Date: 2021-07-09 00:12:11 
 * @Last Modified by: Li Junyan
 * @Last Modified time: 2021-07-09 16:52:57
 */

#pragma once
#include "time.h"
#include "global.h"

void printLocalTime() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Fail to obtain local time...");
        return;
    }
    Serial.println(&timeinfo, "%F %T %A");
}

void lightSleep(int sleep_s) {
    esp_sleep_enable_timer_wakeup(sleep_s*CONST_TIME_US);
    esp_light_sleep_start();
}
