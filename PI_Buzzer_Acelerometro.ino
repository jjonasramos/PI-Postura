const int tempo = 1000;

const int buzzerPower = 11;
const int buzzerGround = 10;

const int groundpin = 10;             // negativo
//const int powerpin = A5;              // positivo

const int xpin = A5;                  // x - acelerometro
const int ypin = A4;                  // y - acelerometro
const int zpin = A3;                   // z - acelerometro

void setup() {

  Serial.begin(9600);
  
  pinMode(buzzerPower, OUTPUT);

  // definir o ground e power para o acelerometro
  pinMode(buzzerGround, OUTPUT);
  //pinMode(powerpin, OUTPUT);
  digitalWrite(buzzerGround, LOW);
  //digitalWrite(powerpin, HIGH);
}

void dispararBuzzer(int ypin) 
{
  if(ypin <= 400) {
    tone(buzzerPower, 5000);
  } else if(ypin <= 450) {
    tone(buzzerPower, 3000);
    delay(100);
    noTone(buzzerPower);
    delay(100);
  } else {
    tone(buzzerPower, 1000);
    delay(1000);
    noTone(buzzerPower);
    delay(1000);
  }
  
}

void loop() 
{
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

  //dispararBuzzer(analogRead(ypin));
}
