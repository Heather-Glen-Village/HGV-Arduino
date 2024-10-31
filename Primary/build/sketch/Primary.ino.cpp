#include <Arduino.h>
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
#include <SoftwareSerial.h>
#include <ModbusRTUMaster.h>
// Pins List
#define SoftTX 16 // A2
#define SoftRX 17 // A3
#define LED 2
#define DHT22 4
#define Motion 5
#define Vibration 6
#define DS18B20 7
#define DERE 9

// Defines the ID for the Secondary Board from 1-246
#define ID 1

// Initialize Libaries
SoftwareSerial modbusSerial(SoftRX, SoftTX);
ModbusRTUMaster modbus(Serial, DERE); // Create Modbus Object

bool coils[1] = {1};
uint16_t InputRegisters[1];


#line 24 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void setup();
#line 30 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void loop();
#line 6 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
void startSerial();
#line 15 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
byte bitsPerChar();
#line 25 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
uint32_t charTimeOut();
#line 34 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
uint32_t frameDelay();
#line 48 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
void startEthernet();
#line 90 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
void checkEthernet();
#line 143 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
bool rollover();
#line 168 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
void resetStats();
#line 183 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
void generateMac();
#line 200 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
void updateEeprom();
#line 218 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
void manageSockets();
#line 321 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
void disconSocket(byte s);
#line 337 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
void CreateTrulyRandomSeed();
#line 47 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\02-modbus-tcp.ino"
void recvUdp();
#line 93 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\02-modbus-tcp.ino"
void recvTcp(EthernetClient &client);
#line 135 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\02-modbus-tcp.ino"
void scanRequest();
#line 176 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\02-modbus-tcp.ino"
byte checkRequest(byte inBuffer[], uint16_t msgLength, const uint32_t remoteIP, const uint16_t remotePort, byte requestType);
#line 230 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\02-modbus-tcp.ino"
void deleteRequest();
#line 242 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\02-modbus-tcp.ino"
void clearQueue();
#line 252 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\02-modbus-tcp.ino"
bool getSlaveStatus(const byte slave, const byte status);
#line 257 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\02-modbus-tcp.ino"
void setSlaveStatus(const byte slave, byte status, const bool value, const bool isScan);
#line 20 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\03-modbus-rtu.ino"
void sendSerial();
#line 125 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\03-modbus-rtu.ino"
void recvSerial();
#line 167 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\03-modbus-rtu.ino"
void sendResponse(const byte MBAP[], const byte PDU[], const uint16_t pduLength);
#line 206 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\03-modbus-rtu.ino"
bool checkCRC(byte buf[], int16_t len);
#line 218 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\03-modbus-rtu.ino"
void calculateCRC(byte b);
#line 113 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\04-webserver.ino"
void recvWeb(EthernetClient &client);
#line 194 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\04-webserver.ino"
void processPost(EthernetClient &client);
#line 390 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\04-webserver.ino"
byte strToByte(const char myStr[]);
#line 417 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\04-webserver.ino"
char * hex(byte val);
#line 14 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
void sendPage(EthernetClient &client, byte reqPage);
#line 182 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
void contentInfo(ChunkedPrint &chunked);
#line 245 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
void contentStatus(ChunkedPrint &chunked);
#line 305 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
void contentIp(ChunkedPrint &chunked);
#line 363 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
void contentTcp(ChunkedPrint &chunked);
#line 420 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
void contentRtu(ChunkedPrint &chunked);
#line 508 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
void contentTools(ChunkedPrint &chunked);
#line 521 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
void contentWait(ChunkedPrint &chunked);
#line 539 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
void tagInputNumber(ChunkedPrint &chunked, const byte name, const byte min, uint16_t max, uint16_t value, const __FlashStringHelper *units);
#line 566 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
void tagInputIp(ChunkedPrint &chunked, const byte name, byte ip[]);
#line 589 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
void tagInputHex(ChunkedPrint &chunked, const byte name, const bool required, const bool printVal, const byte value);
#line 610 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
void tagLabelDiv(ChunkedPrint &chunked, const __FlashStringHelper *label);
#line 629 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
void tagButton(ChunkedPrint &chunked, const __FlashStringHelper *flashString, byte value);
#line 646 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
void tagDivClose(ChunkedPrint &chunked);
#line 659 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
void tagSpan(ChunkedPrint &chunked, const byte JSONKEY);
#line 675 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
void stringPageName(ChunkedPrint &chunked, byte item);
#line 700 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
void stringStats(ChunkedPrint &chunked, const byte stat);
#line 738 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
void jsonVal(ChunkedPrint &chunked, const byte JSONKEY);
#line 24 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
void setup() {
  modbus.begin(9600);
  Serial.begin(9600); // For Debuging
  delay(5000);        // For Debuging
}

void loop() {
Serial.println(modbus.writeSingleCoil(1,0,1));
delay(3000);
Serial.println(modbus.readInputRegisters(1, 0, InputRegisters,1));
Serial.print("InputRegisters: "); Serial.println(InputRegisters[0]);
delay(1000);
}
#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\!Primary.ino"
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

const byte VERSION[] = { 7, 3 };

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <utility/w5100.h>
#include <CircularBuffer.h>  // CircularBuffer https://github.com/rlogiacco/CircularBuffer
#include <EEPROM.h>
#include <StreamLib.h>  // StreamLib https://github.com/jandrassy/StreamLib

// these are used by CreateTrulyRandomSeed() function
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/atomic.h>

typedef struct {
  byte ip[4];
  byte subnet[4];
  byte gateway[4];
  byte dns[4];      // only used if ENABLE_DHCP
  bool enableDhcp;  // only used if ENABLE_DHCP
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

#include "advanced_settings.h"

const config_t DEFAULT_CONFIG = {
  DEFAULT_STATIC_IP,
  DEFAULT_SUBMASK,
  DEFAULT_GATEWAY,
  DEFAULT_DNS,
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
  SLAVE_OK,              // Slave Responded
  SLAVE_ERROR_0X,        // Slave Responded with Error (Codes 1~8)
  SLAVE_ERROR_0A,        // Gateway Overloaded (Code 10)
  SLAVE_ERROR_0B,        // Slave Failed to Respond (Code 11)
  SLAVE_ERROR_0B_QUEUE,  // Slave Failed to Respond (Code 11) & is in Queue (not shown in web UI)
  ERROR_TIMEOUT,         // Response Timeout
  ERROR_RTU,             // Invalid RTU Response
  ERROR_TCP,             // Invalid TCP/UDP Request
  ERROR_LAST             // Number of status flags in this enum. Must be the last element within this enum!!
};

enum flow_t : byte {
  DATA_TX,
  DATA_RX,
  DATA_LAST  // Number of status flags in this enum. Must be the last element within this enum!!
};

typedef struct {
  uint32_t eepromWrites;          // Number of EEPROM write cycles (persistent, it is never cleared during factory resets)
  byte major;                     // major version
  byte mac[6];                    // MAC Address (initial value is random generated)
  config_t config;                // configuration values
  uint32_t errorCnt[ERROR_LAST];  // array for storing error counters
#ifdef ENABLE_EXTENDED_WEBUI
  uint32_t rtuCnt[DATA_LAST];  // array for storing RTU data counters
  uint32_t ethCnt[DATA_LAST];  // array for storing ethernet data counters
#endif                         /* ENABLE_EXTENDED_WEBUI */
} data_t;

data_t data;

typedef struct {
  byte tid[2];       // MBAP Transaction ID
  byte msgLen;       // lenght of Modbus message stored in queueData
  IPAddress remIP;   // remote IP for UDP client (UDP response is sent back to remote IP)
  uint16_t remPort;  // remote port for UDP client (UDP response is sent back to remote port)
  byte requestType;  // TCP client who sent the request
  byte atts;         // attempts counter
} header_t;

// bool arrays for storing Modbus RTU status of individual slaves
byte slaveStatus[SLAVE_ERROR_0B_QUEUE + 1][(MAX_SLAVES + 1 + 7) / 8];  // SLAVE_ERROR_0B_QUEUE is the last status of slaves

// each request is stored in 3 queues (all queues are written to, read and deleted in sync)
CircularBuffer<header_t, MAX_QUEUE_REQUESTS> queueHeaders;  // queue of requests' headers and metadata
CircularBuffer<byte, MAX_QUEUE_DATA> queueData;             // queue of PDU data


/****** ETHERNET AND SERIAL ******/

byte maxSockNum = MAX_SOCK_NUM;

#ifdef ENABLE_DHCP
bool dhcpSuccess = false;
#endif /* ENABLE_DHCP */

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
Timer eepromTimer;    // timer to delay writing statistics to EEPROM
Timer checkEthTimer;  // timer to check SPI connection with ethernet shield

#define RS485_TRANSMIT HIGH
#define RS485_RECEIVE LOW

byte scanCounter = 1;  // Start Modbus RTU scan after boot
enum state_t : byte {
  IDLE,
  SENDING,
  DELAY,
  WAITING
};

byte serialState;


/****** RUN TIME AND DATA COUNTERS ******/

bool scanReqInQueue = false;  // Scan request is in the queue
byte priorityReqInQueue;      // Counter for priority requests in the queue

byte response[MAX_RESPONSE_LEN];  // buffer to store the last Modbus response
byte responseLen;                 // stores actual length of the response shown in WebUI

uint16_t queueDataSize;
byte queueHeadersSize;

#ifdef ENABLE_EXTENDED_WEBUI
// store uptime seconds (includes seconds counted before millis() overflow)
uint32_t seconds;
// store last millis() so that we can detect millis() overflow
uint32_t last_milliseconds = 0;
// store seconds passed until the moment of the overflow so that we can add them to "seconds" on the next call
int32_t remaining_seconds;
// Data counters (we only use uint32_t in ENABLE_EXTENDED_WEBUI, to save flash memory)
#endif /* ENABLE_EXTENDED_WEBUI */

volatile uint32_t seed1;  // seed1 is generated by CreateTrulyRandomSeed()
volatile int8_t nrot;
uint32_t seed2 = 17111989;  // seed2 is static


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
#ifdef ENABLE_EXTENDED_WEBUI
  maintainUptime();  // maintain uptime in case of millis() overflow
#endif               /* ENABLE_EXTENDED_WEBUI */
#ifdef ENABLE_DHCP
  maintainDhcp();
#endif /* ENABLE_DHCP */
}

