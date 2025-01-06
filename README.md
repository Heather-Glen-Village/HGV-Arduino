
# HGV Project REMS006 

## Features

- Light/dark mode toggle
- Live previews
- Fullscreen mode
- Cross platform


## Tech Stack

**Client:** React, Redux, TailwindCSS

**Server:** Node, Express


## Installation

Install my-project with npm

```bash
  npm install my-project
  cd my-project
```
    
## FAQ

#### Question 1

Answer 1

#### Question 2

Answer 2


## Screenshots

![App Screenshot](https://via.placeholder.com/468x300?text=App+Screenshot+Here)


## Roadmap

- Additional browser support

- Add more integrations


## Related Repository
Here are some Repo from Other Students that work on the HGV at the Same Time I did

[Arham's REMS005](https://github.com/HammyTheWammy/rems005)

[Zoya's REMS007](https://github.com/ElectricCornstarch/rems007)

[Abbas's REMS008](https://github.com/abbashaider1444/rems008)

[HGV Website](https://github.com/TriforceGB/HGV-Webapp)

[Custom .sh Shortcuts](https://github.com/TriforceGB/custom.sh-shortcuts)

## Project Flow Chart
A Guide to the Rest of the HGV Project, Each Colour Shows what REMS Computers Each Node is Running/Being Working on
 
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
    Room["**Room Sensors/RTA**<br>• Heater Control <br>• Smoke<br>• ???"] <-...-> Pri
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
