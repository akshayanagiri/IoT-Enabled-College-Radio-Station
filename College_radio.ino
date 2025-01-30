#include "Arduino.h"
#include "WiFi.h"
#include "Audio.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define I2S_DOUT  25
#define I2S_BCLK  27
#define I2S_LRC   26

Audio audio;
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column, 2 row LCD

void setup() {
  Serial.begin(115200);

  // Initialize the LCD and display the message
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Live Radio");
  lcd.setCursor(0, 1);
  lcd.print("Station from Ace");

  // Connect to WiFi
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin("wifi_name", "password");

  // Wait for the WiFi connection to establish
  while (WiFi.status() != WL_CONNECTED)
    delay(1500);

  // Set I2S pins
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);

  // Set volume to maximum
  audio.setVolume(100);

  // Connect to the audio stream
  audio.connecttohost("https://mp3.ffh.de/ffhchannels/80er.aac");
}

void loop() {
  // Keep the audio stream running
  audio.loop();
}

void audio_info(const char *info) {
  Serial.print("audio_info: ");
  Serial.println(info);
}
