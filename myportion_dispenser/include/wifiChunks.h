#ifndef WIFI_CHUNKS_H
#define WIFI_CHUNKS_H

#ifndef ESP8266
#error This code is intended to run on the ESP8266 platform! Please check your Tools->Board setting.
#endif

// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _WIFIMGR_LOGLEVEL_ 0

#include <ESP8266WiFi.h> //https://github.com/esp8266/Arduino
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>

// From v1.1.0
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;

#include <FS.h>

#define USE_LITTLEFS true

#if USE_LITTLEFS
#include <LittleFS.h>
FS* filesystem = &LittleFS;
#define FileFS LittleFS
#define FS_Name "LittleFS"
#else
FS* filesystem = &SPIFFS;
#define FileFS SPIFFS
#define FS_Name "SPIFFS"
#endif
//////

#define ESP_getChipId() (ESP.getChipId())

#define LED_ON LOW
#define LED_OFF HIGH

// You only need to format the filesystem once
//#define FORMAT_FILESYSTEM       true
#define FORMAT_FILESYSTEM false

// SSID and PW for your Router
String Router_SSID;
String Router_Pass;

// From v1.1.0
#define MIN_AP_PASSWORD_SIZE 8

#define SSID_MAX_LEN 32
//From v1.0.10, WPA2 passwords can be up to 63 characters long.
#define PASS_MAX_LEN 64

typedef struct
{
    char wifi_ssid[SSID_MAX_LEN];
    char wifi_pw[PASS_MAX_LEN];
} WiFi_Credentials;

typedef struct
{
    String wifi_ssid;
    String wifi_pw;
} WiFi_Credentials_String;

#define NUM_WIFI_CREDENTIALS 2

typedef struct
{
    WiFi_Credentials WiFi_Creds[NUM_WIFI_CREDENTIALS];
} WM_Config;

WM_Config WM_config;

#define CONFIG_FILENAME F("/wifi_cred.dat")

// Indicates whether ESP has WiFi credentials saved from previous session, or double reset detected
bool initialConfig = false;
//////

// Use false if you don't like to display Available Pages in Information Page of Config Portal
// Comment out or use true to display Available Pages in Information Page of Config Portal
// Must be placed before #include <ESP_WiFiManager.h>
#define USE_AVAILABLE_PAGES false

// From v1.0.10 to permit disable/enable StaticIP configuration in Config Portal from sketch. Valid only if DHCP is used.
// You'll loose the feature of dynamically changing from DHCP to static IP, or vice versa
// You have to explicitly specify false to disable the feature.
//#define USE_STATIC_IP_CONFIG_IN_CP          false

// Use false to disable NTP config. Advisable when using Cellphone, Tablet to access Config Portal.
// See Issue 23: On Android phone ConfigPortal is unresponsive (https://github.com/khoih-prog/ESP_WiFiManager/issues/23)
#define USE_ESP_WIFIMANAGER_NTP false

// Use true to enable CloudFlare NTP service. System can hang if you don't have Internet access while accessing CloudFlare
// See Issue #21: CloudFlare link in the default portal (https://github.com/khoih-prog/ESP_WiFiManager/issues/21)
#define USE_CLOUDFLARE_NTP false

// New in v1.0.11
#define USING_CORS_FEATURE true
//////

// Use USE_DHCP_IP == true for dynamic DHCP IP, false to use static IP which you have to change accordingly to your network
#if (defined(USE_STATIC_IP_CONFIG_IN_CP) && !USE_STATIC_IP_CONFIG_IN_CP)
// Force DHCP to be true
#if defined(USE_DHCP_IP)
#undef USE_DHCP_IP
#endif
#define USE_DHCP_IP true
#else
// You can select DHCP or Static IP here
#define USE_DHCP_IP     true
// #define USE_DHCP_IP false
#endif

#if (USE_DHCP_IP || (defined(USE_STATIC_IP_CONFIG_IN_CP) && !USE_STATIC_IP_CONFIG_IN_CP))
// Use DHCP
#warning Using DHCP IP
IPAddress stationIP = IPAddress(0, 0, 0, 0);
IPAddress gatewayIP = IPAddress(0, 0, 0, 0);
IPAddress netMask = IPAddress(255, 255, 255, 0);
#else
// Use static IP
#warning Using static IP

