#include "Arduino.h"
#include "driver.h"
#include <SPI.h>
#include <SD.h>

#ifdef __cplusplus
extern "C" {
#endif

File settingsFile;

//#define DEBUGFILE1

void sdInit(void) {
    if (!SD.begin()) {
        console.println("SD begin failed");
        while (true) {
            continue;
        }
    }
}

bool sdSettingsRead(uint8_t *dest) {
#ifdef DEBUGFILE
      console.print("sdRead ");
#endif

    settingsFile = SD.open("settings.bin");
    if (settingsFile) {
      settingsFile.read(dest,GRBL_NVS_SIZE);
      settingsFile.close();
#ifdef DEBUGFILE
      console.println("ok");
#endif
      return true;
    } 
#ifdef DEBUGFILE
    console.println("fail");
#endif
    return false;
}

bool sdSettingsWrite(uint8_t *source) {
#ifdef DEBUGFILE
    console.print("sdWrite ");
#endif
    SD.remove("settings.bin");
    settingsFile = SD.open("settings.bin",FILE_WRITE);
    if (settingsFile) {
      settingsFile.write(source,GRBL_NVS_SIZE);
      settingsFile.close();
#ifdef DEBUGFILE
      console.println("ok");
#endif
      return true;
    } 
#ifdef DEBUGFILE
    console.println("fail");
#endif
    return false;
}

uint8_t sdSettingsGetByte(uint32_t addr) {
#ifdef DEBUGFILE
  console.print("sdGetByte ");
  console.println(addr,HEX);
#endif
  return SETTINGS_VERSION;
}

void sdSettingsPutByte(uint32_t addr, uint8_t new_value) {
#ifdef DEBUGFILE
  console.print("sdPutByte ");
  console.print(addr,HEX);
  console.print(" ");
  console.println(new_value,HEX);
#endif
}


#ifdef __cplusplus
}
#endif


