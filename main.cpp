#include <iostream>
#include <algorithm>
#include <stdio.h>

using namespace std;

#define ADEQUADA   0
#define MMADEQUADA 1
#define INADEQUADA 2

typedef struct
{
  int somBuzzer;
  int delay;
} Output;

int main();
void verificarPostura(int x);
Output fuzzy(int x);
float* fuzzificar(float x);
Output inferirEDefuzificar(int postura);
float cPostAdequada(float x);
float cPostMMAdequada(float x);
float cPostInadequada(float x);
float tramp(float x, float a, float b, float c, float d);
float trimf(float x, float a, float b, float c);
int maxIndex(float* x, int n);

int main()
{
    int eixo = 0;

    while(eixo >= 0)
    {
        cout << "==========================================" << endl;
        cout << "Digite o valor do eixo: ";
        cin >> eixo;

        verificarPostura(eixo);
        cout << "==========================================" << endl;
    }

    return 0;
}

void verificarPostura(int x)
{
  Output out = fuzzy(x);

  //if (out.somBuzzer != 0)
   // dispararBuzzer(out);
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
    cout << "POSTURA ADEQUADA";
    out.somBuzzer = 0;
    out.delay = 0;
    break;

  case MMADEQUADA:
    cout << "POSTURA + OU - ADEQUADA";
    out.somBuzzer = 100;
    out.delay = 10;
    break;

  case INADEQUADA:
    cout << "POSTURA INADEQUADA";
    out.somBuzzer = 1500;
    out.delay = 50;
    break;
  }

  cout << endl;

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
