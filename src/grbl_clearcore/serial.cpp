#include "Arduino.h"
#include "driver.h"

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif


