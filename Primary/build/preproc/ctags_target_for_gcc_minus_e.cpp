# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
# 2 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino" 2
# 3 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino" 2
// Pins List
# 13 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
// Defines the ID for the Secondary Board from 1-246


// Initialize Libaries
SoftwareSerial modbusSerial(17 /* A3*/, 16 /* A2*/);
ModbusRTUMaster modbus(Serial, 9); // Create Modbus Object

bool coils[1] = {1};
uint16_t InputRegisters[1];


void setup() {
  modbus.begin(9600);
  Serial.begin(9600); // For Debuging
  delay(5000); // For Debuging
}

void loop() {
Serial.println(modbus.writeSingleCoil(1,0,1));
delay(3000);
Serial.println(modbus.readInputRegisters(1, 0, InputRegisters,1));
Serial.print("InputRegisters: "); Serial.println(InputRegisters[0]);
delay(1000);
}
# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\!Primary.ino"
/* Arduino-based Modbus RTU (slaves) to Modbus TCP/UDP (master) gateway with web interface



  Version history

  v0.1 2020-04-05 Initial commit

  v0.2 2021-03-02 Random MAC generation

  v1.0 2021-03-20 Add web interface, settings stored in EEPROM

  v2.0 2021-04-01 Improve random MAC algorithm (Marsaglia algorithm from https://github.com/RobTillaart/randomHelpers),

                  replace some libraries with more efficient code, compatibility with Arduino Mega

  v2.1 2021-04-12 Code optimisation

  v2.2 2021-06-06 Fix TCP closed socket, support RS485 modules with hardware automatic flow control

  v2.3 2021-09-10 Fix IPAddress cast (gateway freeze)

  v2.4 2021-10-15 Add SW version. Forced factory reset (load defaut settings from sketch) on MAJOR version change.

  v3.0 2021-11-07 Improve POST parameters processing, bugfix 404 and 204 error headers. 

  v3.1 2022-01-28 Code optimization, bugfix DHCP settings.

  v3.2 2022-06-04 Reduce program size (so that it fits on Nano), ethernet data counter only available when ENABLE_EXTENDED_WEBUI.

  v4.0 2023-01-05 Modbus statistics and error reporting on "Modbus Status" page, add Frame Delay setting for Modbus RTU

                  Optimize Modbus timeout and attempts, significant reduction of code size

  v4.1 2023-01-14 Fetch API, bugfix MAX485

  v5.0 2023-02-19 Send Modbus Request from WebUI, optimized POST parameter processing (less RAM consumption), select baud rate in WebUI,

                  improved TCP socket management, Modbus TCP Idle Timeout settings

  v6.0 2023-03-18 Save error counters to EEPROM, code optimization, separate file for advanced settings

  v6.1 2023-04-12 Code optimization

  v7.0 2023-07-21 Manual MAC, better data types

  v7.1 2023-08-25 Simplify EEPROM read and write, Tools page

  v7.2 2023-10-20 Disable DHCP renewal fallback, better advanced_settings.h layout

                  ENABLE_EXTENDED_WEBUI and ENABLE_DHCP is set by default for Mega

  v7.3 2024-01-16 Bugfix Modbus RTU Request form, code comments

*/
# 30 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\!Primary.ino"
const byte VERSION[] = { 7, 3 };

# 33 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\!Primary.ino" 2
# 34 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\!Primary.ino" 2
# 35 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\!Primary.ino" 2
# 36 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\!Primary.ino" 2
# 37 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\!Primary.ino" 2
# 38 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\!Primary.ino" 2
# 39 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\!Primary.ino" 2

// these are used by CreateTrulyRandomSeed() function
# 42 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\!Primary.ino" 2
# 43 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\!Primary.ino" 2
# 44 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\!Primary.ino" 2


# 45 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\!Primary.ino"
typedef struct {
  byte ip[4];
  byte subnet[4];
  byte gateway[4];
  byte dns[4]; // only used if ENABLE_DHCP
  bool enableDhcp; // only used if ENABLE_DHCP
  uint16_t tcpPort;
  uint16_t udpPort;
  uint16_t webPort;
  bool enableRtuOverTcp;
  uint16_t tcpTimeout;
  uint16_t baud;
  byte serialConfig;
  byte frameDelay;
  uint16_t serialTimeout;
  byte serialAttempts;
} config_t;

# 64 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\!Primary.ino" 2

const config_t DEFAULT_CONFIG = {
  { 192, 168, 3, 168 } /* Default Static IP*/,
  { 255, 255, 255, 0 } /* Default Submask*/,
  { 192, 168, 3, 1 } /* Default Gateway*/,
  { 192, 168, 3, 1 } /* Default DNS Server (only used if ENABLE_DHCP)*/,
  DEFAULT_AUTO_IP,
  DEFAULT_TCP_PORT,
  DEFAULT_UDP_PORT,
  DEFAULT_WEB_PORT,
  DEFAULT_RTU_OVER_TCP,
  DEFAULT_TCP_TIMEOUT,
  DEFAULT_BAUD_RATE,
  DEFAULT_SERIAL_CONFIG,
  DEFAULT_FRAME_DELAY,
  DEFAULT_RESPONSE_TIMEPOUT,
  DEFAULT_ATTEMPTS,
};

enum status_t : byte {
  SLAVE_OK, // Slave Responded
  SLAVE_ERROR_0X, // Slave Responded with Error (Codes 1~8)
  SLAVE_ERROR_0A, // Gateway Overloaded (Code 10)
  SLAVE_ERROR_0B, // Slave Failed to Respond (Code 11)
  SLAVE_ERROR_0B_QUEUE, // Slave Failed to Respond (Code 11) & is in Queue (not shown in web UI)
  ERROR_TIMEOUT, // Response Timeout
  ERROR_RTU, // Invalid RTU Response
  ERROR_TCP, // Invalid TCP/UDP Request
  ERROR_LAST // Number of status flags in this enum. Must be the last element within this enum!!
};

enum flow_t : byte {
  DATA_TX,
  DATA_RX,
  DATA_LAST // Number of status flags in this enum. Must be the last element within this enum!!
};

typedef struct {
  uint32_t eepromWrites; // Number of EEPROM write cycles (persistent, it is never cleared during factory resets)
  byte major; // major version
  byte mac[6]; // MAC Address (initial value is random generated)
  config_t config; // configuration values
  uint32_t errorCnt[ERROR_LAST]; // array for storing error counters




} data_t;

data_t data;

typedef struct {
  byte tid[2]; // MBAP Transaction ID
  byte msgLen; // lenght of Modbus message stored in queueData
  IPAddress remIP; // remote IP for UDP client (UDP response is sent back to remote IP)
  uint16_t remPort; // remote port for UDP client (UDP response is sent back to remote port)
  byte requestType; // TCP client who sent the request
  byte atts; // attempts counter
} header_t;

// bool arrays for storing Modbus RTU status of individual slaves
byte slaveStatus[SLAVE_ERROR_0B_QUEUE + 1][(MAX_SLAVES + 1 + 7) / 8]; // SLAVE_ERROR_0B_QUEUE is the last status of slaves

// each request is stored in 3 queues (all queues are written to, read and deleted in sync)
CircularBuffer<header_t, MAX_QUEUE_REQUESTS> queueHeaders; // queue of requests' headers and metadata
CircularBuffer<byte, MAX_QUEUE_DATA> queueData; // queue of PDU data


/****** ETHERNET AND SERIAL ******/

byte maxSockNum = 4;





EthernetUDP Udp;
EthernetServer modbusServer(DEFAULT_CONFIG.tcpPort);
EthernetServer webServer(DEFAULT_CONFIG.webPort);

/****** TIMERS AND STATE MACHINE ******/

class MicroTimer {
private:
  uint32_t timestampLastHitMs;
  uint32_t sleepTimeMs;
public:
  boolean isOver();
  void sleep(uint32_t sleepTimeMs);
};
boolean MicroTimer::isOver() {
  if ((uint32_t)(micros() - timestampLastHitMs) > sleepTimeMs) {
    return true;
  }
  return false;
}
void MicroTimer::sleep(uint32_t sleepTimeMs) {
  this->sleepTimeMs = sleepTimeMs;
  timestampLastHitMs = micros();
}

class Timer {
private:
  uint32_t timestampLastHitMs;
  uint32_t sleepTimeMs;
public:
  boolean isOver();
  void sleep(uint32_t sleepTimeMs);
};
boolean Timer::isOver() {
  if ((uint32_t)(millis() - timestampLastHitMs) > sleepTimeMs) {
    return true;
  }
  return false;
}
void Timer::sleep(uint32_t sleepTimeMs) {
  this->sleepTimeMs = sleepTimeMs;
  timestampLastHitMs = millis();
}

MicroTimer recvMicroTimer;
MicroTimer sendMicroTimer;
Timer eepromTimer; // timer to delay writing statistics to EEPROM
Timer checkEthTimer; // timer to check SPI connection with ethernet shield




byte scanCounter = 1; // Start Modbus RTU scan after boot
enum state_t : byte {
  IDLE,
  SENDING,
  DELAY,
  WAITING
};

byte serialState;


/****** RUN TIME AND DATA COUNTERS ******/

bool scanReqInQueue = false; // Scan request is in the queue
byte priorityReqInQueue; // Counter for priority requests in the queue

byte response[MAX_RESPONSE_LEN]; // buffer to store the last Modbus response
byte responseLen; // stores actual length of the response shown in WebUI

uint16_t queueDataSize;
byte queueHeadersSize;
# 224 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\!Primary.ino"
volatile uint32_t seed1; // seed1 is generated by CreateTrulyRandomSeed()
volatile int8_t nrot;
uint32_t seed2 = 17111989; // seed2 is static


/****** SETUP: RUNS ONCE ******/

void setup() {
  CreateTrulyRandomSeed();
  EEPROM.get(DATA_START, data);
  // is configuration already stored in EEPROM?
  if (data.major != VERSION[0]) {
    data.major = VERSION[0];
    // load default configuration from flash memory
    data.config = DEFAULT_CONFIG;
    generateMac();
    resetStats();
    updateEeprom();
  }
  startSerial();
  startEthernet();
}

/****** LOOP ******/

void loop() {

  scanRequest();
  sendSerial();
  recvUdp();
  recvSerial();

  manageSockets();

  if (EEPROM_INTERVAL > 0 && eepromTimer.isOver() == true) {
    updateEeprom();
  }

  // could help with freeze after power loss reported by some users, not enabled yet
  // if (CHECK_ETH_INTERVAL > 0 && checkEthTimer.isOver() == true) {
  //   checkEthernet();
  // }

  if (rollover()) {
    resetStats();
    updateEeprom();
  }






}
# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
/**************************************************************************/
/*!

  @brief Initiates HW serial interface which we use for the RS485 line.

*/
# 5 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
/**************************************************************************/
void startSerial() {
  Serial /* define serial port for RS485 interface, for Arduino Mega choose from Serial1, Serial2 or Serial3*/.begin((data.config.baud * 100UL), data.config.serialConfig);

  pinMode(9 /* Arduino Pin for RS485 Direction control, disable if you have module with hardware flow control*/, 0x1);
  digitalWrite(9 /* Arduino Pin for RS485 Direction control, disable if you have module with hardware flow control*/, 0x0); // Init Transceiver

}

// Number of bits per character (11 in default Modbus RTU settings)
byte bitsPerChar() {
  byte bits =
    1 + // start bit
    (((data.config.serialConfig & 0x06) >> 1) + 5) + // data bits
    (((data.config.serialConfig & 0x08) >> 3) + 1); // stop bits
  if (((data.config.serialConfig & 0x30) >> 4) > 1) bits += 1; // parity bit (if present)
  return bits;
}

