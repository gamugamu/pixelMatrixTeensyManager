#include <math.h>
#include <stdlib.h>
#include <SPI.h>
#include <SmartMatrix_32x32.h>
#include <SD.h>
#include <ScannerStreams.cpp>

#define DISPLAY_TIME_SECONDS 10

// Declared in FilenameFunctions.cpp
extern int numberOfFiles;
extern int enumerateGIFFiles(const char *directoryName, boolean displayFilenames);
extern void getGIFFilenameByIndex(const char *directoryName, int index, char *pnBuffer);
extern void chooseRandomGIFFilename(const char *directoryName, char *pnBuffer);

// Declared in GIFParseFunctions.cpp
extern int processGIFFile(const char * pathname);

// range 0-255
const int defaultBrightness = 255;

const rgb24 COLOR_BLACK = {
    0, 0, 0 };

const int WIDTH = 32;
const int HEIGHT = 32;

// Smart Matrix instance
SmartMatrix matrix;

// Chip select for SD card on the SmartMatrix Shield
#define SD_CS 15
#define btModule Serial1

// set this to the hardware serial port you wish to use
String outString = "";

// Setup method runs once, when the sketch starts
void setup() {
    Serial.begin(9600);  // Arduino 57600 is actually 58824
  // btModule.begin(115200);
   ScannerStreams scanner;
// end test

    // Seed the random number generator
 /*   randomSeed(analogRead(14));

    // Initialize matrix
    matrix.begin();
    matrix.setBrightness(defaultBrightness);

    // Clear screen
    matrix.fillScreen(COLOR_BLACK);
    matrix.swapBuffers();
    matrix.scrollText("Welkom", -1);
*/

/*    // Determine how many animated GIF files exist
    numberOfFiles = enumerateGIFFiles(GIF_DIRECTORY, false);

    if(numberOfFiles < 0) {
        matrix.scrollText("No gifs directory", -1);
        Serial.println("No gifs directory");
        while(1);
    }

    if(!numberOfFiles) {
        matrix.scrollText("Empty gifs directory", -1);
        Serial.println("Empty gifs directory");
        while(1);
    }
  */ 
}

void loop() {
  // If stuff was typed in the serial monitor
  /*
   while (btModule.available() > 0){
      delay(10);  //small delay to allow input buffer to fill 
      char c = char(btModule.read());     
      outString += c; // Add it
      Serial.println(c);
      
      // '\n' \n 
      if(c == 13 || c ==){
        // echo the input, so the client is informed everything is ok
        btModule.println(outString);
        // Removing the \n because smartMatrix doesn't handle this.        
        int z_lenght = outString.length();
        outString.remove(z_lenght);
        Serial.println(outString);
        Serial.println("will print");
        //btModule.println(outString);
        outString.toCharArray(charBuf, z_lenght);
        Serial.println(charBuf);

        matrix.swapBuffers();
        //matrix.scrollText(charBuf, -1);
        delay(100);
        // wait for scrolling to finish
        outString = "";
        matrix.scrollText(charBuf, -1);
      }
   }  
   
*/
   /*
    unsigned long futureTime;
    char pathname[30];

    int index = random(numberOfFiles);

    // Do forever
    while (true) {
        // Clear screen for new animation
        matrix.fillScreen(COLOR_BLACK);
        matrix.swapBuffers();

        getGIFFilenameByIndex(GIF_DIRECTORY, index++, pathname);
        if (index >= numberOfFiles) {
            index = 0;
        }

        // Calculate time in the future to terminate animation
        futureTime = millis() + (DISPLAY_TIME_SECONDS * 1000);

        while (futureTime > millis()) {
            processGIFFile(pathname);
        }
    }
    */
}

