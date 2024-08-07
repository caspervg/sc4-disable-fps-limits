#pragma once
#include <cstdint>

struct SC4AppPreferences
{
    uint32_t enableFullGamePauseOnAppFocusLoss;
    uint32_t languageID;
    int8_t languageName[64];
    uint8_t field3_0x48;
    uint8_t field4_0x49;
    uint8_t field5_0x4a;
    uint8_t bIME;
    uint8_t field7_0x4c[2400];
};

