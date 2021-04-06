//Transmitter Code (Glove) - Mert Arduino and Tech

#include <SPI.h>                      //bibliotheek communicatie modem
#include "RF24.h"                     //bibliotheek controle radio modem


uint8_t msg[5]; //hoeveelheid data te versturen)

bool radioNumber = 1;
bool role = true;  // true = TX role, false = RX role

uint8_t address[][6] = {"1Node", "2Node"}; //ontvangmodemadres

RF24 radio(9,10);                     //Modem verbonden met arduino: pin 9 en 10 verbonden met CE en CSN

//definieren van flexsensor input pins
int flex_5 = A5;
int flex_4 = A4;
int flex_3 = A3;
int flex_2 = A2;
int flex_1 = A1;

//definieren van variabele waarden flexsensor
int flex_5_val;
int flex_4_val;
int flex_3_val;
int flex_2_val;
int flex_1_val;


void setup(void){
  Serial.begin(115200);
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

void loop(void){

  flex_5_val = analogRead(flex_5); 
  flex_5_val = map(flex_5_val, 630, 730, 80, 20);
  
  flex_4_val = analogRead(flex_4);
  flex_4_val = map(flex_4_val, 520, 710, 70, 175);
 
  flex_3_val = analogRead(flex_3);
  flex_3_val = map(flex_3_val, 510, 680, 140, 10);
 
  flex_2_val = analogRead(flex_2);
  flex_2_val = map(flex_2_val, 580, 715, 90, 175);
  
  flex_1_val = analogRead(flex_1);
  flex_1_val = map(flex_1_val, 550, 700, 90, 175);

  
  msg[0] = flex_5_val;
  msg[1] = flex_4_val;
  msg[2] = flex_3_val;
  msg[3] = flex_2_val;
  msg[4] = flex_1_val;
  
  Serial.println (msg [0]);
  
  radio.write(msg, sizeof(msg));
}
