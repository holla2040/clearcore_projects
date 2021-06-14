#include "Arduino.h"
#include "driver.h"
#include <SPI.h>
#include <SD.h>

#ifdef __cplusplus
extern "C" {
#endif

File settingsFile;

void sdInit(void) {
    if (!SD.begin()) {
        console.println("SD begin failed");
        while (true) {
            continue;
        }
    }
}

bool sdSettingsRead(uint8_t *dest) {
  return false;
    console.print("sdRead ");
    settingsFile = SD.open("settings.bin");
    if (settingsFile) {
      settingsFile.read(dest,GRBL_NVS_SIZE);
      settingsFile.close();
      console.println("ok");
      return true;
    } 
    console.println("fail");
    return false;
}

bool sdSettingsWrite(uint8_t *source) {
    console.print("sdWrite ");
    SD.remove("settings.bin");
    settingsFile = SD.open("settings.bin",FILE_WRITE);
    if (settingsFile) {
      settingsFile.write(source,GRBL_NVS_SIZE);
      settingsFile.close();
      console.println("ok");
      return true;
    } 
    console.println("fail");
    return false;
}

uint8_t sdSettingsGetByte(uint32_t addr) {
  console.print("sdGetByte ");
  console.println(addr,HEX);
  return SETTINGS_VERSION;
}

void sdSettingsPutByte(uint32_t addr, uint8_t new_value) {
  console.print("sdPutByte ");
  console.print(addr,HEX);
  console.print(" ");
  console.println(new_value,HEX);
}


#ifdef __cplusplus
}
#endif


