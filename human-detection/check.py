import serial #for Serial communication
import time   #for delay functions
 
arduino = serial.Serial('com3',9600) #Create Serial port object called arduinoSerialData
time.sleep(2) #wait for 2 secounds for the communication to get established

while True:
    var = arduino.readline()
    print(var)
    val = var.strip('\n')
    val2 = val.strip('\r')
    print(val)
    if val2 == "1":
		break
