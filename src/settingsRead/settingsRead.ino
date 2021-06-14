#include <SPI.h>
#include <SD.h>

#define console Serial0

#define len 25

File file;
File root;
void printDirectory(File dir, int numTabs);

void setup() {
    // Open console communications and wait for port to open:
    console.begin(115200);
/*
    while (!console) {
        // Wait for the USB console port to open.
        continue; 
    }
*/

    console.print("settingsRead setup");

    if (!SD.begin()) {
        console.println("SD begin failed");
        while (true) {
            continue;
        }
    }
    console.println("SD begin success");

    file = SD.open("settings.bin");
    if (file) {
	int i = 0;
	char line[30];
	uint8_t buffer[2048];
        console.println("settings.bin:");

	file.read(buffer,128);
	for (i = 0; i < len; i++) {
	    sprintf(line,"%03d 0x%02X\n",i,buffer[i]);
            console.print(line);
	}
        file.close();
    } 

    file = SD.open("settings.bin");
    if (file) {
	int i = 0;
	char line[30];
        console.println("settings.bin:");

        while (file.available()) {
	    sprintf(line,"%03d 0x%02X\n",i++,file.read());
            console.print(line);
	    if (i > len) break;
        }

        file.close();
    } 

}

void loop() {
}

