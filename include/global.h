/*
 * @Author: Li Junyan 
 * @Date: 2021-07-09 00:12:28 
 * @Last Modified by: Li Junyan
 * @Last Modified time: 2021-07-10 01:19:16
 */

#pragma once
#include "WString.h"

typedef struct HourlyData {
    int diffTime;
    int temp;
    int icon;
    int text;
    int pop;
};

typedef struct WeatherInfo {
    int pastTime;
    HourlyData hourly[24];
};
// WiFi configuration
extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;
// NTP server
extern const char* NTP_SERVER_1;
extern const char* NTP_SERVER_2;
extern const char* NTP_SERVER_3;
// China is GMT+8
extern const int GMT_OFFSET_SEC;
extern const int DAYLIGHT_OFFSET_SEC;
extern const int CONST_TIME_US;
// E-paper
extern const int TIME_X_START;
extern const int TIME_Y_START;
extern const int TIME_WIDTH;
extern const int TIME_HEIGHT;
extern const int TWO_DIGIT_WIDTH;
extern const int TWO_DIGHT_HEIGHT;
extern const int TWO_DIGIT_STORAGE_SIZE;
// API
extern const char* GET_WEATHER_FROM_IP_URL;
const String ROLL_API_APP_ID = "ldmeflrgml3pimdp";
const String ROLL_API_APP_SECRET = "L0l1dHFheDlibFc4aFR3a0ZLdng1Zz09";
