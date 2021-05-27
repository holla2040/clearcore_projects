#define console Serial

void setup() {
  console.begin(115200);
  delay(1000);
  console.println("usbSerial setup");
}

void loop() {
  console.println(millis());
  delay(500);
}