// Character timeout in micros
uint32_t charTimeOut() {
  if (data.config.baud <= 192) {
    return (15000UL * bitsPerChar()) / data.config.baud; // inter-character time-out should be 1,5T
  } else {
    return 750;
  }
}

// Minimum frame delay in micros
uint32_t frameDelay() {
  if (data.config.baud <= 192) {
    return (35000UL * bitsPerChar()) / data.config.baud; // inter-frame delay should be 3,5T
  } else {
    return 1750; // 1750 μs
  }
}

/**************************************************************************/
/*!

  @brief Initiates ethernet interface, if DHCP enabled, gets IP from DHCP,

  starts all servers (UDP, web server).

*/
# 47 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
/**************************************************************************/
void startEthernet() {
  if (ETH_RESET_PIN != 0) {
    pinMode(ETH_RESET_PIN, 0x1);
    digitalWrite(ETH_RESET_PIN, 0x0);
    delay(25);
    digitalWrite(ETH_RESET_PIN, 0x1);
    delay(ETH_RESET_DELAY);
  }
# 64 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
  Ethernet.begin(data.mac, data.config.ip, {}, data.config.gateway, data.config.subnet); // No DNS

  W5100.setRetransmissionTime(TCP_RETRANSMISSION_TIMEOUT);
  W5100.setRetransmissionCount(TCP_RETRANSMISSION_COUNT);
  modbusServer = EthernetServer(data.config.tcpPort);
  webServer = EthernetServer(data.config.webPort);
  Udp.begin(data.config.udpPort);
  modbusServer.begin();
  webServer.begin();



}

/**************************************************************************/
/*!

  @brief Resets Arduino (works only on AVR chips).

*/
# 82 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
/**************************************************************************/
void (*resetFunc)(void) = 0; //declare reset function at address 0

/**************************************************************************/
/*!

  @brief Checks SPI connection to the W5X00 chip.

*/
# 89 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
/**************************************************************************/
void checkEthernet() {
  static byte attempts = 0;
  IPAddress tempIP = Ethernet.localIP();
  if (tempIP[0] == 0) {
    attempts++;
    if (attempts >= 3) {
      resetFunc();
    }
  } else {
    attempts = 0;
  }
  checkEthTimer.sleep(CHECK_ETH_INTERVAL);
}

/**************************************************************************/
/*!

  @brief Maintains DHCP lease.

*/
# 108 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
/**************************************************************************/
# 117 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
/**************************************************************************/
/*!

  @brief Maintains uptime in case of millis() overflow.

*/
# 121 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
/**************************************************************************/
# 138 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
/**************************************************************************/
/*!

  @brief Synchronizes roll-over of data counters to zero.

*/
# 142 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
/**************************************************************************/
bool rollover() {
  const uint32_t ROLLOVER = 0xFFFFFF00;
  for (byte i = 0; i < ERROR_LAST; i++) {
    if (data.errorCnt[i] > ROLLOVER) {
      return true;
    }
  }
# 160 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
  return false;
}

/**************************************************************************/
/*!

  @brief Resets error stats, RTU counter and ethernet data counter.

*/
# 167 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
/**************************************************************************/
void resetStats() {
  memset(data.errorCnt, 0, sizeof(data.errorCnt));





}

/**************************************************************************/
/*!

  @brief Generate random MAC using pseudo random generator,

  bytes 0, 1 and 2 are static (MAC_START), bytes 3, 4 and 5 are generated randomly

*/
# 182 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
/**************************************************************************/
void generateMac() {
  // Marsaglia algorithm from https://github.com/RobTillaart/randomHelpers
  seed1 = 36969L * (seed1 & 65535L) + (seed1 >> 16);
  seed2 = 18000L * (seed2 & 65535L) + (seed2 >> 16);
  uint32_t randomBuffer = (seed1 << 16) + seed2; /* 32-bit random */
  memcpy(data.mac, MAC_START, 3); // set first 3 bytes
  for (byte i = 0; i < 3; i++) {
    data.mac[i + 3] = randomBuffer & 0xFF; // random last 3 bytes
    randomBuffer >>= 8;
  }
}

/**************************************************************************/
/*!

  @brief Write (update) data to Arduino EEPROM.

*/
# 199 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
/**************************************************************************/
void updateEeprom() {
  eepromTimer.sleep(EEPROM_INTERVAL * 60UL * 60UL * 1000UL); // EEPROM_INTERVAL is in hours, sleep is in milliseconds!
  data.eepromWrites++; // we assume that at least some bytes are written to EEPROM during EEPROM.update or EEPROM.put
  EEPROM.put(DATA_START, data);
}


uint32_t lastSocketUse[4];
byte socketInQueue[4];
/**************************************************************************/
/*!

  @brief Closes sockets which are waiting to be closed or which refuse to close,

  forwards sockets with data available for further processing by the webserver,

  disconnects (closes) sockets which are too old (idle for too long), opens

  new sockets if needed (and if available).

  From https://github.com/SapientHetero/Ethernet/blob/master/src/socket.cpp

*/
# 217 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
/**************************************************************************/
void manageSockets() {
  uint32_t maxAge = 0; // the 'age' of the socket in a 'disconnectable' state that was last used the longest time ago
  byte oldest = 4; // the socket number of the 'oldest' disconnectable socket
  byte modbusListening = 4;
  byte webListening = 4;
  byte dataAvailable = 4;
  byte socketsAvailable = 0;
  SPI.beginTransaction(SPISettings(14000000, 1, 0x00)); // begin SPI transaction
  // look at all the hardware sockets, record and take action based on current states
  for (byte s = 0; s < maxSockNum; s++) { // for each hardware socket ...
    byte status = W5100.readSnSR(s); //  get socket status...
    uint32_t sockAge = millis() - lastSocketUse[s]; // age of the current socket
    if (socketInQueue[s] > 0) {
      lastSocketUse[s] = millis();
      continue; // do not close Modbus TCP sockets currently processed (in queue)
    }

    switch (status) {
      case SnSR::CLOSED:
        {
          socketsAvailable++;
        }
        break;
      case SnSR::LISTEN:
      case SnSR::SYNRECV:
        {
          lastSocketUse[s] = millis();
          if (W5100.readSnPORT(s) == data.config.webPort) {
            webListening = s;
          } else {
            modbusListening = s;
          }
        }
        break;
      case SnSR::FIN_WAIT:
      case SnSR::CLOSING:
      case SnSR::TIME_WAIT:
      case SnSR::LAST_ACK:
        {
          socketsAvailable++; // socket will be available soon
          if (sockAge > TCP_DISCON_TIMEOUT) { //     if it's been more than TCP_CLIENT_DISCON_TIMEOUT since disconnect command was sent...
            W5100.execCmdSn(s, Sock_CLOSE); //	    send CLOSE command...
            lastSocketUse[s] = millis(); //       and record time at which it was sent so we don't do it repeatedly.
          }
        }
        break;
      case SnSR::ESTABLISHED:
      case SnSR::CLOSE_WAIT:
        {
          if (EthernetClient(s).available() > 0) {
            dataAvailable = s;
            lastSocketUse[s] = millis();
          } else {
            // remote host closed connection, our end still open
            if (status == SnSR::CLOSE_WAIT) {
              socketsAvailable++; // socket will be available soon
              W5100.execCmdSn(s, Sock_DISCON); //  send DISCON command...
              lastSocketUse[s] = millis(); //   record time at which it was sent...
                                                // status becomes LAST_ACK for short time
            } else if (((W5100.readSnPORT(s) == data.config.webPort && sockAge > WEB_IDLE_TIMEOUT)
                        || (W5100.readSnPORT(s) == data.config.tcpPort && sockAge > (data.config.tcpTimeout * 1000UL)))
                       && sockAge > maxAge) {
              oldest = s; //     record the socket number...
              maxAge = sockAge; //      and make its age the new max age.
            }
          }
        }
        break;
      default:
        break;
    }
  }

  if (dataAvailable != 4) {
    EthernetClient client = EthernetClient(dataAvailable);
    if (W5100.readSnPORT(dataAvailable) == data.config.webPort) {
      recvWeb(client);
    } else {
      recvTcp(client);
    }
  }

  if (modbusListening == 4) {
    modbusServer.begin();
  } else if (webListening == 4) {
    webServer.begin();
  }

  // If needed, disconnect socket that's been idle (ESTABLISHED without data recieved) the longest
  if (oldest != 4 && socketsAvailable == 0 && (webListening == 4 || modbusListening == 4)) {
    disconSocket(oldest);
  }

  SPI.endTransaction(); // Serves to o release the bus for other devices to access it. Since the ethernet chip is the only device
  // we do not need SPI.beginTransaction(SPI_ETHERNET_SETTINGS) or SPI.endTransaction() ??
}

/**************************************************************************/
/*!

  @brief Disconnect or close a socket.

  @param s Socket number.

*/
# 320 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
/**************************************************************************/
void disconSocket(byte s) {
  if (W5100.readSnSR(s) == SnSR::ESTABLISHED) {
    W5100.execCmdSn(s, Sock_DISCON); // Sock_DISCON does not close LISTEN sockets
    lastSocketUse[s] = millis(); //   record time at which it was sent...
  } else {
    W5100.execCmdSn(s, Sock_CLOSE); //  send DISCON command...
  }
}


/**************************************************************************/
/*!

  @brief Seed pseudorandom generator using  watch dog timer interrupt (works only on AVR).

  See https://sites.google.com/site/astudyofentropy/project-definition/timer-jitter-entropy-sources/entropy-library/arduino-random-seed

*/
# 336 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
/**************************************************************************/
void CreateTrulyRandomSeed() {
  seed1 = 0;
  nrot = 32; // Must be at least 4, but more increased the uniformity of the produced seeds entropy.
  // The following five lines of code turn on the watch dog timer interrupt to create
  // the seed value
  
# 342 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino" 3
 __asm__ __volatile__ ("cli" ::: "memory")
# 342 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
      ;
  
# 343 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino" 3
 (*(volatile uint8_t *)((0x34) + 0x20)) 
# 343 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
       = 0;
  
# 344 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino" 3
 (*(volatile uint8_t *)(0x60)) 
# 344 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
                 |= (1 << 
# 344 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino" 3
                          4
# 344 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
                                        ) | (1 << 
# 344 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino" 3
                                                  3
# 344 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
                                                     );
  
# 345 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino" 3
 (*(volatile uint8_t *)(0x60)) 
# 345 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
                 = (1 << 
# 345 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino" 3
                         6
# 345 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
                             );
  
# 346 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino" 3
 __asm__ __volatile__ ("sei" ::: "memory")
# 346 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
      ;
  while (nrot > 0)
    ; // wait here until seed is created
  // The following five lines turn off the watch dog timer interrupt
  
# 350 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino" 3
 __asm__ __volatile__ ("cli" ::: "memory")
# 350 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
      ;
  
# 351 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino" 3
 (*(volatile uint8_t *)((0x34) + 0x20)) 
# 351 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
       = 0;
  
# 352 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino" 3
 (*(volatile uint8_t *)(0x60)) 
# 352 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
                 |= (1 << 
# 352 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino" 3
                          4
# 352 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
                                        ) | (0 << 
# 352 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino" 3
                                                  3
# 352 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
                                                     );
  
# 353 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino" 3
 (*(volatile uint8_t *)(0x60)) 
# 353 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
                 = (0 << 
# 353 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino" 3
                         6
# 353 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
                             );
  
# 354 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino" 3
 __asm__ __volatile__ ("sei" ::: "memory")
# 354 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
      ;
}


# 357 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino" 3
extern "C" void __vector_6 /* Watchdog Time-out Interrupt */ (void) __attribute__ ((signal,used, externally_visible)) ; void __vector_6 /* Watchdog Time-out Interrupt */ (void) 
# 357 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
             {
  nrot--;
  seed1 = seed1 << 8;
  seed1 = seed1 ^ 
# 360 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino" 3
                 (*(volatile uint8_t *)(0x84))
# 360 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
                       ;
}

