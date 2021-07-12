/*
 * @Author: Li Junyan 
 * @Date: 2021-07-09 00:12:28 
 * @Last Modified by: Li Junyan
 * @Last Modified time: 2021-07-10 01:19:16
 */

#pragma once
#include "WString.h"
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
// API: https://www.mxnzp.com/
extern const String ROLL_API_APP_ID;
extern const String ROLL_API_APP_SECRET;
// E-paper
extern const int TIME_X_START;
extern const int TIME_Y_START;
extern const int TIME_WIDTH;
extern const int TIME_HEIGHT;
extern const int TWO_DIGIT_WIDTH;
extern const int TWO_DIGHT_HEIGHT;
extern const int TWO_DIGIT_STORAGE_SIZE;
