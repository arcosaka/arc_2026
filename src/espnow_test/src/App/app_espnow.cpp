/**
 * @file app_espnow.cpp
 * @version 26060619.530
 */

#ifdef USE_ESPNOW
#include "app_espnow.h"
#include "Mid/mid_m5stack.h"

#include "ESP32_NOW.h"
#include "WiFi.h"
#include <esp_mac.h>  // For the MAC2STR and MACSTR macros
#include <vector>
#include <new>  //std::nothrow


//******************************************************
// グローバル変数定義
//******************************************************

volatile U_PAYLOAD u_payload;

//******************************************************
// ローカル型定義
//******************************************************

//******************************************************
// ローカル変数定義
//******************************************************

// Wi-Fi interface to be used by the ESP-NOW protocol
#define ESPNOW_WIFI_IFACE WIFI_IF_STA

// Channel to be used by the ESP-NOW protocol
#define ESPNOW_WIFI_CHANNEL 4

// Delay between sending messages
#define ESPNOW_SEND_INTERVAL_MS 5000

// Number of peers to wait for (excluding this device)
#define ESPNOW_PEER_COUNT 2

// Report to other devices every 5 messages
#define REPORT_INTERVAL 5

// Primary Master Key (PMK) and Local Master Key (LMK)
#define ESPNOW_EXAMPLE_PMK "pmk1234567890123"
#define ESPNOW_EXAMPLE_LMK "lmk1234567890123"

uint32_t self_priority = 0;             // Priority of this device
uint8_t current_peer_count = 0;         // Number of peers that have been found
bool device_is_master = false;          // Flag to indicate if this device is the master
bool master_decided = false;            // Flag to indicate if the master has been decided
uint32_t sent_msg_count = 0;            // Counter for the messages sent. Only starts counting after all peers have been found
uint32_t recv_msg_count = 0;            // Counter for the messages received. Only starts counting after all peers have been found
U_PAYLOAD new_msg;                      // Message that will be sent to the peers
std::vector<u1*> last_data(5);          // Vector that will store the last 5 data received


class ESP_NOW_Network_Peer : public ESP_NOW_Peer {
public:
    uint32_t priority;
    bool peer_is_master = false;
    bool peer_ready = false;

    ESP_NOW_Network_Peer(const uint8_t* mac_addr, uint32_t priority = 0, const uint8_t* lmk = (const uint8_t*)ESPNOW_EXAMPLE_LMK)
        : ESP_NOW_Peer(mac_addr, ESPNOW_WIFI_CHANNEL, ESPNOW_WIFI_IFACE, lmk), priority(priority) {
    }

    ~ESP_NOW_Network_Peer() {
    }

    bool begin() {
      // In this example the ESP-NOW protocol will already be initialized as we require it to receive broadcast messages.
        if (!add()) {
            log_e("Failed to initialize ESP-NOW or register the peer");
            return false;
        }
        return true;
    }

    bool send_message(const uint8_t* data, size_t len) {
        if (data == nullptr || len == 0) {
            log_e("Data to be sent is NULL or has a length of 0");
            return false;
        }

        // Call the parent class method to send the data
        return send(data, len);
    }

    void onReceive(const uint8_t* data, size_t len, bool broadcast) {
        U_PAYLOAD* msg = (U_PAYLOAD*)data;

        if (peer_ready == false) {
            Serial.printf("Peer " MACSTR " reported ready\n", MAC2STR(addr()));
            peer_ready = true;
        }

        if (!broadcast) {
            recv_msg_count++;
            if (device_is_master) {
                Serial.printf("Received a message from peer " MACSTR "\n", MAC2STR(addr()));
                Serial.printf("  Count: %lu\n", msg->s_payload.timestamp);
                Serial.printf("  Random data: %lu\n", msg->s_payload.randdata);
                last_data.push_back(msg->bytes);
                last_data.erase(last_data.begin());
            }
            else if (peer_is_master) {
                Serial.println("Received a message from the master");
                Serial.printf("  Average data: %lu\n", msg->bytes);
            }
            else {

            }
        }
    }

