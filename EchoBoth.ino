/* UART Example, any character received on either the real
 serial port, or USB serial (or emulated serial to the
 Arduino Serial Monitor when using non-serial USB types)
 is printed as a message to both ports.
 
 This example code is in the public domain.
 */

// set this to the hardware serial port you wish to use
#define btModule Serial3

void setup() { 
  Serial.begin(9600);  // Arduino 57600 is actually 58824
  btModule.begin(115200);
}

void loop() {      
  int incomingByte;  

  // If stuff was typed in the serial monitor
  /*
    if(Serial.available()){
   btModule.print("bluetooth received: ");
   btModule.println( Serial.read(), BYTE );
   }*/

  if(btModule.available()){
    btModule.print("bluetooth received: ");
    btModule.println( btModule.read(), BYTE );
  }

  /*
    if(btModule.available()){
   Serial.print("bluethooth X1 received: ");
   Serial.println( btModule.read(), BYTE );
   }
   */
  // delay(100);
  //   btModule.print("hello from bluetooth");
}


