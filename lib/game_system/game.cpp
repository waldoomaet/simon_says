#include "game.h"
#include <Arduino.h>
#include "pitches.h"
#include "sequence.h"
#include "animation.h"

void Game::_interactCounter(int pin)
{
    digitalWrite(pin, HIGH);
    delay(5);
    digitalWrite(pin, LOW);
}

int Game::_buttonPushed()
{
    pinsAsInputs();
    while (1)
    {
        if (!digitalRead(button1Pin))
        {
            tone(buzzerPin, _tonePins[0].tone, 200);
            delay(200);
            return button1Pin;
        }
        else if (!digitalRead(button2Pin))
        {
            tone(buzzerPin, _tonePins[1].tone, 200);
            delay(200);
            return button2Pin;
        }
        else if (!digitalRead(button3Pin))
        {
            tone(buzzerPin, _tonePins[2].tone, 200);
            delay(200);
            return button3Pin;
        }
        else if (!digitalRead(button4Pin))
        {
            tone(buzzerPin, _tonePins[3].tone, 200);
            delay(200);
            return button4Pin;
        }
    }
}

void Game::gameMode1()
{
    bool done = false;
    while (!done)
    {
        generateNextPlay();
        playGameSequence();
        bool correct = checkUserSequence();
        if (correct)
        {
            winAnimation();
            incrementCount();
        }
        else
        {
            gameOverAnimation();
            resetGame();
            done = true;
        }
    }
}

void Game::gameMode2()
{
    bool done = false;
    while (!done)
    {
        generateNextPlay();
        playGameSequence();
        bool correct = checkUserSequence();
        if (correct)
        {
            winAnimation();
            incrementCount();
            gameSequence.Clear();
        }
        else
        {
            gameOverAnimation();
            resetGame();
            done = true;
        }
    }
}

Game::Game(int button1Pin, int button2Pin, int button3Pin, int button4Pin, int buzzerPin, int counterResetPin, int counterUpPin)
{
    this->button1Pin = button1Pin;
    this->button2Pin = button2Pin;
    this->button3Pin = button3Pin;
    this->button4Pin = button4Pin;
    this->buzzerPin = buzzerPin;
    this->counterResetPin = counterResetPin;
    this->counterUpPin = counterUpPin;
}

void Game::begin()
{
    pinMode(counterResetPin, OUTPUT);
    pinMode(counterUpPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);

    digitalWrite(counterResetPin, LOW);
    digitalWrite(counterUpPin, LOW);

    _tonePins.PushBack({NOTE_G3, button1Pin});
    _tonePins.PushBack({NOTE_C4, button2Pin});
    _tonePins.PushBack({NOTE_E4, button3Pin});
    _tonePins.PushBack({NOTE_G5, button4Pin});

    resetCount();
    randomSeed(analogRead(0));
}

void Game::pinsAsOutputs()
{
    pinMode(button1Pin, OUTPUT);
    pinMode(button2Pin, OUTPUT);
    pinMode(button3Pin, OUTPUT);
    pinMode(button4Pin, OUTPUT);
}

void Game::pinsAsInputs()
{
    pinMode(button1Pin, INPUT_PULLUP);
    pinMode(button2Pin, INPUT_PULLUP);
    pinMode(button3Pin, INPUT_PULLUP);
    pinMode(button4Pin, INPUT_PULLUP);
}

void Game::turnAllPins(int state)
{
    digitalWrite(button1Pin, state);
    digitalWrite(button2Pin, state);
    digitalWrite(button3Pin, state);
    digitalWrite(button4Pin, state);
}

void Game::resetCount()
{
    _interactCounter(counterResetPin);
}

void Game::incrementCount()
{
    _interactCounter(counterUpPin);
}

void Game::generateNextPlay()
{
    int rng = random(0, 4);
    switch (rng)
    {
    case 0:
        gameSequence.PushBack(button1Pin);
        break;
    case 1:
        gameSequence.PushBack(button2Pin);
        break;
    case 2:
        gameSequence.PushBack(button3Pin);
        break;
    case 3:
        gameSequence.PushBack(button4Pin);
        break;
    }
}

bool Game::checkUserSequence()
{
    for (int i = 0; i < gameSequence.Size(); i++)
    {
        int button = _buttonPushed();
        if (button != gameSequence[i])
        {
            return false;
        }
    }
    return true;
}

void Game::playGameSequence()
{
    pinsAsOutputs();
    for (int i = 0; i < gameSequence.Size(); i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (_tonePins[j].pin == gameSequence[i])
            {
                tone(buzzerPin, _tonePins[j].tone, 300);
                digitalWrite(gameSequence[i], LOW);
                delay(300);
                digitalWrite(gameSequence[i], HIGH);
                delay(100);
                break;
            }
        }
    }
}

void Game::resetGame()
{
    resetCount();
    gameSequence.Clear();
}