// Preprocessor code for identifying microcontroller board
# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\02-modbus-tcp.ino"
/* *******************************************************************

   Modbus TCP/UDP functions



   recvUdp()

   - receives Modbus UDP (or Modbus RTU over UDP) messages

   - calls checkRequest



   recvTcp()

   - receives Modbus TCP (or Modbus RTU over TCP) messages

   - calls checkRequest



   checkRequest()

   - checks Modbus TCP/UDP requests (correct MBAP header, CRC in case of Modbus RTU over TCP/UDP)

   - checks availability of queue

   - stores requests into queue or returns an error



   scanRequest()

   - inserts scan request into queue



   deleteRequest()

   - deletes requests from queue



   clearQueue()

   - clears queue and corresponding counters



   getSlaveStatus(), setSlaveStatus()

   - read from and write to bool array



   ***************************************************************** */
# 31 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\02-modbus-tcp.ino"
byte masks[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };

// Stored in "header.requestType"






uint16_t crc;

/**************************************************************************/
/*!

  @brief Receives Modbus UDP (or Modbus RTU over UDP) messages, calls @ref checkRequest()

*/
# 46 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\02-modbus-tcp.ino"
/**************************************************************************/
void recvUdp() {
  uint16_t msgLength = Udp.parsePacket();
  if (msgLength) {



    byte inBuffer[MODBUS_SIZE + 4]; // Modbus TCP frame is 4 bytes longer than Modbus RTU frame
                                     // Modbus TCP/UDP frame: [0][1] transaction ID, [2][3] protocol ID, [4][5] length and [6] unit ID (address)..... no CRC
                                     // Modbus RTU frame: [0] address.....[n-1][n] CRC
    memset(inBuffer, 0, sizeof(inBuffer));
    Udp.read(inBuffer, sizeof(inBuffer));
    while (Udp.available()) Udp.read();
    byte errorCode = checkRequest(inBuffer, msgLength, (uint32_t)Udp.remoteIP(), Udp.remotePort(), 32 /* UDP request*/);
    if (errorCode) {
      // send back message with error code
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      if (!data.config.enableRtuOverTcp) {
        Udp.write(inBuffer, 5);
        Udp.write(0x03);
      }
      byte addressPos = 6 * !data.config.enableRtuOverTcp; // position of slave address in the incoming TCP/UDP message (0 for Modbus RTU over TCP/UDP and 6 for Modbus RTU over TCP/UDP)
      Udp.write(inBuffer[addressPos]); // address
      Udp.write(inBuffer[addressPos + 1] + 0x80); // function + 0x80
      Udp.write(errorCode);
      if (data.config.enableRtuOverTcp) {
        crc = 0xFFFF;
        calculateCRC(inBuffer[addressPos]);
        calculateCRC(inBuffer[addressPos + 1] + 0x80);
        calculateCRC(errorCode);
        Udp.write(((uint8_t) ((crc) & 0xff))); // send CRC, low byte first
        Udp.write(((uint8_t) ((crc) >> 8)));
      }
      Udp.endPacket();




    }
  }
}

/**************************************************************************/
/*!

  @brief Receives Modbus TCP (or Modbus RTU over TCP) messages, calls @ref checkRequest()

*/
# 92 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\02-modbus-tcp.ino"
/**************************************************************************/
void recvTcp(EthernetClient &client) {
  uint16_t msgLength = client.available();



  byte inBuffer[MODBUS_SIZE + 4]; // Modbus TCP frame is 4 bytes longer than Modbus RTU frame
                                   // Modbus TCP/UDP frame: [0][1] transaction ID, [2][3] protocol ID, [4][5] length and [6] unit ID (address).....
                                   // Modbus RTU frame: [0] address.....
  memset(inBuffer, 0, sizeof(inBuffer));
  client.read(inBuffer, sizeof(inBuffer));
  while (client.available()) client.read();
  byte errorCode = checkRequest(inBuffer, msgLength, {}, client.remotePort(), 8 /* TCP request*/ | client.getSocketNumber());
  if (errorCode) {
    // send back message with error code
    byte i = 0;
    byte outBuffer[9];
    if (!data.config.enableRtuOverTcp) {
      memcpy(outBuffer, inBuffer, 5);
      outBuffer[5] = 0x03;
      i = 6;
    }
    byte addressPos = 6 * !data.config.enableRtuOverTcp; // position of slave address in the incoming TCP/UDP message (0 for Modbus RTU over TCP/UDP and 6 for Modbus RTU over TCP/UDP)
    outBuffer[i++] = inBuffer[addressPos]; // address
    outBuffer[i++] = inBuffer[addressPos + 1] + 0x80; // function + 0x80
    outBuffer[i++] = errorCode;
    if (data.config.enableRtuOverTcp) {
      crc = 0xFFFF;
      calculateCRC(inBuffer[addressPos]);
      calculateCRC(inBuffer[addressPos + 1] + 0x80);
      calculateCRC(errorCode);
      outBuffer[i++] = ((uint8_t) ((crc) & 0xff)); // send CRC, low byte first
      outBuffer[i++] = ((uint8_t) ((crc) >> 8));
    }
    client.write(outBuffer, i);




  }
}


void scanRequest() {
  // Insert scan request into queue, allow only one scan request in a queue
  static byte scanCommand[] = { SCAN_FUNCTION_FIRST, 0x00, SCAN_DATA_ADDRESS, 0x00, 0x01 };
  if (scanCounter != 0 && queueHeaders.available() > 1 && queueData.available() > sizeof(scanCommand) + 1 && scanReqInQueue == false) {
    scanReqInQueue = true;
    // Store scan request in request queue
    queueHeaders.push(header_t{
      { 0x00, 0x00 }, // tid[2]
      sizeof(scanCommand) + 1, // msgLen
      { 0, 0, 0, 0 }, // remIP
      0, // remPort
      64 /* Request triggered by slave scanner*/, // requestType
      0, // atts
    });
    queueData.push(scanCounter); // address of the scanned slave
    for (byte i = 0; i < sizeof(scanCommand); i++) {
      queueData.push(scanCommand[i]);
    }
    if (scanCommand[0] == SCAN_FUNCTION_FIRST) {
      scanCommand[0] = SCAN_FUNCTION_SECOND;
    } else {
      scanCommand[0] = SCAN_FUNCTION_FIRST;
      scanCounter++;
    }
    if (scanCounter == MAX_SLAVES + 1) scanCounter = 0;
  }
}

/**************************************************************************/
/*!

  @brief Checks Modbus TCP/UDP requests (correct MBAP header,

  CRC in case of Modbus RTU over TCP/UDP), checks availability of queue,

  stores requests into queue or returns an error.

  @param inBuffer Modbus TCP/UDP requests

  @param msgLength Length of the Modbus TCP/UDP requests

  @param remoteIP Remote IP

  @param remotePort Remote port

  @param requestType UDP or TCP, priority or scan request

  @return Modbus error code to be sent back to the recipient.

*/
# 175 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\02-modbus-tcp.ino"
/**************************************************************************/
byte checkRequest(byte inBuffer[], uint16_t msgLength, const uint32_t remoteIP, const uint16_t remotePort, byte requestType) {
  byte addressPos = 6 * !data.config.enableRtuOverTcp; // position of slave address in the incoming TCP/UDP message (0 for Modbus RTU over TCP/UDP and 6 for Modbus RTU over TCP/UDP)
  if (data.config.enableRtuOverTcp) { // check CRC for Modbus RTU over TCP/UDP
    if (checkCRC(inBuffer, msgLength) == false) {
      data.errorCnt[ERROR_TCP]++;
      return 0; // drop request and do not return any error code
    }
  } else { // check MBAP header structure for Modbus TCP/UDP
    if (inBuffer[2] != 0x00 || inBuffer[3] != 0x00 || inBuffer[4] != 0x00 || inBuffer[5] != msgLength - 6) {
      data.errorCnt[ERROR_TCP]++;
      return 0; // drop request and do not return any error code
    }
  }
  msgLength = msgLength - addressPos - (2 * data.config.enableRtuOverTcp); // in Modbus RTU over TCP/UDP do not store CRC
  // check if we have space in request queue
  if (queueHeaders.available() < 1 || queueData.available() < msgLength) {
    setSlaveStatus(inBuffer[addressPos], SLAVE_ERROR_0A, true, false);
    return 0x0A; // return Modbus error code 10 (Gateway Overloaded)
  }
  // allow only one request to non responding slaves
  if (getSlaveStatus(inBuffer[addressPos], SLAVE_ERROR_0B_QUEUE)) {
    data.errorCnt[SLAVE_ERROR_0B]++;
    return 0x0B; // return Modbus error code 11 (Gateway Target Device Failed to Respond)
  } else if (getSlaveStatus(inBuffer[addressPos], SLAVE_ERROR_0B)) {
    setSlaveStatus(inBuffer[addressPos], SLAVE_ERROR_0B_QUEUE, true, false);
  } else {
    // Add PRIORITY_REQUEST flag to requests for responding slaves
    requestType = requestType | 128 /* Request to slave which is not "nonresponding"*/;
    priorityReqInQueue++;
  }
  if (inBuffer[addressPos] == 0x00) { // Modbus Broadcast
    requestType = requestType | 64 /* Request triggered by slave scanner*/; // Treat broadcast as scan (only one attempt, short timeout, do not expect response)
  }
  // all checkes passed OK, we can store the incoming data in request queue
  if (requestType & 8 /* TCP request*/) {
    socketInQueue[requestType & 7 /* Stores TCP client number*/]++;
  }
  // Store in request queue
  queueHeaders.push(header_t{
    { inBuffer[0], inBuffer[1] }, // tid[2] (ignored in Modbus RTU over TCP/UDP)
    byte(msgLength), // msgLen
    (IPAddress)remoteIP, // remIP
    (unsigned int)remotePort, // remPort
    byte(requestType), // requestType
    0, // atts
  });
  for (byte i = 0; i < msgLength; i++) {
    queueData.push(inBuffer[i + addressPos]);
  }
  if (queueData.size() > queueDataSize) queueDataSize = queueData.size();
  if (queueHeaders.size() > queueHeadersSize) queueHeadersSize = queueHeaders.size();
  return 0;
}

void deleteRequest() // delete request from queue
{
  header_t myHeader = queueHeaders.first();
  if (myHeader.requestType & 64 /* Request triggered by slave scanner*/) scanReqInQueue = false;
  if (myHeader.requestType & 8 /* TCP request*/) socketInQueue[myHeader.requestType & 7 /* Stores TCP client number*/]--;
  if (myHeader.requestType & 128 /* Request to slave which is not "nonresponding"*/) priorityReqInQueue--;
  for (byte i = 0; i < myHeader.msgLen; i++) {
    queueData.shift();
  }
  queueHeaders.shift();
}

void clearQueue() {
  queueHeaders.clear();
  queueData.clear();
  scanReqInQueue = false;
  priorityReqInQueue = false;
  memset(socketInQueue, 0, sizeof(socketInQueue));
  memset(slaveStatus[SLAVE_ERROR_0B_QUEUE], 0, sizeof(slaveStatus[SLAVE_ERROR_0B_QUEUE]));
  sendMicroTimer.sleep(0);
}

bool getSlaveStatus(const byte slave, const byte status) {
  if (slave >= MAX_SLAVES) return false; // error
  return (slaveStatus[status][slave / 8] & masks[slave & 7]) > 0;
}

