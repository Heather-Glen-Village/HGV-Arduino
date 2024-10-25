from pyModbusTCP.server import ModbusServer, DataBank
from unit16_converters import floatToUint16
import random

#Create a Random Seed for Random Sensor Data
random.seed()
# Server parmaters
host = '127.0.0.1'
port = 502


def DHT22():
# Random test data
    temp = random.randint(-1000, 5000)/100
    himid = random.randint(5000, 20000)/100
    temp1, temp2 = floatToUint16(temp)
    himid1, himid2 = floatToUint16(himid)    
    return temp1, temp2, himid1, himid2, temp, himid

def motionsensor():
    #Random Test Data

    return random.choice([True, False])


class piDataBank(DataBank):
    def __init__(self):
        super().__init__()
        
    def get_input_registers(self, address, number=1, srv_info=None):
        
        
        #Collects Data Every time a new Request is called
        temp1, temp2, himid1, himid2, temp, himid = DHT22()
        print(temp)
        print(himid)
        
        #Enter Data into a list
        self._h_regs[0] = temp1
        self._h_regs[1] = temp2
        self._h_regs[2] = himid1
        self._h_regs[3] = himid2
        #Add Input Registe data to the Base data structure 

        try: 
            return[self._h_regs[i] for i in range(address, address+number)]
        except KeyError:
            return
    
    def get_discrete_inputs(self, address, number=1, srv_info=None):
       
        #Collects Data Every time a new Request is called
        motion = motionsensor()
        print(motion)
        
        #Add Data into a list
        self._d_inputs[0] = motion
        
        #Add Discrete input data to the Base data structure 
        try: 
            return[self._d_inputs[i] for i in range(address, address+number)]
        except KeyError:
            return
        
if __name__ == '__main__':
    Server = ModbusServer(host=host, port=port, data_bank=piDataBank())
    Server.start()