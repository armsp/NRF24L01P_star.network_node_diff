#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
int rec[1] = {5};
float time;
bool go_to_tx_mode = false;
char input[32] = "";
RF24 radio(9, 10);
const uint64_t pipe[1] = {0xB3B4B5B6CD};

void setup()
{
  Serial.begin(57600);
  radio.begin();
  delay(100);
  radio.setAutoAck(1,true);
  radio.enableAckPayload();
  radio.enableDynamicPayloads();
  radio.stopListening();
  radio.openWritingPipe(pipe[0]);
  radio.setRetries(15, 15);
}

void loop() {

  if (go_to_tx_mode) {
    if (radio.write(input, sizeof(input)))
    {
      time = micros();
      go_to_tx_mode = false;
      //Serial.print( input );
      //Serial.println("...tx success");
      if (radio.isAckPayloadAvailable())
      {
        radio.read(rec, sizeof(int));
        Serial.print(micros() - time);
        Serial.print(".......received ack payload is : ");
        Serial.println(rec[0]);
      }
      else
      {
        go_to_tx_mode = false; //doing this completely shuts down the transmitter if an ack payload is not received !!
        Serial.println("status has become false so stop here....");
      }
    }
  }
  if (Serial.available())
  {
    int len = Serial.readBytesUntil('\n', input, 31);
    input[len] = '\0';
    go_to_tx_mode = true;
  }
}
