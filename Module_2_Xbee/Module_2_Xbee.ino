
//This is the code for the send module 4

#include <SoftwareSerial.h>
//#include <AltSoftSerial.h>
#include <XBee.h>

SoftwareSerial mySerial(8, 9); // RX, TX
XBee xbee = XBee();

int currentAddress = 1;
int destinationAddress = 1;
int data = 111;
int originAddress = 4;
int packetNumber = 0;
 
//const int NUMBER_OF_FIELDS = 5;
//int packetIndex = 0;
//char packet[5];

uint8_t mrmssPacket[4] = {destinationAddress, originAddress, data, packetNumber};

XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x40b69efe);
Tx64Request tx = Tx64Request(addr64, mrmssPacket, sizeof(mrmssPacket));
TxStatusResponse txStatus = TxStatusResponse();

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


//int readDestinationAddress()
//{
//  destinationAddress = packet[0];
//}
//
//int readOriginAddress()
//{
//  originAddress = packet[1];
//}
//
//int readData ()
//{
//  data = (packet[4]) + (packet[3] * 10) + (packet[2] * 100);
//}


void checkDestination()
{
  readPacket();
  if(destinationAddress != currentAddress)
  {
   sendPacket(destinationAddress, originAddress, data);
  }
  else if(destinationAddress == currentAddress)
  {
    Serial.println("The packet has arrived!");
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
}

void populateXbeeData()
{
  mrmssPacket[0] = destinationAddress;
  mrmssPacket[1] = originAddress;
  mrmssPacket[2] = data;
  mrmssPacket[3] = packetNumber;    
}


void setup()  
{
  Serial.begin(9600);  
  mySerial.begin(9600);
  xbee.setSerial(mySerial);
 
}

void loop() 
{
  checkDestination();
  
  //populate xbee packet
  populateXbeeData();
  delay(1000);
  xbee.send(tx);
  
  
    if (xbee.readPacket(5000)) {        
 
    if (xbee.getResponse().getApiId() == TX_STATUS_RESPONSE) {
      xbee.getResponse().getZBTxStatusResponse(txStatus);
      if (txStatus.getStatus() == SUCCESS) {
        // success.  time to celebrate
        //flashLed(roflLed, 5, 50);
        Serial.println("Message confirmation recieved!");
      } 
      else {
        // the remote XBee did not receive our packet. is it powered on?
        //flashLed(roflLed, 3, 500);
        Serial.println("Did not recieve confirmation");
      }
    }      
    } 
    else if (xbee.getResponse().isError()) {
      //nss.print("Error reading packet.  Error code: ");  
      //nss.println(xbee.getResponse().getErrorCode());
      // or flash error led
      Serial.println("Error recieved");
    } 
    else {
      // local XBee did not provide a timely TX Status Response.  Radio is not configured properly or connected
      //flashLed(roflLed, 2, 50);
      Serial.println("last error?");
    }
  
  


  

 
}
