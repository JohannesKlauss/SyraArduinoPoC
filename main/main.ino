#include <TM1638.h>
#include <WebUSB.h>

#define PIN_DIO 10
#define PIN_CLK 9
#define PIN_STB 8

WebUSB WebUSBSerial(1 /* https:// */, "webusb.github.io/arduino/demos/console");

#define Serial WebUSBSerial

const int ledPin = 13;
const int analogPin = A0; // potentiometer wiper (middle terminal) connected to analog pin 3
                    // outside leads to ground and +5V
int val = 0;  // variable to store the value read

TM1638 module(PIN_DIO, PIN_CLK, PIN_STB);

// the setup routine runs once when you press reset:
void setup() {
  while (!Serial) {
    ;
  }
  
  Serial.begin(9600);
  Serial.write("Sketch begins.\r\n> ");
  Serial.flush();
  
  pinMode(ledPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  if (Serial && Serial.available()) {
    int byte = Serial.read();
    Serial.write(byte);
    if (byte == 'q') {
      Serial.write("\r\nTurning LED on.");
      module.setLEDs(1);
    } else if (byte == 'w') {
      Serial.write("\r\nTurning LED off.");
      module.setLEDs(0);
    }
    Serial.write("\r\n> ");
    Serial.flush();
  }

  val = analogRead(analogPin);  // read the input pin
  
  module.setDisplayToDecNumber(val, 0b00000000, false);

  
}
