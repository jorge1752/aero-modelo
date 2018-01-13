 // Módulo transmissor utilizando o FS1000A.

#include <RH_ASK.h>
#include <SPI.h>

// Transmissão utilizando o pino D4.
RH_ASK driver(2000, 0, 4);

int count = 0;
char msg[RH_ASK_MAX_MESSAGE_LEN];

char debug[100];

void setup() {
  Serial.begin(9600);
  Serial.print("Iniciando...");
  if (!driver.init())
    Serial.println(" Erro!");
  else
    Serial.println("Ok!");
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  int cliente = 1;
  int cliente2 = 2;
  int porta1 = 8;
  int porta2 = 9;
  int estado = digitalRead(2);
  int estado2 = digitalRead(3);
  int sensorY2 = analogRead(A2);
  int sensorX2 = analogRead(A3);
  int sensorY1 = analogRead(A0);
  int sensorX1 = analogRead(A1);
  // print out the value you read:
  Serial.println(sensorY1);
  Serial.println(sensorX1);
  Serial.println(sensorY2);
  Serial.println(sensorX2);
  delay(1000);
  sprintf(msg, "%d%d%d", cliente, porta1, estado);

  sprintf(debug, "Cliente1: %d, Porta1: %d, Estado: %d", cliente, porta1, estado);
  sprintf(debug, "Cliente2: %d, Porta2: %d, Estado2: %d", cliente2, porta2, estado2);
  Serial.println(debug);

  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  count++;
}

