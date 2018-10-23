const int tempo = 1000;

const int buzzer = 2;

const int groundpin = A4;             // negativo
const int powerpin = A5;              // positivo
const int xpin = 11;                  // x - acelerometro
const int ypin = 10;                  // y - acelerometro
const int zpin = 9;                   // z - acelerometro

void setup() {

  Serial.begin(9600);
  
  pinMode(buzzer, OUTPUT);

  // definir o ground e power para o acelerometro
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  digitalWrite(groundpin, LOW);
  digitalWrite(powerpin, HIGH);
}

void dispararBuzzer(int ypin) {

  if(ypin <= 400) {
    tone(buzzer, 5000);
  } else if(ypin <= 450) {
    tone(buzzer, 3000);
    delay(100);
    noTone(buzzer);
    delay(100);
  } else {
    tone(buzzer, 1000);
    delay(1000);
    noTone(buzzer);
    delay(1000);
  }
  
}

void loop() {
  
  // dispararBuzzer();

  Serial.print("x = ");
  Serial.print(analogRead(xpin));
  Serial.print("\t");
  Serial.print("y = ");
  Serial.print(analogRead(ypin));
  Serial.print("\t");
  Serial.print("z = ");
  Serial.print(analogRead(zpin));
  Serial.println();
  delay(tempo);

  dispararBuzzer(analogRead(ypin));
  
}
