

#define btModule Serial3

// set this to the hardware serial port you wish to use
String outString = "";

char ch; // Where to store the character read

void setup() { 
  Serial.begin(9600);  // Arduino 57600 is actually 58824
  btModule.begin(115200);
}

void loop() {      
  int incomingByte;  

  // If stuff was typed in the serial monitor

   while (btModule.available() > 0){
      delay(10);  //small delay to allow input buffer to fill 
      char c = char(btModule.read());     
      outString += c; // Add it
       
      if(c == 13 /* \n */){
        Serial.println("will print");
        btModule.println(outString);
        outString = "";
      }
   }  
}
