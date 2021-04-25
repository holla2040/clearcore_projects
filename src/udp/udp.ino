/* from Teknic's ethernetudp example */
#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 0, 177);

unsigned int localPort = 8888;

#define MAX_PACKET_LENGTH 100
char packetReceived[MAX_PACKET_LENGTH];

EthernetUDP Udp;
bool usingDhcp = false;

void setup() {
    Serial.begin(115200);

    delay(3000);

    if (usingDhcp) {
        int dhcpSuccess = Ethernet.begin(mac);
        if (dhcpSuccess) {
            Serial.print("DHCP ");
	    Serial.println(Ethernet.localIP());
        }
        else {
            Serial.println("DHCP failed");
            Serial.println("Try again using a manual configuration...");
            while (true) {
                // UDP will not work without a configured IP address.
                continue;
            }
        }
    }
    else {
        Ethernet.begin(mac, ip);
        Serial.print("IP   ");
	Serial.println(Ethernet.localIP());
    }

    while (Ethernet.linkStatus() == LinkOFF) {
        Serial.println("The Ethernet cable is unplugged...");
        delay(500);
    }

    Udp.begin(localPort);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    int packetSize = Udp.parsePacket();
    if (packetSize > 0) {
        Serial.print("Remote IP: ");
	Serial.print(Udp.remoteIP());
        Serial.print(" ");
        Serial.print(Udp.remotePort());
        Serial.print(" ");

        int bytesRead = Udp.read(packetReceived, MAX_PACKET_LENGTH);
        Serial.write(packetReceived, bytesRead);
        Serial.println();

        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
	for (int i = 0; i < bytesRead; i++) {
	  Udp.write(toupper(packetReceived[i]));
	}
        Udp.endPacket();
	if (packetReceived[0] == '0') digitalWrite(LED_BUILTIN, LOW);
	if (packetReceived[0] == '1') digitalWrite(LED_BUILTIN, HIGH);
    }

    delay(10);
}
