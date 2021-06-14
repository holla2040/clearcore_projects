#define console Serial0

void setup() {
  console.begin(115200);
  delay(1000);
  console.println("serial0 setup");
}

void loop() {
  console.println(millis());
  delay(500);
}
