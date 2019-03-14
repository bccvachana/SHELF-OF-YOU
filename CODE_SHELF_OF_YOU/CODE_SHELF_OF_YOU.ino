#include "HX711.h"
#include <Wire.h>
#include <EEPROM.h>

#define DOUT1  A0
#define CLK1   A1
#define DOUT2  A2
#define CLK2   A3

HX711 scale1(DOUT1, CLK1);
HX711 scale2(DOUT2, CLK2);

char input='0';
float level1constant; //น.น. 1 ชิ้น ชั้น 1 
float level2constant; //น.น. 1 ชิ้น ชั้น 2
float level1count; //จ.น. ชิ้น ชั้น 1
float level2count; //จ.น. ชั้น ชั้น 2

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available()) //รับ input จาก Bluetooth
  {
    input=Serial.read();
  }
  if (input=='1') //แสดงจำนวนสินค้าชั้น 1
  {
    level1count=(scale1.get_units(6)*0.045-16000)/EEPROM.get(0,level1constant); //น้ำหนักทั้งหมดหารน้ำหนักหนึ่งชิ้น
    Serial.println(round(level1count));
  }
  if (input=='2') //แสดงจำนวนสินค้าชั้น 2
  {
    level2count=(scale2.get_units(6)*0.08125-15850)/EEPROM.get(10,level2constant);
    Serial.println(round(level2count));
  }
  if (input=='3') //set สินค้าชั้น 1
  {
    level1constant=scale1.get_units(6)*0.045-16000;
    EEPROM.put(0, level1constant); 
    resetInput();
  }
  if (input=='4') //set สินค้าชั้น 2
  {
    level2constant=scale2.get_units(6)*0.08125-15850;
    EEPROM.put(10, level2constant); 
    resetInput();
  }
  delay(300);
}

void resetInput() {
  input = '0';
}

