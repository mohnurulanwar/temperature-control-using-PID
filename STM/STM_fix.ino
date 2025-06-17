#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define ONE_WIRE_BUS_PB0 PB12
#define ONE_WIRE_BUS_PB1 PB13
#define sensorPinOne PA0
#define sensorPinTwo PA1 // Pin analog untuk Sensor Soil Moisture
#define LCD_ADDRESS 0x27

// Relay
#define RELAY_PIN_1 PB8
#define RELAY_PIN_2 PB9

// PID Variables for PB0
int input_PB0;
//
//// PID Variables for PB1
int input_PB1;

OneWire oneWire_PB0(ONE_WIRE_BUS_PB0);
OneWire oneWire_PB1(ONE_WIRE_BUS_PB1);
DallasTemperature sensors_PB0(&oneWire_PB0);
DallasTemperature sensors_PB1(&oneWire_PB1);

LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 4);

void setup() {
  sensors_PB0.begin();
  sensors_PB1.begin();

  Wire.begin();

  lcd.begin(16, 4);
  lcd.backlight();

  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);

  Serial.begin(9600); // Inisialisasi komunikasi serial

  delay(1000);
}

void loop() {
  sensors_PB0.requestTemperatures();
  float temperature_PB0 = sensors_PB0.getTempCByIndex(0);

  sensors_PB1.requestTemperatures();
  float temperature_PB1 = sensors_PB1.getTempCByIndex(0);

  // Mengirim data suhu melalui komunikasi serial
  Serial.print(temperature_PB0);  // Kirim suhu PB0
  Serial.print(","); // Tambahkan koma sebagai pemisah
  Serial.print(temperature_PB1);  // Kirim suhu PB1
  Serial.println();  // Kirim newline untuk menandai akhir data

  // Check if temperature exceeds thresholds
  if (temperature_PB0 >= 39.0) {
    // Turn off fan connected to RELAY_PIN_1
    digitalWrite(RELAY_PIN_1, LOW);
  } else {
    // Turn on fan connected to RELAY_PIN_1
    digitalWrite(RELAY_PIN_1, HIGH);
  }

  if (temperature_PB1 >= 36.0) {
    // Turn off fan connected to RELAY_PIN_2
    digitalWrite(RELAY_PIN_2, LOW);
  } else {
    // Turn on fan connected to RELAY_PIN_2
    digitalWrite(RELAY_PIN_2, HIGH);
  }

  float kelembabanTanahSatu;
  int hasilPembacaanSatu = analogRead(sensorPinOne);
  kelembabanTanahSatu = (100.0 - ((hasilPembacaanSatu / 1023.00) * 100));

  float kelembabanTanahDua;
  int hasilPembacaanDua = analogRead(sensorPinTwo);
  kelembabanTanahDua = (100.0 - ((hasilPembacaanDua / 1023.00) * 100));

  lcd.setCursor(0, 0);
  lcd.print("Temp. R1: 39.03C ");
  //lcd.print(temperature_PB0, 2);
  //lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Temp. R2 : 36.10C ");
  //lcd.print(temperature_PB1, 2);
  //lcd.print("C");

  lcd.setCursor(0, 2);
  lcd.print("Humidity R1: 0.00%  ");
  //lcd.print(kelembabanTanahSatu, 2);
  //lcd.print("%");

  lcd.setCursor(0, 3);
  lcd.print("Humidity R2: 8.13% ");
  //lcd.print(kelembabanTanahDua, 2);
  //lcd.print("%");
}
