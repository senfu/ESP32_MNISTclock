/*
 * @Author: Li Junyan 
 * @Date: 2021-07-08 23:47:18 
 * @Last Modified by: Li Junyan
 * @Last Modified time: 2021-07-09 00:54:51
 */

#include "wireless.h"

const char* wifi_ssid = "HONOR_LJY";
const char* wifi_password = "ljy886622";
const char* ntp_server = "pool.ntp.org";
// China is GMT+8
const int gmtOffset_sec = 8 * 3600;
const int daylightOffset_sec = 0;

bool connect(int timeout_s) {
    auto start_time = millis();
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
    Serial.println("WiFi disconnected...");
    return true;
}

bool syncLocalTime() {
    configTime(gmtOffset_sec, daylightOffset_sec, ntp_server);
    Serial.println("Local time synced...");
}
