
#include "ScannerStreams.h"
#include <SD.h>

#define HI_NIBBLE(b) (((b) >> 4) & 0x0F)
#define LO_NIBBLE(b) ((b) & 0x0F)

#define GIF_DIRECTORY "/gifs/"
#define TEST_DIRECTORY "/test/"

void ScannerStream::setupScanner(HardwareSerial* serial){
    this->_serial = serial;
}

void ScannerStream::setupDefault(){
    fileName = "test/fileTest.gif";
}

void ScannerStream::setUpSDCard(SDClass* SD, int port){
    _SD = SD;
    // initialize the SD card at full speed
    pinMode(port, OUTPUT);

    if(!_SD->begin(port)) {
       //  matrix.scrollText("No SD card", -1);
        Serial.println("No SD card");
       while(1);
    }else
        _SD->mkdir("test");
}

void ScannerStream::performScannerIfCan(){
    char buffer;
    int moduloNimble = 0;

    // input sent as ascii representating hexa value.
    // Wich means we need to convert them back into the 
    // hexa value they represent litteraly. Paquet is read
    // one byte at a time, so each time, the nimbles must be
    // kept in order. This is what moduloNimble take care of.
    while (_serial->available() > 0){
       char c = _serial->read();
        
        // Remember, the nimble must be keep in order to
        // reconstruct the byte value.
        if(!(moduloNimble++ % 2)){
          // high nimble
          buffer |= LO_NIBBLE(getVal(c)) << 4;
        }else{
          // low nimble + high nimble
          buffer |= LO_NIBBLE(getVal(c));
           _serial->print(buffer);
           // TODO rajouter les règles de parsing.
/*
          myFile.print(buffer);
           
          if(buffer == 'o'){
            openFileSD();
          }
          else if(buffer == 'x'){
            closeFileSD();
          }
          else if(buffer == 't'){
            testTestFileSD();
          }
            */
          // now clear buffer
          buffer = 0x00;
        }
    }
}

void ScannerStream::openFileSD(){
  _SD->remove(fileName);
  
  myFile = _SD->open(fileName, FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
     Serial.println("file opened");
  }else{
     Serial.println("error opening test.txt");
  }
}

void ScannerStream::closeFileSD(){
      // close the file:
    myFile.close();
    Serial.println("file closed");
}

void ScannerStream::testTestFileSD(){
   Serial.println("test reading file");  
   
   myFile = _SD->open(fileName);

   // print file as ascii. Note some binary values are not asii (8 plain full bits)
   while (myFile.available()){ 
     char hexa2 = myFile.read();
     Serial.print(hexa2);
   }

   closeFileSD();
    
   myFile = _SD->open(fileName);

   // print in hexa to test if file has been properly written.
   while (myFile.available()){
      char hexa2 = myFile.read();
      Serial.print(hexa2, HEX);
   }

   closeFileSD();
   Serial.println("test done reading file");
   /*
   char pathName[30];
   int numberOfFiles = enumerateGIFFiles(TEST_DIRECTORY, false);
   getGIFFilenameByIndex(TEST_DIRECTORY, 0, pathName);
   Serial.println("number of file");
   Serial.println(pathName);
   Serial.println(numberOfFiles);
   */
}

// convert ASCII hex representation to hex litteral value.
byte ScannerStream::getVal(char c){
   if(c >= '0' && c <= '9')
     return (byte)(c - '0');
   else
     return (byte)(c-'A'+10);
}
