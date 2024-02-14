# Robocon Robot Alignment using Lidar and Raspberry Pi

## Overview

This repository contains the code and documentation for aligning a Robocon robot around a pole using a Lidar sensor, Raspberry Pi, and Arduino Mega. The alignment process involves obtaining raw data from the Lidar sensor, computing angle values on the Raspberry Pi, and serially transmitting them to the Arduino Mega, where the alignment algorithm is executed.

## Hardware Requirements

- Lidar Sensor
- Raspberry Pi
- Arduino Mega 2560

## Software Requirements

- Python (for Raspberry Pi code)
- Arduino IDE (for Arduino Mega code)
- Ubuntu 20.04 on Raspberry Pi

## Setup

1. Connect the Lidar sensor to the Raspberry Pi.
2. Connect the Raspberry Pi to the Arduino Mega using UART.
3. Upload the Arduino Mega code to the board.
4. Run the Raspberry Pi code to start obtaining Lidar data and computing angle values.

## File Structure

- `/raspberry_pi_code`[](): Contains the Python code for obtaining Lidar data and computing angle values.
- `/arduino_mega_code`: Contains the Arduino code for executing the alignment algorithm.
- `/docs`: Documentation related to the project.

## Usage

1. Navigate to the `/raspberry_pi_code` directory.
2. Run the Raspberry Pi code:
   ```bash
   python3 lidar_alignment.py
   
  ```
