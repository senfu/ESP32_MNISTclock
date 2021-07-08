/*
 * @Author: Li Junyan 
 * @Date: 2021-07-08 23:45:29 
 * @Last Modified by: Li Junyan
 * @Last Modified time: 2021-07-09 00:46:54
 */

#ifndef WIRELESS_H_
#define WIRELESS_H_
#include "WiFi.h"
bool connect(int timeout_s);
bool disconnect();
bool syncLocalTime();
#endif  // WIRELESS_H_
