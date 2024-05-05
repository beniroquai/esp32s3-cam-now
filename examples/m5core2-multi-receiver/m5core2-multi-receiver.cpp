/**************************************************
 * ESPNowCam video Receiver
 * by @hpsaturn Copyright (C) 2024
 * This file is part ESP32S3 camera tests project:
 * https://github.com/hpsaturn/esp32s3-cam
**************************************************/

#include <Arduino.h>
#include <M5Unified.h>
#include "ESPNowCam.h"
#include "Utils.h"

ESPNowCam radio;

// frame buffer camera1
uint8_t *fb_camera1; 
// frame buffer camera2
uint8_t *fb_camera2; 
// display globals
int32_t dw, dh;

void onCamera1DataReady(uint32_t lenght) {
  // Serial.println("onDataReady");
  M5.Display.drawJpg(fb_camera1, lenght , 0, 0, dw, dh);
  // printFPS("M5Core2:");
}

void onCamera2DataReady(uint32_t lenght) {
  // Serial.println("onDataReady");
  M5.Display.drawJpg(fb_camera2, lenght , 161, 0, dw, dh);
  // printFPS("M5Core2:");
}

void setup() {
  Serial.begin(115200);
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Display.setBrightness(96);
  dw=M5.Display.width();
  dh=M5.Display.height();

  if(psramFound()){
    size_t psram_size = esp_spiram_get_size() / 1048576;
    Serial.printf("PSRAM size: %dMb\r\n", psram_size);
  }

  // BE CAREFUL WITH IT, IF JPG LEVEL CHANGES, INCREASE IT
  fb_camera1 = (uint8_t*)  ps_malloc(5000* sizeof( uint8_t ) ) ;
  fb_camera2 = (uint8_t*)  ps_malloc(5000* sizeof( uint8_t ) ) ;

  // TJournal 24:0a:c4:2f:8e:90
  uint8_t camera1[6] = {0x24, 0x0A, 0xC4, 0x2F, 0x8E, 0x90};
  // XIAOSense Camera 74:4d:bd:81:4e:fc
  uint8_t camera2[6] = {0x74, 0x4D, 0xBD, 0x81, 0x4E, 0xFC};

  radio.addMultiSender(fb_camera1, camera1, onCamera1DataReady);
  radio.addMultiSender(fb_camera2, camera2, onCamera2DataReady);

  if (radio.init()) {
    // M5.Display.drawString("ESPNow Init Success", dw / 2, dh / 2);
  } 
  delay(500);
}

void loop() {
}
