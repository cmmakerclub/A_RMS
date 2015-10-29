#include <Wire.h>

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pinMode(16, OUTPUT);
  delay(1000);
  digitalWrite(13, HIGH);
  digitalWrite(16, LOW);
}

void loop()
{
  Read_ARMS();
  delay(500);
}
void Read_ARMS()  {
  Wire.requestFrom(1, 2);
  delay(10);
  int line2 = Wire.read() << 8 | Wire.read();
   Serial.print(line2);
}
