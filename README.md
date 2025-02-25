
# HGV Project REMS006 
A folder of all the code created during my time working at on the HGV Project. All the code is organize into folders with README in each explaning what each file does. 

Most of the code here is either just for testing hardware with only a few file being used in the final Arduino Code. All Docker Container should already be running on REMS006 so there isn't a need to reinstall them. asdfasd

The Main files for the Project Can be found in Primary and Secondarys Folders. Backup Docker Compose files and Conf can be found in the Docker Folder.
## Features

- RS485 Communications via ModbusRTU
- Module Sensor Addition 
- MQTT Messaging 
- NodeRed Setup
- Prometheus + Grafana


## Tech Used
All Items are link to Either the Main Page of the Item or Useful Resources

**Hardware:** 
[RS485](www.circuitstate.com/tutorials/what-is-rs-485-how-to-use-max485-with-arduino-for-reliable-long-distance-serial-communication/), 
Ethernet Port, 
(All The Sensors) 

**Arduino Library:** 
[SPI](https://docs.arduino.cc/learn/communication/spi/), 
[Ethernet](https://docs.arduino.cc/libraries/ethernet/), 
[ModbusRTUMaster](https://github.com/CMB27/ModbusRTUMaster), [ModbusRTUSlave](https://github.com/CMB27/ModbusRTUSlave), [PubSubClient](https://github.com/knolleary/pubsubclient), 
[ArduinoJson](https://arduinojson.org/), 
(All the Sensor Library)

**Docker Container:** 
[Mosquitto](https://github.com/sukesh-ak/setup-mosquitto-with-docker), 
[NodeRed](https://nodered.org/), 
[Prometheus](https://prometheus.io/), 
[Grafana](https://grafana.com/)

### Other
Some extra tools and resources That I used and could be helpful 
- [Circuitstate Doc on Modbus Communication](https://www.circuitstate.com/tutorials/what-is-modbus-communication-protocol-and-how-to-implement-modbus-rtu-with-arduino/)
- [Arduino Community Edition Plug-in](https://marketplace.visualstudio.com/items?itemName=vscode-arduino.vscode-arduino-community) 
## Installation
### Local
To Download all the Code Locally Open a Terminal and cd into a directory you wish to Download all of this  

```bash
  git clone https://github.com/TriforceGB/rems006-Arduino.git
```

### On REMS006
most if not all of this Repo should already be download onto rems006 but if not then your can run the command above or if it just not updated then you can run 

```bash
  git pull
```
in the folder or use the .sh command that should be already on REMS006 and just cancel befrore it start to upload to the Arduino 
## Things Left to Work on

- A Working RS485 Conntion

- Adding RTA/Home Intergartion (Changing Tempature)

- Adding Abilty to Read Primary Sensors (Smoke)


## Related Repository
Here are some Repo from other students that work on the HGV at the Sametime I did

[Arham's REMS005](https://github.com/HammyTheWammy/rems005)

[Zoya's REMS007](https://github.com/ElectricCornstarch/rems007)

[Abbas's REMS008](https://github.com/abbashaider1444/rems008)

[HGV Website](https://github.com/TriforceGB/HGV-Webapp)

[Custom .sh Shortcuts](https://github.com/TriforceGB/custom.sh-shortcuts)


## Project Flow Chart
A Guide to the Rest of the HGV Project, Each Colour Shows what REMS Computers Each Node is Running/Being Working on


| Computers     | Colour        |
| ------------- |:-------------:|
| REMS005       | Blue          |
| REMS006       | Purple        |
| REMS007       | Red           |
| REMS008       | Green         |
 
```mermaid
---
config:
  theme: mc
  look: neo
  layout: dagre
---
flowchart BT
    Sen1["**Sensors**<br>• DS18B20<br>• AM2302<br>• Motion<br>• Water Leak<br>• Vibration"] -.-> Sec("Secondary Arduino")
    Sec -- ModbusRTU ---> Pri("**Primary Arduino**")
    Room["**Room Sensors/RTA**<br>• Heater Control <br>• Smoke Detector<br>"] <-...-> Pri
    Pri <== MQTT ====> Mos["**Mosquitto**<br>• Broker for MQTT messages"]
    Mos ---> NR["**NodeRed**<br>• Formats Data"]
    NR -- HTTP ---> Pro["**Prometheus**<br>• Metrics collection"]
    Pro --> Gra["**Grafana**<br>• Data visualization"]
    NR -- Websocket ---> Web["**HGV Website**<br>• Tempature Control<br>• Home Page<br>• Remote Emails<br>"]
    Web -- MQTT --> Mos
    Web <-- Green Unicorn --> Cad(["**Caddy**<br>• Reverse Proxy"])
    Cad <--> USR["User"]
    Sen1@{ shape: stored-data}
    Room@{ shape: display}
    Mos@{ shape: subproc}
    NR@{ shape: hex}
    Pro@{ shape: diam}
    Gra@{ shape: card}
    Web@{ shape: procs}
    USR@{ shape: loop-limit}
    style Sen1 fill:#BBDEFB,color:#000000
    style Sec fill:#E1BEE7,color:#000000
    style Pri fill:#E1BEE7,color:#000000
    style Room fill:#C8E6C9,color:#000000
    style Mos fill:#E1BEE7,color:#000000
    style NR fill:#E1BEE7,color:#000000
    style Pro fill:#E1BEE7,color:#000000
    style Gra fill:#E1BEE7,color:#000000
    style Web fill:#FFCDD2,color:#000000
    style Cad fill:#FFCDD2,color:#000000
    linkStyle 1 stroke:#AA00FF,fill:none
    linkStyle 3 stroke:#AA00FF,fill:none
    linkStyle 5 stroke:#AA00FF,fill:none
    linkStyle 7 stroke:#D50000,fill:none
    linkStyle 9 stroke:#D50000,fill:none
```

## About Maintaining This Repository
After 2025-01-22 I personally will not Be working on or maintaining this repository but anyone else working on the HVG Project can take from this repository. If you do have any major issue with the main code you can reach out and I do my best to help with anything found in this Repo.  