void setSlaveStatus(const byte slave, byte status, const bool value, const bool isScan) {
  if (slave >= MAX_SLAVES || status > SLAVE_ERROR_0B_QUEUE) return; // error
  if (value == 0) {
    slaveStatus[status][slave / 8] &= ~masks[slave & 7];
  } else {
    for (byte i = 0; i <= SLAVE_ERROR_0B_QUEUE; i++) {
      slaveStatus[i][slave / 8] &= ~masks[slave & 7]; // set all other flags to false, SLAVE_ERROR_0B_QUEUE is the last slave status
    }
    slaveStatus[status][slave / 8] |= masks[slave & 7];
    if (status != SLAVE_ERROR_0B_QUEUE && isScan == false) data.errorCnt[status]++; // there is no counter for SLAVE_ERROR_0B_QUEUE, ignor scans in statistics
  }
}
# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\03-modbus-rtu.ino"
/* *******************************************************************

   Modbus RTU functions



   sendSerial()

   - sends Modbus RTU requests to HW serial port (RS485 interface)



   recvSerial()

   - receives Modbus RTU replies

   - adjusts headers and forward messages as Modbus TCP/UDP or Modbus RTU over TCP/UDP

   - sends Modbus TCP/UDP error messages in case Modbus RTU response timeouts



   checkCRC()

   - checks an array and returns true if CRC is OK



   calculateCRC()



   ***************************************************************** */
# 20 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\03-modbus-rtu.ino"
void sendSerial() {
  if (!sendMicroTimer.isOver()) {
    return;
  }
  if (queueHeaders.isEmpty()) {
    return;
  }
  static uint8_t txNdx = 0;
  header_t myHeader = queueHeaders.first();
  switch (serialState) {
    case 0: // IDLE: Optimize queue (prioritize requests from responding slaves) and trigger sending via serial
      while (priorityReqInQueue && (queueHeaders.first().requestType & 128 /* Request to slave which is not "nonresponding"*/) == false) {
        // move requests to non responding slaves to the tail of the queue
        for (byte i = 0; i < queueHeaders.first().msgLen; i++) {
          queueData.push(queueData.shift());
        }
        queueHeaders.push(queueHeaders.shift());
      }
      serialState++;
      break;
    case 1: // SENDING:
      {
        if (Serial /* define serial port for RS485 interface, for Arduino Mega choose from Serial1, Serial2 or Serial3*/.availableForWrite() > 0 && txNdx == 0) {

          digitalWrite(9 /* Arduino Pin for RS485 Direction control, disable if you have module with hardware flow control*/, 0x1); // Enable RS485 Transmit

          crc = 0xFFFF;
        }
        while (Serial /* define serial port for RS485 interface, for Arduino Mega choose from Serial1, Serial2 or Serial3*/.availableForWrite() > 0 && txNdx < myHeader.msgLen) {
          Serial /* define serial port for RS485 interface, for Arduino Mega choose from Serial1, Serial2 or Serial3*/.write(queueData[txNdx]);
          calculateCRC(queueData[txNdx]);
          txNdx++;
        }
        if (Serial /* define serial port for RS485 interface, for Arduino Mega choose from Serial1, Serial2 or Serial3*/.availableForWrite() > 1 && txNdx == myHeader.msgLen) {
          Serial /* define serial port for RS485 interface, for Arduino Mega choose from Serial1, Serial2 or Serial3*/.write(((uint8_t) ((crc) & 0xff))); // send CRC, low byte first
          Serial /* define serial port for RS485 interface, for Arduino Mega choose from Serial1, Serial2 or Serial3*/.write(((uint8_t) ((crc) >> 8)));
          txNdx++;
        }
        if (Serial /* define serial port for RS485 interface, for Arduino Mega choose from Serial1, Serial2 or Serial3*/.availableForWrite() == 64 - 1 && txNdx > myHeader.msgLen) {
          // wait for last byte (incl. CRC) to be sent from serial Tx buffer
          // this if statement is not very reliable (too fast)
          // Serial.isFlushed() method is needed....see https://github.com/arduino/Arduino/pull/3737
          txNdx = 0;
          Serial /* define serial port for RS485 interface, for Arduino Mega choose from Serial1, Serial2 or Serial3*/.flush();

          // sendMicroTimer.sleep(frameDelay());  // Short delay before we toggle the RS485_CONTROL_PIN and disable RS485 transmit. Not needed if we use flush()

          serialState++;
        }
      }
      break;
    case 2: // DELAY:
      {





        digitalWrite(9 /* Arduino Pin for RS485 Direction control, disable if you have module with hardware flow control*/, 0x0); // Disable RS485 Transmit

        myHeader.atts++;
        queueHeaders.shift();
        queueHeaders.unshift(myHeader);
        uint32_t delay = data.config.serialTimeout;
        if (myHeader.requestType & 64 /* Request triggered by slave scanner*/) delay = SCAN_TIMEOUT; // fixed timeout for scan requests
        sendMicroTimer.sleep(delay * 1000UL);
        serialState++;
      }
      break;
    case 3: // WAITING: Deal with Serial timeouts (i.e. Modbus RTU timeouts)
      {
        if (myHeader.requestType & 64 /* Request triggered by slave scanner*/) { // Only one attempt for scan request (we do not count attempts)
          deleteRequest();
        } else if (myHeader.atts >= data.config.serialAttempts) {
          // send modbus error 0x0B (Gateway Target Device Failed to Respond) - usually means that target device (address) is not present
          setSlaveStatus(queueData[0], SLAVE_ERROR_0B, true, false);
          byte MBAP[] = { myHeader.tid[0],
                          myHeader.tid[1],
                          0x00,
                          0x00,
                          0x00,
                          0x03 };
          byte PDU[5] = { queueData[0],
                          byte(queueData[1] + 0x80),
                          0x0B };
          crc = 0xFFFF;
          for (byte i = 0; i < 3; i++) {
            calculateCRC(PDU[i]);
          }
          PDU[3] = ((uint8_t) ((crc) & 0xff)); // send CRC, low byte first
          PDU[4] = ((uint8_t) ((crc) >> 8));
          sendResponse(MBAP, PDU, 5);
          data.errorCnt[ERROR_TIMEOUT]++;
        } else {
          setSlaveStatus(queueData[0], SLAVE_ERROR_0B_QUEUE, true, false);
          data.errorCnt[ERROR_TIMEOUT]++;
        } // if (myHeader.atts >= MAX_RETRY)
        serialState = 0; // IDLE
      }
      break;
    default:
      break;
  }
}

void recvSerial() {
  static uint8_t rxNdx = 0;
  static byte serialIn[MODBUS_SIZE];
  while (Serial /* define serial port for RS485 interface, for Arduino Mega choose from Serial1, Serial2 or Serial3*/.available() > 0) {
    byte b = Serial /* define serial port for RS485 interface, for Arduino Mega choose from Serial1, Serial2 or Serial3*/.read();
    if (rxNdx < MODBUS_SIZE) {
      serialIn[rxNdx] = b;
      rxNdx++;
    } // if frame longer than maximum allowed, CRC will fail and data.errorCnt[ERROR_RTU] will be recorded down the road
    recvMicroTimer.sleep(charTimeOut());
    sendMicroTimer.sleep(data.config.frameDelay * 1000UL); // delay next serial write
  }
  if (recvMicroTimer.isOver() && rxNdx != 0) {
    // Process Serial data
    // Checks: 1) CRC; 2) address of incoming packet against first request in queue; 3) only expected responses are forwarded to TCP/UDP
    header_t myHeader = queueHeaders.first();
    if (checkCRC(serialIn, rxNdx) == true && serialIn[0] == queueData[0] && serialState == WAITING) {
      if (serialIn[1] > 0x80 && (myHeader.requestType & 64 /* Request triggered by slave scanner*/) == false) {
        setSlaveStatus(serialIn[0], SLAVE_ERROR_0X, true, false);
      } else {
        setSlaveStatus(serialIn[0], SLAVE_OK, true, myHeader.requestType & 64 /* Request triggered by slave scanner*/);
      }
      byte MBAP[] = {
        myHeader.tid[0],
        myHeader.tid[1],
        0x00,
        0x00,
        ((uint8_t) ((rxNdx - 2) >> 8)),
        ((uint8_t) ((rxNdx - 2) & 0xff))
      };
      sendResponse(MBAP, serialIn, rxNdx);
      serialState = IDLE;
    } else {
      data.errorCnt[ERROR_RTU]++;
    }



    rxNdx = 0;
  }
}

void sendResponse(const byte MBAP[], const byte PDU[], const uint16_t pduLength) {
  header_t myHeader = queueHeaders.first();
  responseLen = 0;
  while (responseLen < pduLength) { // include CRC
    if (responseLen < MAX_RESPONSE_LEN) {
      response[responseLen] = PDU[responseLen];
    }
    responseLen++;
  }
  if (myHeader.requestType & 32 /* UDP request*/) {
    Udp.beginPacket(myHeader.remIP, myHeader.remPort);
    if (data.config.enableRtuOverTcp) Udp.write(PDU, pduLength);
    else {
      Udp.write(MBAP, 6);
      Udp.write(PDU, pduLength - 2); //send without CRC
    }
    Udp.endPacket();




  } else if (myHeader.requestType & 8 /* TCP request*/) {
    byte sock = myHeader.requestType & 7 /* Stores TCP client number*/;
    EthernetClient client = EthernetClient(sock);
    if (W5100.readSnSR(sock) == SnSR::ESTABLISHED && W5100.readSnDPORT(sock) == myHeader.remPort) { // Check remote port should be enough or check also rem IP?
      if (data.config.enableRtuOverTcp) client.write(PDU, pduLength);
      else {
        client.write(MBAP, 6);
        client.write(PDU, pduLength - 2); //send without CRC
      }




    } // TODO TCP Connection Error
  } // else SCAN_REQUEST (no data.ethCnt[DATA_TX], but yes delete request)
  deleteRequest();
}

bool checkCRC(byte buf[], int16_t len) {
  crc = 0xFFFF;
  for (byte i = 0; i < len - 2; i++) {
    calculateCRC(buf[i]);
  }
  if (((uint8_t) ((crc) >> 8)) == buf[len - 1] && ((uint8_t) ((crc) & 0xff)) == buf[len - 2]) {
    return true;
  } else {
    return false;
  }
}

void calculateCRC(byte b) {
  crc ^= (uint16_t)b; // XOR byte into least sig. byte of crc
  for (byte i = 8; i != 0; i--) { // Loop over each bit
    if ((crc & 0x0001) != 0) { // If the LSB is set
      crc >>= 1; // Shift right and XOR 0xA001
      crc ^= 0xA001;
    } else // Else LSB is not set
      crc >>= 1; // Just shift right
  }
  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
}
# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\04-webserver.ino"
const byte URI_SIZE = 24; // a smaller buffer for uri
const byte POST_SIZE = 24; // a smaller buffer for single post parameter + key

// Actions that need to be taken after saving configuration.
enum action_type : byte {
  ACT_NONE,
  ACT_DEFAULT, // Load default factory settings (but keep MAC address)
  ACT_MAC, // Generate new random MAC
  ACT_REBOOT, // Reboot the microcontroller
  ACT_RESET_ETH, // Ethernet reset
  ACT_RESET_SERIAL, // Serial reset
  ACT_SCAN, // Initialize RTU scan
  ACT_RESET_STATS, // Reset Modbus Statistics
  ACT_CLEAR_REQUEST, // Clear Modbus Request form
  ACT_WEB // Restart webserver
};
enum action_type action;

// Pages served by the webserver. Order of elements defines the order in the left menu of the web UI.
// URL of the page (*.htm) contains number corresponding to its position in this array.
// The following enum array can have a maximum of 10 elements (incl. PAGE_NONE and PAGE_WAIT)
enum page : byte {
  PAGE_ERROR, // 404 Error
  PAGE_INFO,
  PAGE_STATUS,
  PAGE_IP,
  PAGE_TCP,
  PAGE_RTU,
  PAGE_TOOLS,
  PAGE_WAIT, // page with "Reloading. Please wait..." message.
  PAGE_DATA, // d.json
};

