// Módulo transmissor utilizando o FS1000A.

// Comandos:
//  joystick esquerdo:
//    frente/trás: 
//    esquerda/direita:
//    botão:
//  joystick direito:
//    frente/trás: 
//    esquerda/direita:
//    botão:

#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

RF24 radio(7, 10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int dataToSend[6];

void setup() {
  Serial.begin(9600);
  Serial.print("Iniciando...");

  radio.begin();
  radio.setAutoAck(false);
  radio.setChannel(108); //108 - 2.508 Ghz //0-124 2.4gHz-2.5gHz
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(pipe);
  
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
}

void loop() {
  int estado = digitalRead(2);
  int estado2 = digitalRead(3);
  int sensorY2 = analogRead(A2);
  int sensorX2 = analogRead(A3);
  int sensorY1 = analogRead(A0);
  int sensorX1 = analogRead(A1);

  dataToSend[0] = estado;     
  dataToSend[1] = estado2;    
  dataToSend[2] = sensorY2;     
  dataToSend[3] = sensorX2;    
  dataToSend[4] = sensorY1;    
  dataToSend[5] = sensorX1;
  radio.write(dataToSend, sizeof(dataToSend));
}
