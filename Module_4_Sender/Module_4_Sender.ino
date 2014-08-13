
//This is the code for the send module 4

#include <SoftwareSerial.h>
//#include <AltSoftSerial.h>
#include <XBee.h>

SoftwareSerial mySerial(8, 9); // RX, TX

int currentAddress = 4;
int destinationAddress = 12;
int data = 314;
int originAddress = 4;
int packetNumber = 0;
 
const int NUMBER_OF_FIELDS = 5;
int packetIndex = 0;
int packet[NUMBER_OF_FIELDS]= {4,4,4,5,6};


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
  packetNumber++;
}

void readPacket()
{
  if(mySerial.available())
  {
    for(packetIndex = 0; packetIndex < 5; packetIndex++)
    {
      char inChar = Serial.read();
      packet[packetIndex] = inChar;
      packetIndex++;
    }
    destinationAddress = readDestinationAddress();
    originAddress = readOriginAddress();
    data = readData();
  } 
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
  readData();
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
  //mySerial.println("MRMSS MODULE 4 TEST:");
  sendPacket(destinationAddress, originAddress, data);
  
  
  
  delay(1000);
  

 
}
