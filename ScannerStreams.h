#include <HardWareserial.h>
#include <SD.h>

class ScannerStream{
  public:
  void setupScanner(HardwareSerial* serial);
  void setUpSDCard(SDClass* SD, int port);
  void performScannerIfCan();

  private:
  // setup
  void setupDefault();
  // file management
  void openFileSD();
  void closeFileSD();
  void testTestFileSD();
  byte getVal(char c);
 
  HardwareSerial* _serial;
  SDClass* _SD;

  char* fileName;
  File myFile;
};