#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\01-interfaces.ino"
/**************************************************************************/
/*!
  @brief Initiates HW serial interface which we use for the RS485 line.
*/
/**************************************************************************/
void startSerial() {
  mySerial.begin((data.config.baud * 100UL), data.config.serialConfig);
#ifdef RS485_CONTROL_PIN
  pinMode(RS485_CONTROL_PIN, OUTPUT);
  digitalWrite(RS485_CONTROL_PIN, RS485_RECEIVE);  // Init Transceiver
#endif                                             /* RS485_CONTROL_PIN */
}

// Number of bits per character (11 in default Modbus RTU settings)
byte bitsPerChar() {
  byte bits =
    1 +                                                         // start bit
    (((data.config.serialConfig & 0x06) >> 1) + 5) +            // data bits
    (((data.config.serialConfig & 0x08) >> 3) + 1);             // stop bits
  if (((data.config.serialConfig & 0x30) >> 4) > 1) bits += 1;  // parity bit (if present)
  return bits;
}

// Character timeout in micros
uint32_t charTimeOut() {
  if (data.config.baud <= 192) {
    return (15000UL * bitsPerChar()) / data.config.baud;  // inter-character time-out should be 1,5T
  } else {
    return 750;
  }
}

// Minimum frame delay in micros
uint32_t frameDelay() {
  if (data.config.baud <= 192) {
    return (35000UL * bitsPerChar()) / data.config.baud;  // inter-frame delay should be 3,5T
  } else {
    return 1750;  // 1750 μs
  }
}

/**************************************************************************/
/*!
  @brief Initiates ethernet interface, if DHCP enabled, gets IP from DHCP,
  starts all servers (UDP, web server).
*/
/**************************************************************************/
void startEthernet() {
  if (ETH_RESET_PIN != 0) {
    pinMode(ETH_RESET_PIN, OUTPUT);
    digitalWrite(ETH_RESET_PIN, LOW);
    delay(25);
    digitalWrite(ETH_RESET_PIN, HIGH);
    delay(ETH_RESET_DELAY);
  }
#ifdef ENABLE_DHCP
  if (data.config.enableDhcp) {
    dhcpSuccess = Ethernet.begin(data.mac);
  }
  if (!data.config.enableDhcp || dhcpSuccess == false) {
    Ethernet.begin(data.mac, data.config.ip, data.config.dns, data.config.gateway, data.config.subnet);
  }
#else  /* ENABLE_DHCP */
  Ethernet.begin(data.mac, data.config.ip, {}, data.config.gateway, data.config.subnet);  // No DNS
#endif /* ENABLE_DHCP */
  W5100.setRetransmissionTime(TCP_RETRANSMISSION_TIMEOUT);
  W5100.setRetransmissionCount(TCP_RETRANSMISSION_COUNT);
  modbusServer = EthernetServer(data.config.tcpPort);
  webServer = EthernetServer(data.config.webPort);
  Udp.begin(data.config.udpPort);
  modbusServer.begin();
  webServer.begin();
#if MAX_SOCK_NUM > 4
  if (W5100.getChip() == 51) maxSockNum = 4;  // W5100 chip never supports more than 4 sockets
#endif
}

/**************************************************************************/
/*!
  @brief Resets Arduino (works only on AVR chips).
*/
/**************************************************************************/
void (*resetFunc)(void) = 0;  //declare reset function at address 0

/**************************************************************************/
/*!
  @brief Checks SPI connection to the W5X00 chip.
*/
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
/**************************************************************************/
#ifdef ENABLE_DHCP
void maintainDhcp() {
  if (data.config.enableDhcp && dhcpSuccess == true) {  // only call maintain if initial DHCP request by startEthernet was successfull
    Ethernet.maintain();
  }
}
#endif /* ENABLE_DHCP */

/**************************************************************************/
/*!
  @brief Maintains uptime in case of millis() overflow.
*/
/**************************************************************************/
#ifdef ENABLE_EXTENDED_WEBUI
void maintainUptime() {
  uint32_t milliseconds = millis();
  if (last_milliseconds > milliseconds) {
    //in case of millis() overflow, store existing passed seconds
    remaining_seconds = seconds;
  }
  //store last millis(), so that we can detect on the next call
  //if there is a millis() overflow ( millis() returns 0 )
  last_milliseconds = milliseconds;
  //In case of overflow, the "remaining_seconds" variable contains seconds counted before the overflow.
  //We add the "remaining_seconds", so that we can continue measuring the time passed from the last boot of the device.
  seconds = (milliseconds / 1000) + remaining_seconds;
}
#endif /* ENABLE_EXTENDED_WEBUI */

/**************************************************************************/
/*!
  @brief Synchronizes roll-over of data counters to zero.
*/
/**************************************************************************/
bool rollover() {
  const uint32_t ROLLOVER = 0xFFFFFF00;
  for (byte i = 0; i < ERROR_LAST; i++) {
    if (data.errorCnt[i] > ROLLOVER) {
      return true;
    }
  }
#ifdef ENABLE_EXTENDED_WEBUI
  if (seconds > ROLLOVER) {
    return true;
  }
  for (byte i = 0; i < DATA_LAST; i++) {
    if (data.rtuCnt[i] > ROLLOVER || data.ethCnt[i] > ROLLOVER) {
      return true;
    }
  }
#endif /* ENABLE_EXTENDED_WEBUI */
  return false;
}

/**************************************************************************/
/*!
  @brief Resets error stats, RTU counter and ethernet data counter.
*/
/**************************************************************************/
void resetStats() {
  memset(data.errorCnt, 0, sizeof(data.errorCnt));
#ifdef ENABLE_EXTENDED_WEBUI
  memset(data.rtuCnt, 0, sizeof(data.rtuCnt));
  memset(data.ethCnt, 0, sizeof(data.ethCnt));
  remaining_seconds = -(millis() / 1000);
#endif /* ENABLE_EXTENDED_WEBUI */
}

/**************************************************************************/
/*!
  @brief Generate random MAC using pseudo random generator,
  bytes 0, 1 and 2 are static (MAC_START), bytes 3, 4 and 5 are generated randomly
*/
/**************************************************************************/
void generateMac() {
  // Marsaglia algorithm from https://github.com/RobTillaart/randomHelpers
  seed1 = 36969L * (seed1 & 65535L) + (seed1 >> 16);
  seed2 = 18000L * (seed2 & 65535L) + (seed2 >> 16);
  uint32_t randomBuffer = (seed1 << 16) + seed2; /* 32-bit random */
  memcpy(data.mac, MAC_START, 3);                // set first 3 bytes
  for (byte i = 0; i < 3; i++) {
    data.mac[i + 3] = randomBuffer & 0xFF;  // random last 3 bytes
    randomBuffer >>= 8;
  }
}

/**************************************************************************/
/*!
  @brief Write (update) data to Arduino EEPROM.
*/
/**************************************************************************/
void updateEeprom() {
  eepromTimer.sleep(EEPROM_INTERVAL * 60UL * 60UL * 1000UL);  // EEPROM_INTERVAL is in hours, sleep is in milliseconds!
  data.eepromWrites++;                                        // we assume that at least some bytes are written to EEPROM during EEPROM.update or EEPROM.put
  EEPROM.put(DATA_START, data);
}


uint32_t lastSocketUse[MAX_SOCK_NUM];
byte socketInQueue[MAX_SOCK_NUM];
/**************************************************************************/
/*!
  @brief Closes sockets which are waiting to be closed or which refuse to close,
  forwards sockets with data available for further processing by the webserver,
  disconnects (closes) sockets which are too old (idle for too long), opens
  new sockets if needed (and if available).
  From https://github.com/SapientHetero/Ethernet/blob/master/src/socket.cpp
*/
/**************************************************************************/
void manageSockets() {
  uint32_t maxAge = 0;         // the 'age' of the socket in a 'disconnectable' state that was last used the longest time ago
  byte oldest = MAX_SOCK_NUM;  // the socket number of the 'oldest' disconnectable socket
  byte modbusListening = MAX_SOCK_NUM;
  byte webListening = MAX_SOCK_NUM;
  byte dataAvailable = MAX_SOCK_NUM;
  byte socketsAvailable = 0;
  SPI.beginTransaction(SPI_ETHERNET_SETTINGS);  // begin SPI transaction
  // look at all the hardware sockets, record and take action based on current states
  for (byte s = 0; s < maxSockNum; s++) {            // for each hardware socket ...
    byte status = W5100.readSnSR(s);                 //  get socket status...
    uint32_t sockAge = millis() - lastSocketUse[s];  // age of the current socket
    if (socketInQueue[s] > 0) {
      lastSocketUse[s] = millis();
      continue;  // do not close Modbus TCP sockets currently processed (in queue)
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
          socketsAvailable++;                  // socket will be available soon
          if (sockAge > TCP_DISCON_TIMEOUT) {  //     if it's been more than TCP_CLIENT_DISCON_TIMEOUT since disconnect command was sent...
            W5100.execCmdSn(s, Sock_CLOSE);    //	    send CLOSE command...
            lastSocketUse[s] = millis();       //       and record time at which it was sent so we don't do it repeatedly.
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
              socketsAvailable++;               // socket will be available soon
              W5100.execCmdSn(s, Sock_DISCON);  //  send DISCON command...
              lastSocketUse[s] = millis();      //   record time at which it was sent...
                                                // status becomes LAST_ACK for short time
            } else if (((W5100.readSnPORT(s) == data.config.webPort && sockAge > WEB_IDLE_TIMEOUT)
                        || (W5100.readSnPORT(s) == data.config.tcpPort && sockAge > (data.config.tcpTimeout * 1000UL)))
                       && sockAge > maxAge) {
              oldest = s;        //     record the socket number...
              maxAge = sockAge;  //      and make its age the new max age.
            }
          }
        }
        break;
      default:
        break;
    }
  }

  if (dataAvailable != MAX_SOCK_NUM) {
    EthernetClient client = EthernetClient(dataAvailable);
    if (W5100.readSnPORT(dataAvailable) == data.config.webPort) {
      recvWeb(client);
    } else {
      recvTcp(client);
    }
  }

  if (modbusListening == MAX_SOCK_NUM) {
    modbusServer.begin();
  } else if (webListening == MAX_SOCK_NUM) {
    webServer.begin();
  }

  // If needed, disconnect socket that's been idle (ESTABLISHED without data recieved) the longest
  if (oldest != MAX_SOCK_NUM && socketsAvailable == 0 && (webListening == MAX_SOCK_NUM || modbusListening == MAX_SOCK_NUM)) {
    disconSocket(oldest);
  }

  SPI.endTransaction();  // Serves to o release the bus for other devices to access it. Since the ethernet chip is the only device
  // we do not need SPI.beginTransaction(SPI_ETHERNET_SETTINGS) or SPI.endTransaction() ??
}

