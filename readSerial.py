import serial
import csv
import time

# Configure the serial port and baud rate
ser = serial.Serial('COM5', 9600, timeout=1)  # Adjust 'COM5' as needed
time.sleep(2)  # Wait for the connection to establish

# Open a CSV file for writing
with open('mpu6050_data.csv', mode='w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(['Ax', 'Ay', 'Az'])  # Write header

    try:
        while True:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8').strip()
                try:
                    ax, ay, az = map(float, line.split(','))
                    writer.writerow([ax, ay, az])  # Write data to CSV
                    print(f'Ax: {ax}, Ay: {ay}, Az: {az}')
                except ValueError:
                    print("Data format error")
    except KeyboardInterrupt:
        print("Exiting...")

ser.close()