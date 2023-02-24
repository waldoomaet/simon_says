#include <Arduino.h>
#include "game.h"
// #include "game_tone.h"

GameSystem::GameSystem(int buttonPin1, int buttonPin2, int buttonPin3, int buttonPin4, int buzzerPin, int counterResetPin, int counterUpPin)
{
    buttonPin1 = buttonPin1;
    buttonPin2 = buttonPin2;
    buttonPin3 = buttonPin3;
    buttonPin4 = buttonPin4;
    buzzerPin = buzzerPin;
    counterResetPin = counterResetPin;
    Serial.println("Constructor done!");
}

void GameSystem::begin()
{
    pinMode(counterUpPin, OUTPUT);
    pinMode(counterResetPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);

    digitalWrite(counterUpPin, LOW);
    digitalWrite(counterResetPin, LOW);

    // _setGameTones();
    resetCount();
    incrementCount();
    randomSeed(analogRead(0));
    Serial.println("Begin done!");
}

// void GameSystem::_setGameTones(){
//     _gameTones[0] = new GameTone(NOTE_G3, buttonPin1);
//     _gameTones[1] = GameTone(NOTE_C4, buttonPin2);
//     _gameTones[2] = GameTone(NOTE_E4, buttonPin3);
//     _gameTones[3] = GameTone(NOTE_G5, buttonPin4);
// }

void GameSystem::_turnOff(int pin)
{
    digitalWrite(pin, HIGH);
}

void GameSystem::_turnOn(int pin)
{
    digitalWrite(pin, LOW);
}

int GameSystem::_buttonPushed()
{
    pinsAsInputs();
    while (1)
    {
        if (!digitalRead(buttonPin1))
        {
            delay(200);
            return buttonPin1;
        }
        else if (!digitalRead(buttonPin2))
        {
            delay(200);
            return buttonPin2;
        }
        else if (!digitalRead(buttonPin3))
        {
            delay(200);
            return buttonPin3;
        }
        else if (!digitalRead(buttonPin4))
        {
            delay(200);
            return buttonPin4;
        }
    }
}

void GameSystem::pinsAsInputs()
{
    pinMode(buttonPin1, INPUT_PULLUP);
    pinMode(buttonPin2, INPUT_PULLUP);
    pinMode(buttonPin3, INPUT_PULLUP);
    pinMode(buttonPin4, INPUT_PULLUP);
}

void GameSystem::pinsAsOutputs()
{
    pinMode(buttonPin1, OUTPUT);
    pinMode(buttonPin2, OUTPUT);
    pinMode(buttonPin3, OUTPUT);
    pinMode(buttonPin4, OUTPUT);
}

void GameSystem::turnAllPins(int state)
{
    digitalWrite(buttonPin1, state);
    digitalWrite(buttonPin2, state);
    digitalWrite(buttonPin3, state);
    digitalWrite(buttonPin4, state);
}

void GameSystem::_interactCounter(int pin)
{
    digitalWrite(pin, HIGH);
    delay(5);
    digitalWrite(pin, LOW);
}

void GameSystem::bootUpAnimation()
{
    Serial.println("In the boot animation");
    pinsAsOutputs();
    turnAllPins(HIGH);
    digitalWrite(buzzerPin, LOW);
    delay(500);
    digitalWrite(buzzerPin, HIGH);

    // _turnOn(buttonPin1);
    // delay(500);
    // _turnOff(buttonPin1);

    _turnOn(buttonPin2);
    delay(500);
    _turnOff(buttonPin2);

    _turnOn(buttonPin3);
    delay(500);
    _turnOff(buttonPin3);

    _turnOn(buttonPin4);
    delay(500);
    _turnOff(buttonPin4);
}

void GameSystem::resetCount()
{
    _interactCounter(counterResetPin);
}

void GameSystem::incrementCount()
{
    _interactCounter(counterUpPin);
}

void GameSystem::generateNextPlay()
{
    int rng = random(0, 4);
    switch (rng)
    {
    case 0:
        gameSequence[gameIndex] = buttonPin1;
        break;
    case 1:
        gameSequence[gameIndex] = buttonPin2;
        break;
    case 2:
        gameSequence[gameIndex] = buttonPin3;
        break;
    case 3:
        gameSequence[gameIndex] = buttonPin4;
        break;
    }
    gameIndex++;
}

bool GameSystem::checkUserSequence()
{
    for (int i = 0; i < gameIndex; i++)
    {
        int buttonPushed = _buttonPushed();
        if (buttonPushed != gameSequence[i])
        {
            return false;
        }
    }
    return true;
}

void GameSystem::playGameSequence()
{
    pinsAsOutputs();
    for (int i = 0; i < gameIndex; i++)
    {
        _turnOn(gameSequence[i]);
        delay(300);
        _turnOff(gameSequence[i]);
        delay(100);
    }
}