    void onSent(bool success) {
        bool broadcast = memcmp(addr(), ESP_NOW.BROADCAST_ADDR, ESP_NOW_ETH_ALEN) == 0;
        if (broadcast) {
            log_i("Broadcast message reported as sent %s", success ? "successfully" : "unsuccessfully");
        }
        else {
            log_i("Unicast message reported as sent %s to peer " MACSTR, success ? "successfully" : "unsuccessfully", MAC2STR(addr()));
        }
    }
};


/* Peers */

// Create a vector to store the peer pointers
std::vector<ESP_NOW_Network_Peer*> peers;
// Register the broadcast peer (no encryption support for the broadcast address)
ESP_NOW_Network_Peer broadcast_peer(ESP_NOW.BROADCAST_ADDR, 0, nullptr);
// Pointer to the peer that is the master
ESP_NOW_Network_Peer* master_peer = nullptr;


//******************************************************
// ローカル関数宣言
//******************************************************

//******************************************************
// 関数定義
//******************************************************

// Callback called when a new peer is found
void register_new_peer(const esp_now_recv_info_t *info, const uint8_t *data, int len, void *arg) {
  esp_now_data_t *msg = (esp_now_data_t *)data;
  int priority = msg->priority;

  if (priority == self_priority) {
    Serial.println("ERROR! Device has the same priority as this device. Unsupported behavior.");
    fail_reboot();
  }

  if (current_peer_count < ESPNOW_PEER_COUNT) {
    Serial.printf("New peer found: " MACSTR " with priority %d\n", MAC2STR(info->src_addr), priority);
    ESP_NOW_Network_Peer *new_peer = new (std::nothrow) ESP_NOW_Network_Peer(info->src_addr, priority);
    if (new_peer == nullptr || !new_peer->begin()) {
      Serial.println("Failed to create or register the new peer");
      delete new_peer;
      return;
    }
    peers.push_back(new_peer);
    current_peer_count++;
    if (current_peer_count == ESPNOW_PEER_COUNT) {
      Serial.println("All peers have been found");
      new_msg.ready = true;
    }
  }
}

void espnow_setup(void) {
    // Initialize the Wi-Fi module
    WiFi.mode(WIFI_STA);
    WiFi.setChannel(ESPNOW_WIFI_CHANNEL);
    while (!WiFi.STA.started()) {
        delay(100);
    }

    M5.Log.println("ESP-NOW Network Example");
    M5.Log.println("Wi-Fi parameters:");
    M5.Log.println("  Mode: STA");
    M5.Log.print("  MAC Address: ");
    M5.Log.println(WiFi.macAddress().c_str());
    M5.Log.printf("  Channel: %d\n", ESPNOW_WIFI_CHANNEL);

    // Initialize the ESP-NOW protocol
    if (!ESP_NOW.begin((const uint8_t *)ESPNOW_EXAMPLE_PMK)) {
        M5.Log.println("Failed to initialize ESP-NOW");
        fail_reboot();
    }

    M5.Log.printf("ESP-NOW version: %d, max data length: %d\n", ESP_NOW.getVersion(), ESP_NOW.getMaxDataLen());


    if (!broadcast_peer.begin()) {
        Serial.println("Failed to initialize broadcast peer");
        fail_reboot();
    }

    // Register the callback to be called when a new peer is found
    ESP_NOW.onNewPeer(register_new_peer, nullptr);

    Serial.println("Setup complete. Broadcasting own priority to find the master...");
    memset(&new_msg, 0, sizeof(new_msg));
    strncpy(new_msg.str, "Hello!", sizeof(new_msg.str));
    new_msg.priority = self_priority;

}


// Function to reboot the device
void fail_reboot() {
    Serial.println("Rebooting in 5 seconds...");
    delay(5000);
    ESP.restart();
}

#endif /* USE_ESPNOW */
