/*
 * @Author: Li Junyan 
 * @Date: 2021-07-09 20:45:56 
 * @Last Modified by: Li Junyan
 * @Last Modified time: 2021-07-11 00:00:17
 */

#include "../include/utils.h"

char* urlCNEncode(char* str) {
    const uint mask = 0xff;
    const char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                        'A', 'B', 'C', 'D', 'E', 'F'};
    char* ret_str = (char*)calloc(sizeof(char), strlen(str)*3+1);
    ret_str[strlen(str)*3] = 0x00;
    for (int i=0; str[i] != '\0'; i++) {
        ret_str[3*i] = '%';
        ret_str[3*i+1] = hex[((str[i]&mask)/16)%16];
        ret_str[3*i+2] = hex[(str[i]&mask)%16];
    }
    return ret_str;
}

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
