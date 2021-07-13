/*
 * @Author: Li Junyan 
 * @Date: 2021-07-08 23:47:18 
 * @Last Modified by: Li Junyan
 * @Last Modified time: 2021-07-09 20:46:35
 */

#include "../include/wireless.h"

bool connect(int timeout_s, const char* wifi_ssid, const char* wifi_password) {
    auto start_time = millis();
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi_ssid, wifi_password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
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
    configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, \
                NTP_SERVER_1, \
                NTP_SERVER_2, \
                NTP_SERVER_3);
    Serial.printf("Local time syncing from three NTP server\n");
    struct tm timeinfo;
    while (time(NULL) < 1580000000)
        yield();
    Serial.println("\nLocal time synced...");
}

char* getCityNameFromIP() {
    HTTPClient http;
    String url = "https://www.mxnzp.com/api/ip/self?app_id="+\
                    ROLL_API_APP_ID+"&app_secret="+ROLL_API_APP_SECRET;
    http.begin(url);
    int httpCode = http.GET();
    while (httpCode <= 0) {
        delay(2000);
        httpCode = http.GET();
    }
    const String payload = http.getString();
    // Serial.println(payload.c_str());
    return parseCityName(payload.c_str());
}

char* getCityIDFromCityName(char* city_name) {
    HTTPClient http;
    String url = "https://geoapi.qweather.com/v2/city/lookup?"
                    "location="+String("beijing")+\
                    "&number=1"
                    "&key="+WEATHER_API_KEY;
    http.begin(url);
    int httpCode = http.GET();
    while (httpCode <= 0) {
        delay(2000);
        httpCode = http.GET();
    }
    const String payload_gzip = http.getString();
    Serial.println(url);
    Serial.println(payload_gzip);
    // TODO(Li Junyan): miniz decompression gzip
    return parseCityID(payload_gzip.c_str());
}