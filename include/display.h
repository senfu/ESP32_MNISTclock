/*
 * @Author: Li Junyan 
 * @Date: 2021-07-10 23:18:06 
 * @Last Modified by: Li Junyan
 * @Last Modified time: 2021-07-11 00:35:56
 */

#pragma once
#include "data.h"
#include <Arduino.h>
#include <EPD.h>
#include <GUI_Paint.h>
#include <DEV_Config.h>

UBYTE* initDisplay();
void displayTime(UBYTE* canvas, int hh, int mm);
void _updateHour(int hh);
void _updateMinute(int mm);
