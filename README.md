# Design and Development of Dryer Temperature Control Using Proportional Integral Derivative (PID) Method

This project is the final undergraduate thesis by **Anwar**, focusing on the design and development of a **PID-based temperature control system** for a drying device. It integrates both hardware and software, utilizing **STM32** and **Arduino** microcontrollers to monitor and control the system in real-time.

---

## 📌 Project Description

The system is designed to maintain stable drying temperatures by controlling the speed of cooling fans through PID algorithms. It reads temperature values from sensors using the STM32 and sends them to the Arduino, which processes them and adjusts fan speed accordingly. The system aims to improve energy efficiency and drying consistency in an automated environment.

---

## 🔧 System Components

### 🔲 Hardware
- **STM32F103C8T6 (Blue Pill)** – Reads sensor values and sends data via Serial.
- **Arduino Nano** – Handles PID calculation and PWM output to fans.
- **Temperature Sensors** – Connected to STM32 to measure heat inside the dryer.
- **Cooling Fans** – Controlled using PWM to regulate temperature.
- **16x2 LCD with I2C Module** – Displays real-time temperature readings.
- **Relay Modules** – Controls fan power switching.
- **Power Supply 12V 40A** – Powers all fans and modules.
- **Moisture Sensors** – Optional inputs for future humidity-based control.
- **Push Buttons** – For manual inputs or resets.

---

## 🧠 System Architecture

- The STM32 reads temperature values from two different zones (`PB0` and `PB1`) and sends them as comma-separated values to the Arduino via UART.
- Arduino calculates the required PWM duty cycle using PID control.
- PWM outputs are sent to the fan motor drivers to increase or decrease fan speed.
- An LCD module displays temperature values for both zones.

---

## 🔍 PID Parameters

| Zone | Setpoint | Kp   | Ki   | Kd   |
|------|----------|------|------|------|
| PB0  | 39°C     | 7.6  | 1.2  | 11.4 |
| PB1  | 36°C     | 6.0  | 0.75 | 12.0 |


