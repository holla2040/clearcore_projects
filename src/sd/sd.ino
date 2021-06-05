#include <SPI.h>
#include <SD.h>

File myFile;
File root;
void printDirectory(File dir, int numTabs);

void setup() {
    // Open serial communications and wait for port to open:
    Serial.begin(115200);
    while (!Serial) {
        // Wait for the USB serial port to open.
        continue; 
    }

    Serial.print("SD begin ...");

    if (!SD.begin()) {
        Serial.println("SD begin failed");
        while (true) {
            continue;
        }
    }
    Serial.println("SD begin success");

    root = SD.open("/");
    printDirectory(root, 0);
    Serial.println("done!");

    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    myFile = SD.open("test.txt", FILE_WRITE);

    // If the file opened okay, write to it:
    if (myFile) {
        Serial.print("Writing to test.txt...");
        myFile.println("testing 1, 2, 3.");
        // Close the file:
        myFile.close();
        Serial.println("done.");
    } 
    else {
        // If the file didn't open, print an error:
        Serial.println("error opening test.txt");
        while (true) {
            continue;
        }
    }

    // Re-open the file for reading:
    myFile = SD.open("list.txt");
    if (myFile) {
        Serial.println("list.txt:");

        // Read from the file until there's nothing else in it:
        while (myFile.available()) {
            Serial.write(myFile.read());
        }
        // Close the file:
        myFile.close();
    } 
    else {
        // If the file didn't open, print an error:
        Serial.println("error opening list.txt");
    }

}

void loop() {
    // Nothing happens after setup
}



void printDirectory(File dir, int numTabs) {
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }

    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