/**************************************************************************/
/*!
  @brief Disconnect or close a socket.
  @param s Socket number.
*/
/**************************************************************************/
void disconSocket(byte s) {
  if (W5100.readSnSR(s) == SnSR::ESTABLISHED) {
    W5100.execCmdSn(s, Sock_DISCON);  // Sock_DISCON does not close LISTEN sockets
    lastSocketUse[s] = millis();      //   record time at which it was sent...
  } else {
    W5100.execCmdSn(s, Sock_CLOSE);  //  send DISCON command...
  }
}


/**************************************************************************/
/*!
  @brief Seed pseudorandom generator using  watch dog timer interrupt (works only on AVR).
  See https://sites.google.com/site/astudyofentropy/project-definition/timer-jitter-entropy-sources/entropy-library/arduino-random-seed
*/
/**************************************************************************/
void CreateTrulyRandomSeed() {
  seed1 = 0;
  nrot = 32;  // Must be at least 4, but more increased the uniformity of the produced seeds entropy.
  // The following five lines of code turn on the watch dog timer interrupt to create
  // the seed value
  cli();
  MCUSR = 0;
  _WD_CONTROL_REG |= (1 << _WD_CHANGE_BIT) | (1 << WDE);
  _WD_CONTROL_REG = (1 << WDIE);
  sei();
  while (nrot > 0)
    ;  // wait here until seed is created
  // The following five lines turn off the watch dog timer interrupt
  cli();
  MCUSR = 0;
  _WD_CONTROL_REG |= (1 << _WD_CHANGE_BIT) | (0 << WDE);
  _WD_CONTROL_REG = (0 << WDIE);
  sei();
}

ISR(WDT_vect) {
  nrot--;
  seed1 = seed1 << 8;
  seed1 = seed1 ^ TCNT1L;
}

// Preprocessor code for identifying microcontroller board
#if defined(TEENSYDUINO)
//  --------------- Teensy -----------------
#if defined(__AVR_ATmega32U4__)
#define BOARD F("Teensy 2.0")
#elif defined(__AVR_AT90USB1286__)
#define BOARD F("Teensy++ 2.0")
#elif defined(__MK20DX128__)
#define BOARD F("Teensy 3.0")
#elif defined(__MK20DX256__)
#define BOARD F("Teensy 3.2")  // and Teensy 3.1 (obsolete)
#elif defined(__MKL26Z64__)
#define BOARD F("Teensy LC")
#elif defined(__MK64FX512__)
#define BOARD F("Teensy 3.5")
#elif defined(__MK66FX1M0__)
#define BOARD F("Teensy 3.6")
#else
#define BOARD F("Unknown Board")
#endif
#else  // --------------- Arduino ------------------
#if defined(ARDUINO_AVR_ADK)
#define BOARD F("Arduino Mega Adk")
#elif defined(ARDUINO_AVR_BT)  // Bluetooth
#define BOARD F("Arduino Bt")
#elif defined(ARDUINO_AVR_DUEMILANOVE)
#define BOARD F("Arduino Duemilanove")
#elif defined(ARDUINO_AVR_ESPLORA)
#define BOARD F("Arduino Esplora")
#elif defined(ARDUINO_AVR_ETHERNET)
#define BOARD F("Arduino Ethernet")
#elif defined(ARDUINO_AVR_FIO)
#define BOARD F("Arduino Fio")
#elif defined(ARDUINO_AVR_GEMMA)
#define BOARD F("Arduino Gemma")
#elif defined(ARDUINO_AVR_LEONARDO)
#define BOARD F("Arduino Leonardo")
#elif defined(ARDUINO_AVR_LILYPAD)
#define BOARD F("Arduino Lilypad")
#elif defined(ARDUINO_AVR_LILYPAD_USB)
#define BOARD F("Arduino Lilypad Usb")
#elif defined(ARDUINO_AVR_MEGA)
#define BOARD F("Arduino Mega")
#elif defined(ARDUINO_AVR_MEGA2560)
#define BOARD F("Arduino Mega 2560")
#elif defined(ARDUINO_AVR_MICRO)
#define BOARD F("Arduino Micro")
#elif defined(ARDUINO_AVR_MINI)
#define BOARD F("Arduino Mini")
#elif defined(ARDUINO_AVR_NANO)
#define BOARD F("Arduino Nano")
#elif defined(ARDUINO_AVR_NG)
#define BOARD F("Arduino NG")
#elif defined(ARDUINO_AVR_PRO)
#define BOARD F("Arduino Pro")
#elif defined(ARDUINO_AVR_ROBOT_CONTROL)
#define BOARD F("Arduino Robot Ctrl")
#elif defined(ARDUINO_AVR_ROBOT_MOTOR)
#define BOARD F("Arduino Robot Motor")
#elif defined(ARDUINO_AVR_UNO)
#define BOARD F("Arduino Uno")
#elif defined(ARDUINO_AVR_YUN)
#define BOARD F("Arduino Yun")

// These boards must be installed separately:
#elif defined(ARDUINO_SAM_DUE)
#define BOARD F("Arduino Due")
#elif defined(ARDUINO_SAMD_ZERO)
#define BOARD F("Arduino Zero")
#elif defined(ARDUINO_ARC32_TOOLS)
#define BOARD F("Arduino 101")
#else
#define BOARD F("Unknown Board")
#endif
#endif

#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\02-modbus-tcp.ino"
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

byte masks[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };

// Stored in "header.requestType"
#define PRIORITY_REQUEST B10000000  // Request to slave which is not "nonresponding"
#define SCAN_REQUEST B01000000      // Request triggered by slave scanner
#define UDP_REQUEST B00100000       // UDP request
#define TCP_REQUEST B00001000       // TCP request
#define TCP_REQUEST_MASK B00000111  // Stores TCP client number

uint16_t crc;

/**************************************************************************/
/*!
  @brief Receives Modbus UDP (or Modbus RTU over UDP) messages, calls @ref checkRequest()
*/
/**************************************************************************/
void recvUdp() {
  uint16_t msgLength = Udp.parsePacket();
  if (msgLength) {
#ifdef ENABLE_EXTENDED_WEBUI
    data.ethCnt[DATA_RX] += msgLength;
#endif                               /* ENABLE_EXTENDED_WEBUI */
    byte inBuffer[MODBUS_SIZE + 4];  // Modbus TCP frame is 4 bytes longer than Modbus RTU frame
                                     // Modbus TCP/UDP frame: [0][1] transaction ID, [2][3] protocol ID, [4][5] length and [6] unit ID (address)..... no CRC
                                     // Modbus RTU frame: [0] address.....[n-1][n] CRC
    memset(inBuffer, 0, sizeof(inBuffer));
    Udp.read(inBuffer, sizeof(inBuffer));
    while (Udp.available()) Udp.read();
    byte errorCode = checkRequest(inBuffer, msgLength, (uint32_t)Udp.remoteIP(), Udp.remotePort(), UDP_REQUEST);
    if (errorCode) {
      // send back message with error code
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      if (!data.config.enableRtuOverTcp) {
        Udp.write(inBuffer, 5);
        Udp.write(0x03);
      }
      byte addressPos = 6 * !data.config.enableRtuOverTcp;  // position of slave address in the incoming TCP/UDP message (0 for Modbus RTU over TCP/UDP and 6 for Modbus RTU over TCP/UDP)
      Udp.write(inBuffer[addressPos]);                      // address
      Udp.write(inBuffer[addressPos + 1] + 0x80);           // function + 0x80
      Udp.write(errorCode);
      if (data.config.enableRtuOverTcp) {
        crc = 0xFFFF;
        calculateCRC(inBuffer[addressPos]);
        calculateCRC(inBuffer[addressPos + 1] + 0x80);
        calculateCRC(errorCode);
        Udp.write(lowByte(crc));  // send CRC, low byte first
        Udp.write(highByte(crc));
      }
      Udp.endPacket();
#ifdef ENABLE_EXTENDED_WEBUI
      data.ethCnt[DATA_TX] += 5;
      if (!data.config.enableRtuOverTcp) data.ethCnt[DATA_TX] += 4;
#endif /* ENABLE_EXTENDED_WEBUI */
    }
  }
}

