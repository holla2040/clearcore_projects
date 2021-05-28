#include "Arduino.h"
#include "driver.h"

#ifdef __cplusplus
extern "C" {
#endif

int16_t serialGetC (void) {
  return console.read();
}

bool serialSuspendInput (bool suspend) {
  return 1;
}

void serialInit() {
  console.begin(115200);
  delay(2000);
  console.println("serialInit");
}

bool serialPutC(const char c) {
  console.write(c);
}

bool serialWriteS(const char *s) {
  console.print(s);
}

bool serialWrite(const char *s,uint16_t length) {
    char *ptr = (char *)s;

    while(length--)
      serialPutC(*ptr++);
}

void serialWriteLn(const char *s) {
  console.println(s);
}

uint16_t serialTxCount (void) {
  return 0;
}

uint16_t serialRxCount (void) {
  return console.available();
}

uint16_t serialRxFree (void) {
  return 100;
}

void serialRxFlush (void) {
}

void serialRxCancel (void) {
}






#ifdef __cplusplus
}
#endif


