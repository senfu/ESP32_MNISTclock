/*
 * @Author: Li Junyan 
 * @Date: 2021-07-09 20:45:56 
 * @Last Modified by: Li Junyan
 * @Last Modified time: 2021-07-09 20:46:22
 */

#include "../include/utils.h"

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

char* parseCityName(const String& jsonStr) {
    return "aa";
}
