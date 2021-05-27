#include "Arduino.h"
#include "driver.h"

#ifdef __cplusplus
extern "C" {
#endif

void serialInit() {
  console.begin(BAUD_RATE);
}

bool serialPutC(const char c) {
  console.write(c);
}

bool serialWriteS(const char *s) {
  console.print(s);
}

#ifdef __cplusplus
}
#endif


