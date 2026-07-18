#include <Servo.h>


Servo servo;


// Pines
const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 6;


const int gasPin = A0;
const int humedadPin = A1;
const int ldrPin = A2;


const int buzzer = 8;
const int led = 5;


// Umbrales
const int umbralGas = 150;       // Suena con poca cantidad de gas
const int umbralHumedad = 500;
const int umbralLuz = 400;


void setup() {


  Serial.begin(9600);


  servo.attach(servoPin);
  servo.write(0);


  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
}


void loop() {


  // ---------- Sensor ultrasónico ----------
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);


  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);


  digitalWrite(trigPin, LOW);


  long duracion = pulseIn(echoPin, HIGH);
  int distancia = duracion * 0.034 / 2;


  if (distancia > 0 && distancia <= 20) {
    servo.write(90);
    delay(3000);
    servo.write(0);
  }


  // ---------- Sensor de gas ----------
  int gas = analogRead(gasPin);


  // ---------- Sensor de humedad ----------
  int humedad = analogRead(humedadPin);


  // ---------- Fotoresistencia ----------
  int luz = analogRead(ldrPin);


  // LED
  if (luz < umbralLuz) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }


  // Buzzer
  if (gas >= umbralGas || humedad < umbralHumedad) {
    tone(buzzer, 1000);
  } else {
    noTone(buzzer);
  }


  // Mostrar valores
  Serial.print("Gas: ");
  Serial.print(gas);
  Serial.print("  Humedad: ");
  Serial.print(humedad);
  Serial.print("  Luz: ");
  Serial.print(luz);
  Serial.print("  Distancia: ");
  Serial.println(distancia);


  delay(200);
}