void Game::bootUpAnimation()
{
    const ToneSequence tones[] = {
        {NO_NOTE, 277},
        {NOTE_A4, 54},
        {NO_NOTE, 81},
        {NOTE_C5, 54},
        {NO_NOTE, 81},
        {NOTE_D5, 54},
        {NO_NOTE, 81},
        {NOTE_A4, 54},
        {NO_NOTE, 81},
        {NOTE_C5, 54},
        {NO_NOTE, 81},
        {NOTE_D5, 54},
        {NO_NOTE, 81},
        {NOTE_G4, 54},
        {NO_NOTE, 81},
        {NOTE_A4, 54},
        {NO_NOTE, 81},
        {NOTE_E5, 54},
        {NO_NOTE, 81},
        {NOTE_G4, 54},
        {NO_NOTE, 81},
        {NOTE_A4, 54},
        {NO_NOTE, 81},
        {NOTE_F5, 54},
        {NO_NOTE, 81},
        {NOTE_E5, 54},
        {NO_NOTE, 81},
        {NOTE_C5, 54},
        {NO_NOTE, 81},
        {NOTE_A4, 54},
        {NO_NOTE, 81},
        {NOTE_F4, 54},
        {NO_NOTE, 81},
        {NOTE_A4, 54},
        {NO_NOTE, 81},
        {NOTE_C5, 54},
        {NO_NOTE, 81},
        {NOTE_E5, 54},
        {NO_NOTE, 81},
        {NOTE_D5, 54},
        {NO_NOTE, 81},
        {NOTE_G4, 54},
        {NO_NOTE, 81},
        {NOTE_A4, 54},
        {NO_NOTE, 81},
        {NOTE_C5, 54},
        {NO_NOTE, 1200},
        {-1, -1}};

    int tonesSize = sizeof(tones) / sizeof(tones[0]);

    const LedSequence leds[] = {
        {button1Pin, 10, false},
        {button2Pin, 10, false},
        {button3Pin, 10, false},
        {button4Pin, 10, false},

        {button1Pin, 277, true},
        {button1Pin, 10, false},

        {button2Pin, 277, true},
        {button2Pin, 10, false},

        {button3Pin, 277, true},
        {button3Pin, 10, false},

        {button4Pin, 277, true},
        {button4Pin, 10, false},

        {button1Pin, 277, true},
        {button1Pin, 10, false},

        {button2Pin, 277, true},
        {button2Pin, 10, false},

        {button3Pin, 277, true},
        {button3Pin, 10, false},

        {button4Pin, 277, true},
        {button4Pin, 10, false},

        {button1Pin, 277, true},

        {button2Pin, 277, true},

        {button3Pin, 277, true},

        {button4Pin, 277, true},
        {-1, -1, false}};

    int ledsSize = sizeof(leds) / sizeof(leds[0]);

    pinsAsOutputs();
    playAnimation(buzzerPin, tones, tonesSize, leds, ledsSize);
}

void Game::winAnimation()
{
    const ToneSequence tones[] = {
        {NO_NOTE, 100},
        {NOTE_B4, 54},
        {NO_NOTE, 81},
        {NOTE_C5, 54},
        {NO_NOTE, 81},
        {NOTE_CS5, 54},
        {NO_NOTE, 81},
        {NOTE_D5, 54},
        {NO_NOTE, 175},
        {NOTE_G5, 81},
        {NO_NOTE, 81},
        {NOTE_F5, 108},
        {NO_NOTE, 300},
        {-1, -1}};

    int tonesSize = sizeof(tones) / sizeof(tones[0]);

    const LedSequence leds[] = {
        {button1Pin, 10, false},
        {button2Pin, 10, false},
        {button3Pin, 10, false},
        {button4Pin, 10, false},

        {button1Pin, 200, false},

        {button1Pin, 10, true},
        {button2Pin, 10, true},
        {button3Pin, 10, true},
        {button4Pin, 10, true},

        {button1Pin, 50, true},

        {button1Pin, 10, false},
        {button2Pin, 10, false},
        {button3Pin, 10, false},
        {button4Pin, 10, false},

        {button1Pin, 200, false},

        {button1Pin, 10, true},
        {button2Pin, 10, true},
        {button3Pin, 10, true},
        {button4Pin, 10, true},

        {button1Pin, 50, true},

        {button1Pin, 10, false},
        {button2Pin, 10, false},
        {button3Pin, 10, false},
        {button4Pin, 10, false},

        {button1Pin, 200, false},

        {button1Pin, 10, true},
        {button2Pin, 10, true},
        {button3Pin, 10, true},
        {button4Pin, 10, true},

        {button1Pin, 50, true},

        {-1, -1, false}};

    int ledsSize = sizeof(leds) / sizeof(leds[0]);

    pinsAsOutputs();
    playAnimation(buzzerPin, tones, tonesSize, leds, ledsSize);
}

