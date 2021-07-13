/*
 * @Author: Li Junyan 
 * @Date: 2021-07-08 23:45:29 
 * @Last Modified by: Li Junyan
 * @Last Modified time: 2021-07-09 20:46:46
 */

#pragma once
#include <HTTPClient.h>
#include <rom/miniz.h>
#include "WiFi.h"
#include "global.h"
#include "utils.h"

bool connect(int timeout_s, const char* wifi_ssid, const char* wifi_password);
bool disconnect();
bool syncLocalTime();
char* getCityNameFromIP();
char* getCityIDFromCityName(char* city_name);
