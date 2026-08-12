/**
 * @file app_websetup.cpp
 * @version 26081222.160
 */

#include "app_websetup.h"
#include "cmn_setting.h"
#include "../Mid/mid_pref.h"

#include <WiFi.h>
#include <WiFiAP.h>

#include "MacAddress.h"
#include <WebServer.h>    // サーバー設定用

#include "FS.h"
#include <SPIFFS.h>

//******************************************************
// グローバル変数定義
//******************************************************

//******************************************************
// ローカル型定義
//******************************************************

//******************************************************
// ローカル変数定義
//******************************************************

WebServer server(80);
bi bi_isreboot = false;

//******************************************************
// ローカル関数宣言
//******************************************************

//******************************************************
// 関数定義
//******************************************************

static String spiffs_readfile(const char* chrs_filename){
    String data = "";
    if (SPIFFS.exists(chrs_filename)) {
        File file = SPIFFS.open(chrs_filename, FILE_READ);
        if (!file) {
            M5.Log.println("Failed to open file");
        }
        else {
            data = file.readString();
        }
        file.close();
    }
    return data;
}

static void websetup_root() {
    String html = spiffs_readfile("/index.html");
    server.send(200, "text/html", html);
    M5.Log.println("200, text/html, index.html");
}

static void websetup_notfound() {
    server.send(404, "text/plain", "404 Not Found!");
}

static void websetup_set() {

    if(!server.hasArg("macaddr") && !server.hasArg("channel")){
        server.send(404, "text/plain", "404 Not Found!");
        return;
    }
    server.send(204);
    pref_core.begin("WIFIAP", false);
    if(server.hasArg("macaddr")){
        String arg_macaddr = server.arg("macaddr");
        const MacAddress macaddr(arg_macaddr);
        M5.Log.printf(" arg addr = %s\n",arg_macaddr.c_str());
        M5.Log.printf("peer addr = %s\n",macaddr.toString().c_str());
        if(macaddr.toString() != ""){
            bi_pref_putsetting("peer", macaddr.toString());
        }
    }
    if(server.hasArg("channel")){
        bi_pref_putsetting("ch", (u4)server.arg("channel").toInt());
    }
    pref_core.end();
    pref_putnewver();
    bi_isreboot = true;
}

void websetup_setup(void) {

    if (!SPIFFS.begin()) {
        M5.Log.println("SPIFFS Mount Failed");
        return;
    }

    if(spiffs_readfile("/index.html") == ""){
        M5.Log.println("`index.html` is not found.");
        return;
    }

    WiFi.mode(WIFI_AP);

    while (!(WiFi.STA.started() || WiFi.AP.started())) {
        delay(10);
    }


    String apMac = WiFi.softAPmacAddress();
    const MacAddress macaddr(apMac);
    u8 u8_pass = 0;
    for (size_t i = 0; i < 8; i++)
    {
        u8_pass += (macaddr[i] << (i + 13));
        M5.Log.printf("macaddr[%d]=%u\n", i, macaddr[i]);
        M5.Log.printf("u8_pass=%ld\n", u8_pass);
    }

    M5.Log.setDisplay(&M5.Display);
    M5.Log.println("setting mode");

    M5.Log.printf(" AP MACADDR      \n: %s\n", apMac.c_str());
    apMac.replace(":", "");

    String str_ssid = "M5Stack-" + apMac.substring(6);
    String str_pass = "00000000" + String(u8_pass);
    str_pass = str_pass.substring(str_pass.length() - 8);

    WiFi.softAP(str_ssid.c_str(), str_pass.c_str());
    IPAddress myIP = WiFi.softAPIP();
    M5.Log.printf(" AP SSID         \n: %s\n", str_ssid.c_str());
    M5.Log.printf(" AP PASS         \n: %s\n", str_pass.c_str());
    M5.Log.printf(" AP IP address   \n: %s\n", myIP.toString().c_str());

    server.on("/", websetup_root);
    server.onNotFound(websetup_notfound);
    server.on("/set", websetup_set);
    server.begin();                     // Webサーバー開始
    while (!bi_isreboot){
        server.handleClient();
        M5.delay(100);
    }
    M5.Log.println("setting update!");
    server.stop();
}
