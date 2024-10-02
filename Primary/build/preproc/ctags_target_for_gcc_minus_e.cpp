# 1 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino"
# 2 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino" 2
# 3 "C:\\Users\\Zach_\\Documents\\Code\\HGV-Coop\\Rems006\\Primary\\Primary.ino" 2

// MAC address for the Ethernet shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Start Ethernet client
EthernetClient client;

void setup() {
  // Start Serial communication for debugging
  Serial.begin(9600);

  // Start the Ethernet connection and check for DHCP assignment
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // You can assign a static IP if DHCP fails
    Ethernet.begin(mac, IPAddress(192, 168, 1, 177));
  } else {
    Serial.println("Ethernet configured via DHCP");
  }

  // Print the assigned IP address
  Serial.print("Assigned IP: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // Your loop code here
}
