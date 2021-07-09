/*
 * @Author: Li Junyan 
 * @Date: 2021-07-09 00:12:04 
 * @Last Modified by: Li Junyan
 * @Last Modified time: 2021-07-09 16:50:50
 */

#include "utils.hpp"
#include "wireless.h"
#include "global.h"

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
    delay(1000);
}