/**************************************************************************/
/*!
  @brief Receives Modbus TCP (or Modbus RTU over TCP) messages, calls @ref checkRequest()
*/
/**************************************************************************/
void recvTcp(EthernetClient &client) {
  uint16_t msgLength = client.available();
#ifdef ENABLE_EXTENDED_WEBUI
  data.ethCnt[DATA_RX] += msgLength;
#endif                             /* ENABLE_EXTENDED_WEBUI */
  byte inBuffer[MODBUS_SIZE + 4];  // Modbus TCP frame is 4 bytes longer than Modbus RTU frame
                                   // Modbus TCP/UDP frame: [0][1] transaction ID, [2][3] protocol ID, [4][5] length and [6] unit ID (address).....
                                   // Modbus RTU frame: [0] address.....
  memset(inBuffer, 0, sizeof(inBuffer));
  client.read(inBuffer, sizeof(inBuffer));
  while (client.available()) client.read();
  byte errorCode = checkRequest(inBuffer, msgLength, {}, client.remotePort(), TCP_REQUEST | client.getSocketNumber());
  if (errorCode) {
    // send back message with error code
    byte i = 0;
    byte outBuffer[9];
    if (!data.config.enableRtuOverTcp) {
      memcpy(outBuffer, inBuffer, 5);
      outBuffer[5] = 0x03;
      i = 6;
    }
    byte addressPos = 6 * !data.config.enableRtuOverTcp;  // position of slave address in the incoming TCP/UDP message (0 for Modbus RTU over TCP/UDP and 6 for Modbus RTU over TCP/UDP)
    outBuffer[i++] = inBuffer[addressPos];                // address
    outBuffer[i++] = inBuffer[addressPos + 1] + 0x80;     // function + 0x80
    outBuffer[i++] = errorCode;
    if (data.config.enableRtuOverTcp) {
      crc = 0xFFFF;
      calculateCRC(inBuffer[addressPos]);
      calculateCRC(inBuffer[addressPos + 1] + 0x80);
      calculateCRC(errorCode);
      outBuffer[i++] = lowByte(crc);  // send CRC, low byte first
      outBuffer[i++] = highByte(crc);
    }
    client.write(outBuffer, i);
#ifdef ENABLE_EXTENDED_WEBUI
    data.ethCnt[DATA_TX] += 5;
    if (!data.config.enableRtuOverTcp) data.ethCnt[DATA_TX] += 4;
#endif /* ENABLE_EXTENDED_WEBUI */
  }
}


void scanRequest() {
  // Insert scan request into queue, allow only one scan request in a queue
  static byte scanCommand[] = { SCAN_FUNCTION_FIRST, 0x00, SCAN_DATA_ADDRESS, 0x00, 0x01 };
  if (scanCounter != 0 && queueHeaders.available() > 1 && queueData.available() > sizeof(scanCommand) + 1 && scanReqInQueue == false) {
    scanReqInQueue = true;
    // Store scan request in request queue
    queueHeaders.push(header_t{
      { 0x00, 0x00 },           // tid[2]
      sizeof(scanCommand) + 1,  // msgLen
      { 0, 0, 0, 0 },           // remIP
      0,                        // remPort
      SCAN_REQUEST,             // requestType
      0,                        // atts
    });
    queueData.push(scanCounter);  // address of the scanned slave
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
/**************************************************************************/
byte checkRequest(byte inBuffer[], uint16_t msgLength, const uint32_t remoteIP, const uint16_t remotePort, byte requestType) {
  byte addressPos = 6 * !data.config.enableRtuOverTcp;  // position of slave address in the incoming TCP/UDP message (0 for Modbus RTU over TCP/UDP and 6 for Modbus RTU over TCP/UDP)
  if (data.config.enableRtuOverTcp) {                   // check CRC for Modbus RTU over TCP/UDP
    if (checkCRC(inBuffer, msgLength) == false) {
      data.errorCnt[ERROR_TCP]++;
      return 0;  // drop request and do not return any error code
    }
  } else {  // check MBAP header structure for Modbus TCP/UDP
    if (inBuffer[2] != 0x00 || inBuffer[3] != 0x00 || inBuffer[4] != 0x00 || inBuffer[5] != msgLength - 6) {
      data.errorCnt[ERROR_TCP]++;
      return 0;  // drop request and do not return any error code
    }
  }
  msgLength = msgLength - addressPos - (2 * data.config.enableRtuOverTcp);  // in Modbus RTU over TCP/UDP do not store CRC
  // check if we have space in request queue
  if (queueHeaders.available() < 1 || queueData.available() < msgLength) {
    setSlaveStatus(inBuffer[addressPos], SLAVE_ERROR_0A, true, false);
    return 0x0A;  // return Modbus error code 10 (Gateway Overloaded)
  }
  // allow only one request to non responding slaves
  if (getSlaveStatus(inBuffer[addressPos], SLAVE_ERROR_0B_QUEUE)) {
    data.errorCnt[SLAVE_ERROR_0B]++;
    return 0x0B;  // return Modbus error code 11 (Gateway Target Device Failed to Respond)
  } else if (getSlaveStatus(inBuffer[addressPos], SLAVE_ERROR_0B)) {
    setSlaveStatus(inBuffer[addressPos], SLAVE_ERROR_0B_QUEUE, true, false);
  } else {
    // Add PRIORITY_REQUEST flag to requests for responding slaves
    requestType = requestType | PRIORITY_REQUEST;
    priorityReqInQueue++;
  }
  if (inBuffer[addressPos] == 0x00) {          // Modbus Broadcast
    requestType = requestType | SCAN_REQUEST;  // Treat broadcast as scan (only one attempt, short timeout, do not expect response)
  }
  // all checkes passed OK, we can store the incoming data in request queue
  if (requestType & TCP_REQUEST) {
    socketInQueue[requestType & TCP_REQUEST_MASK]++;
  }
  // Store in request queue
  queueHeaders.push(header_t{
    { inBuffer[0], inBuffer[1] },  // tid[2] (ignored in Modbus RTU over TCP/UDP)
    byte(msgLength),               // msgLen
    (IPAddress)remoteIP,           // remIP
    (unsigned int)remotePort,      // remPort
    byte(requestType),             // requestType
    0,                             // atts
  });
  for (byte i = 0; i < msgLength; i++) {
    queueData.push(inBuffer[i + addressPos]);
  }
  if (queueData.size() > queueDataSize) queueDataSize = queueData.size();
  if (queueHeaders.size() > queueHeadersSize) queueHeadersSize = queueHeaders.size();
  return 0;
}

void deleteRequest()  // delete request from queue
{
  header_t myHeader = queueHeaders.first();
  if (myHeader.requestType & SCAN_REQUEST) scanReqInQueue = false;
  if (myHeader.requestType & TCP_REQUEST) socketInQueue[myHeader.requestType & TCP_REQUEST_MASK]--;
  if (myHeader.requestType & PRIORITY_REQUEST) priorityReqInQueue--;
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
  if (slave >= MAX_SLAVES) return false;  // error
  return (slaveStatus[status][slave / 8] & masks[slave & 7]) > 0;
}

void setSlaveStatus(const byte slave, byte status, const bool value, const bool isScan) {
  if (slave >= MAX_SLAVES || status > SLAVE_ERROR_0B_QUEUE) return;  // error
  if (value == 0) {
    slaveStatus[status][slave / 8] &= ~masks[slave & 7];
  } else {
    for (byte i = 0; i <= SLAVE_ERROR_0B_QUEUE; i++) {
      slaveStatus[i][slave / 8] &= ~masks[slave & 7];  // set all other flags to false, SLAVE_ERROR_0B_QUEUE is the last slave status
    }
    slaveStatus[status][slave / 8] |= masks[slave & 7];
    if (status != SLAVE_ERROR_0B_QUEUE && isScan == false) data.errorCnt[status]++;  // there is no counter for SLAVE_ERROR_0B_QUEUE, ignor scans in statistics
  }
}

#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\03-modbus-rtu.ino"
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
    case 0:  // IDLE: Optimize queue (prioritize requests from responding slaves) and trigger sending via serial
      while (priorityReqInQueue && (queueHeaders.first().requestType & PRIORITY_REQUEST) == false) {
        // move requests to non responding slaves to the tail of the queue
        for (byte i = 0; i < queueHeaders.first().msgLen; i++) {
          queueData.push(queueData.shift());
        }
        queueHeaders.push(queueHeaders.shift());
      }
      serialState++;
      break;
    case 1:  // SENDING:
      {
        if (mySerial.availableForWrite() > 0 && txNdx == 0) {
#ifdef RS485_CONTROL_PIN
          digitalWrite(RS485_CONTROL_PIN, RS485_TRANSMIT);  // Enable RS485 Transmit
#endif                                                      /* RS485_CONTROL_PIN */
          crc = 0xFFFF;
        }
        while (mySerial.availableForWrite() > 0 && txNdx < myHeader.msgLen) {
          mySerial.write(queueData[txNdx]);
          calculateCRC(queueData[txNdx]);
          txNdx++;
        }
        if (mySerial.availableForWrite() > 1 && txNdx == myHeader.msgLen) {
          mySerial.write(lowByte(crc));  // send CRC, low byte first
          mySerial.write(highByte(crc));
          txNdx++;
        }
        if (mySerial.availableForWrite() == SERIAL_TX_BUFFER_SIZE - 1 && txNdx > myHeader.msgLen) {
          // wait for last byte (incl. CRC) to be sent from serial Tx buffer
          // this if statement is not very reliable (too fast)
          // Serial.isFlushed() method is needed....see https://github.com/arduino/Arduino/pull/3737
          txNdx = 0;
          mySerial.flush();
#ifdef RS485_CONTROL_PIN
          // sendMicroTimer.sleep(frameDelay());  // Short delay before we toggle the RS485_CONTROL_PIN and disable RS485 transmit. Not needed if we use flush()
#endif /* RS485_CONTROL_PIN */
          serialState++;
        }
      }
      break;
    case 2:  // DELAY:
      {
#ifdef ENABLE_EXTENDED_WEBUI
        data.rtuCnt[DATA_TX] += myHeader.msgLen;
        data.rtuCnt[DATA_TX] += 2;
#endif
#ifdef RS485_CONTROL_PIN
        digitalWrite(RS485_CONTROL_PIN, RS485_RECEIVE);  // Disable RS485 Transmit
#endif                                                   /* RS485_CONTROL_PIN */
        myHeader.atts++;
        queueHeaders.shift();
        queueHeaders.unshift(myHeader);
        uint32_t delay = data.config.serialTimeout;
        if (myHeader.requestType & SCAN_REQUEST) delay = SCAN_TIMEOUT;  // fixed timeout for scan requests
        sendMicroTimer.sleep(delay * 1000UL);
        serialState++;
      }
      break;
    case 3:  // WAITING: Deal with Serial timeouts (i.e. Modbus RTU timeouts)
      {
        if (myHeader.requestType & SCAN_REQUEST) {  // Only one attempt for scan request (we do not count attempts)
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
          PDU[3] = lowByte(crc);  // send CRC, low byte first
          PDU[4] = highByte(crc);
          sendResponse(MBAP, PDU, 5);
          data.errorCnt[ERROR_TIMEOUT]++;
        } else {
          setSlaveStatus(queueData[0], SLAVE_ERROR_0B_QUEUE, true, false);
          data.errorCnt[ERROR_TIMEOUT]++;
        }                 // if (myHeader.atts >= MAX_RETRY)
        serialState = 0;  // IDLE
      }
      break;
    default:
      break;
  }
}

