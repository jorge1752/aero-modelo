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
  pinMode(2, INPUT);
}

void loop() {
  int cliente = 1;
  int porta = 8;
  int estado = digitalRead(2);
  sprintf(msg, "%d%d%d", cliente, porta, estado);

  sprintf(debug, "Cliente: %d, Porta: %d, Estado: %d", cliente, porta, estado);
  Serial.println(debug);

  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  count++;
}

