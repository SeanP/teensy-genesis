//#define TEENSY_GENESIS_DEBUG

#define AXIS_MIN 0
#define AXIS_MID 512
#define AXIS_MAX 1023

// Pins
const int DPAD_LEFT_PIN  = 15;
const int DPAD_RIGHT_PIN = 16;
const int DPAD_UP_PIN    = 13;
const int DPAD_DOWN_PIN  = 14;

const int START_PIN = 22;
const int A_PIN     = 10;
const int B_PIN     = 9;
const int C_PIN     = 12;


// State storage
int dpadLeftState  = HIGH;
int dpadRightState = HIGH;
int dpadUpState    = HIGH;
int dpadDownState  = HIGH;

int aState     = HIGH;
int bState     = HIGH;
int cState     = HIGH;
int startState = HIGH;

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
    if (LOW == dpadLeftState) {
        Joystick.X(AXIS_MIN);
    } else if (LOW == dpadRightState) {
        Joystick.X(AXIS_MAX);
    } else {
        Joystick.X(AXIS_MID);
    }

    if (LOW == dpadUpState) {
        Joystick.Y(AXIS_MIN);
    } else if (LOW == dpadDownState) {
        Joystick.Y(AXIS_MAX);
    } else {
        Joystick.Y(AXIS_MID);
    }
}

void loop() {
    bool stateChanged = false;
    int currState = digitalRead(DPAD_LEFT_PIN);
    if (currState != dpadLeftState) {
      dpadLeftState = currState;
      stateChanged = true;
    }

    currState = digitalRead(DPAD_RIGHT_PIN);
    if (currState != dpadRightState) {
      dpadRightState = currState;
      stateChanged = true;
    }

    currState = digitalRead(DPAD_UP_PIN);
    if (currState != dpadUpState) {
      dpadUpState = currState;
      stateChanged = true;
    }

    currState = digitalRead(DPAD_DOWN_PIN);
    if (currState != dpadDownState) {
      dpadDownState = currState;
      stateChanged = true;
    }

    currState = digitalRead(START_PIN);
    if (currState != startState) {
      startState = currState;
      stateChanged = true;
    }

    currState = digitalRead(A_PIN);
    if (currState != aState) {
      aState = currState;
      stateChanged = true;
    }

    currState = digitalRead(B_PIN);
    if (currState != bState) {
        bState = currState;
        stateChanged = true;
    }

    currState = digitalRead(C_PIN);
    if (currState != cState) {
        cState = currState;
        stateChanged = true;
    }

    if (stateChanged) {
#ifdef TEENSY_GENESIS_DEBUG
        Serial.println("Buttons:");
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
        
        // USB expects pressed=1, but for us pressed=0. XOR to normalize.
        Joystick.button(1, aState ^ 1);
        Joystick.button(2, bState ^ 1);
        Joystick.button(3, cState ^ 1);
        Joystick.button(4, startState ^ 1);

        Joystick.send_now();
    }

    delay(5);
}
