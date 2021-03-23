/**
 * CFRotaryEncoder.h
 * 
 * A library for Arduino that helps interface for Rotary Encoders.
 * 
 * @author  Caio Frota <caiofrota@gmail.com>
 * @version 1.0.0
 * @since   Mar, 2021
 */

#include "CFRotaryEncoder.h"

/**
 * Constructor.
 * 
 * @param pinOutputA Clock pin.
 * @param pinOutputB DT pin.
 */
CFRotaryEncoder::CFRotaryEncoder(int pinOutputA, int pinOutputB):
        _pinOutputA(pinOutputA), _pinOutputB(pinOutputB),
        _pushButton(NULL), _pushButtonActive(false),
        _direction(NOROTATION), _step(1) {
    
}

/**
 * Constructor.
 * 
 * @param pinOutputA Clock pin.
 * @param pinOutputB DT pin.
 * @param pinPushButton Push Button pin.
 */
CFRotaryEncoder::CFRotaryEncoder(int pinOutputA, int pinOutputB, int pinPushButton):
        _pinOutputA(pinOutputA), _pinOutputB(pinOutputB),
        _pinPushButton(pinPushButton), _pushButton(pinPushButton), _pushButtonActive(true),
        _step(1), _direction(NOROTATION) {
    
}

/**
 * Initial setup.
 */
void CFRotaryEncoder::begin() {
    // Config rotary.
    pinMode(_pinOutputA, INPUT);
    pinMode(_pinOutputB, INPUT);
    
    _lastState = digitalRead(_pinOutputA);
    
    // Config push button, if active.
    if (_pushButtonActive) {
        _pushButton.begin();
        _pushButton.setPulledUp();
    }
}

/**
 * Control Rotary and Push Button if defined.
 */
void CFRotaryEncoder::loop() {
    // Call interrupt function, if it was defined on ISR, it will not do anything because the interrupt will intercept it first.
    interrupt();
    
    // Call Push Button loop if defined.
    if (_pushButtonActive) {
        _pushButton.loop();
    }
}

/**
 * Control Rotary.
 */
void CFRotaryEncoder::interrupt() {
    // Read rotary status.
    _state = digitalRead(_pinOutputA);
    
    // Check if status has changed.
    if (_state != _lastState) {
        _lastChange = millis();
        _lastValue = _value;
        
        // Call before change value callback.
        if (_beforeRotaryChangeValueCallback != NULL) {
            _beforeRotaryChangeValueCallback();
        }

        // Check if it was clockwise.
        if (digitalRead(_pinOutputB) != _state) {
            if (_state == LOW) {
                doClockwise();
            }
        } else {
            if (_state == LOW) {
                doCounterClockwise();
            }
        }
        
        // Call after change value callback.
        if (_afterRotaryChangeValueCallback != NULL) {
            _afterRotaryChangeValueCallback();
        }
    }
    
    // Update rotary state.
    _lastState = _state;
}

/**
 * Method called when encoder is rotating clockwise.
 */
void CFRotaryEncoder::doClockwise() {
    _direction = CLOCKWISE;
    _value += _step;
    Serial.println(_value);
}

/**
 * Method called when encoder is rotating counter clockwise.
 */
void CFRotaryEncoder::doCounterClockwise() {
    _direction = COUNTERCLOCKWISE;
    _value -= _step;
    Serial.println(_value);
}

/**
 * Get Last value.
 * 
 * @return Last value.
 */
int CFRotaryEncoder::getLastValue() {
    return _lastValue;
}

/**
 * Get Rotary Encoder Value.
 * 
 * @return Rotary Encoder value.
 */
int CFRotaryEncoder::getValue() {
    return _value;
}

/**
 * Set Rotary Encoder Value.
 * 
 * @return Rotary Encoder value.
 */
void CFRotaryEncoder::setValue(int value) {
    _value = value;
}

/**
 * Get Rotary Direction.
 * 
 * @return Rotary Direction.
 */
CFRotaryEncoder::Direction CFRotaryEncoder::getDirection() {
    return _direction;
}

/**
 * Define method that should be called before rotary change value.
 *
 * @param func No-parameter and no-return function.
 */
void CFRotaryEncoder::setBeforeRotaryChangeValueCallback(std::function<void()> func) {
    _beforeRotaryChangeValueCallback = func;
}

