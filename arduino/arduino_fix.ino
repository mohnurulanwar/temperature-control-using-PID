#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ADDRESS 0x27

// Variables for temperature readings
float temperature_PB0;
float temperature_PB1;

// Constants for PID tuning
const double Kp_PB0 = 7.6;
const double Ki_PB0 = 1.2;
const double Kd_PB0 = 11.4;
const double setpoint_PB0 = 39.0;
 
const double Kp_PB1 = 6;
const double Ki_PB1 = 0.75;
const double Kd_PB1 = 12;
const double setpoint_PB1 = 36.0;

// Variables for PID calculations
double input_PB0;
double prevInput_PB0 = 0.0;
double integral_PB0 = 0.0;

double input_PB1;
double prevInput_PB1 = 0.0;
double integral_PB1 = 0.0;

// Define PWM output pins
#define PWM_PIN_1 9
#define PWM_PIN_2 10

LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 4);

void setup() {
  Wire.begin();

  lcd.begin(16, 4);
  lcd.backlight();

  pinMode(PWM_PIN_1, OUTPUT);
  pinMode(PWM_PIN_2, OUTPUT);

  Serial.begin(9600); // Inisialisasi komunikasi serial
  delay(1000);
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    int commaIndex = input.indexOf(',');

    if (commaIndex != -1) {
      String temp_PB0_str = input.substring(0, commaIndex);
      String temp_PB1_str = input.substring(commaIndex + 1);

      temperature_PB0 = temp_PB0_str.toFloat();
      temperature_PB1 = temp_PB1_str.toFloat();

      // Calculate PID for PB0
      input_PB0 = temperature_PB0;
      double error_PB0 = setpoint_PB0 - input_PB0;
      integral_PB0 += error_PB0;
      double derivative_PB0 = input_PB0 - prevInput_PB0;

      double output_PB0 = Kp_PB0 * error_PB0 + Ki_PB0 * integral_PB0 + Kd_PB0 * derivative_PB0;
      prevInput_PB0 = input_PB0;

      // Calculate PID for PB1
      input_PB1 = temperature_PB1;
      double error_PB1 = setpoint_PB1 - input_PB1;
      integral_PB1 += error_PB1;
      double derivative_PB1 = input_PB1 - prevInput_PB1;

      double output_PB1 = Kp_PB1 * error_PB1 + Ki_PB1 * integral_PB1 + Kd_PB1 * derivative_PB1;
      prevInput_PB1 = input_PB1;

      // Constrain output values to the range 0-255 (PWM)
      output_PB0 = constrain(output_PB0, 0, 255);
      output_PB1 = constrain(output_PB1, 0, 255);

      // Update PWM outputs
      analogWrite(PWM_PIN_1, output_PB0);
      analogWrite(PWM_PIN_2, output_PB1);

      // Print PWM values to Serial Monitor
      Serial.print("PWM PB0: ");
      Serial.println(output_PB0);
      Serial.print("PWM PB1: ");
      Serial.println(output_PB1);

      // Display values on LCD

      Serial.print("Temp PB0: ");
      Serial.print(temperature_PB0, 2);
      Serial.print("C");

      Serial.print("Temp PB1: ");
      Serial.print(temperature_PB1, 2);
      Serial.print("C");
    }
  }
}
