#define watersensor A0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Water level = ");
  int waterLevel;
  if (analogRead(watersensor) <= 320){
    waterLevel = 0; 
  }
  if (analogRead(watersensor) > 321 &&  analogRead(watersensor) <= 370){
    waterLevel = 25; 
  }
  if (analogRead(watersensor) > 371 &&  analogRead(watersensor) <= 415){
    waterLevel = 50; 
  }
  if (analogRead(watersensor) > 416 &&  analogRead(watersensor) <= 428){
    waterLevel = 75; 
  }
  if (analogRead(watersensor) >= 429){
    waterLevel = 100; 
  }
  Serial.print(waterLevel);
  Serial.println("%"); 
  delay(1000);
}

