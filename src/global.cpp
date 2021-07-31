/*
 * @Author: Li Junyan 
 * @Date: 2021-07-10 01:17:47 
 * @Last Modified by: Li Junyan
 * @Last Modified time: 2021-07-10 01:19:11
 */

#include "../include/global.h"

// const char* WIFI_SSID = "Xiangyu1131";
// const char* WIFI_PASSWORD = "xy523067";
const char* WIFI_SSID = "HONOR_LJY";
const char* WIFI_PASSWORD = "ljy886622";
const char* NTP_SERVER_1 = "cn.ntp.org.cn";
const char* NTP_SERVER_2 = "ntp.ntsc.ac.cn";
const char* NTP_SERVER_3 = "time.windows.com";
const int GMT_OFFSET_SEC = 8 * 3600;
const int DAYLIGHT_OFFSET_SEC = 0;
const int CONST_TIME_US = 1000000;
const int TIME_X_START = 10;
const int TIME_Y_START = 10;
const int TIME_WIDTH = 56;
const int TIME_HEIGHT = 237;
const int TWO_DIGIT_WIDTH = 56;
const int TWO_DIGHT_HEIGHT = 112;
const int TWO_DIGIT_STORAGE_SIZE = TWO_DIGIT_WIDTH*TWO_DIGHT_HEIGHT/8;
extern const char* GET_WEATHER_FROM_CITY_URL = \
    "https://1420383976168764.cn-shanghai.fc.aliyuncs.com"
    "/2016-08-15/proxy/ESP32.LATEST/getWeather/city=";
const String ROLL_API_APP_ID = "ldmeflrgml3pimdp";
const String ROLL_API_APP_SECRET = "L0l1dHFheDlibFc4aFR3a0ZLdng1Zz09";
