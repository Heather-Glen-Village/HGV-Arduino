from pyModbusTCP.client import ModbusClient
from unit16_converters import floatConvertion
from time import sleep


Gateway_IP = "192.168.1.254"
Board_ID = 0

try: 
    clinet = ModbusClient(host="192.168.1.254", unit_id=Board_ID, auto_open=True, auto_close=False) 
except ValueError:
    print(f"Could not connect to Modbus server: {ValueError}")
    
    
while True:
    Input_Registers = clinet.read_input_registers(0,2)
    
    if Input_Registers:
        print(Input_Registers[0])
        print(Input_Registers[1])
    else:
        print("Error reading input registers")