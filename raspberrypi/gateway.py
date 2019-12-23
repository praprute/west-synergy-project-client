import json
import time
import serial
import pyfirmata
import requests

# -----------------------กำหนดพอร์ท PI connect Arduino---------------------------------------------------#

ser = serial.Serial(
               port='/dev/ttyACM0',
               baudrate = 9600,
               parity=serial.PARITY_NONE,
               stopbits=serial.STOPBITS_ONE,
               bytesize=serial.EIGHTBITS,
               timeout=1
           )

# -------------------------------------------------------------------------------#

millis = int((time.time()))


while True:
    
        millis2 = int((time.time()))
        if(millis2 - millis >= 5):
            millis = int((time.time()))

# -------------------Gateway 1 lis node_name and id_node----------------------------------------------#
            
            idnode = "30"
            node_name  = "A1"
            node_name = str.encode(node_name)
            node_name = node_name.decode('utf-8')

# ----------------------Send node name for resend sensor---------------------------------------------------------#

            ser.write(str.encode(node_name))

# -----------------------Read Sensor--------------------------------------------------------#
            
            read_sensor = ser.readline()
            read_sensor = read_sensor.decode('ascii').strip()

# -----------------------Generate Json--------------------------------------------------------#
            
            data_buffer = {}
            data_buffer["idnode"]    = idnode
            data_buffer["node_name"] = node_name
            data_buffer["sensor"]    = read_sensor
            
            json_data = json.dumps(data_buffer)
            
            print(json_data)

# -------------------------Send Request to api------------------------------------------------------#
            
            headers = {'Content-type': 'application/json'}
            r = requests.post("http://192.168.1.62:3020/sensor",
                          data=json_data, headers=headers)
            
            print(r.json())