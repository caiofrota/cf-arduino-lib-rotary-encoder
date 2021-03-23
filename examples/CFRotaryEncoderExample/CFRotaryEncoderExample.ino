#include <CFRotaryEncoder.h>                                                                                // CF Rotary Encoder.

const int ROT_PIN_OUTPUT_A = D6;
const int ROT_PIN_OUTPUT_B = D0;
const int ROT_PIN_PUSH_BUT = D5;
CFRotaryEncoder rotaryEncoder(ROT_PIN_OUTPUT_A, ROT_PIN_OUTPUT_B, ROT_PIN_PUSH_BUT);                        // Rotary Endoder.

void setup() {
    Serial.begin(9600);
    
    // Define callbacks.
    rotaryEncoder.setAfterRotaryChangeValueCallback(rotaryAfterChangeValueCallback);
    rotaryEncoder.setPushButtonOnPressCallback(rotaryOnPressCallback);
    
    // Start rotary encoder.
    rotaryEncoder.begin();
}

void loop() {
    // Loop rotary encoder.
    rotaryEncoder.loop();
}

// ====================
// Callbacks.
// ====================


void rotaryAfterChangeValueCallback() {
    if (rotaryEncoder.getDirection() > 0) {
        Serial.print("Clockwise: ");
    } else {
        Serial.print("Counter Clockwise: ");
    }
    Serial.println(rotaryEncoder.getValue());
}

void rotaryOnPressCallback() {
    Serial.println("Button was pressed.");
}
