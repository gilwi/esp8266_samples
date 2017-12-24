int D0_pin = 16;
int D1_pin = 5;
int D2_pin = 4;

int D5_pin = 14;
int D6_pin = 12;
int D7_pin = 13;

void init_fire(int red1, int red2) {
  digitalWrite(red1, HIGH);
  digitalWrite(red2, HIGH);
  delay(500);
}

void fire_cycle(int green, int orange, int red) {
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  delay(2000);

  digitalWrite(green, LOW);
  digitalWrite(orange, HIGH);
  delay(800);

  digitalWrite(orange, LOW);
  digitalWrite(red, HIGH);
  delay(500);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(D0_pin, OUTPUT); //green
  pinMode(D1_pin, OUTPUT); //orange
  pinMode(D2_pin, OUTPUT); //red

  pinMode(D5_pin, OUTPUT); //green
  pinMode(D6_pin, OUTPUT); //orange
  pinMode(D7_pin, OUTPUT); //red
  init_fire(D2_pin, D7_pin);
}

void loop() {
  // put your main code here, to run repeatedly:

  fire_cycle(D0_pin, D1_pin, D2_pin);
  fire_cycle(D5_pin, D6_pin, D7_pin);

  
}
