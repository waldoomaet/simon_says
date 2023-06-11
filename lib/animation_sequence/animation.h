#include "pitches.h"
#include <Arduino.h>
#include <Vector.h>

void playAnimation(int buzzer, const ToneSequence tones[], int tonesSize, const LedSequence leds[], int ledsSize, int baseTicks = 10)
{
    // Serial.println("Starting animation. Tones size: " + String(tonesSize) + ". Leds size: " + String(ledsSize));
    int tonesIndex = 0;
    ToneSequence currentTone = tones[tonesIndex];
    int relativeToneTime = 0;

    int ledsIndex = 0;
    LedSequence currentLed = leds[ledsIndex];
    int relativeLedTime = 0;

    while (tonesIndex + 1 < tonesSize  || ledsIndex + 1 < ledsSize)
    {
        if (currentTone.time != -1 && relativeToneTime >= currentTone.time)
        {
            // Serial.println("Relative time: " + String(relativeToneTime) + " -> Current note: " + String(currentTone.tone) + " -> Tone index: " + String(tonesIndex));
            relativeToneTime = 0;
            tonesIndex++;
            noTone(buzzer);
            currentTone = tones[tonesIndex];
        }

        if (currentTone.tone != -1)
        {
            relativeToneTime += baseTicks;
            if (currentTone.tone != NO_NOTE)
            {
                tone(buzzer, currentTone.tone);
            }
        }

        if (currentLed.time != -1 && relativeLedTime >= currentLed.time)
        {
            // Serial.println("Relative time: " + String(relativeLedTime) + " -> Current Led: " + String(currentLed.pin) + " -> Led index: " + String(ledsIndex));
            relativeLedTime = 0;
            ledsIndex++;
            currentLed = leds[ledsIndex];
        }

        if (currentLed.pin != -1)
        {
            relativeLedTime += baseTicks;
            digitalWrite(currentLed.pin, currentLed.state);
        }

        delay(baseTicks);
    }
    noTone(buzzer);
    // Serial.println("Out of animation");
}