void Game::gameOverAnimation()
{
    const ToneSequence tones[] = {
        {NOTE_E5, 100},
        {NO_NOTE, 100},
        {NOTE_E5, 100},
        {NO_NOTE, 100},
        {NOTE_E5, 100},
        {NO_NOTE, 100},
        {NOTE_B5, 300},
        {NO_NOTE, 100},
        {NOTE_A5, 100},
        {NO_NOTE, 100},
        {NOTE_FS5, 100},
        {NO_NOTE, 100},
        {NOTE_D5, 100},
        {NO_NOTE, 100},
        {NOTE_G5, 100},
        {NO_NOTE, 500},
        {NOTE_C5, 105},
        {NO_NOTE, 105},
        {NOTE_D5, 105},
        {NO_NOTE, 105},
        {NOTE_G4, 105},
        {NO_NOTE, 1200},
        {
            -1,
            -1,
        }};

    int tonesSize = sizeof(tones) / sizeof(tones[0]);

    const LedSequence leds[] = {
        {button1Pin, 10, false},
        {button2Pin, 10, false},
        {button3Pin, 10, false},
        {button4Pin, 10, false},

        {button1Pin, 200, false},

        {button1Pin, 10, true},
        {button2Pin, 10, true},
        {button3Pin, 10, true},
        {button4Pin, 10, true},

        {button1Pin, 200, true},

        {button1Pin, 10, false},
        {button2Pin, 10, false},
        {button3Pin, 10, false},
        {button4Pin, 10, false},

        {button1Pin, 200, false},

        {button1Pin, 10, true},
        {button2Pin, 10, true},
        {button3Pin, 10, true},
        {button4Pin, 10, true},

        {button1Pin, 200, true},

        {button1Pin, 10, false},
        {button2Pin, 10, false},
        {button3Pin, 10, false},
        {button4Pin, 10, false},

        {button1Pin, 200, false},

        {button1Pin, 10, true},
        {button2Pin, 10, true},
        {button3Pin, 10, true},
        {button4Pin, 10, true},

        {button1Pin, 200, true},

        {button1Pin, 10, false},
        {button2Pin, 10, false},
        {button3Pin, 10, false},
        {button4Pin, 10, false},

        {button1Pin, 200, false},

        {button1Pin, 10, true},
        {button2Pin, 10, true},
        {button3Pin, 10, true},
        {button4Pin, 10, true},

        {button1Pin, 200, true},

        {button1Pin, 10, false},
        {button2Pin, 10, false},
        {button3Pin, 10, false},
        {button4Pin, 10, false},

        {button1Pin, 200, false},

        {button1Pin, 10, true},
        {button2Pin, 10, true},
        {button3Pin, 10, true},
        {button4Pin, 10, true},

        {button1Pin, 200, true},

        {button1Pin, 10, false},
        {button2Pin, 10, false},
        {button3Pin, 10, false},
        {button4Pin, 10, false},

        {button1Pin, 200, false},

        {button1Pin, 10, true},
        {button2Pin, 10, true},
        {button3Pin, 10, true},
        {button4Pin, 10, true},

        {button1Pin, 200, true},

        {button1Pin, 10, false},
        {button2Pin, 10, false},
        {button3Pin, 10, false},
        {button4Pin, 10, false},

        {button1Pin, 200, false},

        {button1Pin, 10, true},
        {button2Pin, 10, true},
        {button3Pin, 10, true},
        {button4Pin, 10, true},

        {button1Pin, 200, true},

        {button1Pin, 10, false},
        {button2Pin, 10, false},
        {button3Pin, 10, false},
        {button4Pin, 10, false},

        {button1Pin, 200, false},

        {button1Pin, 10, true},
        {button2Pin, 10, true},
        {button3Pin, 10, true},
        {button4Pin, 10, true},

        {button1Pin, 200, true},

        {-1, -1, false}};

    int ledsSize = sizeof(leds) / sizeof(leds[0]);

    pinsAsOutputs();
    playAnimation(buzzerPin, tones, tonesSize, leds, ledsSize);
}

void Game::selectGameMode()
{
    unsigned long currentTime = millis();
    const int16_t difference = 1000;
    bool done = false;
    bool ledStatus = false;

    pinMode(button1Pin, OUTPUT);
    pinMode(button4Pin, OUTPUT);
    pinMode(button2Pin, INPUT);
    pinMode(button3Pin, INPUT);

    while (!done)
    {
        if (millis() - currentTime >= difference)
        {
            digitalWrite(button1Pin, ledStatus);
            digitalWrite(button4Pin, ledStatus);
            ledStatus = !ledStatus;
            currentTime = millis();
        }

        if (!digitalRead(button2Pin))
        {
            pinsAsOutputs();
            turnAllPins(true);
            delay(350);
            gameMode1();
            done = true;
        }

        if (!digitalRead(button3Pin))
        {
            pinsAsOutputs();
            turnAllPins(true);
            delay(350);
            gameMode2();
            done = true;
        }
    }
}