IPAddress stationIP = IPAddress(192, 168, 2, 186);
IPAddress gatewayIP = IPAddress(192, 168, 2, 1);
IPAddress netMask = IPAddress(255, 255, 255, 0);

#endif

#define USE_CONFIGURABLE_DNS true

IPAddress dns1IP = gatewayIP;
// IPAddress dns2IP = gatewayIP;
IPAddress dns2IP = IPAddress(8, 8, 8, 8);

#include <ESP_WiFiManager.h> //https://github.com/khoih-prog/ESP_WiFiManager

// Function Prototypes
uint8_t connectMultiWiFi(void);
void setupWifi(void);

void wifiHeartBeatPrint(void)
{
    static int num = 1;

    if (WiFi.status() == WL_CONNECTED)
        Serial.println("[WM] H"); // H means connected to WiFi
    else
        Serial.println("[WM] F"); // F means not connected to WiFi

    if (num == 80) {
        Serial.println();
        num = 1;
    } else if (num++ % 10 == 0) {
        Serial.print(" ");
    }

    // IPAddress address;
    // if(WiFi.hostByName("Google.com", address, 3000) == 1) {
    //     Serial.print("[WM] Successfully resolved google to ");
    //     Serial.println(address);
    // }
}

void checkWiFi(void)
{
    if ((WiFi.status() != WL_CONNECTED)) {
        Serial.println("\n[WM] WiFi lost. Call connectMultiWiFi in loop");
        connectMultiWiFi();
    }
}

void checkWifiStatus(void)
{
    static ulong checkstatus_timeout = 0;
    static ulong checkwifi_timeout = 0;

    static ulong current_millis;

#define WIFICHECK_INTERVAL 1000L
#define HEARTBEAT_INTERVAL 10000L

    current_millis = millis();

    // Check WiFi every WIFICHECK_INTERVAL (1) seconds.
    if ((current_millis > checkwifi_timeout) || (checkwifi_timeout == 0)) {
        checkWiFi();
        checkwifi_timeout = current_millis + WIFICHECK_INTERVAL;
    }

    // Print hearbeat every HEARTBEAT_INTERVAL (10) seconds.
    if ((current_millis > checkstatus_timeout) || (checkstatus_timeout == 0)) {
        wifiHeartBeatPrint();
        checkstatus_timeout = current_millis + HEARTBEAT_INTERVAL;
    }
}

void loadWifiConfigData(void)
{
    File file = FileFS.open(CONFIG_FILENAME, "r");
    LOGERROR(F("LoadWiFiCfgFile "));

    if (file) {
        file.readBytes((char*)&WM_config, sizeof(WM_config));
        file.close();
        LOGERROR(F("OK"));
    } else {
        LOGERROR(F("failed"));
    }
}

void saveWifiConfigData(void)
{
    File file = FileFS.open(CONFIG_FILENAME, "w");
    LOGERROR(F("SaveWiFiCfgFile "));

    if (file) {
        file.write((uint8_t*)&WM_config, sizeof(WM_config));
        file.close();
        LOGERROR(F("OK"));
    } else {
        LOGERROR(F("failed"));
    }
}

