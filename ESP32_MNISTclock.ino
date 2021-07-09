/*
 * @Author: Li Junyan 
 * @Date: 2021-07-09 00:12:04 
 * @Last Modified by: Li Junyan
 * @Last Modified time: 2021-07-09 20:46:31
 */

#include "include/utils.h"
#include "include/wireless.h"
#include "include/global.h"

void setup() {
    Serial.begin(115200);
    bool success = connect(60, WIFI_SSID, WIFI_PASSWORD);
    if (!success) {
        while(true) {}
    }
    syncLocalTime();
}

void loop() {
    printLocalTime();
    lightSleep(10);
    Serial.println("Wake up...");
    char* cityName = getCityNameFromIP();
}
