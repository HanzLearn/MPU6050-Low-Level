import serial
import time
import gspread
from oauth2client.service_account import ServiceAccountCredentials

# Setup Google Sheets API
scope = ["https://spreadsheets.google.com/feeds", "https://www.googleapis.com/auth/drive"]
creds = ServiceAccountCredentials.from_json_keyfile_name('credentials.json', scope)
client = gspread.authorize(creds)

# Replace 'YourSpreadsheetName' with the name of your Google Sheet
spreadsheet = client.open("MPU6050 Data")
worksheet = spreadsheet.sheet1

# Setup Serial
ser = serial.Serial('COM5', 9600)  # Adjust the port as necessary
time.sleep(2)  # Wait for the connection to establish

try:
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()  # Read line from Arduino
            print(f"Raw line: '{line}'")  # Print the raw line for debugging
            ax, ay, az = line.split(',')  # Split the data
            
            # Append data to Google Sheets
            worksheet.append_row([ax, ay, az])
            print(f"Logged: {ax}, {ay}, {az}")

except KeyboardInterrupt:
    print("Program stopped by user")
finally:
    ser.close()