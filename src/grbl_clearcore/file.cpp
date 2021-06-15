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
    SD.remove("settings.bin"); // FILE_WRITE is really append
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
  uint8_t rv;

#ifdef DEBUGFILE
  console.print("sdGetByte ");
  console.println(addr,HEX);
#endif

  settingsFile = SD.open("settings.bin");
  settingsFile.seek(addr);
  rv = settingsFile.read();
  settingsFile.close();

  return rv;
}

void sdSettingsPutByte(uint32_t addr, uint8_t new_value) {
#ifdef DEBUGFILE
  console.print("sdPutByte ");
  console.print(addr,HEX);
  console.print(" ");
  console.println(new_value,HEX);
#endif
  settingsFile = SD.open("settings.bin",FILE_WRITE);
  settingsFile.seek(addr);
  settingsFile.write(new_value);
  settingsFile.close();
}

#ifdef __cplusplus
}
#endif


