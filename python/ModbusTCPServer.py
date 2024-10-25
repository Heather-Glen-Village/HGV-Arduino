from pyModbusTCP.server import ModbusServer, DataBank
from unit16_converters import floatToUint16
import random

#Create a Random Seed for Random Sensor Data
random.seed()
# Server parmaters
host = '127.0.0.1'
port = 1562


def randomfloats():
# Random test data
    DHT22 = random.randint(-1000, 5000)/100
    DS18B20 = DHT22+(random.randint(-300,300)/100)
    humidity = random.randint(5000, 20000)/100
    DHT22_1, DHT22_2 = floatToUint16(DHT22)
    DS18B20_1, DS18B20_2 = floatToUint16(DS18B20)
    humidity_1, humidity_2 = floatToUint16(humidity)    
    return DHT22_1, DHT22_2, DS18B20_1, DS18B20_2, humidity_1, humidity_2, DHT22, DS18B20, humidity

def randombool():
    #Random Test Dat
    return random.choice([True, False])


class piDataBank(DataBank):
    def __init__(self):
        super().__init__()
        
    def get_input_registers(self, address, number=1, srv_info=None):
        
        
        #Collects Data Every time a new Request is called
        DHT22_1, DHT22_2, DS18B20_1, DS18B20_2, humidity_1, humidity_2, DHT22, DS18B20, humidity = randomfloats()
        print(f'DHT22 = {DHT22}')
        print(f'DS18B20 = {DS18B20}')
        print(f'humidity = {humidity}')
        print()
        #Enter Data into a list
        self._h_regs[0] = DHT22_1
        self._h_regs[1] = DHT22_2
        self._h_regs[2] = DS18B20_1
        self._h_regs[3] = DS18B20_2
        self._h_regs[4] = humidity_1
        self._h_regs[5] = humidity_2
        #Add Input Registe data to the Base data structure 

        try: 
            return[self._h_regs[i] for i in range(address, address+number)]
        except KeyError:
            return
    
    def get_discrete_inputs(self, address, number=1, srv_info=None):
       
        #Collects Data Every time a new Request is called
        
        motion = randombool()
        print(f'motion = {motion}')
        
        smoke = randombool()
        print(f'smoke = {smoke}')
        
        waterLeak = randombool()
        print(f'waterLeak = {waterLeak}')
        
        vibration = randombool()
        print(f'vibration = {vibration}')
        
        #Add Data into a list
        self._d_inputs[0] = motion
        self._d_inputs[1] = smoke
        self._d_inputs[2] = waterLeak
        self._d_inputs[3] = vibration
        
        print()
        
        #Add Discrete input data to the Base data structure 
        try: 
            return[self._d_inputs[i] for i in range(address, address+number)]
        except KeyError:
            return
        
if __name__ == '__main__':
    Server = ModbusServer(host=host, port=port, data_bank=piDataBank())
    print("Server has Started!")
    Server.start()
    