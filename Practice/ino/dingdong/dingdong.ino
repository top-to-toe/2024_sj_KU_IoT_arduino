

const int pinSW = 2;
const int pinBuzz = 11;
const int ding = 784; // 300
const int dong = 659; // 500

int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(pinSW, INPUT);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(pinSW);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        tone(pinBuzz, ding); delay(300); noTone(pinBuzz);
        tone(pinBuzz, dong); delay(500); noTone(pinBuzz);
        tone(pinBuzz, ding); delay(300); noTone(pinBuzz);
        tone(pinBuzz, dong); delay(500); noTone(pinBuzz);
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
