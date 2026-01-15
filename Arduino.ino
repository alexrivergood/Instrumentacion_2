#include <SPI.h>
#include <math.h>
#define PI 3.1415926535897932384626433832795

const byte csPin           = 2;
const int  maxPositions    = 256;
const long rAB             = 107800;
const byte rWiperh         = 189;
const byte rWiperl         = 220;
const byte pot0            = 0x11;
const byte pot1            = 0x12;
const byte potBoth         = 0x13;
const byte pot0Shutdown    = 0x21;
const byte pot1Shutdown    = 0x22;
const byte potBothShutdown = 0x23;

double Clp = pow(10,-8);
double Chp = 2.2*pow(10,-8);
char modo;
float A = 1.25;
float Q = 0.5;
float m = 2;
float Rhref = 120000;
float Rlref = 100000000;
const long R1 = 120000;
float f0, Rhp, Rlp, Rph, Rpl;
int bitph, bitpl;
bool correcto = false;

void setup() {

  Serial.begin(9600);

  digitalWrite(csPin, HIGH);
  pinMode(csPin, OUTPUT);
  SPI.begin();

  Serial.println();
  Serial.println("Que rango de frecuencias quieres escuchar?");
  Serial.println("1: Graves");
  Serial.println("2: Medios");
  Serial.println("3: Agudos");
  Serial.println("4: Muy agudos");
  Serial.println("5: Personalizable");
}

void loop() {

  if (!Serial.available()) return;
  modo = Serial.read();

  correcto = false;

  switch (modo) {

    case '1':
      f0 = 155;
      correcto = true;
      break;

    case '2':
      f0 = 1125;
      correcto = true;
      break;

    case '3':
      f0 = 3000;
      correcto = true;
      break;

    case '4':
      f0 = 10000;
      correcto = true;
      break;

    case '5':
      Serial.println("Introduce el valor de la frecuencia sobre el cual te quieres centrar (de 155 a 20000 Hz)");
      while (!Serial.available());
      f0 = Serial.parseFloat();
      correcto = true;
      break;

    default:
      Serial.println("Escoge una de las opciones");
      break;
  }

  if (correcto) {

    Rhp = Q / (2 * PI * f0 * A * Clp);
    Rlp = Rhp * m * A;

    Rph = 1.0 / (1.0 / Rhp - 1.0 / Rhref);
    Rpl = Rlp;

    bitph = (int)((Rph - rWiperh) * 255.0 / rAB);
    bitpl = (int)((Rpl - rWiperl) * 255.0 / rAB);

    bitph = constrain(bitph, 0, 255);
    bitpl = constrain(bitpl, 0, 255);

    setPotWiper(pot0, bitph);
    delay(500);
    setPotWiper(pot1, bitpl);
    delay(500);
  }

  while (Serial.available()) Serial.read();

  Serial.println();
  Serial.println("Que rango de frecuencias quieres escuchar?");
  Serial.println("1: Graves");
  Serial.println("2: Medios");
  Serial.println("3: Agudos");
  Serial.println("4: Muy agudos");
  Serial.println("5: Personalizable");
}

void setPotWiper(int addr, int pos) {

  pos = constrain(pos, 0, 255);

  digitalWrite(csPin, LOW);
  SPI.transfer(addr);
  SPI.transfer(pos);
  digitalWrite(csPin, HIGH);

  long resistanceWB = ((rAB * pos) / maxPositions);

  if (addr == pot0) {
    Serial.print("POT0: ");
  } else if (addr == pot1) {
    Serial.print("POT1: ");
  }

  Serial.print(pos);
  Serial.print(" ");
  Serial.println(resistanceWB);
}
