#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
const uint64_t pipe[2] = { 0xB3B4B5B6CD , 0xB3B4B5B6F1};
//uint8_t p[2];//={'1','2'};
//p[0] = 0xB3B4B5B6CD & 0xfffff;
//uint8_t pipe_num;
//p[0] = 'CD'; p[1] = 'F1';
//const uint64_t pipe[1] = {0xF0F0F0F0E1LL};
RF24 radio(9, 10);
int rec[1] = {2};
char red[32];
//byte p[2];
uint8_t pipe_num;

void setup()
{
  Serial.begin(57600);
  radio.begin();
  delay(100);
  //radio.setAutoAck(true);
  radio.setAutoAck(1,true);//delay(100);
  radio.setAutoAck(2,true);
  radio.enableAckPayload();//to enable CUSTOM payloads
  radio.enableDynamicPayloads();// seems to be very necessary for sending out ack data to tx nodes.
  radio.startListening();
  radio.openReadingPipe(1, pipe[0]);
  radio.openReadingPipe(2, pipe[1]);
  radio.startListening();
  radio.setRetries(15, 15);
  Serial.println(pipe_num);
}
void loop() {//Serial.println(pipe_num);
  //uint8_t pipe_num;
  if ( radio.available(&pipe_num) ) {
    if(pipe_num == 1)
    {
      //Serial.print("its one !!  ");
      Serial.println(pipe_num);
    }
    else if(pipe_num == 2)
    {
      //Serial.print("its two  ");
      Serial.println(pipe_num);
    }
      radio.writeAckPayload(pipe_num , rec, sizeof(int) );
      radio.read( red, sizeof(red) );
    rec[0] += 2;
    //Serial.print("data got is : ");
    Serial.println(red);
    }
  /*else if(radio.available(&pipe_num[1]))
    {
      Serial.println("its two !!");
      radio.writeAckPayload(2, rec, sizeof(int) );
      radio.read( red, sizeof(red) );
    rec[0] += 2;
    Serial.print("data got is : ");
    Serial.println(red);
    }
    //radio.writeAckPayload(2 , rec, sizeof(int) );
    //radio.writeAckPayload(2 , rec, sizeof(int) );
    /*radio.read( red, sizeof(red) );
    rec[0] += 2;
    Serial.print("data got is : ");
    Serial.println(red);*/
  }
  /*else if ( radio.available(pipe_num) ) {
    radio.writeAckPayload( 2, rec, sizeof(int) );
    radio.read( red, sizeof(red) );
    rec[0] += 2;
    Serial.print("character got is : ");
    Serial.println(red);
  }*/
//}
