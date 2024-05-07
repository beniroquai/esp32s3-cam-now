/**************************************************
 * ESPNowCam video Receiver
 * by @hpsaturn Copyright (C) 2024
 * This file is part ESP32S3 camera tests project:
 * https://github.com/hpsaturn/esp32s3-cam
**************************************************/

#include <Arduino.h>
#include "ESPNowCam.h"
#include "Utils.h"

ESPNowCam radio;

// frame buffer camera1
uint8_t *fb_camera1; 
// frame buffer camera2
uint8_t *fb_camera2; 
// frame buffer camera2
uint8_t *fb_camera3;
// display globals
int32_t dw, dh;

void onCamera1DataReady(uint32_t lenght) {
    Serial.print("Camera1: ");
    //Serial.println(fb_camera1);
  //M5.Display.drawJpg(fb_camera1, lenght , 0, 0, dw, dh);
}

void onCamera2DataReady(uint32_t lenght) {
    Serial.print("Camera2: ");
    //Serial.println(fb_camera2);
  //M5.Display.drawJpg(fb_camera2, lenght , 161, 0, dw, dh);
}

void onCamera3DataReady(uint32_t lenght) {
    Serial.print("Camera3: ");
    //Serial.println(fb_camera3->length);    
  //M5.Display.drawJpg(fb_camera3, lenght , 0, 121, dw, dh);
}

void setup() {
  Serial.begin(115200);
  
  /*
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Display.setBrightness(96);
  dw=M5.Display.width();
  dh=M5.Display.height();

  if(psramFound()){
    size_t psram_size = esp_spiram_get_size() / 1048576;
    Serial.printf("PSRAM size: %dMb\r\n", psram_size);
  }
*/
  // BE CAREFUL WITH IT, IF JPG LEVEL CHANGES, INCREASE IT
  fb_camera1 = (uint8_t*)  ps_malloc(5000* sizeof( uint8_t ) ) ;
  fb_camera2 = (uint8_t*)  ps_malloc(5000* sizeof( uint8_t ) ) ;
  fb_camera3 = (uint8_t*)  ps_malloc(5000* sizeof( uint8_t ) ) ;

/*
EC:DA:3B:41:63:5C
EC:DA:3B:41:6B:24
EC:DA:3B:41:3F:60
EC:DA:3B:41:7B:7C
*/
  uint8_t camera1[6] = {0xEC, 0xDA, 0x3B, 0x41, 0x63, 0x5C};
  uint8_t camera2[6] = {0xEC, 0xDA, 0x3B, 0x41, 0x6B, 0x24};
  uint8_t camera3[6] = {0xEC, 0xDA, 0x3B, 0x41, 0x3F, 0x60};

  radio.setRecvFilter(fb_camera1, camera1, onCamera1DataReady);
  radio.setRecvFilter(fb_camera2, camera2, onCamera2DataReady);
  radio.setRecvFilter(fb_camera3, camera3, onCamera3DataReady);

  if (radio.init()) {
    Serial.println("Radio Init OK");
  } 
  delay(500);
}

void loop() {
}
