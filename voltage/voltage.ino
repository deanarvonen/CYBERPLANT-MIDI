#include "U8glib.h"            // U8glib library for the OLED


int analogInput = 0;
float R1 = 120; // resistance of R1 (100K)
float R2 = 10; // resistance of R2 (10K)



U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0); // I2C / TWI
void draw(float batt_voltage)
{
  u8g.setFont(u8g_font_profont17r);        // select font
  u8g.drawStr(18, 12, "VOLTAGE");
  u8g.setPrintPos(33, 40);
  u8g.drawRFrame(15, 20, 100, 30, 10);     // draws frame with rounded edges
  u8g.println(batt_voltage);                        //Prints the voltage
  u8g.println("V");
}
void setup() {
  Serial.begin(9600);
  pinMode(analogInput, INPUT);
}
void loop() {
  // read the value at analog input
  int value = analogRead(analogInput);

  float pin_voltage = (value * 5.0) / 1024.0; // see text
  float batt_voltage = pin_voltage / (R2 / (R1 + R2));
  u8g.firstPage();
  do
  {
    draw(batt_voltage);
  }
  while ( u8g.nextPage() );
  delay(500);
}
