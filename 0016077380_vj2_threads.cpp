#include <iostream>
#include <cstdlib>
#include <csignal>
#include <pthread.h>
using namespace std;

int **tField;
void *fillField(void *x);
void *tCalculate(void *x);
int temp, a, b, c, d, e, f, g;

int main (int arg, char *argc[])
{
  sigset(SIGKILL, NULL);
  int M = atoi(argc[1]);
  tField = new int*[M];
  for (a = 0; a < M; a++)
    tField[a] = new int[30];
  pthread_t tid1[M];
  pthread_t tid2[M];
  temp = 0;
 
  for (b = 0; b < M; b++)
  {
    if(pthread_create (&tid1[b], NULL, fillField, &temp) != 0)
    {
      cout << "Creating thread " << b+1 << " failed!" << endl;
      exit(1);
    }
  }
   
  for (c = 0; c < M; c++)
     pthread_join(tid1[c], NULL);
 
  temp = 0;

  for (d = 0; d < M; d++)
  {
    if(pthread_create (&tid2[d], NULL, tCalculate, &temp) != 0)
    {
      cout << "Creating thread " << d+1 << "failed!" << endl;
      exit(1);
    }
  sleep(2);
  }
  
  for (e = 0; e < M; e++)
     pthread_join(tid2[e], NULL);
  
  return 0;
}

void *fillField (void *x)
{
  for (f = 0; f < 30; f++)
  {
    tField[temp][f] = rand() % 100;
  }
  temp++;
};

void *tCalculate (void *x)
{
  int sum = 0;
  float arith = 0;

  for (int g = 0; g < 30; g++)
      sum += tField[temp][g];
  
  temp++;
  cout << "Thread " << temp << " sum: " << sum << endl;
  sleep(1);
  arith = sum/30;
  cout << "Thread " << temp << " arithm: " << arith << endl;
};
