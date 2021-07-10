/*
 * @Author: Li Junyan 
 * @Date: 2021-07-09 20:45:56 
 * @Last Modified by: Li Junyan
 * @Last Modified time: 2021-07-11 00:00:17
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
    Serial.println("Enter light sleep mode...");
    if (sleep_s > 2) {
        delay(2000);
        sleep_s -= 2;
    }
    esp_sleep_enable_timer_wakeup(sleep_s*CONST_TIME_US);
    esp_light_sleep_start();
}

char* parseCityName(const char* jsonStr) {
    cJSON *pJsonRoot = cJSON_Parse(jsonStr);
    if (pJsonRoot) {
        cJSON *pData = cJSON_GetObjectItem(pJsonRoot, "data");
        if (pData) {
            cJSON *pCity = cJSON_GetObjectItem(pData, "city");
            if (pCity && cJSON_IsString(pCity)) {
                return pCity->valuestring;
            } else {
                return "#IC";
            }
        } else {
            return "#ID";
        }
    } else {
        return "#IJ";
    }
    return "#??";
}
