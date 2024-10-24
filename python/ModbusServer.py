from pyModbusTCP.server import ModbusServer, DataBank
from python.modbus.unit16_converters import floatConvertion, floatToUint16
from random import uniform
from time import sleep

float_list = [1.12,2.732,3.853,4.854,5.585,6.153,7.435,8.123,9.142,10.324]

input_register_val = floatToUint16(float_list)
print(input_register_val)
input_register = []


server = ModbusServer("127.0.0.1", 12345, no_block=True)

try:
    print("Start server...")
    server.start()
    print("Server started")
    DataBank.set_coils(server,0,[1])  
    while True:
        sleep(0.5)
except Exception as e:
    print("Shutdown Server...")
    server.stop()
    print("Server is Offline")
    print(e)