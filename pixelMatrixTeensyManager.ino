/*
 * Animated GIFs Display Code for SmartMatrix and 32x32 RGB LED Panels
 *
 * Uses SmartMatrix Library for Teensy 3.1 written by Louis Beaudoin at pixelmatix.com
 *
 * Written by: Craig A. Lindley
 *
 * Copyright (c) 2014 Craig A. Lindley
 * Minor modifications by Louis Beaudoin (Pixelmatix)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

 /*
  * This example displays 32x32 GIF animations loaded from a SD Card connected to the Teensy 3.1
  * The GIFs must be 32x32 pixels exactly
  * Wiring is on the default Teensy 3.1 SPI pins, and chip select can be on any GPIO,
  * set by defining SD_CS in the code below
  * Function     | Pin
  * DOUT         |  11
  * DIN          |  12
  * CLK          |  13
  * CS (default) |  15
  *
  * This code first looks for .gif files in the /gifs/ directory
  * (customize below with the GIF_DIRECTORY definition) then plays random GIFs in the directory,
  * looping each GIF for DISPLAY_TIME_SECONDS
  *
  * This example is meant to give you an idea of how to add GIF playback to your own sketch.
  * For a project that adds GIF playback with other features, take a look at
  * Light Appliance:
  * https://github.com/CraigLindley/LightAppliance
  *
  * If you find any 32x32 GIFs that won't play properly, please attach them to a new
  * Issue post in the GitHub repo here:
  * https://github.com/pixelmatix/AnimatedGIFs/issues
  *
  * This sketch requires the SdFat Library: https://github.com/greiman/SdFat
  *
  * If you're having trouble compiling this sketch, view instructions in the README file, which is
  * available online here: https://github.com/pixelmatix/AnimatedGIFs/
  *
  */

#include <math.h>
#include <stdlib.h>
#include <SPI.h>
#include <SD.h>
#include <SmartMatrix_32x32.h>

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

#define GIF_DIRECTORY "/gifs/"

#define btModule Serial1
// set this to the hardware serial port you wish to use
String outString = "";

// Setup method runs once, when the sketch starts
void setup() {
    Serial.begin(9600);  // Arduino 57600 is actually 58824
   // btModule.begin(115200);
    Serial.println("will initialize");
    
    // initialize the SD card at full speed
    pinMode(SD_CS, OUTPUT);
    
      Serial.println("execute");
  if(!SD.begin(SD_CS)) {
     //  matrix.scrollText("No SD card", -1);
     Serial.println("No SD card");
     while(1);
   }
   
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

void testSD(){
    
  char fileName[] = "fileTest.txt";
  File myFile;

 // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open(fileName, FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
	// close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening");
  }
  
  // re-open the file for reading:
  myFile = SD.open(fileName);
  if (myFile) {
    Serial.println(fileName);
    
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
    	Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
    Serial.println("file closed");
  } else {
  	// if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

}

void loop() {
  
  while (Serial.available() > 0){
        char c = char(Serial.read());     
        if(c == 'x'){
          testSD();
        }
  }

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