/**
 * Define method that should be called after rotary change value.
 *
 * @param func No-parameter and no-return function.
 */
void CFRotaryEncoder::setAfterRotaryChangeValueCallback(std::function<void()> func) {
    _afterRotaryChangeValueCallback = func;
}

// =================================================================================================
// Push Button methods.
// =================================================================================================

/**
 * Push Button initial setup.
 */
void CFRotaryEncoder::pushButtonBegin() {
    if (_pushButtonActive) {
        return _pushButton.begin();
    }
}

/**
 * Push Button Loop.
 */
void CFRotaryEncoder::pushButtonLoop() {
    if (_pushButtonActive) {
        return _pushButton.loop();
    }
}

/**
 * Get button state.
 * 
 * @returns Button state.
 */
int CFRotaryEncoder::getPushButtonState() {
    if (_pushButtonActive) {
        return _pushButton.getState();
    }
}

/**
 * True if button is pulled up.
 * 
 * @returns True if button is pulled high.
 */
bool CFRotaryEncoder::isPushButtonPulledUp() {
    if (_pushButtonActive) {
        return _pushButton.isPulledUp();
    }
}

/**
 * Define button is pulled up.
 */
void CFRotaryEncoder::setPushButtonPulledUp() {
    if (_pushButtonActive) {
        _pushButton.setPulledUp();
    }
}

/**
 * Define button is pulled down.
 */
void CFRotaryEncoder::setPushButtonPulledDown() {
    if (_pushButtonActive) {
        _pushButton.setPulledDown();
    }
}

/**
 * Get short time in millis that the button should be pressed to call short press callback.
 *
 * @returns Short time in millis.
 */
int CFRotaryEncoder::getPushButtonShortPressTime() {
    if (_pushButtonActive) {
        return _pushButton.getShortPressTime();
    }
}

/**
 * Define short time in millis that the button should be pressed to call short press callback.
 * 
 * @param shortPressTime Short time in millis.
 */
void CFRotaryEncoder::setPushButtonShortPressTime(int shortPressTime) {
    if (_pushButtonActive) {
        _pushButton.setShortPressTime(shortPressTime);
    }
}

/**
 * Get long time in millis that the button should be pressed to call long press callback.
 *
 * @returns Long time in millis.
 */
int CFRotaryEncoder::getPushButtonLongPressTime() {
    if (_pushButtonActive) {
        return _pushButton.getLongPressTime();
    }
}

/**
 * Define long time in millis that the button should be pressed to call long press callback.
 * 
 * @param longPressTime Long time in millis.
 */
void CFRotaryEncoder::setPushButtonLongPressTime(int longPressTime) {
    if (_pushButtonActive) {
        _pushButton.setLongPressTime(longPressTime);
    }
}

/**
 * Define method that should be called when short time is reached.
 *
 * @param func No-parameter and no-return function.
 */
void CFRotaryEncoder::setPushButtonOnShortPressReachedCallback(std::function<void()> func) {
    if (_pushButtonActive) {
        _pushButton.setOnShortPressReachedCallback(func);
    }
}

/**
 * Define method that should be called when long time is reached.
 *
 * @param func No-parameter and no-return function.
 */
void CFRotaryEncoder::setPushButtonOnLongPressReachedCallback(std::function<void()> func) {
    if (_pushButtonActive) {
        _pushButton.setOnLongPressReachedCallback(func);
    }
}

/**
 * Define method that should be called when button is pressed.
 *
 * @param func No-parameter and no-return function.
 */
void CFRotaryEncoder::setPushButtonOnPressCallback(std::function<void()> func) {
    if (_pushButtonActive) {
        _pushButton.setOnPressCallback(func);
    }
}

/**
 * Define method that should be called when button is short time pressed.
 *
 * @param func No-parameter and no-return function.
 */
void CFRotaryEncoder::setPushButtonOnShortPressCallback(std::function<void()> func) {
    if (_pushButtonActive) {
        _pushButton.setOnShortPressCallback(func);
    }
}

/**
 * Define method that should be called when button is long time pressed.
 *
 * @param func No-parameter and no-return function.
 */
void CFRotaryEncoder::setPushButtonOnLongPressCallback(std::function<void()> func) {
    if (_pushButtonActive) {
        _pushButton.setOnLongPressCallback(func);
    }
}