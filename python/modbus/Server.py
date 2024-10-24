from pyModbusTCP.server import ModbusServer, DataBank
from unit16_converters import floatToUint16
import random
import time
import logging

logging.basicConfig()
logging.getLogger('pyModbusTCP.server').setLevel(logging.DEBUG)

# Server parmaters
host = '127.0.0.1'
port = 502

random.seed()
def DHT22():
# Random test data
    temp = random.randint(-1000, 5000)/100
    himid = random.randint(5000, 20000)/100
    temp1, temp2 = floatToUint16(temp)
    himid1, himid2 = floatToUint16(himid)    
    return temp1, temp2, himid1, himid2, temp, himid

def motionsensor():
    return random.choice([True, False])


class piDataBank(DataBank):
    def __init__(self):
        super().__init__()
        
    def get_input_registers(self, address, number=1, srv_info=None):
        
        temp1, temp2, himid1, himid2, temp, himid = DHT22()
        print(temp)
        print(himid)
        self._h_regs[0] = temp1
        self._h_regs[1] = temp2
        self._h_regs[2] = himid1
        self._h_regs[3] = himid2
        
        try: 
            return[self._h_regs[i] for i in range(address, address+number)]
        except KeyError:
            return
    
    def get_discrete_inputs(self, address, number=1, srv_info=None):
        
        motion = motionsensor()
        print(motion)
        self._d_inputs[0] = motion
        try: 
            return[self._d_inputs[i] for i in range(address, address+number)]
        except KeyError:
            return
        
if __name__ == '__main__':
    Server = ModbusServer(host=host, port=port, data_bank=piDataBank())
    Server.start()