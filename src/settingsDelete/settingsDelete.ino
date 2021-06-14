#include <SPI.h>
#include <SD.h>

#define console Serial0

File root;
void printDirectory(File dir, int numTabs);

void setup() {
    console.begin(115200);

    console.println("settingsRead setup");

    if (!SD.begin()) {
        console.println("SD begin failed");
        while (true) {
            continue;
        }
    }

    root = SD.open("/");
    printDirectory(root, 0);
    console.println();
    SD.remove("settings.bin");
    root = SD.open("/");
    printDirectory(root, 0);
    console.println();

}

void loop() {
}

void printDirectory(File dir, int numTabs) {
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }

    for (uint8_t i = 0; i < numTabs; i++) {
      console.print('\t');
    }
    console.print(entry.name());
    if (entry.isDirectory()) {
      console.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      console.print("\t\t");
      console.println(entry.size(), DEC);
    }
    entry.close();
  }
}
