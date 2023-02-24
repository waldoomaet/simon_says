#include "pitches.h"
#include "game_tone.h"

class GameSystem
{
private:
    // GameTone _gameTones[4];
    // void _setGameTones();
    void _interactCounter(int pin);
    void _turnOn(int pin);
    void _turnOff(int pin);
    int _buttonPushed();
    int _getPinTone(int pin);

public:
    int gameSequence[99];
    int gameIndex = 0;

    int buttonPin1;
    int buttonPin2;
    int buttonPin3;
    int buttonPin4;
    int buzzerPin;
    int counterResetPin;
    int counterUpPin;

    void pinsAsOutputs();
    void pinsAsInputs();
    void turnAllPins(int state);
    void resetCount();
    void incrementCount();
    void playGameSequence();
    void generateNextPlay();
    void bootUpAnimation();
    bool checkUserSequence();
    void begin();
    GameSystem(int buttonPin1, int buttonPin2, int buttonPin3, int buttonPin4, int buzzerPin, int counterResetPin, int counterUpPin);
};