// Keys for POST parameters, used in web forms and processed by processPost() function.
// Using enum ensures unique identification of each POST parameter key and consistence across functions.
// In HTML code, each element will apear as number corresponding to its position in this array.
enum post_key : byte {
  POST_NONE, // reserved for NULL
  POST_DHCP, // enable DHCP
  POST_MAC,
  POST_MAC_1,
  POST_MAC_2,
  POST_MAC_3,
  POST_MAC_4,
  POST_MAC_5,
  POST_IP,
  POST_IP_1,
  POST_IP_2,
  POST_IP_3, // IP address         || Each part of an IP address has its own POST parameter.     ||
  POST_SUBNET,
  POST_SUBNET_1,
  POST_SUBNET_2,
  POST_SUBNET_3, // subnet             || Because HTML code for IP, subnet, gateway and DNS          ||
  POST_GATEWAY,
  POST_GATEWAY_1,
  POST_GATEWAY_2,
  POST_GATEWAY_3, // gateway            || is generated through one (nested) for-loop,                ||
  POST_DNS,
  POST_DNS_1,
  POST_DNS_2,
  POST_DNS_3, // DNS                || all these 16 enum elements must be listed in succession!!  ||
  POST_TCP, // TCP port                  || Because HTML code for these 3 ports              ||
  POST_UDP, // UDP port                  || is generated through one for-loop,               ||
  POST_WEB, // web UI port               || these 3 elements must be listed in succession!!  ||
  POST_RTU_OVER, // RTU over TCP/UDP
  POST_TCP_TIMEOUT, // Modbus TCP socket close timeout
  POST_BAUD, // baud rate
  POST_DATA, // data bits
  POST_PARITY, // parity
  POST_STOP, // stop bits
  POST_FRAMEDELAY, //frame delay
  POST_TIMEOUT, // response timeout
  POST_ATTEMPTS, // number of request attempts
  POST_REQ, // Modbus request send from WebUI (first byte)
  POST_REQ_1,
  POST_REQ_2,
  POST_REQ_3,
  POST_REQ_4,
  POST_REQ_5,
  POST_REQ_6,
  POST_REQ_LAST, // 8 bytes in total
  POST_ACTION, // actions on Tools page
};

byte request[POST_REQ_LAST - POST_REQ + 1]; // Array to store Modbus request sent from WebUI
byte requestLen = 0; // Length of the Modbus request send from WebUI


// Keys for JSON elements, used in: 1) JSON documents, 2) ID of span tags, 3) Javascript.
enum JSON_type : byte {
  JSON_TIME, // Runtime seconds
  JSON_RTU_DATA,
  JSON_ETH_DATA,
  JSON_RESPONSE,
  JSON_STATS, // Modbus statistics from array data.errorCnt[]
  JSON_QUEUE,
  JSON_TCP_UDP_MASTERS, // list of Modbus TCP/UDP masters separated by <br>
  JSON_SLAVES, // list of Modbus RTU slaves separated by <br>
  JSON_SOCKETS,
  JSON_LAST, // Must be the very last element in this array
};

/**************************************************************************/
/*!

  @brief Receives GET requests for web pages, receives POST data from web forms,

  calls @ref processPost() function, sends web pages. For simplicity, all web pages

  should are numbered (1.htm, 2.htm, ...), the page number is passed to 

  the @ref sendPage() function. Also executes actions (such as ethernet restart,

  reboot) during "please wait" web page.

  @param client Ethernet TCP client.

*/
# 112 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\04-webserver.ino"
/**************************************************************************/
void recvWeb(EthernetClient &client) {
  char uri[URI_SIZE]; // the requested page
  memset(uri, 0, sizeof(uri));
  while (client.available()) { // start reading the first line which should look like: GET /uri HTTP/1.1
    if (client.read() == ' ') break; // find space before /uri
  }
  byte len = 0;
  while (client.available() && len < sizeof(uri) - 1) {
    char c = client.read(); // parse uri
    if (c == ' ') break; // find space after /uri
    uri[len] = c;
    len++;
  }
  while (client.available()) {
    if (client.read() == '\r')
      if (client.read() == '\n')
        if (client.read() == '\r')
          if (client.read() == '\n')
            break; // find 2 end of lines between header and body
  }
  if (client.available()) {
    processPost(client); // parse post parameters
  }

  // Get the requested page from URI
  byte reqPage = PAGE_ERROR; // requested page, 404 error is a default
  if (uri[0] == '/') {
    if (uri[1] == '\0') // the homepage System Info
      reqPage = PAGE_INFO;
    else if (!strcmp(uri + 2, ".htm")) {
      reqPage = byte(uri[1] - 48); // Convert single ASCII char to byte
      if (reqPage >= PAGE_WAIT) reqPage = PAGE_ERROR;
    } else if (!strcmp(uri, "/d.json")) {
      reqPage = PAGE_DATA;
    }
  }
  // Actions that require "please wait" page
  if (action == ACT_WEB || action == ACT_MAC || action == ACT_RESET_ETH || action == ACT_REBOOT || action == ACT_DEFAULT) {
    reqPage = PAGE_WAIT;
  }
  // Send page
  sendPage(client, reqPage);

  // Do all actions before the "please wait" redirects (5s delay at the moment)
  if (reqPage == PAGE_WAIT) {
    switch (action) {
      case ACT_WEB:
        for (byte s = 0; s < maxSockNum; s++) {
          // close old webserver TCP connections
          if (EthernetClient(s).localPort() != data.config.tcpPort) {
            disconSocket(s);
          }
        }
        webServer = EthernetServer(data.config.webPort);
        break;
      case ACT_MAC:
      case ACT_RESET_ETH:
        for (byte s = 0; s < maxSockNum; s++) {
          // close all TCP and UDP sockets
          disconSocket(s);
        }
        startEthernet();
        break;
      case ACT_REBOOT:
      case ACT_DEFAULT:
        resetFunc();
        break;
      default:
        break;
    }
  }
  action = ACT_NONE;
}

/**************************************************************************/
/*!

  @brief Processes POST data from forms and buttons, updates data.config (in RAM)

  and saves config into EEPROM. Executes actions which do not require webserver restart

  @param client Ethernet TCP client.

*/
# 193 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\04-webserver.ino"
/**************************************************************************/
void processPost(EthernetClient &client) {
  while (client.available()) {
    char post[POST_SIZE];
    byte len = 0;
    while (client.available() && len < sizeof(post) - 1) {
      char c = client.read();
      if (c == '&') break;
      post[len] = c;
      len++;
    }
    post[len] = '\0';
    char *paramKey = post;
    char *paramValue = post;
    while (*paramValue) {
      if (*paramValue == '=') {
        paramValue++;
        break;
      }
      paramValue++;
    }
    if (*paramValue == '\0')
      continue; // do not process POST parameter if there is no parameter value
    byte paramKeyByte = strToByte(paramKey);
    uint16_t paramValueUint = atol(paramValue);
    switch (paramKeyByte) {
      case POST_NONE: // reserved, because atoi / atol returns NULL in case of error
        break;
# 233 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\04-webserver.ino"
      case POST_REQ ... POST_REQ_LAST:
        {
          requestLen = paramKeyByte - POST_REQ + 1;
          request[requestLen - 1] = strToByte(paramValue);
        }
        break;
      case POST_MAC ... POST_MAC_5:
        {
          action = ACT_RESET_ETH; // this RESET_ETH is triggered when the user changes anything on the "IP Settings" page.
                                   // No need to trigger RESET_ETH for other cases (POST_SUBNET, POST_GATEWAY etc.)
                                   // if "Randomize" button is pressed, action is set to ACT_MAC
          data.mac[paramKeyByte - POST_MAC] = strToByte(paramValue);
        }
        break;
      case POST_IP ... POST_IP_3:
        {
          data.config.ip[paramKeyByte - POST_IP] = byte(paramValueUint);
        }
        break;
      case POST_SUBNET ... POST_SUBNET_3:
        {
          data.config.subnet[paramKeyByte - POST_SUBNET] = byte(paramValueUint);
        }
        break;
      case POST_GATEWAY ... POST_GATEWAY_3:
        {
          data.config.gateway[paramKeyByte - POST_GATEWAY] = byte(paramValueUint);
        }
        break;
      case POST_TCP:
        {
          if (paramValueUint != data.config.webPort && paramValueUint != data.config.tcpPort) { // continue only of the value changed and it differs from WebUI port
            for (byte s = 0; s < maxSockNum; s++) {
              if (EthernetClient(s).localPort() == data.config.tcpPort) { // close only Modbus TCP sockets
                disconSocket(s);
              }
            }
            data.config.tcpPort = paramValueUint;
            modbusServer = EthernetServer(data.config.tcpPort);
          }
        }
        break;
      case POST_UDP:
        {
          data.config.udpPort = paramValueUint;
          Udp.stop();
          Udp.begin(data.config.udpPort);
        }
        break;
      case POST_WEB:
        {
          if (paramValueUint != data.config.webPort && paramValueUint != data.config.tcpPort) { // continue only of the value changed and it differs from Modbus TCP port
            data.config.webPort = paramValueUint;
            action = ACT_WEB;
          }
        }
        break;
      case POST_RTU_OVER:
        data.config.enableRtuOverTcp = byte(paramValueUint);
        break;
      case POST_TCP_TIMEOUT:
        data.config.tcpTimeout = paramValueUint;
        break;
      case POST_BAUD:
        {
          action = ACT_RESET_SERIAL; // this RESET_SERIAL is triggered when the user changes anything on the "RTU Settings" page.
          // No need to trigger RESET_ETH for other cases (POST_DATA, POST_PARITY etc.)
          data.config.baud = paramValueUint;
          byte minFrameDelay = byte((frameDelay() / 1000UL) + 1);
          if (data.config.frameDelay < minFrameDelay) {
            data.config.frameDelay = minFrameDelay;
          }
        }
        break;
      case POST_DATA:
        {
          data.config.serialConfig = (data.config.serialConfig & 0xF9) | ((byte(paramValueUint) - 5) << 1);
        }
        break;
      case POST_PARITY:
        {
          data.config.serialConfig = (data.config.serialConfig & 0xCF) | (byte(paramValueUint) << 4);
        }
        break;
      case POST_STOP:
        {
          data.config.serialConfig = (data.config.serialConfig & 0xF7) | ((byte(paramValueUint) - 1) << 3);
        }
        break;
      case POST_FRAMEDELAY:
        data.config.frameDelay = byte(paramValueUint);
        break;
      case POST_TIMEOUT:
        data.config.serialTimeout = paramValueUint;
        break;
      case POST_ATTEMPTS:
        data.config.serialAttempts = byte(paramValueUint);
        break;
      case POST_ACTION:
        action = action_type(paramValueUint);
        break;
      default:
        break;
    }
  }
  switch (action) {
    case ACT_DEFAULT:
      data.config = DEFAULT_CONFIG;
      break;
    case ACT_RESET_STATS:
      resetStats();
      break;
    case ACT_MAC:
      generateMac();
      break;
    case ACT_RESET_SERIAL:
      clearQueue();
      startSerial();
      break;
    case ACT_SCAN:
      scanCounter = 1;
      memset(&slaveStatus, 0, sizeof(slaveStatus)); // clear all status flags
      break;
    case ACT_CLEAR_REQUEST:
      requestLen = 0;
      responseLen = 0;
      break;
    default:
      break;
  }
  // if new Modbus request received, put into queue
  if (action != ACT_SCAN && action != ACT_RESET_STATS && requestLen > 1 && queueHeaders.available() > 1 && queueData.available() > requestLen) { // at least 2 bytes in request (slave address and function)
    // push to queue
    queueHeaders.push(header_t{
      { 0x00, 0x00 }, // tid[2]
      requestLen, // msgLen
      { 0, 0, 0, 0 }, // remIP[4]
      0, // remPort
      32 /* UDP request*/, // requestType
      0, // atts
    });
    for (byte i = 0; i < requestLen; i++) {
      queueData.push(request[i]);
    }
    responseLen = 0; // clear old Modbus Response from WebUI
  }
  // new parameter values received, save them to EEPROM
  updateEeprom(); // it is safe to call, only changed values (and changed error and data counters) are updated
}