void recvSerial() {
  static uint8_t rxNdx = 0;
  static byte serialIn[MODBUS_SIZE];
  while (mySerial.available() > 0) {
    byte b = mySerial.read();
    if (rxNdx < MODBUS_SIZE) {
      serialIn[rxNdx] = b;
      rxNdx++;
    }  // if frame longer than maximum allowed, CRC will fail and data.errorCnt[ERROR_RTU] will be recorded down the road
    recvMicroTimer.sleep(charTimeOut());
    sendMicroTimer.sleep(data.config.frameDelay * 1000UL);  // delay next serial write
  }
  if (recvMicroTimer.isOver() && rxNdx != 0) {
    // Process Serial data
    // Checks: 1) CRC; 2) address of incoming packet against first request in queue; 3) only expected responses are forwarded to TCP/UDP
    header_t myHeader = queueHeaders.first();
    if (checkCRC(serialIn, rxNdx) == true && serialIn[0] == queueData[0] && serialState == WAITING) {
      if (serialIn[1] > 0x80 && (myHeader.requestType & SCAN_REQUEST) == false) {
        setSlaveStatus(serialIn[0], SLAVE_ERROR_0X, true, false);
      } else {
        setSlaveStatus(serialIn[0], SLAVE_OK, true, myHeader.requestType & SCAN_REQUEST);
      }
      byte MBAP[] = {
        myHeader.tid[0],
        myHeader.tid[1],
        0x00,
        0x00,
        highByte(rxNdx - 2),
        lowByte(rxNdx - 2)
      };
      sendResponse(MBAP, serialIn, rxNdx);
      serialState = IDLE;
    } else {
      data.errorCnt[ERROR_RTU]++;
    }
#ifdef ENABLE_EXTENDED_WEBUI
    data.rtuCnt[DATA_RX] += rxNdx;
#endif /* ENABLE_EXTENDED_WEBUI */
    rxNdx = 0;
  }
}

void sendResponse(const byte MBAP[], const byte PDU[], const uint16_t pduLength) {
  header_t myHeader = queueHeaders.first();
  responseLen = 0;
  while (responseLen < pduLength) {  // include CRC
    if (responseLen < MAX_RESPONSE_LEN) {
      response[responseLen] = PDU[responseLen];
    }
    responseLen++;
  }
  if (myHeader.requestType & UDP_REQUEST) {
    Udp.beginPacket(myHeader.remIP, myHeader.remPort);
    if (data.config.enableRtuOverTcp) Udp.write(PDU, pduLength);
    else {
      Udp.write(MBAP, 6);
      Udp.write(PDU, pduLength - 2);  //send without CRC
    }
    Udp.endPacket();
#ifdef ENABLE_EXTENDED_WEBUI
    data.ethCnt[DATA_TX] += pduLength;
    if (!data.config.enableRtuOverTcp) data.ethCnt[DATA_TX] += 4;
#endif /* ENABLE_EXTENDED_WEBUI */
  } else if (myHeader.requestType & TCP_REQUEST) {
    byte sock = myHeader.requestType & TCP_REQUEST_MASK;
    EthernetClient client = EthernetClient(sock);
    if (W5100.readSnSR(sock) == SnSR::ESTABLISHED && W5100.readSnDPORT(sock) == myHeader.remPort) {  // Check remote port should be enough or check also rem IP?
      if (data.config.enableRtuOverTcp) client.write(PDU, pduLength);
      else {
        client.write(MBAP, 6);
        client.write(PDU, pduLength - 2);  //send without CRC
      }
#ifdef ENABLE_EXTENDED_WEBUI
      data.ethCnt[DATA_TX] += pduLength;
      if (!data.config.enableRtuOverTcp) data.ethCnt[DATA_TX] += 4;
#endif /* ENABLE_EXTENDED_WEBUI */
    }  // TODO TCP Connection Error
  }    // else SCAN_REQUEST (no data.ethCnt[DATA_TX], but yes delete request)
  deleteRequest();
}

bool checkCRC(byte buf[], int16_t len) {
  crc = 0xFFFF;
  for (byte i = 0; i < len - 2; i++) {
    calculateCRC(buf[i]);
  }
  if (highByte(crc) == buf[len - 1] && lowByte(crc) == buf[len - 2]) {
    return true;
  } else {
    return false;
  }
}

void calculateCRC(byte b) {
  crc ^= (uint16_t)b;              // XOR byte into least sig. byte of crc
  for (byte i = 8; i != 0; i--) {  // Loop over each bit
    if ((crc & 0x0001) != 0) {     // If the LSB is set
      crc >>= 1;                   // Shift right and XOR 0xA001
      crc ^= 0xA001;
    } else        // Else LSB is not set
      crc >>= 1;  // Just shift right
  }
  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
}

#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\04-webserver.ino"
const byte URI_SIZE = 24;   // a smaller buffer for uri
const byte POST_SIZE = 24;  // a smaller buffer for single post parameter + key

// Actions that need to be taken after saving configuration.
enum action_type : byte {
  ACT_NONE,
  ACT_DEFAULT,        // Load default factory settings (but keep MAC address)
  ACT_MAC,            // Generate new random MAC
  ACT_REBOOT,         // Reboot the microcontroller
  ACT_RESET_ETH,      // Ethernet reset
  ACT_RESET_SERIAL,   // Serial reset
  ACT_SCAN,           // Initialize RTU scan
  ACT_RESET_STATS,    // Reset Modbus Statistics
  ACT_CLEAR_REQUEST,  // Clear Modbus Request form
  ACT_WEB             // Restart webserver
};
enum action_type action;

// Pages served by the webserver. Order of elements defines the order in the left menu of the web UI.
// URL of the page (*.htm) contains number corresponding to its position in this array.
// The following enum array can have a maximum of 10 elements (incl. PAGE_NONE and PAGE_WAIT)
enum page : byte {
  PAGE_ERROR,  // 404 Error
  PAGE_INFO,
  PAGE_STATUS,
  PAGE_IP,
  PAGE_TCP,
  PAGE_RTU,
  PAGE_TOOLS,
  PAGE_WAIT,  // page with "Reloading. Please wait..." message.
  PAGE_DATA,  // d.json
};

// Keys for POST parameters, used in web forms and processed by processPost() function.
// Using enum ensures unique identification of each POST parameter key and consistence across functions.
// In HTML code, each element will apear as number corresponding to its position in this array.
enum post_key : byte {
  POST_NONE,  // reserved for NULL
  POST_DHCP,  // enable DHCP
  POST_MAC,
  POST_MAC_1,
  POST_MAC_2,
  POST_MAC_3,
  POST_MAC_4,
  POST_MAC_5,
  POST_IP,
  POST_IP_1,
  POST_IP_2,
  POST_IP_3,  // IP address         || Each part of an IP address has its own POST parameter.     ||
  POST_SUBNET,
  POST_SUBNET_1,
  POST_SUBNET_2,
  POST_SUBNET_3,  // subnet             || Because HTML code for IP, subnet, gateway and DNS          ||
  POST_GATEWAY,
  POST_GATEWAY_1,
  POST_GATEWAY_2,
  POST_GATEWAY_3,  // gateway            || is generated through one (nested) for-loop,                ||
  POST_DNS,
  POST_DNS_1,
  POST_DNS_2,
  POST_DNS_3,        // DNS                || all these 16 enum elements must be listed in succession!!  ||
  POST_TCP,          // TCP port                  || Because HTML code for these 3 ports              ||
  POST_UDP,          // UDP port                  || is generated through one for-loop,               ||
  POST_WEB,          // web UI port               || these 3 elements must be listed in succession!!  ||
  POST_RTU_OVER,     // RTU over TCP/UDP
  POST_TCP_TIMEOUT,  // Modbus TCP socket close timeout
  POST_BAUD,         // baud rate
  POST_DATA,         // data bits
  POST_PARITY,       // parity
  POST_STOP,         // stop bits
  POST_FRAMEDELAY,   //frame delay
  POST_TIMEOUT,      // response timeout
  POST_ATTEMPTS,     // number of request attempts
  POST_REQ,          // Modbus request send from WebUI (first byte)
  POST_REQ_1,
  POST_REQ_2,
  POST_REQ_3,
  POST_REQ_4,
  POST_REQ_5,
  POST_REQ_6,
  POST_REQ_LAST,  // 8 bytes in total
  POST_ACTION,    // actions on Tools page
};

byte request[POST_REQ_LAST - POST_REQ + 1];  // Array to store Modbus request sent from WebUI
byte requestLen = 0;                         // Length of the Modbus request send from WebUI


