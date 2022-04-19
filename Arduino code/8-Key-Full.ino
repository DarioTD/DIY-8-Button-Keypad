/*
 
Copyright (c) 2019, Charles Garcia
Copyright (c) 2021 - 2022, Dario Tabares
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
#define PIN_1 7
#define PIN_2 8

// Change if adding more or less LEDs
#define NUM_LEDS 2

// Using PWM to limit LED current
#define LED_RED_MAX_LIMIT 98    //  98 = 1.9V MAX
#define LED_GREEN_MAX_LIMIT 159 // 159 = 3.1V MAX
#define LED_BLUE_MAX_LIMIT 153  // 153 = 3.0V MAX

// Pins used by the RGB LEDs
#define PIN_LED_1_RED 3
#define PIN_LED_1_COM 4
#define PIN_LED_1_GREEN 5
#define PIN_LED_1_BLUE 6

#define PIN_LED_2_RED 13
#define PIN_LED_2_COM 12
#define PIN_LED_2_GREEN 11
#define PIN_LED_2_BLUE 10

// Arrays used for the for-loop sections of this program
const byte PIN_ARRAY[NUM_KEYS] = {PIN_1, PIN_2};
const byte KEY_ARRAY[NUM_KEYS] = {KEY_1, KEY_2};
const byte LED_ARRAY_COM[NUM_KEYS] = {PIN_LED_1_COM, PIN_LED_2_COM};
const byte LED_ARRAY_RGB[NUM_KEYS][3] = {{PIN_LED_1_RED, PIN_LED_1_GREEN, PIN_LED_1_BLUE},
                                        {PIN_LED_2_RED, PIN_LED_2_GREEN, PIN_LED_2_BLUE}};

Bounce button[NUM_KEYS];

// Change to false if your LEDs are not Common Anode
const bool IS_LED_COMMON_ANODE = true;

void setup() {

  byte ledRGBIntensity[NUM_LEDS][3] = {{0, 16, 15},
                                       {10, 0, 15}};

  for (byte i = 0; i < NUM_KEYS; i++) {
    // Initialize buttons w/ debounce code
    button[i] = Bounce();
    button[i].attach(PIN_ARRAY[i], INPUT_PULLUP);
    button[i].interval(1);

    // Initialize RGB LEDs
    if (ledRGBIntensity[i][0] > LED_RED_MAX_LIMIT) {
      ledRGBIntensity[i][0] = LED_RED_MAX_LIMIT;
    }
    if (ledRGBIntensity[i][1] > LED_GREEN_MAX_LIMIT) {
      ledRGBIntensity[i][1] = LED_GREEN_MAX_LIMIT;
    }
    if (ledRGBIntensity[i][2] > LED_BLUE_MAX_LIMIT) {
      ledRGBIntensity[i][2] = LED_BLUE_MAX_LIMIT;
    }
    for (byte j = 0; j < 3; j++) {
      pinMode(LED_ARRAY_RGB[i][j], OUTPUT);
      if (IS_LED_COMMON_ANODE == true) {
        ledRGBIntensity[i][j] = 255 - ledRGBIntensity[i][j];
      }
      analogWrite(LED_ARRAY_RGB[i][j], ledRGBIntensity[i][j]);
    }
    pinMode(LED_ARRAY_COM[i], OUTPUT);
    if (IS_LED_COMMON_ANODE == true) {
      digitalWrite(LED_ARRAY_COM[i], HIGH);
    } else {
      digitalWrite(LED_ARRAY_COM[i], LOW);
    }
  }
}

void loop() {

  // Scan each button individually
  for (byte i = 0; i < NUM_KEYS; i++) {
    button[i].update();

    if (button[i].fell()) {
      Keyboard.press(KEY_ARRAY[i]);
      byte ledRGBIntensity[NUM_LEDS][3] = {{0, 255, 255},
                                           {255, 0, 255}};
      if (ledRGBIntensity[i][0] > LED_RED_MAX_LIMIT) {
        ledRGBIntensity[i][0] = LED_RED_MAX_LIMIT;
      }
      if (ledRGBIntensity[i][1] > LED_GREEN_MAX_LIMIT) {
        ledRGBIntensity[i][1] = LED_GREEN_MAX_LIMIT;
      }
      if (ledRGBIntensity[i][2] > LED_BLUE_MAX_LIMIT) {
        ledRGBIntensity[i][2] = LED_BLUE_MAX_LIMIT;
      }
      for (byte j = 0; j < 3; j++) {
        if (IS_LED_COMMON_ANODE == true) {
          ledRGBIntensity[i][j] = 255 - ledRGBIntensity[i][j];
        }
        analogWrite(LED_ARRAY_RGB[i][j], ledRGBIntensity[i][j]);
      }
    }

    if (button[i].rose()) {
      Keyboard.release(KEY_ARRAY[i]);
      byte ledRGBIntensity[NUM_LEDS][3] = {{0, 16, 15},
                                          {10, 0, 15}};
      if (ledRGBIntensity[i][0] > LED_RED_MAX_LIMIT) {
        ledRGBIntensity[i][0] = LED_RED_MAX_LIMIT;
      }
      if (ledRGBIntensity[i][1] > LED_GREEN_MAX_LIMIT) {
        ledRGBIntensity[i][1] = LED_GREEN_MAX_LIMIT;
      }
      if (ledRGBIntensity[i][2] > LED_BLUE_MAX_LIMIT) {
        ledRGBIntensity[i][2] = LED_BLUE_MAX_LIMIT;
      }
      for (byte j = 0; j < 3; j++) {
        if (IS_LED_COMMON_ANODE == true) {
          ledRGBIntensity[i][j] = 255 - ledRGBIntensity[i][j];
        }
        analogWrite(LED_ARRAY_RGB[i][j], ledRGBIntensity[i][j]);
      }
    }
  }
}
