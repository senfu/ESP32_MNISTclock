/*
 * @Author: Li Junyan 
 * @Date: 2021-07-08 23:45:29 
 * @Last Modified by: Li Junyan
 * @Last Modified time: 2021-07-09 16:52:15
 */

#pragma once
#include "WiFi.h"
#include "global.h"
bool connect(int timeout_s, const char* wifi_ssid, const char* wifi_password);
bool disconnect();
bool syncLocalTime();
