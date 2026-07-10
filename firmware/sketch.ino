#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int redLedPin = 2;
const int yellowLedPin = 4;
const int blueLedPin = 7;
const int buttonPin = 8;

int lastButtonState;

unsigned long targetWaitTimeRedYellow = 0;
unsigned long waitTimeDelay = 0;
unsigned long currentMillis = 0;
unsigned long startMillisRedYellow = 0;
unsigned long startMillisDelay = 0;
unsigned long startClickTime = 0;
unsigned long clickTime = 0;
unsigned long startMillisTryAgain = 0;

unsigned long startMillisTooLate = 0;
unsigned long tooLateWaitTime = 22000;


unsigned long reactionSpeed;

enum gameState {
  waitingToStart,
  showingRed,
  showingYellow,
  showingResults,
  showingTryAgain,
  showingTooEarlyResults,
  showingTooEarlyTryAgain,
  showingTooLateResults,
  showingTooLateTryAgain
};

gameState currentState = waitingToStart;

bool screenNeedsUpdate = false;

void setup() {
  Serial.begin(1000);
  setupAll();
}

void setupButton() {
  pinMode(buttonPin, INPUT_PULLUP);
  lastButtonState = digitalRead(buttonPin);
}

void setupLED() {
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
}

void setupLCD() {
  lcd.init();
  lcd.backlight();

  startingLcdTxt();
}

void startingLcdTxt() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Click Button to ");
  lcd.setCursor(0, 1);
  lcd.print("Start Game");
}

void setupAll() {
  currentState = waitingToStart;
  screenNeedsUpdate = false;

  setupLED();
  setupLCD();
  setupButton();

  startMillisRedYellow = millis();
  startMillisDelay = millis();
  randomSeed(analogRead(A0)); 
}

void buttonPress() {
  if (currentState == showingYellow) {
    clickTime = millis();
    reactionSpeed = (clickTime - startClickTime) / 2;

    startMillisTryAgain = millis();

    screenNeedsUpdate = true;
    currentState = showingResults;

    changeLedState(redLedPin, false);
    changeLedState(yellowLedPin, false);
    changeLedState(blueLedPin, false);
  }
  else if (currentState == showingRed) {
    startMillisTryAgain = millis();

    screenNeedsUpdate = true;
    currentState = showingTooEarlyResults;

    changeLedState(redLedPin, false);
    changeLedState(yellowLedPin, false);
    changeLedState(blueLedPin, false);
  }
  else if (currentState == waitingToStart) {
    changeLedState(blueLedPin, true);
    changeLcdText("Game Starting!");
    delay(1000);
    startGame();
  }
  else if (currentState == showingResults || currentState == showingTryAgain || currentState == showingTooEarlyResults || currentState == showingTooEarlyTryAgain || currentState == showingTooLateResults || currentState == showingTooLateTryAgain) {
    reset();
  }
}

void enableEndScreen() {
  if (!screenNeedsUpdate) {
    return;
  }

  screenNeedsUpdate = false;

  lcd.clear();
  if (currentState == showingResults) {
    lcd.setCursor(0, 0);
    lcd.print("Reaction Time: ");
    lcd.setCursor(0, 1);
    lcd.print((String)reactionSpeed);
    lcd.print(" ms");
  }
  else if (currentState == showingTryAgain || currentState == showingTooEarlyTryAgain || currentState == showingTooLateTryAgain) {
    lcd.setCursor(0, 0);
    lcd.print("Click Button ");
    lcd.setCursor(0, 1);
    lcd.print("to Try Again");
  }
  else if (currentState == showingTooEarlyResults) {
    lcd.setCursor(0, 0);
    lcd.print("Too Early!");
    lcd.setCursor(0, 1);
    lcd.print("You Failed!");
  }
  else if (currentState == showingTooLateResults) {
    lcd.setCursor(0, 0);
    lcd.print("Too Late!");
    lcd.setCursor(0, 1);
    lcd.print("You Failed!");
  }
}

void startGame() {
  currentState = showingRed;
  changeLcdText("Get Ready!");
  targetWaitTimeRedYellow = random(4000, 8000);
  changeLedState(redLedPin, true);

  startMillisRedYellow = millis();
}

void changeLedState(int pin, bool turnOn) {
  if (turnOn) {
    digitalWrite(pin, HIGH);
  }
  else {
    digitalWrite(pin, LOW);
  }
}

void changeLcdText(String txt) {
  lcd.clear();
  lcd.print(txt);
}

void turnYellow() {
  startMillisTooLate = millis();
  startMillisRedYellow = millis();
  currentState = showingYellow;
  changeLedState(redLedPin, false);
  changeLedState(yellowLedPin, true);
  changeLcdText("Click!");
  startClickTime = millis();
}

void loop() {
  currentMillis = millis();
  int currentButtonState = digitalRead(buttonPin);

  if (lastButtonState == HIGH && currentButtonState == LOW && (currentMillis - startMillisDelay) >= waitTimeDelay) {
    buttonPress();
    waitTimeDelay = 60;
    startMillisDelay = millis();
  }

  lastButtonState = currentButtonState;

  currentMillis = millis();
  if (currentState == showingRed) {
    if ((currentMillis - startMillisRedYellow) >= targetWaitTimeRedYellow) {
      turnYellow();
    }
  }

  currentMillis = millis();
  if (currentState == showingYellow) {
    if ((currentMillis - startMillisTooLate) >= tooLateWaitTime) {
      startMillisTryAgain = millis();

      screenNeedsUpdate = true;
      currentState = showingTooLateResults;

      changeLedState(redLedPin, false);
      changeLedState(yellowLedPin, false);
      changeLedState(blueLedPin, false);
    }
  }

  currentMillis = millis();
  if (currentState == showingResults || currentState == showingTryAgain) {
    if ((currentMillis - startMillisTryAgain) >= 1600) {
      if (currentState == showingResults) {
        currentState = showingTryAgain;
      }
      else if (currentState == showingTryAgain) {
        currentState = showingResults;
      }
      startMillisTryAgain = millis();
      screenNeedsUpdate = true;
    }
    enableEndScreen();
  }

  // Too Early
  if (currentState == showingTooEarlyResults || currentState == showingTooEarlyTryAgain) {
    if ((currentMillis - startMillisTryAgain) >= 1600) {
      if (currentState == showingTooEarlyResults) {
        currentState = showingTooEarlyTryAgain;
      }
      else if (currentState == showingTooEarlyTryAgain) {
        currentState = showingTooEarlyResults;
      }
      startMillisTryAgain = millis();
      screenNeedsUpdate = true;
    }
    enableEndScreen();
  }

  // Too Late
  if (currentState == showingTooLateResults || currentState == showingTooLateTryAgain) {
    if ((currentMillis - startMillisTryAgain) >= 1600) {
      if (currentState == showingTooLateResults) {
        currentState = showingTooLateTryAgain;
      }
      else if (currentState == showingTooLateTryAgain) {
        currentState = showingTooLateResults;
      }
      startMillisTryAgain = millis();
      screenNeedsUpdate = true;
    }
    enableEndScreen();
  }
}

void reset() {
  changeLedState(redLedPin, false);
  changeLedState(yellowLedPin, false);
  changeLedState(blueLedPin, true);
  changeLcdText("Game Starting!");
  delay(1500);
  startGame();
}