
//This is the code for the send module 4

#include <SoftwareSerial.h>
//#include <AltSoftSerial.h>
#include <XBee.h>

SoftwareSerial mySerial(8, 9); // RX, TX

int currentAddress = 2;
int destinationAddress = 1;
int data = 111;
int originAddress = 4;
int packetNumber = 0;
 
//const int NUMBER_OF_FIELDS = 5;
int packetIndex = 0;
char packet[5];


void sendPacket(int destinationAddress, int originAddress, int data)
{
  Serial.print("H");
  Serial.print(destinationAddress);
  Serial.print(";");
  Serial.print(originAddress);
  Serial.print(";");
  Serial.print(data);
  Serial.print(";");
  Serial.print(packetNumber);
  Serial.println();
}

void readPacket()
{
 if(Serial.available())
 {
  destinationAddress = Serial.parseInt();
  //Serial.print(destinationAddress);
  originAddress = Serial.parseInt();
  //Serial.print(originAddress);
  data = Serial.parseInt();
  packetNumber = Serial.parseInt();
  //Serial.print(data);
  //Serial.println();
 }
//  if(mySerial.available() > 0)
//  {
//    for(packetIndex = 0; packetIndex < 5; packetIndex++)
//    {
//      char inChar = mySerial.read();
//      mySerial.println(inChar);
//      packet[packetIndex] = inChar;
//      //mySerial.println(packetIndex);
//    }
//    destinationAddress = readDestinationAddress();
//    originAddress = readOriginAddress();
//    data = readData();
    //packetIndex = 0;
    
//    mySerial.print(destinationAddress);
//    // mySerial.print(";");
//    mySerial.print(originAddress);
//    //mySerial.print(":");
//    mySerial.print(data);
//    //mySerial.print(";");
//    mySerial.println();
  
}


int readDestinationAddress()
{
  destinationAddress = packet[0];
}

int readOriginAddress()
{
  originAddress = packet[1];
}

int readData ()
{
  data = (packet[4]) + (packet[3] * 10) + (packet[2] * 100);
}


void checkDestination()
{
  readPacket();
  if(destinationAddress != currentAddress)
  {
   sendPacket(destinationAddress, originAddress, data);
  }
}




void setup()  
{
  Serial.begin(9600);  
  mySerial.begin(9600);
 
}

void loop() 
{

  //readPacket();
  //sendPacket(destinationAddress, originAddress, data);
   
  
  //mySerial.println("MRMSS MODULE 4 TEST:");
  
//    if(Serial.available() > 0){
//      Serial.println("Data from port one:");
//      while (Serial.available() > 0) 
//      {
//        char inByte = Serial.read();
//        Serial.write(inByte);
//      }
// 
//       Serial.println();
//      }
  checkDestination();
  //sendPacket(destinationAddress, originAddress, data);
  
  
  
  //delay(1000);
  

 
}
