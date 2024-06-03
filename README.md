# Effective Water Management System

This project is an effective water management system using Arduino, which monitors soil moisture and waters plants when the moisture level drops below a certain threshold. It also supports manual watering via a button or Bluetooth commands.

## Components

- Arduino (Uno, Nano, or compatible)
- Soil Moisture Sensor
- Water Pump Motor
- Relay Module (for motor control)
- Bluetooth Module (HC-05 or HC-06)
- Push Button (for manual watering)
- Jumper wires

## Pin Connections

- **Soil Moisture Sensor**:
  - Analog Output to `A0` on Arduino
- **Water Pump Motor**:
  - Controlled via Relay, connected to `9` on Arduino
- **Manual Watering Button**:
  - Connected to `2` on Arduino with internal pull-up resistor
- **Bluetooth Module**:
  - TX to `3` on Arduino (via SoftwareSerial)
  - RX to `4` on Arduino (via SoftwareSerial)

## Installation

1. Clone this repository:
   ```sh
   git clone https://github.com/aravind1000/Effective_Water_Management_System.git
   cd Effective_Water_Management_System

2. Follow the instructions uploaded in this project
