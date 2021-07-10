/*
 * @Author: Li Junyan 
 * @Date: 2021-07-10 23:18:00 
 * @Last Modified by: Li Junyan
 * @Last Modified time: 2021-07-11 00:45:03
 */

#include "../include/display.h"
UBYTE* initDisplay() {
    DEV_Module_Init();
    EPD_2IN13_V2_Init(EPD_2IN13_V2_FULL);
    EPD_2IN13_V2_Clear();
    delay(2000);
    // Create a new image cache
    UBYTE* canvas = NULL;
    UWORD Imagesize = ((EPD_2IN13_V2_WIDTH % 8 == 0) ? \
                        (EPD_2IN13_V2_WIDTH / 8) : \
                        (EPD_2IN13_V2_WIDTH / 8 + 1)) * EPD_2IN13_V2_HEIGHT;
    if ((canvas = (UBYTE *)malloc(Imagesize)) == NULL) {
        Serial.println("Fail to apply for blank memory...");
        while (true) {}
    }
    Paint_NewImage(canvas, \
                    EPD_2IN13_V2_WIDTH, \
                    EPD_2IN13_V2_HEIGHT, \
                    0, WHITE);
    Paint_SelectImage(canvas);
    Paint_SetMirroring(MIRROR_NONE);
    Paint_Clear(WHITE);
    EPD_2IN13_V2_Display(canvas);
    delay(2000);
    Serial.println("E-paper is clear and ready...");
    EPD_2IN13_V2_Init(EPD_2IN13_V2_FULL);
    EPD_2IN13_V2_DisplayPartBaseImage(canvas);
    EPD_2IN13_V2_Init(EPD_2IN13_V2_PART);
    Paint_SelectImage(canvas);
    delay(500);
    Serial.println("partial refresh is ready...");
    return canvas;
}

void displayTime(UBYTE* canvas, int hh, int mm) {
    EPD_2IN13_V2_Init(EPD_2IN13_V2_PART);
    Paint_SelectImage(canvas);
    static int hh_prev = -1;
    static int mm_prev = -1;
    bool update = false;
    if (hh_prev != hh) {
        _updateHour(hh);
        hh_prev = hh;
        update = true;
    }
    if (mm_prev != mm) {
        _updateMinute(mm);
        mm_prev = mm;
        update = true;
    }
    if (update) {
        Paint_DrawCircle(55, 128, 3, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        Paint_DrawCircle(70, 128, 3, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        EPD_2IN13_V2_DisplayPart(canvas);
        delay(500);
        Serial.println("Time updated...");
    }
    return;
}

void _updateHour(int hh) {
    Paint_ClearWindows(35, 10, 35 + 56, 10 + 112, WHITE);
    Paint_DrawImage(DIGIT_DATA_112x56+hh*112*56/8, 35, 10, 56, 112);
}

void _updateMinute(int mm) {
    Paint_ClearWindows(35, 135, 35 + 56, 135 + 112, WHITE);
    Paint_DrawImage(DIGIT_DATA_112x56+mm*112*56/8, 35, 135, 56, 112);
}