// Keys for JSON elements, used in: 1) JSON documents, 2) ID of span tags, 3) Javascript.
enum JSON_type : byte {
  JSON_TIME,  // Runtime seconds
  JSON_RTU_DATA,
  JSON_ETH_DATA,
  JSON_RESPONSE,
  JSON_STATS,  // Modbus statistics from array data.errorCnt[]
  JSON_QUEUE,
  JSON_TCP_UDP_MASTERS,  // list of Modbus TCP/UDP masters separated by <br>
  JSON_SLAVES,           // list of Modbus RTU slaves separated by <br>
  JSON_SOCKETS,
  JSON_LAST,  // Must be the very last element in this array
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
/**************************************************************************/
void recvWeb(EthernetClient &client) {
  char uri[URI_SIZE];  // the requested page
  memset(uri, 0, sizeof(uri));
  while (client.available()) {        // start reading the first line which should look like: GET /uri HTTP/1.1
    if (client.read() == ' ') break;  // find space before /uri
  }
  byte len = 0;
  while (client.available() && len < sizeof(uri) - 1) {
    char c = client.read();  // parse uri
    if (c == ' ') break;     // find space after /uri
    uri[len] = c;
    len++;
  }
  while (client.available()) {
    if (client.read() == '\r')
      if (client.read() == '\n')
        if (client.read() == '\r')
          if (client.read() == '\n')
            break;  // find 2 end of lines between header and body
  }
  if (client.available()) {
    processPost(client);  // parse post parameters
  }

  // Get the requested page from URI
  byte reqPage = PAGE_ERROR;  // requested page, 404 error is a default
  if (uri[0] == '/') {
    if (uri[1] == '\0')  // the homepage System Info
      reqPage = PAGE_INFO;
    else if (!strcmp(uri + 2, ".htm")) {
      reqPage = byte(uri[1] - 48);  // Convert single ASCII char to byte
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
      continue;  // do not process POST parameter if there is no parameter value
    byte paramKeyByte = strToByte(paramKey);
    uint16_t paramValueUint = atol(paramValue);
    switch (paramKeyByte) {
      case POST_NONE:  // reserved, because atoi / atol returns NULL in case of error
        break;
#ifdef ENABLE_DHCP
      case POST_DHCP:
        {
          data.config.enableDhcp = byte(paramValueUint);
        }
        break;
      case POST_DNS ... POST_DNS_3:
        {
          data.config.dns[paramKeyByte - POST_DNS] = byte(paramValueUint);
        }
        break;
#endif /* ENABLE_DHCP */
      case POST_REQ ... POST_REQ_LAST:
        {
          requestLen = paramKeyByte - POST_REQ + 1;
          request[requestLen - 1] = strToByte(paramValue);
        }
        break;
      case POST_MAC ... POST_MAC_5:
        {
          action = ACT_RESET_ETH;  // this RESET_ETH is triggered when the user changes anything on the "IP Settings" page.
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
          if (paramValueUint != data.config.webPort && paramValueUint != data.config.tcpPort) {  // continue only of the value changed and it differs from WebUI port
            for (byte s = 0; s < maxSockNum; s++) {
              if (EthernetClient(s).localPort() == data.config.tcpPort) {  // close only Modbus TCP sockets
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
          if (paramValueUint != data.config.webPort && paramValueUint != data.config.tcpPort) {  // continue only of the value changed and it differs from Modbus TCP port
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
          action = ACT_RESET_SERIAL;  // this RESET_SERIAL is triggered when the user changes anything on the "RTU Settings" page.
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
      memset(&slaveStatus, 0, sizeof(slaveStatus));  // clear all status flags
      break;
    case ACT_CLEAR_REQUEST:
      requestLen = 0;
      responseLen = 0;
      break;
    default:
      break;
  }
  // if new Modbus request received, put into queue
  if (action != ACT_SCAN && action != ACT_RESET_STATS && requestLen > 1 && queueHeaders.available() > 1 && queueData.available() > requestLen) {  // at least 2 bytes in request (slave address and function)
    // push to queue
    queueHeaders.push(header_t{
      { 0x00, 0x00 },  // tid[2]
      requestLen,      // msgLen
      { 0, 0, 0, 0 },  // remIP[4]
      0,               // remPort
      UDP_REQUEST,     // requestType
      0,               // atts
    });
    for (byte i = 0; i < requestLen; i++) {
      queueData.push(request[i]);
    }
    responseLen = 0;  // clear old Modbus Response from WebUI
  }
  // new parameter values received, save them to EEPROM
  updateEeprom();  // it is safe to call, only changed values (and changed error and data counters) are updated
}

/**************************************************************************/
/*!
  @brief Parses string and returns single byte.
  @param myStr String (2 chars, 1 char + null or 1 null) to be parsed.
  @return Parsed byte.
*/
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

#line 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\05-pages.ino"
const byte WEB_OUT_BUFFER_SIZE = 64;  // size of web server write buffer (used by StreamLib)

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
/**************************************************************************/
void sendPage(EthernetClient &client, byte reqPage) {
  char webOutBuffer[WEB_OUT_BUFFER_SIZE];
  ChunkedPrint chunked(client, webOutBuffer, sizeof(webOutBuffer));  // the StreamLib object to replace client print
  if (reqPage == PAGE_ERROR) {
    chunked.print(F("HTTP/1.1 404 Not Found\r\n"
                    "\r\n"
                    "404 Not found"));
    chunked.end();
    return;
  } else if (reqPage == PAGE_DATA) {
    chunked.print(F("HTTP/1.1 200\r\n"  // An advantage of HTTP 1.1 is that you can keep the connection alive
                    "Content-Type: application/json\r\n"
                    "Transfer-Encoding: chunked\r\n"
                    "\r\n"));
    chunked.begin();
    chunked.print(F("{"));
    for (byte i = 0; i < JSON_LAST; i++) {
      if (i) chunked.print(F(","));
      chunked.print(F("\""));
      chunked.print(i);
      chunked.print(F("\":\""));
      jsonVal(chunked, i);
      chunked.print(F("\""));
    }
    chunked.print(F("}"));
    chunked.end();
    return;
  }
  chunked.print(F("HTTP/1.1 200 OK\r\n"
                  "Content-Type: text/html\r\n"
                  "Transfer-Encoding: chunked\r\n"
                  "\r\n"));
  chunked.begin();
  chunked.print(F("<!DOCTYPE html>"
                  "<html>"
                  "<head>"
                  "<meta"));
  if (reqPage == PAGE_WAIT) {  // redirect to new IP and web port
    chunked.print(F(" http-equiv=refresh content=5;url=http://"));
    chunked.print(IPAddress(data.config.ip));
    chunked.print(F(":"));
    chunked.print(data.config.webPort);
  }
  chunked.print(F(">"
                  "<title>Modbus RTU &rArr; Modbus TCP/UDP Gateway</title>"
                  "<style>"
                  /*
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
                  "body,.m{padding:1px;margin:0;font-family:sans-serif}"
                  "h1,h4{padding:10px}"
                  "h1,.m,h4{background:#0067AC;margin:1px}"
                  ".m,.c{height:calc(100vh - 71px)}"
                  ".m{min-width:20%}"
                  ".c{flex-grow:1;overflow-y:auto}"
                  ".w,.r{display:flex}"
                  "a,h1,h4{color:white;text-decoration:none}"
                  ".c h4{padding-left:30%;margin-bottom:20px}"
                  ".r{margin:4px}"
                  "label{width:30%;text-align:right;margin-right:2px}"
                  "input,button,select{margin-top:-2px}"  // improve vertical allignment of input, button and select
                  ".s{text-align:right}"
                  ".s>option{direction:rtl}"
                  ".i{text-align:center;width:3ch;color:black}"
                  ".n{width:8ch}"
                  "</style>"
                  "</head>"
                  "<body"));
#ifdef ENABLE_DHCP
  chunked.print(F(" onload=g(document.getElementById('o').checked)>"
                  "<script>function g(h) {var x = document.getElementsByClassName('p');for (var i = 0; i < x.length; i++) {x[i].disabled = h}}</script"));
#endif /* ENABLE_DHCP */
  if (reqPage == PAGE_STATUS) {
    chunked.print(F("><script>"
                    "var a;"
                    "const b=()=>{"
                    "fetch('d.json')"  // Call the fetch function passing the url of the API as a parameter
                    ".then(e=>{return e.json();a=0})"
                    ".then(f=>{for(var i in f){if(document.getElementById(i))document.getElementById(i).innerHTML=f[i];}})"
                    ".catch(()=>{if(!a){alert('Connnection lost');a=1}})"
                    "};"
                    "setInterval(()=>b(),"));
    chunked.print(FETCH_INTERVAL);
    chunked.print(F(");"
                    "</script"));
  }
  chunked.print(F(">"
                  "<h1>Modbus RTU &rArr; Modbus TCP/UDP Gateway</h1>"
                  "<div class=w>"
                  "<div class=m>"));

  // Left Menu
  for (byte i = 1; i < PAGE_WAIT; i++) {  // PAGE_WAIT is the last item in enum
    chunked.print(F("<h4 "));
    if ((i) == reqPage) {
      chunked.print(F(" style=background-color:#FF6600"));
    }
    chunked.print(F("><a href="));
    chunked.print(i);
    chunked.print(F(".htm>"));
    stringPageName(chunked, i);
    chunked.print(F("</a></h4>"));
  }
  chunked.print(F("</div>"  // <div class=w>
                  "<div class=c>"
                  "<h4>"));
  stringPageName(chunked, reqPage);
  chunked.print(F("</h4>"
                  "<form method=post>"));

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
    chunked.print(F("<p><div class=r><label><input type=submit value='Save & Apply'></label><input type=reset value=Cancel></div>"));
  }
  chunked.print(F("</form>"));
  tagDivClose(chunked);  // close tags <div class=c> <div class=w>
  chunked.end();         // closing tags not required </body></html>
}


/**************************************************************************/
/*!
  @brief System Info

  @param chunked Chunked buffer
*/
/**************************************************************************/
void contentInfo(ChunkedPrint &chunked) {
  tagLabelDiv(chunked, F("SW Version"));
  chunked.print(VERSION[0]);
  chunked.print(F("."));
  chunked.print(VERSION[1]);
  tagDivClose(chunked);
  tagLabelDiv(chunked, F("Microcontroller"));
  chunked.print(BOARD);
  tagDivClose(chunked);
  tagLabelDiv(chunked, F("EEPROM Health"));
  chunked.print(data.eepromWrites);
  chunked.print(F(" Write Cycles"));
  tagDivClose(chunked);
  tagLabelDiv(chunked, F("Ethernet Chip"));
  switch (W5100.getChip()) {
    case 51:
      chunked.print(F("W5100"));
      break;
    case 52:
      chunked.print(F("W5200"));
      break;
    case 55:
      chunked.print(F("W5500"));
      break;
    default:  // TODO: add W6100 once it is included in Ethernet library
      chunked.print(F("Unknown"));
      break;
  }
  tagDivClose(chunked);
  tagLabelDiv(chunked, F("Ethernet Sockets"));
  chunked.print(maxSockNum);
  tagDivClose(chunked);
  tagLabelDiv(chunked, F("MAC Address"));
  for (byte i = 0; i < 6; i++) {
    chunked.print(hex(data.mac[i]));
    if (i < 5) chunked.print(F(":"));
  }
  tagDivClose(chunked);

#ifdef ENABLE_DHCP
  tagLabelDiv(chunked, F("DHCP Status"));
  if (!data.config.enableDhcp) {
    chunked.print(F("Disabled"));
  } else if (dhcpSuccess == true) {
    chunked.print(F("Success"));
  } else {
    chunked.print(F("Failed, using fallback static IP"));
  }
  tagDivClose(chunked);
#endif /* ENABLE_DHCP */

  tagLabelDiv(chunked, F("IP Address"));
  chunked.print(IPAddress(Ethernet.localIP()));
  tagDivClose(chunked);
}

/**************************************************************************/
/*!
  @brief P1P2 Status

  @param chunked Chunked buffer
*/
/**************************************************************************/
void contentStatus(ChunkedPrint &chunked) {

#ifdef ENABLE_EXTENDED_WEBUI
  tagLabelDiv(chunked, F("Run Time"));
  tagSpan(chunked, JSON_TIME);
  tagDivClose(chunked);
  tagLabelDiv(chunked, F("RTU Data"));
  tagSpan(chunked, JSON_RTU_DATA);
  tagDivClose(chunked);
  tagLabelDiv(chunked, F("Ethernet Data"));
  tagSpan(chunked, JSON_ETH_DATA);
  tagDivClose(chunked);
#endif /* ENABLE_EXTENDED_WEBUI */

  tagLabelDiv(chunked, F("Modbus RTU Request"));
  for (byte i = 0; i <= POST_REQ_LAST - POST_REQ; i++) {
    bool required = false;
    bool printVal = false;
    byte value;
    if (i == 0 || i == 1) {
      required = true;  // first byte (slave address) and second byte (function code) are required
    }
    if (i < requestLen) {
      printVal = true;
      value = request[i];
    }
    tagInputHex(chunked, POST_REQ + i, required, printVal, value);
  }
  chunked.print(F("h (without CRC) <input type=submit value=Send>"));
  tagButton(chunked, F("Clear"), ACT_CLEAR_REQUEST);
  tagDivClose(chunked);
  chunked.print(F("</form><form method=post>"));
  tagLabelDiv(chunked, F("Modbus RTU Response"));
  tagSpan(chunked, JSON_RESPONSE);
  tagDivClose(chunked);
  tagLabelDiv(chunked, F("Requests Queue"));
  tagSpan(chunked, JSON_QUEUE);
  tagDivClose(chunked);
  tagLabelDiv(chunked, F("Modbus Statistics"));
  tagButton(chunked, F("Reset Stats"), ACT_RESET_STATS);
  chunked.print(F("<br>"));
  tagSpan(chunked, JSON_STATS);
  tagDivClose(chunked);
  tagLabelDiv(chunked, F("Modbus Masters"));
  tagSpan(chunked, JSON_TCP_UDP_MASTERS);
  tagDivClose(chunked);
  tagLabelDiv(chunked, F("Modbus Slaves"));
  tagButton(chunked, F("Scan Slaves"), ACT_SCAN);
  chunked.print(F("<br>"));
  tagSpan(chunked, JSON_SLAVES);
  tagDivClose(chunked);
}

/**************************************************************************/
/*!
  @brief IP Settings

  @param chunked Chunked buffer
*/
/**************************************************************************/
void contentIp(ChunkedPrint &chunked) {

  tagLabelDiv(chunked, F("MAC Address"));
  for (byte i = 0; i < 6; i++) {
    tagInputHex(chunked, POST_MAC + i, true, true, data.mac[i]);
    if (i < 5) chunked.print(F(":"));
  }
  tagButton(chunked, F("Randomize"), ACT_MAC);
  tagDivClose(chunked);

#ifdef ENABLE_DHCP
  tagLabelDiv(chunked, F("Auto IP"));
  chunked.print(F("<input type=hidden name="));
  chunked.print(POST_DHCP, HEX);
  chunked.print(F(" value=0>"
                  "<input type=checkbox id=o name="));
  chunked.print(POST_DHCP, HEX);
  chunked.print(F(" onclick=g(this.checked) value=1"));
  if (data.config.enableDhcp) chunked.print(F(" checked"));
  chunked.print(F("> DHCP"));
  tagDivClose(chunked);
#endif /* ENABLE_DHCP */

  byte *tempIp;
  for (byte j = 0; j < 3; j++) {
    switch (j) {
      case 0:
        tagLabelDiv(chunked, F("Static IP"));
        tempIp = data.config.ip;
        break;
      case 1:
        tagLabelDiv(chunked, F("Submask"));
        tempIp = data.config.subnet;
        break;
      case 2:
        tagLabelDiv(chunked, F("Gateway"));
        tempIp = data.config.gateway;
        break;
      default:
        break;
    }
    tagInputIp(chunked, POST_IP + (j * 4), tempIp);
    tagDivClose(chunked);
  }
#ifdef ENABLE_DHCP
  tagLabelDiv(chunked, F("DNS Server"));
  tagInputIp(chunked, POST_DNS, data.config.dns);
  tagDivClose(chunked);
#endif /* ENABLE_DHCP */
}

/**************************************************************************/
/*!
  @brief TCP/UDP Settings

  @param chunked Chunked buffer
*/
/**************************************************************************/
void contentTcp(ChunkedPrint &chunked) {
  uint16_t value;
  for (byte i = 0; i < 3; i++) {
    switch (i) {
      case 0:
        tagLabelDiv(chunked, F("Modbus TCP Port"));
        value = data.config.tcpPort;
        break;
      case 1:
        tagLabelDiv(chunked, F("Modbus UDP Port"));
        value = data.config.udpPort;
        break;
      case 2:
        tagLabelDiv(chunked, F("WebUI Port"));
        value = data.config.webPort;
        break;
      default:
        break;
    }
    tagInputNumber(chunked, POST_TCP + i, 1, 65535, value, F(""));
    tagDivClose(chunked);
  }
  tagLabelDiv(chunked, F("Modbus Mode"));
  chunked.print(F("<select name="));
  chunked.print(POST_RTU_OVER, HEX);
  chunked.print(F(">"));
  for (byte i = 0; i < 2; i++) {
    chunked.print(F("<option value="));
    chunked.print(i);
    if (data.config.enableRtuOverTcp == i) chunked.print(F(" selected"));
    chunked.print(F(">"));
    switch (i) {
      case 0:
        chunked.print(F("Modbus TCP/UDP"));
        break;
      case 1:
        chunked.print(F("Modbus RTU over TCP/UDP"));
        break;
      default:
        break;
    }
    chunked.print(F("</option>"));
  }
  chunked.print(F("</select>"));
  tagDivClose(chunked);
  tagLabelDiv(chunked, F("Modbus TCP Idle Timeout"));
  tagInputNumber(chunked, POST_TCP_TIMEOUT, 1, 3600, data.config.tcpTimeout, F("sec"));
  tagDivClose(chunked);
}

/**************************************************************************/
/*!
  @brief RTU Settings

  @param chunked Chunked buffer
*/
/**************************************************************************/
void contentRtu(ChunkedPrint &chunked) {
  tagLabelDiv(chunked, F("Baud Rate"));
  chunked.print(F("<select class=s name="));
  chunked.print(POST_BAUD, HEX);
  chunked.print(F(">"));
  for (byte i = 0; i < (sizeof(BAUD_RATES) / 2); i++) {
    chunked.print(F("<option value="));
    chunked.print(BAUD_RATES[i]);
    if (data.config.baud == BAUD_RATES[i]) chunked.print(F(" selected"));
    chunked.print(F(">"));
    chunked.print(BAUD_RATES[i]);
    chunked.print(F("00</option>"));
  }
  chunked.print(F("</select> bps"));
  tagDivClose(chunked);
  tagLabelDiv(chunked, F("Data Bits"));
  chunked.print(F("<select name="));
  chunked.print(POST_DATA, HEX);
  chunked.print(F(">"));
  for (byte i = 5; i <= 8; i++) {
    chunked.print(F("<option value="));
    chunked.print(i);
    if ((((data.config.serialConfig & 0x06) >> 1) + 5) == i) chunked.print(F(" selected"));
    chunked.print(F(">"));
    chunked.print(i);
    chunked.print(F("</option>"));
  }
  chunked.print(F("</select> bit"));
  tagDivClose(chunked);
  tagLabelDiv(chunked, F("Parity"));
  chunked.print(F("<select name="));
  chunked.print(POST_PARITY, HEX);
  chunked.print(F(">"));
  for (byte i = 0; i <= 3; i++) {
    if (i == 1) continue;  // invalid value, skip and continue for loop
    chunked.print(F("<option value="));
    chunked.print(i);
    if (((data.config.serialConfig & 0x30) >> 4) == i) chunked.print(F(" selected"));
    chunked.print(F(">"));
    switch (i) {
      case 0:
        chunked.print(F("None"));
        break;
      case 2:
        chunked.print(F("Even"));
        break;
      case 3:
        chunked.print(F("Odd"));
        break;
      default:
        break;
    }
    chunked.print(F("</option>"));
  }
  chunked.print(F("</select>"));
  tagDivClose(chunked);
  tagLabelDiv(chunked, F("Stop Bits"));
  chunked.print(F("<select name="));
  chunked.print(POST_STOP, HEX);
  chunked.print(F(">"));
  for (byte i = 1; i <= 2; i++) {
    chunked.print(F("<option value="));
    chunked.print(i);
    if ((((data.config.serialConfig & 0x08) >> 3) + 1) == i) chunked.print(F(" selected"));
    chunked.print(F(">"));
    chunked.print(i);
    chunked.print(F("</option>"));
  }
  chunked.print(F("</select> bit"));
  tagDivClose(chunked);
  tagLabelDiv(chunked, F("Inter-frame Delay"));
  tagInputNumber(chunked, POST_FRAMEDELAY, byte(frameDelay() / 1000UL) + 1, 250, data.config.frameDelay, F("ms"));
  tagDivClose(chunked);
  tagLabelDiv(chunked, F("Response Timeout"));
  tagInputNumber(chunked, POST_TIMEOUT, 50, 5000, data.config.serialTimeout, F("ms"));
  tagDivClose(chunked);
  tagLabelDiv(chunked, F("Attempts"));
  tagInputNumber(chunked, POST_ATTEMPTS, 1, 5, data.config.serialAttempts, F(""));
  tagDivClose(chunked);
}

/**************************************************************************/
/*!
  @brief Tools

  @param chunked Chunked buffer
*/
/**************************************************************************/
void contentTools(ChunkedPrint &chunked) {
  tagLabelDiv(chunked, 0);
  tagButton(chunked, F("Load Default Settings"), ACT_DEFAULT);
  chunked.print(F(" (static IP: "));
  chunked.print(IPAddress(DEFAULT_CONFIG.ip));
  chunked.print(F(")"));
  tagDivClose(chunked);
  tagLabelDiv(chunked, 0);
  tagButton(chunked, F("Reboot"), ACT_REBOOT);
  tagDivClose(chunked);
}


void contentWait(ChunkedPrint &chunked) {
  tagLabelDiv(chunked, 0);
  chunked.print(F("Reloading. Please wait..."));
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
/**************************************************************************/
void tagInputNumber(ChunkedPrint &chunked, const byte name, const byte min, uint16_t max, uint16_t value, const __FlashStringHelper *units) {
  chunked.print(F("<input class='s n' required type=number name="));
  chunked.print(name, HEX);
  chunked.print(F(" min="));
  chunked.print(min);
  chunked.print(F(" max="));
  chunked.print(max);
  chunked.print(F(" value="));
  chunked.print(value);
  chunked.print(F("> ("));
  chunked.print(min);
  chunked.print(F("~"));
  chunked.print(max);
  chunked.print(F(") "));
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
/**************************************************************************/
void tagInputIp(ChunkedPrint &chunked, const byte name, byte ip[]) {
  for (byte i = 0; i < 4; i++) {
    chunked.print(F("<input name="));
    chunked.print(name + i, HEX);
    chunked.print(F(" class='p i' required maxlength=3 pattern='^(&bsol;d{1,2}|1&bsol;d&bsol;d|2[0-4]&bsol;d|25[0-5])$' value="));
    chunked.print(ip[i]);
    chunked.print(F(">"));
    if (i < 3) chunked.print(F("."));
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
/**************************************************************************/
void tagInputHex(ChunkedPrint &chunked, const byte name, const bool required, const bool printVal, const byte value) {
  chunked.print(F("<input name="));
  chunked.print(name, HEX);
  if (required) {
    chunked.print(F(" required"));
  }
  chunked.print(F(" minlength=2 maxlength=2 class=i pattern='[a-fA-F&bsol;d]+' value='"));
  if (printVal) {
    chunked.print(hex(value));
  }
  chunked.print(F("'>"));
}

/**************************************************************************/
/*!
  @brief <label><div>

  @param chunked Chunked buffer
  @param label Label string
*/
/**************************************************************************/
void tagLabelDiv(ChunkedPrint &chunked, const __FlashStringHelper *label) {
  chunked.print(F("<div class=r>"));
  chunked.print(F("<label> "));
  if (label) {
    chunked.print(label);
    chunked.print(F(":"));
  }
  chunked.print(F("</label><div>"));
}

/**************************************************************************/
/*!
  @brief <button>

  @param chunked Chunked buffer
  @param flashString Button string
  @param value Value to be sent via POST
*/
/**************************************************************************/
void tagButton(ChunkedPrint &chunked, const __FlashStringHelper *flashString, byte value) {
  chunked.print(F(" <button name="));
  chunked.print(POST_ACTION, HEX);
  chunked.print(F(" value="));
  chunked.print(value);
  chunked.print(F(">"));
  chunked.print(flashString);
  chunked.print(F("</button>"));
}

/**************************************************************************/
/*!
  @brief </div>

  @param chunked Chunked buffer
*/
/**************************************************************************/
void tagDivClose(ChunkedPrint &chunked) {
  chunked.print(F("</div>"
                  "</div>"));  // <div class=r>
}

/**************************************************************************/
/*!
  @brief <span>

  @param chunked Chunked buffer
  @param JSONKEY JSON_ id
*/
/**************************************************************************/
void tagSpan(ChunkedPrint &chunked, const byte JSONKEY) {
  chunked.print(F("<span id="));
  chunked.print(JSONKEY);
  chunked.print(F(">"));
  jsonVal(chunked, JSONKEY);
  chunked.print(F("</span>"));
}

/**************************************************************************/
/*!
  @brief Menu item strings

  @param chunked Chunked buffer
  @param item Page number
*/
/**************************************************************************/
void stringPageName(ChunkedPrint &chunked, byte item) {
  switch (item) {
    case PAGE_INFO:
      chunked.print(F("System Info"));
      break;
    case PAGE_STATUS:
      chunked.print(F("Modbus Status"));
      break;
    case PAGE_IP:
      chunked.print(F("IP Settings"));
      break;
    case PAGE_TCP:
      chunked.print(F("TCP/UDP Settings"));
      break;
    case PAGE_RTU:
      chunked.print(F("RTU Settings"));
      break;
    case PAGE_TOOLS:
      chunked.print(F("Tools"));
      break;
    default:
      break;
  }
}

void stringStats(ChunkedPrint &chunked, const byte stat) {
  switch (stat) {
    case SLAVE_OK:
      chunked.print(F(" Slave Responded"));
      break;
    case SLAVE_ERROR_0X:
      chunked.print(F(" Slave Responded with Error (Codes 1~8)"));
      break;
    case SLAVE_ERROR_0A:
      chunked.print(F(" Gateway Overloaded (Code 10)"));
      break;
    case SLAVE_ERROR_0B:
    case SLAVE_ERROR_0B_QUEUE:
      chunked.print(F(" Slave Failed to Respond (Code 11)"));
      break;
    case ERROR_TIMEOUT:
      chunked.print(F(" Response Timeout"));
      break;
    case ERROR_RTU:
      chunked.print(F(" Invalid RTU Response"));
      break;
    case ERROR_TCP:
      chunked.print(F(" Invalid TCP/UDP Request"));
      break;
    default:
      break;
  }
  chunked.print(F("<br>"));
}

/**************************************************************************/
/*!
  @brief Provide JSON value to a corresponding JSON key. The value is printed
  in <span> and in JSON document fetched on the background.
  @param chunked Chunked buffer
  @param JSONKEY JSON key
*/
/**************************************************************************/
void jsonVal(ChunkedPrint &chunked, const byte JSONKEY) {
  switch (JSONKEY) {
#ifdef ENABLE_EXTENDED_WEBUI
    case JSON_TIME:
      chunked.print(seconds / (3600UL * 24L));
      chunked.print(F(" days, "));
      chunked.print((seconds / 3600UL) % 24L);
      chunked.print(F(" hours, "));
      chunked.print((seconds / 60UL) % 60L);
      chunked.print(F(" mins, "));
      chunked.print((seconds) % 60L);
      chunked.print(F(" secs"));
      break;
    case JSON_RTU_DATA:
      for (byte i = 0; i < DATA_LAST; i++) {
        chunked.print(data.rtuCnt[i]);
        switch (i) {
          case DATA_TX:
            chunked.print(F(" Tx bytes / "));
            break;
          case DATA_RX:
            chunked.print(F(" Rx bytes"));
            break;
        }
      }
    case JSON_ETH_DATA:
      for (byte i = 0; i < DATA_LAST; i++) {
        chunked.print(data.ethCnt[i]);
        switch (i) {
          case DATA_TX:
            chunked.print(F(" Tx bytes / "));
            break;
          case DATA_RX:
            chunked.print(F(" Rx bytes (excl. WebUI)"));
            break;
        }
      }
      break;
#endif /* ENABLE_EXTENDED_WEBUI */
    case JSON_RESPONSE:
      {
        for (byte i = 0; i < MAX_RESPONSE_LEN; i++) {
          chunked.print(F("<input value='"));
          if (i < responseLen) {
            chunked.print(hex(response[i]));
          }
          chunked.print(F("' disabled class=i>"));
        }
        chunked.print(F("h"));
        if (responseLen > MAX_RESPONSE_LEN) {
          chunked.print(F(" +"));
          chunked.print(byte(responseLen - MAX_RESPONSE_LEN));
          chunked.print(F(" bytes"));
        }
      }
      break;
    case JSON_QUEUE:
      chunked.print(queueDataSize);
      chunked.print(F(" / "));
      chunked.print(MAX_QUEUE_DATA);
      chunked.print(F(" bytes<br>"));
      chunked.print(queueHeadersSize);
      chunked.print(F(" / "));
      chunked.print(MAX_QUEUE_REQUESTS);
      chunked.print(F(" requests"));
      queueDataSize = queueData.size();
      queueHeadersSize = queueHeaders.size();
      break;
    case JSON_STATS:
      for (byte i = 0; i < ERROR_LAST; i++) {
        if (i == SLAVE_ERROR_0B_QUEUE) continue;  // SLAVE_ERROR_0B_QUEUE is not shown in web UI
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
              chunked.print(F(" UDP<br>"));
            } else if (W5100.readSnSR(s) == SnSR::ESTABLISHED && W5100.readSnPORT(s) == data.config.tcpPort) {
              chunked.print(IPAddress(remoteIParray));
              chunked.print(F(" TCP<br>"));
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
              chunked.print(F("h"));
              if (k == scanCounter) {
                chunked.print(F(" Scanning...<br>"));
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

