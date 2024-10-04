#include <Wire.h>
#define MPU_ADDRESS 0b1101000

long accelX,accelY,accelZ;
float gForceX,gForceY,gForceZ;

void setupMPU()
{
 // put your setup code here, to run once:
Wire.beginTransmission(MPU_ADDRESS);
Wire.write(0x6B);
Wire.write(0b00000000);
Wire.endTransmission();

// Accelerometer config
Wire.beginTransmission(MPU_ADDRESS);
Wire.write(0x1C);
Wire.write(0b00000000);
Wire.endTransmission();
}

void setup() {
Serial.begin(9600);
Wire.begin();
setupMPU();
}

void recordAccelRegisters()
{
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(MPU_ADDRESS,6);
  if (Wire.available() == 6)
  {
    accelX = Wire.read() << 8 | Wire.read();
    accelY = Wire.read() << 8 | Wire.read();
    accelZ = Wire.read() << 8 | Wire.read();
  }
  processAccelData();

}

void processAccelData()
{
  gForceX = accelX / 16384.0;
  gForceY = accelY / 16384.0;
  gForceZ = accelZ / 16384.0;
}

void printData()
{
  Serial.println("gForceX");
  Serial.println(gForceX);
 /* Serial.println("gForceY");
  Serial.print(gForceY);*/
  Serial.println("gForceZ");
  Serial.println(gForceZ);
}

void loop() {
  // put your main code here, to run repeatedly:

  recordAccelRegisters();
  printData();
  delay(2000);
}
