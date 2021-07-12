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
    delay(1000);
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
        const int center = (TIME_X_START+TIME_X_START+TIME_WIDTH)/2;
        const int center1 = (TIME_X_START+center)/2 + 5;
        const int center2 = (TIME_X_START+TIME_WIDTH+center)/2 - 5;
        const int centerY = (TIME_Y_START+TIME_Y_START+TIME_HEIGHT)/2;
        Paint_DrawCircle(center1, centerY, 3, BLACK, DOT_PIXEL_1X1, \
                            DRAW_FILL_FULL);
        Paint_DrawCircle(center2, centerY, 3, BLACK, DOT_PIXEL_1X1, \
                            DRAW_FILL_FULL);
        EPD_2IN13_V2_DisplayPart(canvas);
        delay(300);
        Serial.println("Time updated...");
    }
    return;
}

void _updateHour(int hh) {
    Paint_ClearWindows(TIME_X_START, TIME_Y_START, \
                        TIME_X_START + TWO_DIGIT_WIDTH, \
                        TIME_Y_START + TWO_DIGHT_HEIGHT, \
                        WHITE);
    Paint_DrawImage(DIGIT_DATA_112x56+hh*TWO_DIGIT_STORAGE_SIZE, \
                    TIME_X_START, TIME_Y_START, \
                    TWO_DIGIT_WIDTH, TWO_DIGHT_HEIGHT);
}

void _updateMinute(int mm) {
    Paint_ClearWindows(TIME_X_START, \
                        TIME_Y_START+TIME_HEIGHT-TWO_DIGHT_HEIGHT, \
                        TIME_X_START + TWO_DIGIT_WIDTH, \
                        TIME_Y_START+TIME_HEIGHT, \
                        WHITE);
    Paint_DrawImage(DIGIT_DATA_112x56+mm*TWO_DIGIT_STORAGE_SIZE, \
                    TIME_X_START, \
                    TIME_Y_START+TIME_HEIGHT-TWO_DIGHT_HEIGHT, \
                    TWO_DIGIT_WIDTH, TWO_DIGHT_HEIGHT);
}
