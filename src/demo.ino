// JLed dynamic sequence demo
//
// Toggles between sequences using a push button.
// After a sequence is finished, leds are turned off by calling
// Stop() on the sequence object.
//
// (c) Copyright 2022 by Jan Delgado
// see https://github.com/jandelgado/jled
//
// -----------------------------------------------------------------
// setup:
//   LEDs are connected to GPIO 22 and 23.
//   Button is connected to GPIO 5 and GND.
//
#include <JC_Button.h> // https://github.com/JChristensen/JC_Button
#include <jled.h>

JLed leds1[] = {
    JLed(22).FadeOn(500).Repeat(10),
    JLed(23).Off(),
};

JLed leds2[] = {
    JLed(22).Off(1),
    JLed(23).Blink(500, 500).Repeat(10),
};

JLed leds3[] = {
    JLed(22).FadeOn(500).DelayAfter(500).Repeat(10),
    JLed(23).DelayBefore(500).FadeOn(500).DelayAfter(500).Repeat(10),
};

auto seq = JLedSequence(JLedSequence::eMode::PARALLEL, leds3);
auto button = Button(5, 25, true /*pull-up*/, true /*inverted*/);

void setup()
{
    Serial.begin(9600);
    Serial.println("press button to cycle through effects");
    button.begin();
}

void loop()
{
    static auto count = 0;
    button.read();

    if (!seq.Update()) {
        // turn leds off after sequence is done
        seq.Stop();
    }

    if (button.wasPressed()) {
        switch (count) {
        case 0:
            Serial.println("FX1");
            seq = JLedSequence(JLedSequence::eMode::PARALLEL, leds1);
            seq.Reset();
            break;
        case 1:
            Serial.println("FX2");
            seq = JLedSequence(JLedSequence::eMode::PARALLEL, leds2);
            seq.Reset();
            break;
        case 2:
            Serial.println("FX3");
            seq = JLedSequence(JLedSequence::eMode::PARALLEL, leds3);
            seq.Reset();
            break;
        }
        count = (count + 1) % 3;
    }
}
