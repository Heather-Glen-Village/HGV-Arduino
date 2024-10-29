from unit16_converters import floatConvertion, floatToUint16
from Sqlite import Sensor, initDB, addReading
from ModbusTCPClient import Modbus
from decimal import Decimal, ROUND_UP
from time import sleep
from datetime import datetime

host = '192.168.3.126'
port = 1562
unitID = 1

modbusClient = Modbus(host,port,unitID)
connection = modbusClient.modbusConnect()
session = initDB()


while connection:
    inputRegisters = modbusClient.modbusRead('ir',0,6)
    discreteInputs = modbusClient.modbusRead('di',0,4)
    #Turn Unit16 into floats and rounds to 2 Decimals
    convertedDHT22= Decimal(str(floatConvertion(inputRegisters[0], inputRegisters[1]))).quantize(Decimal('.01'), rounding=ROUND_UP)
    convertedDS18B20 = Decimal(str(floatConvertion(inputRegisters[2], inputRegisters[3]))).quantize(Decimal('.01'), rounding=ROUND_UP) 
    convertedHumidity= Decimal(str(floatConvertion(inputRegisters[4], inputRegisters[5]))).quantize(Decimal('.01'), rounding=ROUND_UP)   

    #Adding Data to DB
    addReading(session, datetime.now(), convertedDHT22, convertedDS18B20, convertedHumidity, discreteInputs[0], discreteInputs[1], discreteInputs[2], discreteInputs[3])
    sleep(5)