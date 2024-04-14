#include <SoftwareSerial.h>

// Pin Definitions
const int moistureSensorPin = A0; // Analog pin for moisture sensor
const int motorPin = 9; // Digital pin for controlling the water pump motor
const int manualWateringButtonPin = 2; // Digital pin for manual watering button

// Thresholds and settings
const int moistureThreshold = 700; // Moisture threshold for automatic watering
const unsigned long wateringDuration = 5000; // Duration of watering in milliseconds (5 seconds)
const int bluetoothTxPin = 3; // Bluetooth TX pin
const int bluetoothRxPin = 4; // Bluetooth RX pin
const char endMarker = '\n'; // End marker for incoming Bluetooth messages

// Variables
bool isManualWatering = false;
SoftwareSerial bluetoothSerial(bluetoothTxPin, bluetoothRxPin);

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);
  bluetoothSerial.begin(9600);

  // Set pin modes
  pinMode(moistureSensorPin, INPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(manualWateringButtonPin, INPUT_PULLUP);

  // Set initial motor state
  digitalWrite(motorPin, LOW);
}

void loop() {
  // Read moisture sensor value
  int moistureValue = analogRead(moistureSensorPin);
  Serial.print("Moisture: ");
  Serial.println(moistureValue);

  // Check if manual watering button is pressed
  if (digitalRead(manualWateringButtonPin) == LOW) {
    isManualWatering = true;
  } else {
    isManualWatering = false;
  }

  // Check if moisture is below threshold for automatic watering
  if (!isManualWatering && moistureValue < moistureThreshold) {
    waterPlants();
  }

  // Check for incoming Bluetooth commands
  while (bluetoothSerial.available() > 0) {
    char receivedChar = bluetoothSerial.read();
    if (receivedChar == 'W') { // Watering command
      waterPlants();
    }
  }
}

void waterPlants() {
  // Turn on water pump motor
  digitalWrite(motorPin, HIGH);
  Serial.println("Watering...");
  delay(wateringDuration); // Watering duration
  // Turn off water pump motor
  digitalWrite(motorPin, LOW);
}

void serialEvent() {
  static String receivedMessage = "";
  while (bluetoothSerial.available()) {
    char inChar = (char)bluetoothSerial.read();
    if (inChar != endMarker) {
      receivedMessage += inChar;
    } else {
      processMessage(receivedMessage);
      receivedMessage = "";
    }
  }
}

void processMessage(String message) {
  if (message == "MANUAL_ON") {
    isManualWatering = true;
  } else if (message == "MANUAL_OFF") {
    isManualWatering = false;
  }
}
