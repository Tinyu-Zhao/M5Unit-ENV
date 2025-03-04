/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5StickCPlus sample source code
*                          配套  M5StickCPlus 示例源代码
* Visit for more information: https://docs.m5stack.com/en/hat/hat_envII
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/hat/hat_envII
*
* Product: ENVII_SHT30_BMP280_BMM150.  环境传感器
* Date: 2023/2/7
*******************************************************************************
  Please connect to Port,Read temperature, humidity and atmospheric pressure and
  display them on the display screen
  请连接端口,读取温度、湿度和大气压强并在显示屏上显示
  Libraries:
  - [Adafruit_BMP280](https://github.com/adafruit/Adafruit_BMP280_Library)
  - [Adafruit_Sensor](https://github.com/adafruit/Adafruit_Sensor)
*/

#include <M5StickCPlus.h>
#include "M5_ENV.h"
#include <Adafruit_BMP280.h>
#include "Adafruit_Sensor.h"

SHT3X sht30(0x44, 1);
Adafruit_BMP280 bme;

float tmp      = 0.0;
float hum      = 0.0;
float pressure = 0.0;

void setup() {
    M5.begin();             // Init M5StickCPlus.  初始化 M5StickCPlus
    M5.Lcd.setRotation(3);  // Rotate the screen.  旋转屏幕
    Wire.begin(0, 26);
    M5.Lcd.println(F("ENVII Unit(SHT30 and BMP280) test...\n"));
}

void loop() {
    while (!bme.begin(0x76)) {  //初始化bme传感器.  Init the sensor of bme
        M5.Lcd.println("Could not find a valid BMP280 sensor, check wiring!");
    }
    pressure = bme.readPressure();  // Stores the pressure gained by BMP.
                                    // 存储bmp获取到的压强
    sht30.get();           // Obtain the data of shT30.  获取sht30的数据
    tmp = sht30.cTemp;     // Store the temperature obtained from shT30.
                           // 将sht30获取到的温度存储
    hum = sht30.humidity;  // Store the humidity obtained from the SHT30.
                           // 将sht30获取到的湿度存储
    M5.Lcd.setCursor(0, 20);
    M5.Lcd.fillRect(0, 20, 100, 60,
                    BLACK);  // Fill the screen with black (to clear the
                             // screen).  将屏幕填充满黑色(用来清屏)
    M5.Lcd.printf("Temp: %2.1f  \r\nHumi: %2.0f%%  \r\nPressure:%2.0fPa\r\n",
                  tmp, hum, pressure);
    delay(2000);
}
