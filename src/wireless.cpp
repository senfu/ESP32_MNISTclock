/*
 * @Author: Li Junyan 
 * @Date: 2021-07-08 23:47:18 
 * @Last Modified by: Li Junyan
 * @Last Modified time: 2021-07-09 16:53:42
 */

#include "../include/wireless.h"

bool connect(int timeout_s, const char* wifi_ssid, const char* wifi_password) {
    auto start_time = millis();
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi_ssid, wifi_password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        if ((millis()-start_time)/1000 >= timeout_s) {
            Serial.println();
            Serial.println("Fail to connect to WiFi...");
            Serial.printf("SSID: %s\nPassword: %s\n", wifi_ssid, wifi_password);
            return false;
        }
    }
    Serial.println("\nWiFi connected...");
    Serial.printf("SSID: %s\n", wifi_ssid);
    return true;
}

bool disconnect() {
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    Serial.println("WiFi disconnected...");
    return true;
}

bool syncLocalTime() {
    configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);
    Serial.println("Local time synced...");
}