uint8_t connectMultiWiFi(void)
{

// For ESP8266, this better be 2200 to enable connect the 1st time
#define WIFI_MULTI_1ST_CONNECT_WAITING_MS 2200L

#define WIFI_MULTI_CONNECT_WAITING_MS 100L

    uint8_t status;

    LOGERROR(F("ConnectMultiWiFi with :"));

    if ((Router_SSID != "") && (Router_Pass != "")) {
        LOGERROR3(F("* Flash-stored Router_SSID = "), Router_SSID, F(", Router_Pass = "), Router_Pass);
    }

    for (uint8_t i = 0; i < NUM_WIFI_CREDENTIALS; i++) {
        // Don't permit NULL SSID and password len < MIN_AP_PASSWORD_SIZE (8)
        if ((String(WM_config.WiFi_Creds[i].wifi_ssid) != "") && (strlen(WM_config.WiFi_Creds[i].wifi_pw) >= MIN_AP_PASSWORD_SIZE)) {
            LOGERROR3(F("* Additional SSID = "), WM_config.WiFi_Creds[i].wifi_ssid, F(", PW = "), WM_config.WiFi_Creds[i].wifi_pw);
        }
    }

    LOGERROR(F("Connecting MultiWifi..."));

    WiFi.mode(WIFI_STA);

#if !USE_DHCP_IP
#if USE_CONFIGURABLE_DNS
    // Set static IP, Gateway, Subnetmask, DNS1 and DNS2. New in v1.0.5
    WiFi.config(stationIP, gatewayIP, netMask, dns1IP, dns2IP);
#else
    // Set static IP, Gateway, Subnetmask, Use auto DNS1 and DNS2.
    WiFi.config(stationIP, gatewayIP, netMask);
#endif
#endif

    int i = 0;
    status = wifiMulti.run();
    delay(WIFI_MULTI_1ST_CONNECT_WAITING_MS);

    while ((i++ < 10) && (status != WL_CONNECTED)) {
        status = wifiMulti.run();

        if (status == WL_CONNECTED)
            break;
        else
            delay(WIFI_MULTI_CONNECT_WAITING_MS);
    }

    if (status == WL_CONNECTED) {
        LOGERROR1(F("WiFi connected after time: "), i);
        LOGERROR3(F("SSID:"), WiFi.SSID(), F(",RSSI="), WiFi.RSSI());
        LOGERROR3(F("Channel:"), WiFi.channel(), F(",IP address:"), WiFi.localIP());
    } else {
        LOGERROR(F("WiFi not connected"));
        static uint16_t numRetries = 0;
        #define MAX_NUM_RETRIES 50U
        ;
        if (numRetries++ > MAX_NUM_RETRIES)
        {
            numRetries = 0;
            setupWifi();
        }
        
    }

    return status;
}

void setupWifi()
{

    Serial.print("\n[WM] Starting AutoConnectAP using " + String(FS_Name));
    Serial.println(" on " + String(ARDUINO_BOARD));

    if (FORMAT_FILESYSTEM)
        FileFS.format();

        // Format FileFS if not yet
    if (!FileFS.begin())
    {
        Serial.print("[WM] ");
        Serial.print(FS_Name);
        Serial.println(F(" failed! AutoFormatting."));

        FileFS.format();
    }

    unsigned long startedAt = millis();

    // Use this to default DHCP hostname to ESP8266-XXXXXX
    //ESP_WiFiManager ESP_wifiManager;
    // Use this to personalize DHCP hostname (RFC952 conformed)
    ESP_WiFiManager ESP_wifiManager("AutoConnectAP");

    ESP_wifiManager.setDebugOutput(true);

    //reset settings - for testing
    // ESP_wifiManager.resetSettings();

    //set custom ip for portal
    ESP_wifiManager.setAPStaticIPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));

    ESP_wifiManager.setMinimumSignalQuality(-1);

    // From v1.0.10 only
    // Set config portal channel, default = 1. Use 0 => random channel from 1-13
    ESP_wifiManager.setConfigPortalChannel(0);
    //////

#if !USE_DHCP_IP
#if USE_CONFIGURABLE_DNS
    // Set static IP, Gateway, Subnetmask, DNS1 and DNS2. New in v1.0.5
    ESP_wifiManager.setSTAStaticIPConfig(stationIP, gatewayIP, netMask, dns1IP, dns2IP);
#else
    // Set static IP, Gateway, Subnetmask, Use auto DNS1 and DNS2.
    ESP_wifiManager.setSTAStaticIPConfig(stationIP, gatewayIP, netMask);
#endif
#endif

    // New from v1.1.1
#if USING_CORS_FEATURE
    ESP_wifiManager.setCORSHeader("[WM] Your Access-Control-Allow-Origin");
