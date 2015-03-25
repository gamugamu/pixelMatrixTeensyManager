#include <HardWareserial.h>
#include <SD.h>

class ScannerStream{
  public:
  void setupScanner(HardwareSerial* serial);
  void performScannerIfCan();

  private:
  // setup
  void setupDefault();
  void setUpSDCard(int port);
  // file management
  void openFileSD();
  void closeFileSD();
  void testTestFileSD();
  byte getVal(char c);
 
  HardwareSerial* _serial;
  char* fileName;
  File myFile;
};
