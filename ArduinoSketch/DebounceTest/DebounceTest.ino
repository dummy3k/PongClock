const byte PIN_INT0 = 2;

void setup() {
  pinMode(PIN_INT0, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_INT0), int0, CHANGE);
}

void loop() {

}

void int0() {
  //state = !state;
}
