/*
 * @Author: Li Junyan 
 * @Date: 2021-07-09 00:12:11 
 * @Last Modified by: Li Junyan
 * @Last Modified time: 2021-07-09 00:36:59
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_
void printLocalTime() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Fail to obtain local time...");
        return;
    }
    Serial.println(&timeinfo, "%F %T %A");
}
#endif  // UTILS_HPP_