/**************************************************************************/
/*!

  @brief Parses string and returns single byte.

  @param myStr String (2 chars, 1 char + null or 1 null) to be parsed.

  @return Parsed byte.

*/
# 389 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\04-webserver.ino"
/**************************************************************************/
byte strToByte(const char myStr[]) {
  if (!myStr) return 0;
  byte x = 0;
  for (byte i = 0; i < 2; i++) {
    char c = myStr[i];
    if (c >= '0' && c <= '9') {
      x *= 16;
      x += c - '0';
    } else if (c >= 'A' && c <= 'F') {
      x *= 16;
      x += (c - 'A') + 10;
    } else if (c >= 'a' && c <= 'f') {
      x *= 16;
      x += (c - 'a') + 10;
    }
  }
  return x;
}

char __printbuffer[3];
/**************************************************************************/
/*!

  @brief Converts byte to char string, from https://github.com/RobTillaart/printHelpers

  @param val Byte to be conferted.

  @return Char string.

*/
# 416 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\04-webserver.ino"
/**************************************************************************/
char *hex(byte val) {
  char *buffer = __printbuffer;
  byte digits = 2;
  buffer[digits] = '\0';
  while (digits > 0) {
    byte v = val & 0x0F;
    val >>= 4;
    digits--;
    buffer[digits] = (v < 10) ? '0' + v : ('A' - 10) + v;
  }
  return buffer;
}
# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
const byte WEB_OUT_BUFFER_SIZE = 64; // size of web server write buffer (used by StreamLib)

/**************************************************************************/
/*!

  @brief Sends the requested page (incl. 404 error and JSON document),

  displays main page, renders title and left menu using, calls content functions

  depending on the number (i.e. URL) of the requested web page.

  In order to save flash memory, some HTML closing tags are omitted,

  new lines in HTML code are also omitted.

  @param client Ethernet TCP client

  @param reqPage Requested page number

*/
# 13 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
/**************************************************************************/
void sendPage(EthernetClient &client, byte reqPage) {
  char webOutBuffer[WEB_OUT_BUFFER_SIZE];
  ChunkedPrint chunked(client, webOutBuffer, sizeof(webOutBuffer)); // the StreamLib object to replace client print
  if (reqPage == PAGE_ERROR) {
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 18 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 18 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 "HTTP/1.1 404 Not Found\r\n" "\r\n" "404 Not found"
# 18 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 18 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 ))

                                    );
    chunked.end();
    return;
  } else if (reqPage == PAGE_DATA) {
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 24 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 24 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 "HTTP/1.1 200\r\n" /* An advantage of HTTP 1.1 is that you can keep the connection alive*/ "Content-Type: application/json\r\n" "Transfer-Encoding: chunked\r\n" "\r\n"
# 24 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 24 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 ))


                           );
    chunked.begin();
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 29 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 29 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 "{"
# 29 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 29 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
    for (byte i = 0; i < JSON_LAST; i++) {
      if (i) chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 31 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                          (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 31 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                          ","
# 31 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                          ); &__c[0];}))
# 31 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                          )));
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 32 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 32 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   "\""
# 32 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 32 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      chunked.print(i);
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 34 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 34 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   "\":\""
# 34 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 34 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      jsonVal(chunked, i);
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 36 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 36 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   "\""
# 36 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 36 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
    }
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 38 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 38 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 "}"
# 38 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 38 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
    chunked.end();
    return;
  }
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 42 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 42 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "HTTP/1.1 200 OK\r\n" "Content-Type: text/html\r\n" "Transfer-Encoding: chunked\r\n" "\r\n"
# 42 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 42 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               ))


                         );
  chunked.begin();
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 47 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 47 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "<!DOCTYPE html>" "<html>" "<head>" "<meta"
# 47 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 47 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               ))


                          );
  if (reqPage == PAGE_WAIT) { // redirect to new IP and web port
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 52 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 52 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 " http-equiv=refresh content=5;url=http://"
# 52 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 52 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
    chunked.print(IPAddress(data.config.ip));
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 54 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 54 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 ":"
# 54 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 54 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
    chunked.print(data.config.webPort);
  }
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 57 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 57 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               ">" "<title>Modbus RTU &rArr; Modbus TCP/UDP Gateway</title>" "<style>" /*

                  HTML Tags

                    h1 - main title of the page

                    h4 - text in navigation menu and header of page content

                    a - items in left navigation menu

                    label - first cell of a row in content

                  CSS Classes

                    w - wrapper (includes m + c)

                    m  - navigation menu (left)

                    c - content of a page

                    r - row inside a content

                    i - short input (byte or IP address octet)

                    n - input type=number

                    s - select input with numbers

                    p - inputs disabled by id=o checkbox

                  CSS Ids

                    o - checkbox which disables other checkboxes and inputs

                  */
# 57 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                "body,.m{padding:1px;margin:0;font-family:sans-serif}" "h1,h4{padding:10px}" "h1,.m,h4{background:#0067AC;margin:1px}" ".m,.c{height:calc(100vh - 71px)}" ".m{min-width:20%}" ".c{flex-grow:1;overflow-y:auto}" ".w,.r{display:flex}" "a,h1,h4{color:white;text-decoration:none}" ".c h4{padding-left:30%;margin-bottom:20px}" ".r{margin:4px}" "label{width:30%;text-align:right;margin-right:2px}" "input,button,select{margin-top:-2px}" /* improve vertical allignment of input, button and select*/ ".s{text-align:right}" ".s>option{direction:rtl}" ".i{text-align:center;width:3ch;color:black}" ".n{width:8ch}" "</style>" "</head>" "<body"
# 57 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 57 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               ))
# 96 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                          );




  if (reqPage == PAGE_STATUS) {
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 102 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 102 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 "><script>" "var a;" "const b=()=>{" "fetch('d.json')" /* Call the fetch function passing the url of the API as a parameter*/ ".then(e=>{return e.json();a=0})" ".then(f=>{for(var i in f){if(document.getElementById(i))document.getElementById(i).innerHTML=f[i];}})" ".catch(()=>{if(!a){alert('Connnection lost');a=1}})" "};" "setInterval(()=>b(),"
# 102 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 102 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 ))







                                           );
    chunked.print(FETCH_INTERVAL);
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 112 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 112 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 ");" "</script"
# 112 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 112 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 ))
                               );
  }
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 115 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 115 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               ">" "<h1>Modbus RTU &rArr; Modbus TCP/UDP Gateway</h1>" "<div class=w>" "<div class=m>"
# 115 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 115 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               ))


                                  );

  // Left Menu
  for (byte i = 1; i < PAGE_WAIT; i++) { // PAGE_WAIT is the last item in enum
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 122 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 122 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 "<h4 "
# 122 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 122 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
    if ((i) == reqPage) {
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 124 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 124 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   " style=background-color:#FF6600"
# 124 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 124 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
    }
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 126 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 126 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 "><a href="
# 126 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 126 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
    chunked.print(i);
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 128 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 128 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 ".htm>"
# 128 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 128 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
    stringPageName(chunked, i);
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 130 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 130 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 "</a></h4>"
# 130 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 130 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
  }
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 132 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 132 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "</div>" /* <div class=w>*/ "<div class=c>" "<h4>"
# 132 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 132 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               ))

                         );
  stringPageName(chunked, reqPage);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 136 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 136 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "</h4>" "<form method=post>"
# 136 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 136 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               ))
                                       );

  //   PLACE FUNCTIONS PROVIDING CONTENT HERE
  switch (reqPage) {
    case PAGE_INFO:
      contentInfo(chunked);
      break;
    case PAGE_STATUS:
      contentStatus(chunked);
      break;
    case PAGE_IP:
      contentIp(chunked);
      break;
    case PAGE_TCP:
      contentTcp(chunked);
      break;
    case PAGE_RTU:
      contentRtu(chunked);
      break;
    case PAGE_TOOLS:
      contentTools(chunked);
      break;
    case PAGE_WAIT:
      contentWait(chunked);
      break;
    default:
      break;
  }

  if (reqPage == PAGE_IP || reqPage == PAGE_TCP || reqPage == PAGE_RTU) {
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 167 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 167 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 "<p><div class=r><label><input type=submit value='Save & Apply'></label><input type=reset value=Cancel></div>"
# 167 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 167 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
  }
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 169 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 169 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "</form>"
# 169 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 169 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  tagDivClose(chunked); // close tags <div class=c> <div class=w>
  chunked.end(); // closing tags not required </body></html>
}


/**************************************************************************/
/*!

  @brief System Info



  @param chunked Chunked buffer

*/
# 181 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
/**************************************************************************/
void contentInfo(ChunkedPrint &chunked) {
  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 183 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 183 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "SW Version"
# 183 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 183 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  chunked.print(VERSION[0]);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 185 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 185 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "."
# 185 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 185 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  chunked.print(VERSION[1]);
  tagDivClose(chunked);
  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 188 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 188 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "Microcontroller"
# 188 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 188 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 189 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 189 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "Arduino Nano"
# 189 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 189 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  tagDivClose(chunked);
  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 191 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 191 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "EEPROM Health"
# 191 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 191 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  chunked.print(data.eepromWrites);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 193 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 193 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               " Write Cycles"
# 193 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 193 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  tagDivClose(chunked);
  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 195 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 195 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "Ethernet Chip"
# 195 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 195 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  switch (W5100.getChip()) {
    case 51:
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 198 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 198 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   "W5100"
# 198 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 198 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      break;
    case 52:
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 201 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 201 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   "W5200"
# 201 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 201 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      break;
    case 55:
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 204 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 204 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   "W5500"
# 204 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 204 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      break;
    default: // TODO: add W6100 once it is included in Ethernet library
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 207 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 207 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   "Unknown"
# 207 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 207 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      break;
  }
  tagDivClose(chunked);
  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 211 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 211 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "Ethernet Sockets"
# 211 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 211 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  chunked.print(maxSockNum);
  tagDivClose(chunked);
  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 214 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 214 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "MAC Address"
# 214 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 214 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  for (byte i = 0; i < 6; i++) {
    chunked.print(hex(data.mac[i]));
    if (i < 5) chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 217 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                            (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 217 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                            ":"
# 217 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                            ); &__c[0];}))
# 217 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                            )));
  }
  tagDivClose(chunked);
# 233 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 233 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 233 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "IP Address"
# 233 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 233 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  chunked.print(IPAddress(Ethernet.localIP()));
  tagDivClose(chunked);
}

/**************************************************************************/
/*!

  @brief P1P2 Status



  @param chunked Chunked buffer

*/
# 244 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
/**************************************************************************/
void contentStatus(ChunkedPrint &chunked) {
# 259 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 259 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 259 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "Modbus RTU Request"
# 259 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 259 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  for (byte i = 0; i <= POST_REQ_LAST - POST_REQ; i++) {
    bool required = false;
    bool printVal = false;
    byte value;
    if (i == 0 || i == 1) {
      required = true; // first byte (slave address) and second byte (function code) are required
    }
    if (i < requestLen) {
      printVal = true;
      value = request[i];
    }
    tagInputHex(chunked, POST_REQ + i, required, printVal, value);
  }
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 273 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 273 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "h (without CRC) <input type=submit value=Send>"
# 273 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 273 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  tagButton(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 274 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                    (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 274 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                    "Clear"
# 274 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                    ); &__c[0];}))
# 274 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                    )), ACT_CLEAR_REQUEST);
  tagDivClose(chunked);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 276 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 276 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "</form><form method=post>"
