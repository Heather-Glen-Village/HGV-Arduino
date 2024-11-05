from flask import Flask, render_template, redirect, request
from flask_scss import Scss
from flask_sqlalchemy import SQLAlchemy
from unit16_converters import floatToUint16
from ModbusTCPClient import Modbus
from datetime import datetime

# My App Setup
app = Flask(__name__)
Scss(app)

ModbusHost = 'localhost'
Modbusport = 1562
unitID = 1

modbusClient = Modbus(ModbusHost,Modbusport,unitID)
connection = modbusClient.modbusConnect()

app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///database.db"
db = SQLAlchemy(app)

# Data Class ~ Row of data
class SensorData(db.Model):
    time = db.Column(db.DateTime(), default=datetime.now(), nullable=False, primary_key=True)
    temperature_DHT22 = db.Column(db.Float())
    temperature_DS18B20 = db.Column(db.Float())
    humidity_DHT22 = db.Column(db.Float())
    motion = db.Column(db.Boolean())
    smoke = db.Column(db.Boolean())
    waterLeak = db.Column(db.Boolean())
    vibration = db.Column(db.Boolean())
    
    def __repr__(self) -> str:
        return f"Task {self.id}" #forgot what this does
    
    
#Home Page
@app.route('/',methods=['POST', 'GET'])
def index():
    if request.method == 'POST':
        wantedTemp = float(request.form['content'])
        WT_Unit16 = [1,2]
        WT_Unit16[0], WT_Unit16[1] = floatToUint16(wantedTemp)
        
        try: 
            modbusClient.modbusWrite('hr',0,WT_Unit16, True)
            return modbusClient.modbusRead('hr',0,2)
        except Exception as e:
            print(f"ERROR: {e}")
            return f"ERROR: {e}"
    # See all current tasks
    else: 
        return render_template('index.html')

# Runner and Dubgger
if __name__ == '__main__':
    app.run(debug=True)