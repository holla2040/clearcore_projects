#define DURATION 100

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(DURATION);
  digitalWrite(LED_BUILTIN, LOW);
  delay(DURATION);
}
