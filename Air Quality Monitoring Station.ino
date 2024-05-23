#include "U8glib.h"
#include <Arduino.h>
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);
int UVOUT = A0; //Output from the sensor
int REF_3V3 = A1; //3.3V power on the Arduino board



void draw2(void) {
   int uvLevel = averageAnalogRead(UVOUT);
  int refLevel = averageAnalogRead(REF_3V3);
  
  //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
  float outputVoltage = 3.3 / refLevel * uvLevel;

 delay(2000);
  float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); //Convert the voltage to a UV intensity level
  Serial.print("UV measurement");
  Serial.print("UV voltage: ");
  Serial.print(outputVoltage);
  Serial.print("\n");
  Serial.print("UV Intensity (mW/cm^2): ");
  Serial.print(uvIntensity);
  Serial.println();
  delay(200);

  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(0, 10);
  u8g.print("UV voltage: ");
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(0, 25);
  u8g.print(outputVoltage);
}

void setup()
{
  Serial.begin(9600);
  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);
  Serial.println("ML8511 example"); 
}

void loop()
{
  u8g.firstPage();
  do {
    draw();
  } while (u8g.nextPage() );
  delay(800);
  u8g.firstPage();
  do {
    draw2();
  } while (u8g.nextPage());
  delay(800);
u8g.firstPage();
  do {
    draw3();
  } while (u8g.nextPage());
  delay(800);

}
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 
  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;
  return(runningValue);
}
void draw3(void) {
 

 float sensor_volt;  
 float RS_air; //  Rs in clean air 
 float R0;  // R0 in 1000 ppm LPG 
 float sensorValue; 
//Average   
   for(int x = 0 ; x < 100 ; x++) 
 { 
   sensorValue = sensorValue + analogRead(A0); 
 } 
 sensorValue = sensorValue/100.0; 
//-----------------------------------------------/ 
 sensor_volt = (sensorValue/1024)*5.0; 
 RS_air = (5.0-sensor_volt)/sensor_volt; // Depend on RL on yor module 
 R0 = RS_air/9.9; // According to MQ9 datasheet table 
 Serial.print("-------CO measurement------ "); 
 Serial.print("CO_volt = "); 
 Serial.print(sensor_volt); 
 Serial.println("V");
 Serial.print("R0 = "); 
 Serial.println(R0); 
 delay(1000); 


 u8g.setFont(u8g_font_profont10);
  u8g.setPrintPos(0, 10);
  u8g.println("CO_volt = ");
  u8g.setFont(u8g_font_profont10);
  u8g.setPrintPos(0, 25);
  u8g.print(sensor_volt);
  u8g.setPrintPos(0, 40);
  
  
}

void draw(void) {
  int mq135Value = analogRead(A0); // read the input on analog pin 0:
  u8g.setFont(u8g_font_profont10);
  u8g.setPrintPos(0, 10);
  u8g.println("CO2_MEASUREMENT");
  u8g.setFont(u8g_font_profont10);
  u8g.setPrintPos(0, 25);
  u8g.println(" CO2 (in PPM):");
  u8g.print(mq135Value);
  u8g.setPrintPos(0, 40);
}

