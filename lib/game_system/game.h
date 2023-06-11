#include "tone_pin.h"
#include <Vector.h>

class Game
{
    void _interactCounter(int pin);
    int _buttonPushed();
    Vector<TonePin> _tonePins;

public:
    Vector<int> gameSequence;

    int button1Pin;
    int button2Pin;
    int button3Pin;
    int button4Pin;
    int buzzerPin;
    int counterResetPin;
    int counterUpPin;

    Game(int button1Pin, int button2Pin, int button3Pin, int button4Pin, int buzzerPin, int counterResetPin, int counterUpPin);
    void begin();
    void pinsAsOutputs();
    void pinsAsInputs();
    void turnAllPins(int state);
    void resetCount();
    void incrementCount();
    void generateNextPlay();
    bool checkUserSequence();
    void playGameSequence();
    void resetGame();
    void bootUpAnimation();
    void winAnimation();
    void gameOverAnimation();

    void selectGameMode();
    void gameMode1();
    void gameMode2();
};