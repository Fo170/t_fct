// t_fct – basic example
// Prints uptime and estimated boot time to Serial every second.

#include <t_fct.h>

// NTP configuration (France)
const char* ntpServer = "fr.pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Connect to Wi-Fi (required for NTP)
  WiFi.begin("your-ssid", "your-password");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  INIT_Temp_fct();

  Serial.println("t_fct ready");
}

void loop() {
  Calcule_Temp_fct();

  Serial.print("Uptime: ");
  Serial.print(t_fct, 1);
  Serial.println(" s");

  Serial.print("Boot time: ");
  Serial.println(getBootTimeString());

  delay(1000);
}
