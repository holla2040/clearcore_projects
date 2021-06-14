#include <SPI.h>
#include <SD.h>

#define console Serial0

File myFile;
File root;
void printDirectory(File dir, int numTabs);

void setup() {
    // Open console communications and wait for port to open:
    console.begin(115200);
    while (!console) {
        // Wait for the USB console port to open.
        continue; 
    }

    console.print("SD begin ...");

    if (!SD.begin()) {
        console.println("SD begin failed");
        while (true) {
            continue;
        }
    }
    console.println("SD begin success");

    root = SD.open("/");
    printDirectory(root, 0);
    console.println("done!");

    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    myFile = SD.open("test.txt", FILE_WRITE);

    // If the file opened okay, write to it:
    if (myFile) {
        console.print("Writing to test.txt...");
        myFile.println("testing 1, 2, 3.");
        // Close the file:
        myFile.close();
        console.println("done.");
    } 
    else {
        // If the file didn't open, print an error:
        console.println("error opening test.txt");
        while (true) {
            continue;
        }
    }

    // Re-open the file for reading:
    myFile = SD.open("list.txt");
    if (myFile) {
        console.println("list.txt:");

        // Read from the file until there's nothing else in it:
        while (myFile.available()) {
            console.write(myFile.read());
        }
        // Close the file:
        myFile.close();
    } 
    else {
        // If the file didn't open, print an error:
        console.println("error opening list.txt");
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
