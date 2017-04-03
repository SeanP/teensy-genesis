
#define TEENSY_GENESIS_DEBUG

#define HAT_N 0
#define HAT_NE 45
#define HAT_E 90
#define HAT_SE 135
#define HAT_S 180
#define HAT_SW 225
#define HAT_W 270
#define HAT_NW 315
#define HAT_CENTER -1

// Pins
const int DPAD_LEFT_PIN  = 0;
const int DPAD_RIGHT_PIN = 0;
const int DPAD_UP_PIN    = 0;
const int DPAD_DOWN_PIN  = 0;

const int START_PIN = 0;
const int A_PIN     = 0;
const int B_PIN     = 0;
const int C_PIN     = 0;


// State storage
int dpadLeftState = LOW;
int dpadRightState = LOW;
int dpadUpState = LOW;
int dpadDownState = LOW;

int aState = LOW;
int bState = LOW;
int cState = LOW;
int startState = LOW;

// Debounce handling
// TODO

void setup() {

#ifdef TEENSY_GENESIS_DEBUG
    Serial.begin(9600);
#endif

    Joystick.useManualSend(true);

    pinMode(DPAD_LEFT_PIN, INPUT);
    pinMode(DPAD_RIGHT_PIN, INPUT);
    pinMode(DPAD_UP_PIN, INPUT);
    pinMode(DPAD_DOWN_PIN, INPUT);
    pinMode(START_PIN, INPUT);
    pinMode(A_PIN, INPUT);
    pinMode(B_PIN, INPUT);
    pinMode(C_PIN, INPUT);
}

void setDpadDirection() {
    if (LOW == dpadUpState) {
        if (LOW == dpadLeftState) {
            Joystick.hat(HAT_NW);
        } else if (LOW == dpadRightState) {
            Joystick.hat(HAT_NE);
        } else {
            Joystick.hat(HAT_N);
        }
    } else if (LOW == dpadDownState) {
        if (LOW == dpadLeftState) {
            Joystick.hat(HAT_SW);
        } else if (LOW == dpadRightState) {
            Joystick.hat(HAT_SE);
        } else {
            Joystick.hat(HAT_S);
        }
    } else if (LOW == dpadLeftState) {
        Joystick.hat(HAT_W);
    } else if (LOW == dpadRightState) {
        Joystick.hat(HAT_E);
    } else {
        Joystick.hat(HAT_CENTER);
    }
}

void loop() {
    bool stateChanged = false;
    int currState = digitalRead(DPAD_LEFT_PIN);
    if (currState != dpadLeftState) {
      dpadLeftState = currState;
      stateChanged = true;
      // Do the thing.
    }

    currState = digitalRead(DPAD_RIGHT_PIN);
    if (currState != dpadRightState) {
      dpadRightState = currState;
      stateChanged = true;
      // Do the thing.
    }

    currState = digitalRead(DPAD_UP_PIN);
    if (currState != dpadUpState) {
      dpadUpState = currState;
      stateChanged = true;
      // Do the thing.
    }

    currState = digitalRead(DPAD_RIGHT_PIN);
    if (currState != dpadRightState) {
      dpadDownState = currState;
      stateChanged = true;
      // Do the thing.
    }

    currState = digitalRead(START_PIN);
    if (currState != startState) {
      startState = currState;
      stateChanged = true;
      // Do the thing.
    }

    currState = digitalRead(A_PIN);
    if (currState != aState) {
      aState = currState;
      stateChanged = true;
      // Do the thing.
    }

    currState = digitalRead(B_PIN);
    if (currState != bState) {
        bState = currState;
        stateChanged = true;
        // Do the thing.
    }

    currState = digitalRead(C_PIN);
    if (currState != cState) {
        cState = currState;
        stateChanged = true;
        // Do the thing.
    }

    if (stateChanged) {
#ifdef TEENSY_GENESIS_DEBUG
        Serial.println("Buttons: \n");
        Serial.print("\tDPAD_UP: ");
        Serial.println(dpadUpState, DEC);
        Serial.print("\tDPAD_DOWN: ");
        Serial.println(dpadDownState, DEC);
        Serial.print("\tDPAD_LEFT: ");
        Serial.println(dpadLeftState, DEC);
        Serial.print("\tDPAD_RIGHT: ");
        Serial.println(dpadRightState, DEC);
        Serial.print("\tA: ");
        Serial.println(aState, DEC);
        Serial.print("\tB: ");
        Serial.println(bState, DEC);
        Serial.print("\tC: ");
        Serial.println(cState, DEC);
        Serial.print("\tSTART: ");
        Serial.println(startState, DEC);
#endif

        setDpadDirection();
        Joystick.button(1, aState ^ 1);
        Joystick.button(2, bState ^ 1);
        Joystick.button(3, cState ^ 1);
        Joystick.button(4, startState ^ 1);

        Joystick.send_now();
    }

    delay(5);
}
