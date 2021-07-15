/*
 * @Author: Li Junyan 
 * @Date: 2021-07-09 20:45:56 
 * @Last Modified by: Li Junyan
 * @Last Modified time: 2021-07-11 00:00:17
 */

#include "../include/utils.h"

char* urlCNEncode(char* str) {
    const uint mask = 0xff;
    const char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                        'A', 'B', 'C', 'D', 'E', 'F'};
    char* ret_str = (char*)calloc(sizeof(char), strlen(str)*3+1);
    ret_str[strlen(str)*3] = 0x00;
    for (int i=0; str[i] != '\0'; i++) {
        ret_str[3*i] = '%';
        ret_str[3*i+1] = hex[((str[i]&mask)/16)%16];
        ret_str[3*i+2] = hex[(str[i]&mask)%16];
    }
    return ret_str;
}

int vidpeek_uncompressGzip(unsigned char* pSrc, \
                            unsigned int srcSize, \
                            char** pOutDest, unsigned int* pOutBufSize) {
    #define OK 0
    #define ERR -1
    int ret = OK;
    char* pBuf = (char*)pSrc+ (srcSize - 1);
    unsigned int len = *pBuf;
    int uncompressResult;
    z_stream d_stream;
    int i = 0;

    // check gz file,rfc1952 P6
    if ((*pSrc != 0x1f) || (*(pSrc+1) != 0x8b)) {
        printf("\nuncompressGzip non Gzip\n");
        return ERR;
    }
    for (i = 0; i < 3; i++) {
        pBuf--;
        len <<= 8;
        len += *pBuf;
    }

    // fortest
    if ((len== 0) || (len > 1000000)) {
        printf("\nuncompressGzip, error gzip!\n");
        return ERR;
    }

    // gzip decompression start!!!

    d_stream.zalloc = Z_NULL;
    d_stream.zfree = Z_NULL;
    d_stream.opaque = Z_NULL;
    d_stream.next_in = Z_NULL;
    d_stream.avail_in = 0;
    uncompressResult = mz_inflateInit2(&d_stream, 47);
    if (uncompressResult != Z_OK) {
        printf("\ninflateInit2 error:%d\n", uncompressResult);
        return uncompressResult;
    }

    d_stream.next_in = pSrc;
    d_stream.avail_in = srcSize;
    d_stream.next_out = (unsigned char *)*pOutDest;
    d_stream.avail_out = len;
    uncompressResult = inflate(&d_stream, Z_NO_FLUSH);

    switch (uncompressResult) {
        case Z_NEED_DICT:
            uncompressResult = Z_DATA_ERROR;
        case Z_DATA_ERROR:
        case Z_MEM_ERROR:
            (void)inflateEnd(&d_stream);
            return uncompressResult;
    }
    inflateEnd(&d_stream);
    *pOutBufSize = len-2;
    return ret;
}

char* decompress(String str) {
    uLong src_len = str.length();
    unsigned int dest_len = src_len*10;
    for (int i=0; i < str.length(); i++)
    Serial.printf("%x|", str[i]);
    Serial.println();
    Serial.println(src_len);
    char* dest_str = (char*)malloc(dest_len);
    int code = vidpeek_uncompressGzip((unsigned char*)str.c_str(), src_len, \
                                        &dest_str, &dest_len);
    Serial.printf("Code: %d\n", code);
    if (code == OK) {
        dest_str = (char*)realloc(dest_str, strlen((char*)dest_str)+1);
        return dest_str;
    } else {
        return NULL;
    }
}

void printLocalTime() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Fail to obtain local time...");
        return;
    }
    Serial.println(&timeinfo, "%F %T %A");
}

void lightSleep(int sleep_s) {
    Serial.println("Enter light sleep mode...");
    if (sleep_s > 2) {
        delay(2000);
        sleep_s -= 2;
    }
    esp_sleep_enable_timer_wakeup(sleep_s*CONST_TIME_US);
    esp_light_sleep_start();
}

char* parseCityName(const char* jsonStr) {
    cJSON *pJsonRoot = cJSON_Parse(jsonStr);
    if (pJsonRoot) {
        cJSON *pData = cJSON_GetObjectItem(pJsonRoot, "data");
        if (pData) {
            cJSON *pCity = cJSON_GetObjectItem(pData, "city");
            if (pCity && cJSON_IsString(pCity)) {
                return pCity->valuestring;
            } else {
                return "#IC";
            }
        } else {
            return "#ID";
        }
    } else {
        return "#IJ";
    }
    return "#??";
}

char* parseCityID(const char* jsonStr) {
    cJSON *pJsonRoot = cJSON_Parse(jsonStr);
    if (pJsonRoot) {
        cJSON *pLocation = cJSON_GetObjectItem(pJsonRoot, "location");
        if (pLocation) {
            cJSON *pID = cJSON_GetObjectItem(pLocation, "id");
            if (pID && cJSON_IsString(pID)) {
                return pID->valuestring;
            } else {
                return "#II";
            }
        } else {
            return "#IL";
        }
    } else {
        return "#IJ";
    }
    return "#??";
}

