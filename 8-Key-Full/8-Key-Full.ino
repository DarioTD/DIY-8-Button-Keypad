/*
 
Copyright (c) 2019, Charles Garcia
Copyright (c) 2021 - 2023, Dario Tabares
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
#define NUM_KEYS 2

// Edit the buttons you want pressed here
#define KEY_1 'z'
#define KEY_2 'x'

// Pins used by the buttons
#define PIN_1 A0
#define PIN_2 A1
#define PIN_COM A2

// Change if adding more or less LEDs
#define NUM_LEDS 2

// Pins used by the RGB LEDs
#define PIN_LED_1_RED 13
#define PIN_LED_1_COM 12
#define PIN_LED_1_GREEN 11
#define PIN_LED_1_BLUE 10

#define PIN_LED_2_RED 3
#define PIN_LED_2_COM 4
#define PIN_LED_2_GREEN 5
#define PIN_LED_2_BLUE 6

// Arrays used for the for-loop sections of this program
const byte PIN[NUM_KEYS] = {PIN_1, PIN_2};
const byte KEY[NUM_KEYS] = {KEY_1, KEY_2};
const byte LED_COM[NUM_LEDS] = {PIN_LED_1_COM, PIN_LED_2_COM};
const byte LED_PIN[NUM_LEDS][3] = {{PIN_LED_1_RED, PIN_LED_1_GREEN, PIN_LED_1_BLUE},
                                   {PIN_LED_2_RED, PIN_LED_2_GREEN, PIN_LED_2_BLUE}};
// Using PWM to limit LED current
const byte LED_MAX_CURRENT[3] = {98, 159, 153}; // RED: 1.9V, GREEN: 3.1V, BLUE: 3.0V MAX

Bounce button[NUM_KEYS];

// Change to false if your LEDs are not Common Anode
const bool IS_LED_COMMON_ANODE = true;

void setup() {

  for (byte i = 0; i < NUM_KEYS; i++) {
    // Initialize buttons w/ debounce code
    button[i] = Bounce();
    button[i].attach(PIN[i], INPUT_PULLUP);
    button[i].interval(1);

    // Initialize RGB LEDs
    byte ledIntensity[NUM_LEDS][3] = {{0x00, 0x0A, 0x0A},
                                      {0x0A, 0x00, 0x0A}};
    for (byte j = 0; j < 3; j++) {
      ledIntensity[i][j] = map(ledIntensity[i][j], 0, 255, 0, LED_MAX_CURRENT[j]);

      if (IS_LED_COMMON_ANODE == true)
        ledIntensity[i][j] = 255 - ledIntensity[i][j];

      pinMode(LED_PIN[i][j], OUTPUT);
      analogWrite(LED_PIN[i][j], ledIntensity[i][j]);
    }
    pinMode(PIN_COM, OUTPUT);
    pinMode(LED_COM[i], OUTPUT);
    if (IS_LED_COMMON_ANODE == true)
      digitalWrite(LED_COM[i], HIGH);
    else
      digitalWrite(LED_COM[i], LOW);
  }
}

void loop() {

  // Scan each button individually
  for (byte i = 0; i < NUM_KEYS; i++) {
    button[i].update();

    if (button[i].fell()) {
      Keyboard.press(KEY[i]);
      byte ledIntensity[NUM_LEDS][3] = {{0x00, 0xFF, 0xFF},
                                        {0xFF, 0x00, 0xFF}};
      for (byte j = 0; j < 3; j++) {
        ledIntensity[i][j] = map(ledIntensity[i][j], 0, 255, 0, LED_MAX_CURRENT[j]);

        if (IS_LED_COMMON_ANODE == true)
          ledIntensity[i][j] = 255 - ledIntensity[i][j];

        analogWrite(LED_PIN[i][j], ledIntensity[i][j]);
      }
    }

    if (button[i].rose()) {
      Keyboard.release(KEY[i]);
      byte ledIntensity[NUM_LEDS][3] = {{0x00, 0x0A, 0x0A},
                                        {0x0A, 0x00, 0x0A}};
      for (byte j = 0; j < 3; j++) {
        ledIntensity[i][j] = map(ledIntensity[i][j], 0, 255, 0, LED_MAX_CURRENT[j]);

        if (IS_LED_COMMON_ANODE == true)
          ledIntensity[i][j] = 255 - ledIntensity[i][j];

        analogWrite(LED_PIN[i][j], ledIntensity[i][j]);
      }
    }
  }
}
