#include <Wire.h>

#define MPU6050_ADDRESS 0x68  // MPU6050 I2C address

// MPU6050 Registers
#define PWR_MGMT_1 0x6B
#define ACCEL_XOUT_H 0x3B

void setup() {
    Serial.begin(9600);
    Wire.begin();

    // Wake up the MPU6050 (default is sleep mode)
    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(PWR_MGMT_1); // Power management register
    Wire.write(0);           // Set to zero to wake up the MPU6050
    Wire.endTransmission();
}

void loop() {
    int16_t ax, ay, az;

    // Read the acceleration data
    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(ACCEL_XOUT_H); // Starting with the ACCEL_XOUT_H register
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050_ADDRESS, 6); // Request 6 bytes

    if (Wire.available() == 6) {
        ax = (Wire.read() << 8 | Wire.read()); // X-axis
        ay = (Wire.read() << 8 | Wire.read()); // Y-axis
        az = (Wire.read() << 8 | Wire.read()); // Z-axis

        ax = ax / 16384.0;
        ay = ay / 16384.0;
        az = az / 16384.0;
        // Send X, Y, Z values as comma-separated values
        Serial.print(ax);
        Serial.print(",");
        Serial.print(ay);
        Serial.print(",");
        Serial.println(az);
    }

    delay(100);  // Send data every 100 ms
}