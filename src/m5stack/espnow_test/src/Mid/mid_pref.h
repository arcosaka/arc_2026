/**
 * @file mid_pref.h
 * @version 26081222.160
 */

#ifndef LOAD_MID_PREF_H
#define LOAD_MID_PREF_H

#include "main.h"

#include <Preferences.h>

extern Preferences pref_core;
extern u4 u4_core_ver;

extern u4 u4_wifi_ch;
extern char chr_wifi_peer[18];

void pref_setup(void);
void pref_putnewver(void);
bi bi_pref_putsetting(const char* chrs_app_key, u4 u4_app_value);
bi bi_pref_putsetting(const char* chrs_app_key, const char* chrs_app_value);
bi bi_pref_putsetting(const char* chrs_app_key, String str_app_value);

#endif /* LOAD_MID_PREF_H */