#endif

    // We can't use WiFi.SSID() in ESP32 as it's only valid after connected.
    // SSID and Password stored in ESP32 wifi_ap_record_t and wifi_config_t are also cleared in reboot
    // Have to create a new function to store in EEPROM/SPIFFS for this purpose
    Router_SSID = ESP_wifiManager.WiFi_SSID();
    Router_Pass = ESP_wifiManager.WiFi_Pass();

    //Remove this line if you do not want to see WiFi password printed
    Serial.println("[WM] Stored: SSID = " + Router_SSID + ", Pass = " + Router_Pass);

    if (Router_SSID != "") {
        ESP_wifiManager.setConfigPortalTimeout(120); //If no access point name has been previously entered disable timeout.
        Serial.println("[WM] Got stored Credentials. Timeout 120s");
    } else {
        Serial.println("[WM] No stored Credentials. No timeout");
    }

    String chipID = String(ESP_getChipId(), HEX);
    chipID.toUpperCase();

    // SSID and PW for Config Portal
    String AP_SSID = "ESP_" + chipID + "_AutoConnectAP";
    String AP_PASS = "MyESP_" + chipID;

    // From v1.1.0, Don't permit NULL password
    if ((Router_SSID == "") || (Router_Pass == "")) {
        Serial.println("[WM] We haven't got any access point credentials, so get them now");

        initialConfig = true;

        // Starts an access point
        //if (!ESP_wifiManager.startConfigPortal((const char *) ssid.c_str(), password))
        if (!ESP_wifiManager.startConfigPortal(AP_SSID.c_str(), AP_PASS.c_str()))
            Serial.println("[WM] Not connected to WiFi but continuing anyway.");
        else
            Serial.println("[WM] WiFi connected...yeey :)");

        // Stored  for later usage, from v1.1.0, but clear first
        memset(&WM_config, 0, sizeof(WM_config));

        for (uint8_t i = 0; i < NUM_WIFI_CREDENTIALS; i++) {
            String tempSSID = ESP_wifiManager.getSSID(i);
            String tempPW = ESP_wifiManager.getPW(i);

            if (strlen(tempSSID.c_str()) < sizeof(WM_config.WiFi_Creds[i].wifi_ssid) - 1)
                strcpy(WM_config.WiFi_Creds[i].wifi_ssid, tempSSID.c_str());
            else
                strncpy(WM_config.WiFi_Creds[i].wifi_ssid, tempSSID.c_str(), sizeof(WM_config.WiFi_Creds[i].wifi_ssid) - 1);

            if (strlen(tempPW.c_str()) < sizeof(WM_config.WiFi_Creds[i].wifi_pw) - 1)
                strcpy(WM_config.WiFi_Creds[i].wifi_pw, tempPW.c_str());
            else
                strncpy(WM_config.WiFi_Creds[i].wifi_pw, tempPW.c_str(), sizeof(WM_config.WiFi_Creds[i].wifi_pw) - 1);

            // Don't permit NULL SSID and password len < MIN_AP_PASSWORD_SIZE (8)
            if ((String(WM_config.WiFi_Creds[i].wifi_ssid) != "") && (strlen(WM_config.WiFi_Creds[i].wifi_pw) >= MIN_AP_PASSWORD_SIZE)) {
                LOGERROR3(F("* Add SSID = "), WM_config.WiFi_Creds[i].wifi_ssid, F(", PW = "), WM_config.WiFi_Creds[i].wifi_pw);
                wifiMulti.addAP(WM_config.WiFi_Creds[i].wifi_ssid, WM_config.WiFi_Creds[i].wifi_pw);
            }
        }

        saveWifiConfigData();
    } else {
        wifiMulti.addAP(Router_SSID.c_str(), Router_Pass.c_str());
    }

    startedAt = millis();

    if (!initialConfig) {
        // Load stored data, the addAP ready for MultiWiFi reconnection
        loadWifiConfigData();

        for (uint8_t i = 0; i < NUM_WIFI_CREDENTIALS; i++) {
            // Don't permit NULL SSID and password len < MIN_AP_PASSWORD_SIZE (8)
            if ((String(WM_config.WiFi_Creds[i].wifi_ssid) != "") && (strlen(WM_config.WiFi_Creds[i].wifi_pw) >= MIN_AP_PASSWORD_SIZE)) {
                LOGERROR3(F("* Add SSID = "), WM_config.WiFi_Creds[i].wifi_ssid, F(", PW = "), WM_config.WiFi_Creds[i].wifi_pw);
                wifiMulti.addAP(WM_config.WiFi_Creds[i].wifi_ssid, WM_config.WiFi_Creds[i].wifi_pw);
            }
        }

        if (WiFi.status() != WL_CONNECTED) {
            Serial.println("[WM] ConnectMultiWiFi in setup");

            connectMultiWiFi();
        }
    }

    Serial.print("[WM] After waiting ");
    Serial.print((float)(millis() - startedAt) / 1000L);
    Serial.print(" secs more in setup(), connection result is ");

    if (WiFi.status() == WL_CONNECTED) {
        Serial.print("[WM] connected. Local IP: ");
        Serial.println(WiFi.localIP());
    } else
        Serial.println(ESP_wifiManager.getStatus(WiFi.status()));
}

#endif // WIFI_CHUNKS_H