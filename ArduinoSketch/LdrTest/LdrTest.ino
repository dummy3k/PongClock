#define LDR 3

void setup() {
  Serial.begin(9600);
  
  Serial.println(F("LDR Test v0.1"));
  Serial.println(F(__DATE__));
  Serial.println(F(__TIME__));
    
  pinMode(LDR, INPUT);

}

void loop() {
   int v = analogRead(LDR);
   Serial.println(v);
   delay(1000);
}
