//connection for blynk software
#define BLYNK_TEMPLATE_ID "TMPL3yQKbRHih"
#define BLYNK_TEMPLATE_NAME "GAS"
#define BLYNK_AUTH_TOKEN "kwnywz4dwqeEViCdp9zefrNRrVkjF4gS"

//library import for the project
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#define BLYNK_PRINT Serial

// WiFi
char ssid[] = "Sunny";
char pass[] = "12345678";

// ---------------- MQ Sensors ----------------
#define MQ2_PIN 34
#define MQ135_PIN 35

// ---------------- ULTRASONIC ----------------
#define TRIG_PIN 17
#define ECHO_PIN 18

#define COLLISION_DISTANCE 20   // cm
long distance;

//  ---------------- Motor Pins ----------------
#define IN1 27
#define IN2 26
#define IN3 25
#define IN4 33
#define ENA 14
#define ENB 12

// ---------------- DHT Setup ----------------
#define DHTPIN 4
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

int speedValue = 200;

String camURL = "";

// -------- Motor Speed --------
void motorSpeed(int spd) {
  speedValue = spd;
  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);
}

// -------- Motor Directions --------
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// -------- Distance Function --------
void getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
   distance = duration * 0.034 / 2;
   Serial.print("Distance: ");
   Serial.println(distance);

   Blynk.virtualWrite(V11,distance);

    // -------- Collision Detection --------
  if (distance > 0 && distance < COLLISION_DISTANCE) {
    stopMotors();
    Serial.println("Obstacle detected! Stopping...");
  }
}

// -------- DHT Function --------
void sendDHTData() {
  float humidity = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(humidity) || isnan(t)) {
    Serial.println("Failed to read from DHT!");
    return;
  }

  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print(" °C  Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Blynk.virtualWrite(V0, t);

  if (t>45) {
    Blynk.virtualWrite(V1,"⚠ DANGER ,VERY HOT");
  } else if(t > 25 && t < 35){
    Blynk.virtualWrite(V1,"⚠ MODERATE TEMPERATURE ");
  }else if(t >15 && t < 25){
    Blynk.virtualWrite(V1,"✅ NORMAL TEMPERATURE ");
  }else if(t <15){
    Blynk.virtualWrite(V1,"⚠ DANGER,VERY COOL ");
  }
}

void sendGASValue(){
  int MQ135_gasvalue = analogRead(MQ135_PIN);
  int MQ2_gasvalue = analogRead(MQ2_PIN);
 
  Serial.print("MQ135 Value: ");
  Serial.println(MQ135_gasvalue);
  Serial.print("MQ2 Value: ");
  Serial.println(MQ2_gasvalue);

  //*********************//MQ135//********************//
  
  if (MQ135_gasvalue > 800 ) {   // Threshold (adjust this)
    Blynk.virtualWrite( V2,"⚠ DANGER ");
    Serial.println("⚠ DANGER ");
    
  } else if(MQ135_gasvalue > 600 && MQ135_gasvalue < 800 ) {
    Serial.println(" ⚠ HIGH METHANE GAS DETECTED ");
    Blynk.virtualWrite(V2," ⚠ HIGH METHANE GAS DETECTED ");
    
  }else if(MQ135_gasvalue > 300 && MQ135_gasvalue < 600 ){
    Serial.println(" ⚠ MEDIUM METHANE GAS DETECTED  ");
    Blynk.virtualWrite(V2," ⚠ MEDIUM METHANE GAS DETECTED  ");
    
  }else if(MQ135_gasvalue > 100 && MQ135_gasvalue < 300){
    Serial.println(" ⚠ LOW METHANE GAS DETECTED ");
    Blynk.virtualWrite(V2," ⚠ LOW METHANE GAS DETECTED ");
    
  }else{
    Serial.println(" ✅ METHANE Gas Level Normal ");
    Blynk.virtualWrite(V2," ✅ METHANE Gas Level Normal ");
  }

  //*********************//MQ2//********************//
  
  if (MQ2_gasvalue > 400 ) {   // Threshold (adjust this)
    Serial.println("⚠ DANGER ");
    Blynk.virtualWrite(V3,"⚠ DANGER ");
   
  } else if(MQ2_gasvalue > 300 && MQ2_gasvalue < 400 ) {
    Serial.println(" ⚠ HIGH C02 GAS DETECTED ");
   Blynk.virtualWrite(V3," ⚠ HIGH C02 GAS DETECTED ");
    
  }else if(MQ2_gasvalue > 200 && MQ2_gasvalue < 300 ){
    Serial.println(" ⚠ MEDIUM CO2 GAS DETECTED  ");
    Blynk.virtualWrite(V3," ⚠ MEDIUM CO2 GAS DETECTED  ");
    
  }else if(MQ2_gasvalue > 100 && MQ2_gasvalue < 200){
    Serial.println(" ⚠ LOW CO2 GAS DETECTED ");
    Blynk.virtualWrite(V3," ⚠ LOW CO2 GAS DETECTED ");
    
  }else{
    Serial.println(" ✅ C02 Gas Level Normal ");
    Blynk.virtualWrite(V3," ✅ CO2 Gas Level Normal ");
  }

  delay(1000);
}

// -------- Blynk Buttons --------
BLYNK_WRITE(V4) { if (param.asInt()) forward(); }
BLYNK_WRITE(V5) { if (param.asInt()) backward(); }
BLYNK_WRITE(V7) { if (param.asInt()) left(); }
BLYNK_WRITE(V6) { if (param.asInt()) right(); }
BLYNK_WRITE(V8) { if (param.asInt()) stopMotors(); }
BLYNK_WRITE(V9) { motorSpeed(param.asInt()); }

void receiveCamLink() {

  if (Serial2.available()) {
    camURL = Serial2.readStringUntil('\n');
    camURL.trim();

    Serial.print("Received Camera Link: ");
    Serial.println(camURL);

    Blynk.virtualWrite(V12, camURL);   // Send to Blynk
  }
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(MQ2_PIN, INPUT);
  pinMode(MQ135_PIN, INPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);


  dht.begin();
  stopMotors();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, sendDHTData);
  timer.setInterval(1000L, sendGASValue);
  timer.setInterval(1000L, getDistance);
  timer.setInterval(2000L, receiveCamLink);

}

void loop() {
  Blynk.run();
  timer.run();
}
