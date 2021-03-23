/**
 * CFRotaryEncoder.h
 * 
 * A library for Arduino that helps interface for Rotary Encoders.
 * 
 * @author  Caio Frota <caiofrota@gmail.com>
 * @version 1.0.0
 * @since   Mar, 2021
 */

#include <CFPushButton.h>

#ifndef CFRotaryEncoder_h
#define CFRotaryEncoder_h

class CFRotaryEncoder {
    public:
        // Enumarations.
        enum Direction {
            NOROTATION = 0,
            CLOCKWISE = 1,
            COUNTERCLOCKWISE = -1
        };
        
        // Methods.
        CFRotaryEncoder(int pinOutputA, int pinOutputB);
        CFRotaryEncoder(int pinOutputA, int pinOutputB, int pinPushButton);
        void begin();
        void loop();
        void interrupt();
        void doClockwise();
        void doCounterClockwise();
        
        // Accessors.
        int getLastValue();
        int getValue();
        void setValue(int value);
        Direction getDirection();
        
        // Callbacks.
        void setBeforeRotaryChangeValueCallback(std::function<void()> func);
        void setAfterRotaryChangeValueCallback(std::function<void()> func);
        
        // Push Button Methods.
        void pushButtonBegin();                                                                     // Initial setup.
        void pushButtonLoop();                                                                      // Control push button state.
        int getPushButtonState();                                                                   // Get button state.
        bool isPushButtonPulledUp();                                                                // True if button is pulled up.
        void setPushButtonPulledUp();                                                               // Define button is pulled up.
        void setPushButtonPulledDown();                                                             // Define button is pulled down.
        int getPushButtonShortPressTime();                                                          // Get short time.
        void setPushButtonShortPressTime(int shortPressTime);                                       // Define short time.
        int getPushButtonLongPressTime();                                                           // Get long time.
        void setPushButtonLongPressTime(int shortPressTime);                                        // Define long time.
        
        // Push Button Callbacks.
        void setPushButtonOnShortPressReachedCallback(std::function<void()> func);                  // Define short time reached callback.
        void setPushButtonOnLongPressReachedCallback(std::function<void()> func);                   // Define long time reached callback.
        void setPushButtonOnPressCallback(std::function<void()> func);                              // Define button press callback.
        void setPushButtonOnShortPressCallback(std::function<void()> func);                         // Define button short press callback.
        void setPushButtonOnLongPressCallback(std::function<void()> func);                          // Define button long press callback.
    private:
        // Attributes.
        int _pinOutputA;
        int _pinOutputB;
        int _pinPushButton;
        int _lastValue;
        int _lastState;
        long _lastChange;
        int _step;
        int _value;
        int _state;
        bool _pushButtonActive;
        Direction _direction;
        CFPushButton _pushButton;
        
        // Callbacks
        std::function<void()> _beforeRotaryChangeValueCallback;
        std::function<void()> _afterRotaryChangeValueCallback;
};

#endif
