#include <Arduino.h>
#include "pitches.h"
#include "game.h"

#define COUNT_RESET A4
#define COUNT_UP A5
#define RED_BUTTON 2    // 1
#define YELLOW_BUTTON 3 // 0
#define BLUE_BUTTON 4   // 2
#define GREEN_BUTTON 5  // 3
#define BUZZER 6
#define DEBOUNCE_TIME 200

Game gameSystem(RED_BUTTON, GREEN_BUTTON, BLUE_BUTTON, YELLOW_BUTTON, BUZZER, COUNT_RESET, COUNT_UP);

void setup()
{
  Serial.begin(115200);
  gameSystem.begin();
  gameSystem.bootUpAnimation();
}

void loop()
{
  // This is the normal game mode. Default
  gameSystem.gameMode1();

  // Simpler version (matching colors)
  // gameSystem.gameMode2();
  
  // This is some kind of "menu" every time ask the desired game mode
  // gameSystem.selectGameMode();
}