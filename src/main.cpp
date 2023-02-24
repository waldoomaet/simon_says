#include <Arduino.h>
#include "pitches.h"

#define COUNT_RESET A4
#define COUNT_UP A5
#define RED_BUTTON 2
#define YELLOW_BUTTON 3
#define BLUE_BUTTON 4
#define GREEN_BUTTON 5
#define BUZZER 6
#define DEBOUNCE_TIME 200

struct TonePin
{
  int tone;
  int pin;
};

const TonePin tonePins[] = {{NOTE_G3, RED_BUTTON}, {NOTE_C4, YELLOW_BUTTON}, {NOTE_E4, BLUE_BUTTON}, {NOTE_G5, GREEN_BUTTON}};

int gameIndex = 0;
int gameSequence[99];

void pinsAsInputs()
{
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(YELLOW_BUTTON, INPUT_PULLUP);
  pinMode(BLUE_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

void pinsAsOutputs()
{
  pinMode(RED_BUTTON, OUTPUT);
  pinMode(YELLOW_BUTTON, OUTPUT);
  pinMode(BLUE_BUTTON, OUTPUT);
  pinMode(GREEN_BUTTON, OUTPUT);
}

void turnAllPins(int state)
{
  digitalWrite(RED_BUTTON, state);
  digitalWrite(YELLOW_BUTTON, state);
  digitalWrite(BLUE_BUTTON, state);
  digitalWrite(GREEN_BUTTON, state);
}

int buttonPushed()
{
  pinsAsInputs();
  while (1)
  {
    if (!digitalRead(RED_BUTTON))
    {
      tone(BUZZER, tonePins[0].tone, 200);
      delay(200);
      return RED_BUTTON;
    }
    else if (!digitalRead(YELLOW_BUTTON))
    {
      tone(BUZZER, tonePins[1].tone, 200);
      delay(200);
      return YELLOW_BUTTON;
    }
    else if (!digitalRead(BLUE_BUTTON))
    {
      tone(BUZZER, tonePins[2].tone, 200);
      delay(200);
      return BLUE_BUTTON;
    }
    else if (!digitalRead(GREEN_BUTTON))
    {
      tone(BUZZER, tonePins[3].tone, 200);
      delay(200);
      return GREEN_BUTTON;
    }
  }
}

void interactCounter(int pin)
{
  digitalWrite(pin, HIGH);
  delay(5);
  digitalWrite(pin, LOW);
}

void winTone()
{
  tone(BUZZER, NOTE_B4, 100);
  delay(150);
  tone(BUZZER, NOTE_C5, 100);
  delay(150);
  tone(BUZZER, NOTE_CS5, 100);
  delay(150);
  tone(BUZZER, NOTE_D5, 100);
  delay(325);
  tone(BUZZER, NOTE_G5, 150);
  delay(150);
  tone(BUZZER, NOTE_F5, 200);
  delay(150);
}

void gameOverTone()
{
  tone(BUZZER, NOTE_E5);
  delay(100);
  noTone(BUZZER);
  delay(100);
  tone(BUZZER, NOTE_E5);
  delay(100);
  noTone(BUZZER);
  delay(100);
  tone(BUZZER, NOTE_E5);
  delay(100);
  noTone(BUZZER);
  delay(100);
  tone(BUZZER, NOTE_B5);
  delay(300);
  noTone(BUZZER);
  delay(100);
  tone(BUZZER, NOTE_A5);
  delay(100);
  noTone(BUZZER);
  delay(100);
  tone(BUZZER, NOTE_FS5);
  delay(100);
  noTone(BUZZER);

  delay(100);
  tone(BUZZER, NOTE_D5);
  delay(100);
  noTone(BUZZER);

  delay(100);
  tone(BUZZER, NOTE_G5);
  delay(100);
  noTone(BUZZER);

  delay(500);
  tone(BUZZER, NOTE_C5);
  delay(105);
  noTone(BUZZER);

  delay(105);
  tone(BUZZER, NOTE_D5);
  delay(105);
  noTone(BUZZER);

  delay(105);
  tone(BUZZER, NOTE_G4);
  delay(105);
  noTone(BUZZER);
}

void bootUpTone()
{
  delay(500);
  tone(BUZZER, NOTE_A4, 100);
  delay(150);
  tone(BUZZER, NOTE_C5, 100);
  delay(150);
  tone(BUZZER, NOTE_D5, 100);
  delay(150);
  tone(BUZZER, NOTE_A4, 100);
  delay(150);
  tone(BUZZER, NOTE_C5, 100);
  delay(150);
  tone(BUZZER, NOTE_D5, 100);
  delay(150);
  tone(BUZZER, NOTE_G4, 100);
  delay(150);
  tone(BUZZER, NOTE_A4, 100);
  delay(150);
  tone(BUZZER, NOTE_E5, 100);
  delay(150);
  tone(BUZZER, NOTE_G4, 100);
  delay(150);
  tone(BUZZER, NOTE_A4, 100);
  delay(150);
  tone(BUZZER, NOTE_F5, 100);
  delay(150);
  tone(BUZZER, NOTE_E5, 100);
  delay(150);
  tone(BUZZER, NOTE_C5, 100);
  delay(150);
  tone(BUZZER, NOTE_A4, 100);
  delay(150);
  tone(BUZZER, NOTE_F4, 100);
  delay(150);
  tone(BUZZER, NOTE_A4, 100);
  delay(150);
  tone(BUZZER, NOTE_C5, 100);
  delay(150);
  tone(BUZZER, NOTE_E5, 100);
  delay(150);
  tone(BUZZER, NOTE_D5, 100);
  delay(150);
  tone(BUZZER, NOTE_G4, 100);
  delay(150);
  tone(BUZZER, NOTE_A4, 100);
  delay(150);
  tone(BUZZER, NOTE_C5, 100);
  delay(150);
}

void bootUp()
{
  bootUpTone();
  pinsAsOutputs();
  turnAllPins(HIGH);

  digitalWrite(RED_BUTTON, LOW);
  delay(500);
  digitalWrite(RED_BUTTON, HIGH);

  digitalWrite(YELLOW_BUTTON, LOW);
  delay(500);
  digitalWrite(YELLOW_BUTTON, HIGH);

  digitalWrite(BLUE_BUTTON, LOW);
  delay(500);
  digitalWrite(BLUE_BUTTON, HIGH);

  digitalWrite(GREEN_BUTTON, LOW);
  delay(500);
  digitalWrite(GREEN_BUTTON, HIGH);
}

void gameOver()
{
  gameOverTone();
  pinsAsOutputs();
  for (int i = 0; i < 3; i++)
  {
    turnAllPins(LOW);
    delay(500);
    turnAllPins(HIGH);
    delay(500);
  }
}

void resetCount()
{
  interactCounter(COUNT_RESET);
}

void incrementCount()
{
  interactCounter(COUNT_UP);
}

void generateNextPlay()
{
  int rng = random(0, 4);
  switch (rng)
  {
  case 0:
    gameSequence[gameIndex] = RED_BUTTON;
    break;
  case 1:
    gameSequence[gameIndex] = YELLOW_BUTTON;
    break;
  case 2:
    gameSequence[gameIndex] = BLUE_BUTTON;
    break;
  case 3:
    gameSequence[gameIndex] = GREEN_BUTTON;
    break;
  }
  gameIndex++;
}

bool checkUserSequence()
{
  for (int i = 0; i < gameIndex; i++)
  {
    int button = buttonPushed();
    if (button != gameSequence[i])
    {
      return false;
    }
  }
  return true;
}

void playGameSequence()
{
  pinsAsOutputs();
  for (int i = 0; i < gameIndex; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      if (tonePins[j].pin == gameSequence[i])
      {
        tone(BUZZER, tonePins[j].tone, 300);
        digitalWrite(gameSequence[i], LOW);
        delay(300);
        digitalWrite(gameSequence[i], HIGH);
        delay(100);
        break;
      }
    }
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(COUNT_RESET, OUTPUT);
  pinMode(COUNT_UP, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(COUNT_RESET, LOW);
  digitalWrite(COUNT_UP, LOW);

  bootUp();
  resetCount();
  randomSeed(analogRead(0));
}

void loop()
{
  generateNextPlay();
  playGameSequence();
  bool correct = checkUserSequence();
  if (correct)
  {
    winTone();
    incrementCount();
  }
  else
  {
    gameOver();
    resetCount();
    gameIndex = 0;
  }
}