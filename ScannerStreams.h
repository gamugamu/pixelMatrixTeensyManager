#include <HardWareserial.h>
#include <SD.h>

class ScannerStream{
  public:
  ScannerStream(HardwareSerial* serial);
  void setupDefault();
  void setUpSDCard(int port);
  void performScannerIfCan();

  void openFileSD();
  void closeFileSD();
  void testTestFileSD();

  char getVal(char c);
 
  private:
  HardwareSerial* _serial;
  char* fileName;
  File myFile;
};