# 276 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 276 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 277 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 277 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "Modbus RTU Response"
# 277 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 277 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  tagSpan(chunked, JSON_RESPONSE);
  tagDivClose(chunked);
  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 280 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 280 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "Requests Queue"
# 280 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 280 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  tagSpan(chunked, JSON_QUEUE);
  tagDivClose(chunked);
  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 283 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 283 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "Modbus Statistics"
# 283 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 283 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  tagButton(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 284 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                    (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 284 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                    "Reset Stats"
# 284 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                    ); &__c[0];}))
# 284 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                    )), ACT_RESET_STATS);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 285 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 285 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "<br>"
# 285 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 285 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  tagSpan(chunked, JSON_STATS);
  tagDivClose(chunked);
  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 288 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 288 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "Modbus Masters"
# 288 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 288 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  tagSpan(chunked, JSON_TCP_UDP_MASTERS);
  tagDivClose(chunked);
  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 291 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 291 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "Modbus Slaves"
# 291 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 291 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  tagButton(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 292 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                    (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 292 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                    "Scan Slaves"
# 292 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                    ); &__c[0];}))
# 292 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                    )), ACT_SCAN);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 293 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 293 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "<br>"
# 293 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 293 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  tagSpan(chunked, JSON_SLAVES);
  tagDivClose(chunked);
}

