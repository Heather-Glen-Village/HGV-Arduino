from pyModbusTCP.client import ModbusClient
from unit16_converters import floatConvertion
from time import sleep

slave_address = '127.0.0.1'
port = 502
unit_id = 1

class Modbus:
    
    def __init__(self, host, port, unit_id):
        self.host = host
        self.port = port
        self.unit = unit_id
        self.auto_open = False
        self.auto_close = False
        
        self.modbus_client = None
        self.response = None
        
    def modbus_connect(self):
        
        if not self.modbus_client:
            print("Creating modbus clinet instance")
            self.modbus_client = ModbusClient(host=self.host, port=self.port, unit_id=self.unit, auto_open=self.auto_open, auto_close=self.auto_close)
            
            
            print("Creating connection")
            
            if self.modbus_client.open():
                print("Connectted to Modbus Server at: ", self.host )
            else:
                print("Connected to Modbus Server at: ", self.host, " Failed!")
                self.modbus_client = None
                
    def modbus_request(self, start_address=0, reg_no=5, function_code=1, data=[]):
        
        if self.modbus_client:
            
            if function_code == 1:
                self.response = self.modbus_client.read_coils(start_address, reg_no)
            elif function_code == 2:
                self.response = self.modbus_client.read_discrete_inputs(start_address, reg_no)
            elif function_code == 3:
                self.response = self.modbus_client.read_holding_registers(start_address, reg_no)
            elif function_code == 4:
                self.response = self.modbus_client.read_input_registers(start_address, reg_no)
            elif function_code == 11:
                self.response = self.modbus_client.write_single_coil(start_address, data[0])
            elif function_code == 21:
                self.response = self.modbus_client.write_multiple_coils(start_address, data)
            elif function_code == 13:
                self.response = self.modbus_client.write_single_register(start_address, data[0])
            elif function_code == 23:
                self.response = self.modbus_client.write_multiple_registers(start_address, data)

        if self.response:
            print("modbus response: ", self.response)
        else:
            print("No modbus response")
        
        return self.response 

Modbus_Clinet = Modbus('127.0.0.1',502,1)

Modbus_Clinet.modbus_connect()
while True:
    unitfloat = Modbus_Clinet.modbus_request(0,4,4)
    Convertedtemp = floatConvertion(unitfloat[0], unitfloat[1])
    Convertedhimid = floatConvertion(unitfloat[2], unitfloat[3])
    print(f"temp={Convertedtemp}, himid={Convertedhimid}")
    sleep(2)
    motion = Modbus_Clinet.modbus_request(0,1,2)
    print(f"Was There Motion? {motion}")
    sleep(5)
