from pyModbusTCP.client import ModbusClient
from unit16_converters import floatConvertion
from time import sleep
from decimal import Decimal, ROUND_UP

class Modbus:
    
    def __init__(self, host, port, unitID):
        self.host = host
        self.port = port
        self.unitID = unitID
        self.autoOpen = False
        self.autoClose = False
        self.Client = None
        self.response = None
        
    def modbusConnect(self):
        #Check if not alreaedy Connected
        if not self.Client:
            print("Creating modbus clinet instance")
            #Trys to Make a Connection
            self.modbusClient = ModbusClient(host=self.host, port=self.port, unit_id=self.unitID, auto_open=self.autoOpen, auto_close=self.autoClose)
            
            print("Creating connection")
            
            if self.modbusClient.open():
                print("Connected to Modbus Server at: ", self.host )
                return True
            else:
                print("Failed to Connect to Modbus Server at: ", self.host)
                self.modbusClient = None
                return False
                
                
    def modbusRead(self, Datatype='c', startAddress=0, quantity=1):
        # Ask for the Datatype You Wish to Read, Starting Address, and Amount to read
        
        if self.modbusClient:
            
            if Datatype.lower() == 'c':
                self.response = self.modbusClient.read_coils(startAddress, quantity)
            elif Datatype.lower() == 'di':
                self.response = self.modbusClient.read_discrete_inputs(startAddress, quantity)
            elif Datatype.lower() == 'hr':
                self.response = self.modbusClient.read_holding_registers(startAddress, quantity)
            elif Datatype.lower() == 'ir':
                self.response = self.modbusClient.read_input_registers(startAddress, quantity)
            else:
                raise TypeError(f'{Datatype} is not not a valid Datatype')
        if quantity == 1:
            return self.response[0]
        else:
            return self.response
    def modbusWrite(self, Datatype='c', startAddress=0, data=[], multiple=False):
        
        if self.modbusClient:
            
            if Datatype.lower() == 'c':
                if multiple==True:
                    self.response = self.modbusClient.write_multiple_coils(startAddress, data)
                elif multiple==False:
                    self.response = self.modbusClient.write_single_coil(startAddress, data[0])
            elif Datatype.lower() == 'hr':
                if multiple==True:
                    self.response = self.modbusClient.write_multiple_registers(startAddress, data)
                elif multiple==False:
                    self.response = self.modbusClient.write_single_register(startAddress, data[0])
            else:
                raise TypeError(f'{Datatype} is not not a valid Datatype')
                    
        return self.response 



# #Testing if it works

# # Server Parmaters
# host = '127.0.0.1'
# port = 1562
# unitID = 1
# #Create a Modbus Clinet and Trys to connect to Server
# modbusClient = Modbus(host,port,unitID)
# connection = modbusClient.modbusConnect()

# while connection:
#     inputRegisters = modbusClient.modbusRead('ir',0,4)
#     #Turn Unit16 into floats and rounds to 2 Decimals
#     convertedTemp = Decimal(str(floatConvertion(inputRegisters[0], inputRegisters[1]))).quantize(Decimal('.01'), rounding=ROUND_UP)
#     convertedHimid = Decimal(str(floatConvertion(inputRegisters[2], inputRegisters[3]))).quantize(Decimal('.01'), rounding=ROUND_UP)

    
#     motion = modbusClient.modbusRead('di',0,1)
#     print(f"temp={convertedTemp}, himid={convertedHimid}")
#     if motion[0] == True:
#         print("Yes There was motion")
#     else:
#         print("No Motion")
    
#     sleep(5)

#     modbusClient.modbusWrite('hr',0,[20])