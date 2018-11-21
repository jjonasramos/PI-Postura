const int tempo = 500;

const int buzzerPower = 11;
const int buzzerGround = 10;

const int groundpin = 10;             // negativo
//const int powerpin = A5;              // positivo

const int xpin = A3;                  // x - acelerometro
const int ypin = A4;                  // y - acelerometro
const int zpin = A5;                   // z - acelerometro

#define ADEQUADA   0
#define MMADEQUADA 1
#define INADEQUADA 2

typedef struct
{
  int somBuzzer;
  int delay;
} Output;

void setup() 
{
  Serial.begin(9600);
  
  pinMode(buzzerPower, OUTPUT);

  // definir o ground e power para o acelerometro
  pinMode(buzzerGround, OUTPUT);
  //pinMode(powerpin, OUTPUT);
  digitalWrite(buzzerGround, LOW);
  //digitalWrite(powerpin, HIGH);
}

/*void dispararBuzzer(int ypin) 
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
}*/

void loop() 
{
  int x = analogRead(xpin);
  int y = analogRead(ypin);
  int z = analogRead(zpin);
  Serial.print("x = ");
  Serial.print(x);
  Serial.print("\t");
  Serial.print("y = ");
  Serial.print(y);
  Serial.print("\t");
  Serial.print("z = ");
  Serial.print(z);
  Serial.println();

  verificarPostura(y);

  delay(tempo);
}

void verificarPostura(int x)
{
  Output out = fuzzy(x);

  if (out.somBuzzer != 0)
    dispararBuzzer(out);
}

void dispararBuzzer(Output out)
{
    tone(buzzerPower, out.somBuzzer); 
    delay(out.delay);
    noTone(buzzerPower);
    delay(out.delay);
}

Output fuzzy(int x)
{
  int i;

  float* pertinencia = fuzzificar(x);

  int postura = maxIndex(pertinencia, 3);

  Output out = inferirEDefuzificar(postura);

  printf("Fuzzy: ");
  for (i = 0; i < 3; i++)
    printf("%.3f ", pertinencia[i]);

  printf("\n\nSom Buzzer: %i\n", out.somBuzzer);
  printf("Delay: %i\n", out.delay);

  free(pertinencia);

  return out;
}

float* fuzzificar(float x)
{
  float* pertinencia = (float*)malloc(sizeof(float) * 3);

  pertinencia[0] = cPostAdequada(x);
  pertinencia[1] = cPostMMAdequada(x);
  pertinencia[2] = cPostInadequada(x);

  return pertinencia;
}

Output inferirEDefuzificar(int postura)
{
  Output out;

  switch (postura)
  {
  case ADEQUADA:
    out.somBuzzer = 0;
    out.delay = 0;
    break;

  case MMADEQUADA:
    out.somBuzzer = 100;
    out.delay = 10;
    break;

  case INADEQUADA:
    out.somBuzzer = 1500;
    out.delay = 50;
    break;
  }

  return out;
}

float cPostAdequada(float x) {
  return tramp(x, 0, 404, 414, 419);
}

float cPostMMAdequada(float x) {
  return trimf(x, 413, 422, 430);
}

float cPostInadequada(float x) {
  return tramp(x, 423, 430, 440, 445);
}

float tramp(float x, float a, float b, float c, float d)
{
  float min1 = (x - a) / (b - a);
  float min2 = 1;
  float min3 = (d - x) / (d - c);

  //printf("\n\nmin: %.3f   %.3f\n\n", min1);

  return max(min(min(min1, min2), min3), 0.0f);
}

float trimf(float x, float a, float b, float c)
{
  float min1 = (x - a) / (b - a);
  float min2 = (c - x) / (c - b);

  return max(min(min1, min2), 0.0f);
}

int maxIndex(float* x, int n)
{
  float maxIndex = 0;
  float maior = x[0];
  int i;

  for (i = 1; i < n; i++)
    if (x[i] > maior)
    {
      maxIndex = i;
      maior = x[i];
    }

  return maxIndex;
}
