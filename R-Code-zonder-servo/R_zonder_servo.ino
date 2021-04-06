#include <SPI.h>      //bibliotheek communicatie modem
#include "RF24.h"     //bibliotheek controle radio modem

RF24 radio(9,10);    //Modem verbonden met arduino: pin 9 en 10 verbonden met CE en CSN

uint8_t address[][6] = {"1Node", "2Node"};
uint8_t msg[5];

bool radioNumber = 0; // 0 uses address[0] to transmit, 1 uses address[1] to transmit
bool role = false;  // true = TX role, false = RX role

void setup() {

  Serial.begin (115200);
  while (!Serial) {
    // some boards need to wait to ensure access to serial over USB
  }
  radio.begin ();
  radio.setPALevel(RF24_PA_MAX);  // RF24_PA_MAX is default.
   radio.openWritingPipe(address[radioNumber]);     // always uses pipe 0
    radio.openReadingPipe(1, address[!radioNumber]); // using pipe 1
 if (role) {
    radio.stopListening();  // put radio in TX mode
  } else {
    radio.startListening(); // put radio in RX mode
  }
  }

void loop() {
   uint8_t pipe;
  if(radio.available(&pipe)){
    uint8_t msg[5]; 
    radio.read(msg, sizeof(msg));
    
    Serial.println (msg [1]);

  }
}
