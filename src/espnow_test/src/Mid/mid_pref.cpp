/**
 * @file mid_pref.cpp
 * @version 26081620.030
 */

#include "mid_pref.h"

#define VER_00  0U
#define VER_01  26081215U
#define VER_NEW (VER_01)

Preferences pref_core;

u4 u4_core_ver;

u4 u4_wifi_ch;
char chr_wifi_peer[18];

void pref_setup(void) {
    M5.Log.println("pref_setup start");
    pref_core.begin("DEV", true);
    M5.Log.println("pref_setup DEV");
    u4_core_ver = pref_core.getUInt("ver", VER_00);
    M5.Log.printf("pref_setup get `DEV.ver` = %ld\n", u4_core_ver);
    pref_core.end();

    if(u4_core_ver >= VER_01){
        pref_core.begin("WIFIAP", true);
        M5.Log.println("pref_setup WIFIAP");
        u4_wifi_ch = pref_core.getUInt("ch", 0U);
        M5.Log.printf("pref_setup get `WIFIAP.ch` = %ld\n", u4_wifi_ch);
        pref_core.getString("peer", chr_wifi_peer, sizeof(chr_wifi_peer));
        M5.Log.printf("pref_setup get `WIFIAP.peer` = %s\n", chr_wifi_peer);
        pref_core.end();
    }
    else{
        u4_wifi_ch = 0U;
    }
    M5.Log.println("pref_setup end");
}

void pref_putnewver(void) {
    pref_core.begin("DEV", false);
    bi_pref_putsetting("ver", (u4)VER_NEW);
    pref_core.end();
}

bi bi_pref_putsetting(const char* chrs_app_key, u4 u4_app_value){
    size_t size_res = 0;
    bi bi_iserr = false;
    size_res = pref_core.putUInt(chrs_app_key, u4_app_value);
    bi_iserr = (size_res == 0);
    M5.Log.printf("[%s]=%ld\n", chrs_app_key, u4_app_value);
    return bi_iserr;
}

bi bi_pref_putsetting(const char* chrs_app_key, const char* chrs_app_value) {
    String str_app_value(chrs_app_value);
    return bi_pref_putsetting(chrs_app_key, str_app_value);
}

bi bi_pref_putsetting(const char* chrs_app_key, String str_app_value) {
    size_t size_res = 0;
    bi bi_iserr = false;
    if (str_app_value != "") {
        size_res = pref_core.putString(chrs_app_key, str_app_value);
        bi_iserr = (size_res == 0);
        M5.Log.printf("[%s]='%s'\n", chrs_app_key, str_app_value.c_str());
    }
    return bi_iserr;
}
