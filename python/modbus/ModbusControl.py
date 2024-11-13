from unit16_converters import floatConvertion, floatToUint16
from Sqlite import Sensor, initDB, addReading
from ModbusTCPClient import Modbus
from decimal import Decimal, ROUND_UP
from time import sleep
from datetime import datetime

host = 'localhost'
port = 1562
unitID = 1
db_uri = "HGV_DB.db"

modbusClient = Modbus(host,port,unitID)
connection = modbusClient.modbusConnect()
session = initDB(db_uri)


while connection:
    
    #Reading Input Register and Discrete Input
    inputRegisters = modbusClient.modbusRead('ir',0,6)
    discreteInputs = modbusClient.modbusRead('di',0,4)
    
    #Temp Code Real Code Should be 
    #wantedtemp_unit16 = modbusClient.modbusRead('hr',0,2)
    #wantedtemp = floatConvertion(wantedtemp_unit16[0],wantedtemp_unit16[1])
    wantedtemp = 22
    wantedtemp_unit16 = floatToUint16(wantedtemp)
    modbusClient.modbusWrite('hr',0,wantedtemp_unit16,True)
    wantedhimid = 22
    wantedhimid_unit16 = floatToUint16(wantedhimid)
    modbusClient.modbusWrite('hr',2,wantedhimid_unit16,True)
    #Turn Unit16 into floats and rounds to 2 Decimals
    
    convertedDHT22= Decimal(str(floatConvertion(inputRegisters[0], inputRegisters[1]))).quantize(Decimal('.01'), rounding=ROUND_UP)
    convertedDS18B20 = Decimal(str(floatConvertion(inputRegisters[2], inputRegisters[3]))).quantize(Decimal('.01'), rounding=ROUND_UP) 
    convertedHumidity= Decimal(str(floatConvertion(inputRegisters[4], inputRegisters[5]))).quantize(Decimal('.01'), rounding=ROUND_UP)   

    print("Writing To DB")
    print(f"Time: {datetime.now()} DHT22: {convertedDHT22}, DS18B20: {convertedDS18B20}, Humidity: {convertedHumidity}, Motion: {discreteInputs[0]},  Smoke: {discreteInputs[1]}, Water Leak: {discreteInputs[2]}, Vibtation: {discreteInputs[3]}")
    #Adding Data to DB
    addReading(session, datetime.now(), convertedDHT22, convertedDS18B20, convertedHumidity, discreteInputs[0], discreteInputs[1], discreteInputs[2], discreteInputs[3],22, 64)
    sleep(5)