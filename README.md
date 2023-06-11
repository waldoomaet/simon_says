# Inspiration
[Simon Game from Wokwi](https://wokwi.com/projects/344891334169985618)

Pretty much the same game. My version includes the board design and the game logic made with OOP (as a way to dive with this paradigm into embedded systems). Go check it out to see the simulation!

# Description
This is a personal project called Simon Says (or "Simon Dice", in Spanish).

Pretty much is an Arduino Nano with four buttons, four LEDs and a buzzer (and some displays for score), which randomly generates a pattern that the user must match. Match it, and you get a point, fail, and it is game over. Pretty simple! There is also an easier game mode, intended for smaller kids, that just generates a one-step pattern (so the game simplifies to matching the color).

# Hardware
Parts list:
* 1x Arduino Nano
* 1x SPDT switch 
* 1x Terminal block
* 1x 5v buzzer
* 2x CD4033 Decade Counter IC
* 2x common cathode 7-segment display
* 4x push buttons (preferably with color caps)
* 4x LEDs (preferably that match the caps' colors)
* 6x 1k resistors

The circuit board was made using KiCad, and there are two versions:
* A single copper side version (not tested)
* A double copper side version

Each version includes all the necessary files to fabricate the board with services such as JLCPCB.

It should be possible to also use some of the homemade methods (such as the iron method), but I never tried it.

# Hardware limitations

1. THE BOARD NEED TWO JUMPERS. I didn't notice that I used two pins of the Arduino that can't be used as digital I/O (A6 and A7), so two jumpers from A7 to A5 and from A6 to A4 are necessary.

2. Due to me using some old and obscure CD4033 Decade Counter ICs as a way to get rid of them, you can only:
    * Show numbers on the displays (and none of the hex letters that you normally could use)
    * Reset the count back to 0 or increment it. This is particularly awful since you can't set a specific number or decrement the count without first resetting the count and then increment all the way to the number that you want 

3. Due to me being too cheap to use an individual pin, of the many that the Arduino offers, for every led/button, I ended up sharing the same pin for a button and a LED, and then switch between the pin being an output or an input as needed. This ended up biting me right in the butt, as this was:

    * More annoying than it needed to be, implementing in software
    * Limiting in the sense that you can't easily, for example, play an animation and also get user input

# Software

On the software side of things, there are two important directories:
* *./src*, which have the initializing/main code
* *./lib/game_system*, which have all the game logic

The files on those directories are the main one to change in order to make any modification to the game. 

For example, to change from the normal game mode to the simpler one, you have to go tho the *main.cpp* in *./src*, and change the method called in loop:

```cpp
void loop()
{
    // This is the normal game mode. Default
    gameSystem.gameMode1();

    // Simpler version (matching colors)
    // gameSystem.gameMode2();
    
    // This is some kind of "menu" to ask every time the desired game mode
    // gameSystem.selectGameMode();
}
```