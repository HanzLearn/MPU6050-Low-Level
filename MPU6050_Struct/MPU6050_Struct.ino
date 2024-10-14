#include <Wire.h>

#define MPU6050_ADDRESS 0x68
#define PWR_MGMT_1 0x6B
#define ACCEL_CONFIG 0x1C

struct MPU6050
{
  struct Acceleration
  {
    
    float x;
    float y;
    float z;

    void printData()
  {
    Serial.println("Acceleration:");
    Serial.print("X : ");
    Serial.println(x);
    Serial.print("Y : ");
    Serial.println(y);
    Serial.print("Z : ");
    Serial.println(z);
  }

} accel;

  void begin()
  {
    
    Wire.beginTransmission(MPU6050_ADDRESS); // Writing to I2C device (MPU6050)
    Wire.write(PWR_MGMT_1); // Writing to Power Management 1 register
    Wire.write(0);  // Setting sleep mode to 0
    Wire.endTransmission(); // closing bus

    Wire.beginTransmission(MPU6050_ADDRESS); //I2C address of the MPU
    Wire.write(ACCEL_CONFIG); //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5) 
    Wire.write(0b00000000); //Setting the accel to +/- 2g
    Wire.endTransmission();

  }

  Acceleration readAcceleration(Acceleration* myAccel)
  {

    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(0x3B);
    Wire.endTransmission(false);

    Wire.requestFrom(MPU6050_ADDRESS,6);
    myAccel->x = Wire.read() << 8 | Wire.read();
    myAccel->y = Wire.read() << 8 | Wire.read();
    myAccel->z = Wire.read() << 8 | Wire.read();

    myAccel->x /= 16384.0; // Convert data to readable values in g (defined as 16384.0 LSB/g)
    myAccel->y /= 16384.0;
    myAccel->z /= 16384.0;
    
  }

  
};


void setup() 
{

  Serial.begin(9600);
  Wire.begin();
  MPU6050 mpu;
  mpu.begin();

}

void loop() 
{ 
  // MPU6050 mpu;
  MPU6050* pMPU =(MPU6050*) malloc(sizeof(MPU6050));
  
  MPU6050::Acceleration myAccel;
  MPU6050::Acceleration* pMyAccel = &myAccel;
  if (pMPU != nullptr)
  {
    pMPU->readAcceleration(&myAccel);
    myAccel.printData();
    free(pMPU);

  }
  else 
  {
    Serial.print("Memory Allocation failed!");

  }
  
  
  delay(1000);
}
