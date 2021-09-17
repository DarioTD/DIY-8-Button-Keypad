/*
 
Copyright (c) 2019, Charles Garcia
Copyright (c) 2021, Dario Tabares
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the DIY-8-Button-Keypad project.

*/

#include <Keyboard.h>
#include <Bounce2.h>

// Change if adding more or less buttons
#define NUMKEYS 2

// Edit the buttons you want pressed here
#define KEY_1 'z'
#define KEY_2 'x'

// Pins used by the buttons
#define PIN_1 7
#define PIN_2 8

// Pins used by the RGB LEDs
#define PIN_LED_1R 3
#define PIN_LED_1CA 4
#define PIN_LED_1G 5
#define PIN_LED_1B 6

#define PIN_LED_2R 13
#define PIN_LED_2CA 12
#define PIN_LED_2G 11
#define PIN_LED_2B 10

// Arrays used for the for-loop sections of this program
const byte pinArray[NUMKEYS] = {PIN_1, PIN_2};

const byte keyArray[NUMKEYS] = {KEY_1, KEY_2};

const byte ledArrayR[NUMKEYS] = {PIN_LED_1R, PIN_LED_2R};
const byte ledArrayCA[NUMKEYS] = {PIN_LED_1CA, PIN_LED_2CA};
const byte ledArrayG[NUMKEYS] = {PIN_LED_1G, PIN_LED_2G};
const byte ledArrayB[NUMKEYS] = {PIN_LED_1B, PIN_LED_2B};

const byte LED_1R = 98;   //  98 = 1.9V
const byte LED_1G = 159;  // 159 = 3.1V
const byte LED_1B = 153;  // 153 = 3.0V

const byte LED_2R = 98;   //  98 = 1.9V
const byte LED_2G = 159;  // 159 = 3.1V
const byte LED_2B = 153;  // 153 = 3.0V

byte ledIntensityR[NUMKEYS] = {255 - LED_1R, 255 - LED_2R};
byte ledIntensityG[NUMKEYS] = {255 - LED_1G, 255 - LED_2G};
byte ledIntensityB[NUMKEYS] = {255 - LED_1B, 255 - LED_2B};

Bounce button[NUMKEYS];

void setup() {

  for (uint8_t i = 0; i < NUMKEYS; i++) {

    // Initialize buttons w/ debounce code
    button[i] = Bounce();
    button[i].attach(pinArray[i], INPUT_PULLUP);
    button[i].interval(1);

    // Initialize RGB LEDs
    pinMode(ledArrayR[i], OUTPUT);
    pinMode(ledArrayCA[i], OUTPUT);
    pinMode(ledArrayG[i], OUTPUT);
    pinMode(ledArrayB[i], OUTPUT);

    analogWrite(ledArrayR[i], ledIntensityR[i]);
    digitalWrite(ledArrayCA[i], HIGH);
    analogWrite(ledArrayG[i], ledIntensityG[i]);
    analogWrite(ledArrayB[i], ledIntensityB[i]);
  }
}

void loop() {

  // Scan each button individually
  for (uint8_t i = 0; i < NUMKEYS; i++) {
    button[i].update();

    if (button[i].fell()) {
      Keyboard.press(keyArray[i]);
      
      byte ledIntensityR[NUMKEYS] = {255, 157};
      byte ledIntensityG[NUMKEYS] = {96, 96};
      byte ledIntensityB[NUMKEYS] = {102, 255};
      
      analogWrite(ledArrayR[i], ledIntensityR[i]);
      analogWrite(ledArrayG[i], ledIntensityG[i]);
      analogWrite(ledArrayB[i], ledIntensityB[i]);
    }
    if (button[i].rose()) {
      Keyboard.release(keyArray[i]);
      
      byte ledIntensityR[NUMKEYS] = {157, 255};
      byte ledIntensityG[NUMKEYS] = {96, 96};
      byte ledIntensityB[NUMKEYS] = {255, 102};
      
      analogWrite(ledArrayR[i], ledIntensityR[i]);
      analogWrite(ledArrayG[i], ledIntensityG[i]);
      analogWrite(ledArrayB[i], ledIntensityB[i]);
    }
  }
}
