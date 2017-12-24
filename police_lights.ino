int D0_pin = 16;
int D1_pin = 5;
int D2_pin = 4;

int D5_pin = 14;
int D6_pin = 12;
int D7_pin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(D0_pin, OUTPUT); //green
  pinMode(D1_pin, OUTPUT); //orange
  pinMode(D2_pin, OUTPUT); //red

  pinMode(D5_pin, OUTPUT); //green
  pinMode(D6_pin, OUTPUT); //orange
  pinMode(D7_pin, OUTPUT); //red
}

void loop() {
  // put your main code here, to run repeatedly:

  //first trifeu
  digitalWrite(D2_pin, HIGH);
  digitalWrite(D7_pin, HIGH); 
  delay(500);

  digitalWrite(D2_pin, LOW);
  digitalWrite(D0_pin, HIGH);
  delay(2000);

  digitalWrite(D0_pin, LOW);
  digitalWrite(D1_pin, HIGH);
  delay(800);

  digitalWrite(D1_pin, LOW);
  digitalWrite(D2_pin, HIGH);
  delay(500);

  //second trifeu
  digitalWrite(D7_pin, LOW);
  digitalWrite(D5_pin, HIGH);
  delay(2000);

  digitalWrite(D5_pin, LOW);
  digitalWrite(D6_pin, HIGH);
  delay(800);

  digitalWrite(D6_pin, LOW);

  
}
