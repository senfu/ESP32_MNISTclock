/*
 * @Author: Li Junyan 
 * @Date: 2021-07-09 00:12:04 
 * @Last Modified by: Li Junyan
 * @Last Modified time: 2021-07-11 00:37:48
 */

#include "include/utils.h"
#include "include/wireless.h"
#include "include/global.h"
#include "include/display.h"

UBYTE* canvas = NULL;
char* cityName = NULL;
int count = 100;
WeatherInfo* weatherInfoNow;

void setup() {
    Serial.begin(115200);
    canvas = initDisplay();
    bool success = connect(60, WIFI_SSID, WIFI_PASSWORD);
    if (!success) {
        while(true) {}
    }
    syncLocalTime();
    cityName = getCityNameFromIP();
    Serial.printf("city name:", cityName);
    weatherInfoNow = getWeatherInfoFromCityName(cityName);
}

void loop() {
    if (count <= 0) {
        EPD_2IN13_V2_Init(EPD_2IN13_V2_FULL);
        EPD_2IN13_V2_Clear();
        delay(2000);
        Serial.println("System halt...");
        EPD_2IN13_V2_Sleep();
        free(canvas);
        canvas = NULL;
        while (true) {}
    }
    Serial.println("Wake up...");
    printLocalTime();
    struct tm timeinfo;
    getLocalTime(&timeinfo);
    displayTime(canvas, timeinfo.tm_hour, timeinfo.tm_min);
    // count --;
    // lightSleep(10);
}
