/*
 * @Author: Li Junyan 
 * @Date: 2021-07-09 00:12:28 
 * @Last Modified by: Li Junyan
 * @Last Modified time: 2021-07-09 20:47:40
 */

#pragma once
#include "WString.h"
// WiFi configuration
static const char* WIFI_SSID = "HONOR_LJY";
static const char* WIFI_PASSWORD = "ljy886622";
// NTP server
static const char* NTP_SERVER = "pool.ntp.org";
// China is GMT+8
static const int GMT_OFFSET_SEC = 8 * 3600;
static const int DAYLIGHT_OFFSET_SEC = 0;
static const int CONST_TIME_US = 1000000;
// API: https://www.mxnzp.com/
static const String APP_ID = "ldmeflrgml3pimdp";
static const String APP_SECRET = "L0l1dHFheDlibFc4aFR3a0ZLdng1Zz09";
