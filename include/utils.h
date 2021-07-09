/*
 * @Author: Li Junyan 
 * @Date: 2021-07-09 00:12:11 
 * @Last Modified by: Li Junyan
 * @Last Modified time: 2021-07-09 20:46:16
 */

#pragma once
#include <time.h>
#include <cJSON.h>
#include "global.h"

void printLocalTime();
void lightSleep(int sleep_s);
char* parseCityName(const String& jsonStr);