/**************************************************************************/
/*!

  @brief IP Settings



  @param chunked Chunked buffer

*/
# 304 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
/**************************************************************************/
void contentIp(ChunkedPrint &chunked) {

  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 307 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 307 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "MAC Address"
# 307 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 307 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  for (byte i = 0; i < 6; i++) {
    tagInputHex(chunked, POST_MAC + i, true, true, data.mac[i]);
    if (i < 5) chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 310 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                            (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 310 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                            ":"
# 310 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                            ); &__c[0];}))
# 310 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                            )));
  }
  tagButton(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 312 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                    (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 312 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                    "Randomize"
# 312 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                    ); &__c[0];}))
# 312 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                    )), ACT_MAC);
  tagDivClose(chunked);
# 328 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
  byte *tempIp;
  for (byte j = 0; j < 3; j++) {
    switch (j) {
      case 0:
        tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 332 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                            (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 332 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                            "Static IP"
# 332 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                            ); &__c[0];}))
# 332 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                            )));
        tempIp = data.config.ip;
        break;
      case 1:
        tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 336 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                            (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 336 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                            "Submask"
# 336 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                            ); &__c[0];}))
# 336 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                            )));
        tempIp = data.config.subnet;
        break;
      case 2:
        tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 340 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                            (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 340 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                            "Gateway"
# 340 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                            ); &__c[0];}))
# 340 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                            )));
        tempIp = data.config.gateway;
        break;
      default:
        break;
    }
    tagInputIp(chunked, POST_IP + (j * 4), tempIp);
    tagDivClose(chunked);
  }





}

/**************************************************************************/
/*!

  @brief TCP/UDP Settings



  @param chunked Chunked buffer

*/
# 362 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
/**************************************************************************/
void contentTcp(ChunkedPrint &chunked) {
  uint16_t value;
  for (byte i = 0; i < 3; i++) {
    switch (i) {
      case 0:
        tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 368 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                            (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 368 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                            "Modbus TCP Port"
# 368 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                            ); &__c[0];}))
# 368 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                            )));
        value = data.config.tcpPort;
        break;
      case 1:
        tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 372 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                            (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 372 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                            "Modbus UDP Port"
# 372 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                            ); &__c[0];}))
# 372 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                            )));
        value = data.config.udpPort;
        break;
      case 2:
        tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 376 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                            (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 376 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                            "WebUI Port"
# 376 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                            ); &__c[0];}))
# 376 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                            )));
        value = data.config.webPort;
        break;
      default:
        break;
    }
    tagInputNumber(chunked, POST_TCP + i, 1, 65535, value, (reinterpret_cast<const __FlashStringHelper *>(
# 382 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                                                          (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 382 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                                                          ""
# 382 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                                                          ); &__c[0];}))
# 382 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                                                          )));
    tagDivClose(chunked);
  }
  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 385 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 385 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "Modbus Mode"
# 385 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 385 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 386 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 386 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "<select name="
# 386 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 386 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  chunked.print(POST_RTU_OVER, 16);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 388 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 388 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               ">"
# 388 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 388 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  for (byte i = 0; i < 2; i++) {
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 390 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 390 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 "<option value="
# 390 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 390 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
    chunked.print(i);
    if (data.config.enableRtuOverTcp == i) chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 392 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                                                        (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 392 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                                                        " selected"
# 392 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                                                        ); &__c[0];}))
# 392 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                                                        )));
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 393 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 393 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 ">"
# 393 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 393 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
    switch (i) {
      case 0:
        chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 396 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 396 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                     "Modbus TCP/UDP"
# 396 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                     ); &__c[0];}))
# 396 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                     )));
        break;
      case 1:
        chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 399 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 399 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                     "Modbus RTU over TCP/UDP"
# 399 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                     ); &__c[0];}))
# 399 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                     )));
        break;
      default:
        break;
    }
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 404 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 404 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 "</option>"
# 404 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 404 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
  }
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 406 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 406 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "</select>"
# 406 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 406 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  tagDivClose(chunked);
  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 408 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 408 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "Modbus TCP Idle Timeout"
# 408 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 408 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  tagInputNumber(chunked, POST_TCP_TIMEOUT, 1, 3600, data.config.tcpTimeout, (reinterpret_cast<const __FlashStringHelper *>(
# 409 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                                                                            (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 409 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                                                                            "sec"
# 409 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                                                                            ); &__c[0];}))
# 409 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                                                                            )));
  tagDivClose(chunked);
}

/**************************************************************************/
/*!

  @brief RTU Settings



  @param chunked Chunked buffer

*/
# 419 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
/**************************************************************************/
void contentRtu(ChunkedPrint &chunked) {
  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 421 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 421 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "Baud Rate"
# 421 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 421 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 422 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 422 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "<select class=s name="
# 422 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 422 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  chunked.print(POST_BAUD, 16);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 424 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 424 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               ">"
# 424 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 424 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  for (byte i = 0; i < (sizeof(BAUD_RATES) / 2); i++) {
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 426 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 426 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 "<option value="
# 426 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 426 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
    chunked.print(BAUD_RATES[i]);
    if (data.config.baud == BAUD_RATES[i]) chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 428 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                                                        (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 428 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                                                        " selected"
# 428 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                                                        ); &__c[0];}))
# 428 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                                                        )));
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 429 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 429 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 ">"
# 429 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 429 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
    chunked.print(BAUD_RATES[i]);
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 431 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 431 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 "00</option>"
# 431 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 431 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
  }
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 433 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 433 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "</select> bps"
# 433 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 433 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  tagDivClose(chunked);
  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 435 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 435 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "Data Bits"
# 435 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 435 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 436 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 436 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "<select name="
# 436 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 436 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  chunked.print(POST_DATA, 16);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 438 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 438 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               ">"
# 438 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 438 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  for (byte i = 5; i <= 8; i++) {
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 440 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 440 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 "<option value="
# 440 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 440 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
    chunked.print(i);
    if ((((data.config.serialConfig & 0x06) >> 1) + 5) == i) chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 442 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                                                                          (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 442 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                                                                          " selected"
# 442 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                                                                          ); &__c[0];}))
# 442 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                                                                          )));
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 443 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 443 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 ">"
# 443 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 443 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
    chunked.print(i);
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 445 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 445 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 "</option>"
# 445 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 445 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
  }
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 447 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 447 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "</select> bit"
# 447 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 447 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  tagDivClose(chunked);
  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 449 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 449 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "Parity"
# 449 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 449 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 450 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 450 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "<select name="
# 450 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 450 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  chunked.print(POST_PARITY, 16);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 452 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 452 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               ">"
# 452 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 452 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  for (byte i = 0; i <= 3; i++) {
    if (i == 1) continue; // invalid value, skip and continue for loop
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 455 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 455 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 "<option value="
# 455 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 455 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
    chunked.print(i);
    if (((data.config.serialConfig & 0x30) >> 4) == i) chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 457 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                                                                    (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 457 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                                                                    " selected"
# 457 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                                                                    ); &__c[0];}))
# 457 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                                                                    )));
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 458 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 458 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 ">"
# 458 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 458 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
    switch (i) {
      case 0:
        chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 461 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 461 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                     "None"
# 461 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                     ); &__c[0];}))
# 461 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                     )));
        break;
      case 2:
        chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 464 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 464 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                     "Even"
# 464 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                     ); &__c[0];}))
# 464 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                     )));
        break;
      case 3:
        chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 467 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 467 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                     "Odd"
# 467 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                     ); &__c[0];}))
# 467 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                     )));
        break;
      default:
        break;
    }
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 472 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 472 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 "</option>"
# 472 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 472 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
  }
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 474 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 474 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "</select>"
# 474 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 474 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  tagDivClose(chunked);
  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 476 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 476 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "Stop Bits"
# 476 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 476 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 477 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 477 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "<select name="
# 477 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 477 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  chunked.print(POST_STOP, 16);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 479 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 479 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               ">"
# 479 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 479 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  for (byte i = 1; i <= 2; i++) {
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 481 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 481 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 "<option value="
# 481 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 481 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
    chunked.print(i);
    if ((((data.config.serialConfig & 0x08) >> 3) + 1) == i) chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 483 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                                                                          (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 483 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                                                                          " selected"
# 483 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                                                                          ); &__c[0];}))
# 483 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                                                                          )));
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 484 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 484 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 ">"
# 484 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 484 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
    chunked.print(i);
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 486 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 486 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 "</option>"
# 486 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 486 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
  }
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 488 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 488 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "</select> bit"
# 488 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 488 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  tagDivClose(chunked);
  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 490 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 490 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "Inter-frame Delay"
# 490 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 490 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  tagInputNumber(chunked, POST_FRAMEDELAY, byte(frameDelay() / 1000UL) + 1, 250, data.config.frameDelay, (reinterpret_cast<const __FlashStringHelper *>(
# 491 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                                                                                                        (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 491 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                                                                                                        "ms"
# 491 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                                                                                                        ); &__c[0];}))
# 491 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                                                                                                        )));
  tagDivClose(chunked);
  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 493 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 493 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "Response Timeout"
# 493 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 493 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  tagInputNumber(chunked, POST_TIMEOUT, 50, 5000, data.config.serialTimeout, (reinterpret_cast<const __FlashStringHelper *>(
# 494 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                                                                            (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 494 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                                                                            "ms"
# 494 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                                                                            ); &__c[0];}))
# 494 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                                                                            )));
  tagDivClose(chunked);
  tagLabelDiv(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 496 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 496 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      "Attempts"
# 496 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                      ); &__c[0];}))
# 496 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                      )));
  tagInputNumber(chunked, POST_ATTEMPTS, 1, 5, data.config.serialAttempts, (reinterpret_cast<const __FlashStringHelper *>(
# 497 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                                                                          (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 497 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                                                                          ""
# 497 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                                                                          ); &__c[0];}))
# 497 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                                                                          )));
  tagDivClose(chunked);
}

/**************************************************************************/
/*!

  @brief Tools



  @param chunked Chunked buffer

*/
# 507 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
/**************************************************************************/
void contentTools(ChunkedPrint &chunked) {
  tagLabelDiv(chunked, 0);
  tagButton(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 510 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                    (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 510 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                    "Load Default Settings"
# 510 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                    ); &__c[0];}))
# 510 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                    )), ACT_DEFAULT);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 511 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 511 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               " (static IP: "
# 511 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 511 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  chunked.print(IPAddress(DEFAULT_CONFIG.ip));
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 513 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 513 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               ")"
# 513 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 513 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  tagDivClose(chunked);
  tagLabelDiv(chunked, 0);
  tagButton(chunked, (reinterpret_cast<const __FlashStringHelper *>(
# 516 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                    (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 516 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                    "Reboot"
# 516 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                    ); &__c[0];}))
# 516 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                    )), ACT_REBOOT);
  tagDivClose(chunked);
}


void contentWait(ChunkedPrint &chunked) {
  tagLabelDiv(chunked, 0);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 523 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 523 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "Reloading. Please wait..."
# 523 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 523 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  tagDivClose(chunked);
}

/**************************************************************************/
/*!

  @brief <input type=number>



  @param chunked Chunked buffer

  @param name Name POST_

  @param min Minimum value

  @param max Maximum value

  @param value Current value

  @param units Units (string)

*/
# 538 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
/**************************************************************************/
void tagInputNumber(ChunkedPrint &chunked, const byte name, const byte min, uint16_t max, uint16_t value, const __FlashStringHelper *units) {
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 540 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 540 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "<input class='s n' required type=number name="
# 540 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 540 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  chunked.print(name, 16);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 542 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 542 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               " min="
# 542 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 542 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  chunked.print(min);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 544 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 544 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               " max="
# 544 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 544 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  chunked.print(max);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 546 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 546 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               " value="
# 546 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 546 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  chunked.print(value);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 548 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 548 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "> ("
# 548 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 548 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  chunked.print(min);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 550 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 550 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "~"
# 550 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 550 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  chunked.print(max);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 552 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 552 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               ") "
# 552 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 552 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  chunked.print(units);
}

/**************************************************************************/
/*!

  @brief <input>

  IP address (4 elements)



  @param chunked Chunked buffer

  @param name Name POST_

  @param ip IP address from data.config

*/
# 565 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
/**************************************************************************/
void tagInputIp(ChunkedPrint &chunked, const byte name, byte ip[]) {
  for (byte i = 0; i < 4; i++) {
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 568 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 568 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 "<input name="
# 568 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 568 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
    chunked.print(name + i, 16);
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 570 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 570 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 " class='p i' required maxlength=3 pattern='^(&bsol;d{1,2}|1&bsol;d&bsol;d|2[0-4]&bsol;d|25[0-5])$' value="
# 570 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 570 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
    chunked.print(ip[i]);
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 572 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 572 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 ">"
# 572 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 572 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
    if (i < 3) chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 573 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                            (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 573 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                            "."
# 573 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                            ); &__c[0];}))
# 573 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                            )));
  }
}

/**************************************************************************/
/*!

  @brief <input>

  HEX string (2 chars)



  @param chunked Chunked buffer

  @param name Name POST_

  @param required True if input is required

  @param printVal True if value is shown

  @param value Value

*/
# 588 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
/**************************************************************************/
void tagInputHex(ChunkedPrint &chunked, const byte name, const bool required, const bool printVal, const byte value) {
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 590 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 590 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "<input name="
# 590 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 590 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  chunked.print(name, 16);
  if (required) {
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 593 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 593 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 " required"
# 593 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 593 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
  }
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 595 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 595 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               " minlength=2 maxlength=2 class=i pattern='[a-fA-F&bsol;d]+' value='"
# 595 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 595 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  if (printVal) {
    chunked.print(hex(value));
  }
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 599 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 599 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "'>"
# 599 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 599 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
}

/**************************************************************************/
/*!

  @brief <label><div>



  @param chunked Chunked buffer

  @param label Label string

*/
# 609 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
/**************************************************************************/
void tagLabelDiv(ChunkedPrint &chunked, const __FlashStringHelper *label) {
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 611 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 611 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "<div class=r>"
# 611 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 611 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 612 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 612 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "<label> "
# 612 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 612 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  if (label) {
    chunked.print(label);
    chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 615 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 615 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 ":"
# 615 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                 ); &__c[0];}))
# 615 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                 )));
  }
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 617 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 617 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "</label><div>"
# 617 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 617 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
}

/**************************************************************************/
/*!

  @brief <button>



  @param chunked Chunked buffer

  @param flashString Button string

  @param value Value to be sent via POST

*/
# 628 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
/**************************************************************************/
void tagButton(ChunkedPrint &chunked, const __FlashStringHelper *flashString, byte value) {
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 630 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 630 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               " <button name="
# 630 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 630 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  chunked.print(POST_ACTION, 16);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 632 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 632 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               " value="
# 632 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 632 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  chunked.print(value);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 634 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 634 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               ">"
# 634 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 634 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  chunked.print(flashString);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 636 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 636 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "</button>"
# 636 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 636 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
}

/**************************************************************************/
/*!

  @brief </div>



  @param chunked Chunked buffer

*/
# 645 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
/**************************************************************************/
void tagDivClose(ChunkedPrint &chunked) {
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 647 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 647 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "</div>" "</div>"
# 647 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 647 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               ))
                           ); // <div class=r>
}

/**************************************************************************/
/*!

  @brief <span>



  @param chunked Chunked buffer

  @param JSONKEY JSON_ id

*/
# 658 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
/**************************************************************************/
void tagSpan(ChunkedPrint &chunked, const byte JSONKEY) {
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 660 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 660 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "<span id="
# 660 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 660 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  chunked.print(JSONKEY);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 662 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 662 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               ">"
# 662 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 662 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
  jsonVal(chunked, JSONKEY);
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 664 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 664 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "</span>"
# 664 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 664 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
}

/**************************************************************************/
/*!

  @brief Menu item strings



  @param chunked Chunked buffer

  @param item Page number

*/
# 674 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
/**************************************************************************/
void stringPageName(ChunkedPrint &chunked, byte item) {
  switch (item) {
    case PAGE_INFO:
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 678 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 678 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   "System Info"
# 678 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 678 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      break;
    case PAGE_STATUS:
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 681 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 681 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   "Modbus Status"
# 681 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 681 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      break;
    case PAGE_IP:
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 684 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 684 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   "IP Settings"
# 684 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 684 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      break;
    case PAGE_TCP:
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 687 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 687 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   "TCP/UDP Settings"
# 687 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 687 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      break;
    case PAGE_RTU:
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 690 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 690 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   "RTU Settings"
# 690 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 690 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      break;
    case PAGE_TOOLS:
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 693 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 693 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   "Tools"
# 693 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 693 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      break;
    default:
      break;
  }
}

void stringStats(ChunkedPrint &chunked, const byte stat) {
  switch (stat) {
    case SLAVE_OK:
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 703 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 703 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   " Slave Responded"
# 703 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 703 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      break;
    case SLAVE_ERROR_0X:
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 706 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 706 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   " Slave Responded with Error (Codes 1~8)"
# 706 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 706 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      break;
    case SLAVE_ERROR_0A:
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 709 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 709 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   " Gateway Overloaded (Code 10)"
# 709 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 709 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      break;
    case SLAVE_ERROR_0B:
    case SLAVE_ERROR_0B_QUEUE:
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 713 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 713 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   " Slave Failed to Respond (Code 11)"
# 713 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 713 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      break;
    case ERROR_TIMEOUT:
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 716 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 716 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   " Response Timeout"
# 716 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 716 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      break;
    case ERROR_RTU:
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 719 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 719 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   " Invalid RTU Response"
# 719 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 719 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      break;
    case ERROR_TCP:
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 722 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 722 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   " Invalid TCP/UDP Request"
# 722 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 722 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      break;
    default:
      break;
  }
  chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 727 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 727 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               "<br>"
# 727 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
               ); &__c[0];}))
# 727 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
               )));
}

/**************************************************************************/
/*!

  @brief Provide JSON value to a corresponding JSON key. The value is printed

  in <span> and in JSON document fetched on the background.

  @param chunked Chunked buffer

  @param JSONKEY JSON key

*/
# 737 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
/**************************************************************************/
void jsonVal(ChunkedPrint &chunked, const byte JSONKEY) {
  switch (JSONKEY) {
# 777 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
    case JSON_RESPONSE:
      {
        for (byte i = 0; i < MAX_RESPONSE_LEN; i++) {
          chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 780 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                       (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 780 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                       "<input value='"
# 780 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                       ); &__c[0];}))
# 780 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                       )));
          if (i < responseLen) {
            chunked.print(hex(response[i]));
          }
          chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 784 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                       (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 784 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                       "' disabled class=i>"
# 784 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                       ); &__c[0];}))
# 784 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                       )));
        }
        chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 786 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 786 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                     "h"
# 786 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                     ); &__c[0];}))
# 786 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                     )));
        if (responseLen > MAX_RESPONSE_LEN) {
          chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 788 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                       (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 788 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                       " +"
# 788 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                       ); &__c[0];}))
# 788 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                       )));
          chunked.print(byte(responseLen - MAX_RESPONSE_LEN));
          chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 790 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                       (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 790 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                       " bytes"
# 790 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                       ); &__c[0];}))
# 790 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                       )));
        }
      }
      break;
    case JSON_QUEUE:
      chunked.print(queueDataSize);
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 796 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 796 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   " / "
# 796 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 796 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      chunked.print(MAX_QUEUE_DATA);
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 798 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 798 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   " bytes<br>"
# 798 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 798 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      chunked.print(queueHeadersSize);
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 800 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 800 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   " / "
# 800 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 800 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      chunked.print(MAX_QUEUE_REQUESTS);
      chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 802 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 802 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   " requests"
# 802 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                   ); &__c[0];}))
# 802 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                   )));
      queueDataSize = queueData.size();
      queueHeadersSize = queueHeaders.size();
      break;
    case JSON_STATS:
      for (byte i = 0; i < ERROR_LAST; i++) {
        if (i == SLAVE_ERROR_0B_QUEUE) continue; // SLAVE_ERROR_0B_QUEUE is not shown in web UI
        chunked.print(data.errorCnt[i]);
        stringStats(chunked, i);
      }
      break;
    case JSON_TCP_UDP_MASTERS:
      {
        for (byte s = 0; s < maxSockNum; s++) {
          byte remoteIParray[4];
          W5100.readSnDIPR(s, remoteIParray);
          if (remoteIParray[0] != 0) {
            if (W5100.readSnSR(s) == SnSR::UDP) {
              chunked.print(IPAddress(remoteIParray));
              chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 821 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                           (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 821 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                           " UDP<br>"
# 821 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                           ); &__c[0];}))
# 821 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                           )));
            } else if (W5100.readSnSR(s) == SnSR::ESTABLISHED && W5100.readSnPORT(s) == data.config.tcpPort) {
              chunked.print(IPAddress(remoteIParray));
              chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 824 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                           (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 824 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                           " TCP<br>"
# 824 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                           ); &__c[0];}))
# 824 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                           )));
            }
          }
        }
      }
      break;
    case JSON_SLAVES:
      {
        for (byte k = 1; k < MAX_SLAVES; k++) {
          for (byte s = 0; s <= SLAVE_ERROR_0B_QUEUE; s++) {
            if (getSlaveStatus(k, s) == true || k == scanCounter) {
              chunked.print(hex(k));
              chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 836 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                           (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 836 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                           "h"
# 836 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                           ); &__c[0];}))
# 836 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                           )));
              if (k == scanCounter) {
                chunked.print((reinterpret_cast<const __FlashStringHelper *>(
# 838 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                             (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 838 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                             " Scanning...<br>"
# 838 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino" 3
                             ); &__c[0];}))
# 838 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
                             )));
                break;
              }
              stringStats(chunked, s);
            }
          }
        }
      }
      break;
    default:
      break;
  }
}
