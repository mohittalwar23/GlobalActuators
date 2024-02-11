#include <ESP32Firebase.h>

#define _SSID "YOUR_SSID"          
#define _PASSWORD "YOUR_PASSWORD"     
#define REFERENCE_URL "your_Firebase_project_reference_URL"  

Firebase firebase(REFERENCE_URL);

#define LED_PIN 21 // GPIO pin connected to the LED
#define TRIG_PIN 17
#define ECHO_PIN 16

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Connect to WiFi
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(_SSID);
  WiFi.begin(_SSID, _PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // No need to initialize Firebase here
}

void loop() {
  // Read LED state from Firebase
  String ledState = firebase.getString("led_state");  
  //your key that you set for led in firebase's realtime database for buzzer

  if (ledState == "on") {
    digitalWrite(LED_PIN, HIGH);
  } 
  else if (ledState == "off") {
    digitalWrite(LED_PIN, LOW);
  }

  // Ultrasonic sensor reading
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  float duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;

  Serial.println(distance);
  Serial.println(ledState);

  // Send ultrasonic sensor reading to Firebase
  //your key that you set for led in firebase's realtime database for distance
  firebase.setFloat("data_state", distance);

  delay(100); // Adjust delay as needed
}
