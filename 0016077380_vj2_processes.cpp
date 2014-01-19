#include <iostream>
#include <cstdlib>
#include <csignal>
#include <unistd.h>
#include <cmath>
#include <sys/wait.h>
using namespace std;

void processingPolygon(float n, float a)
{
   float P = 0.25*n*a*a/tan(3.14159265358979/n);
   cout << "n = " << n << "  a = " << a << "  P = " << P << endl;
   sleep(1);
   float O = n*a;
   cout << "n = " << n << "  a = " << a << "  O = " << O << endl;
}

int main (int arg, char *argc[])
{
  sigset(SIGKILL, NULL);
  int M = 0;
  while(argc[M] != 0)
  {
    M++;
  }
  M = M-1;
  float polygon[M];
  int i, j, k;

  if(M > 10)
  {
    cout << "Max. 5!" << endl;
    exit(0);
  }

  for(i = 0; i < M; i++)
  {
    polygon[i] = atof(argc[i+1]);
  }

  for(j = 0; j < M; j = j+2)
  {
    sleep(1);
    switch(fork())
    {
      case 0: processingPolygon(polygon[j], polygon[j+1]);
      	      exit(0);
      case -1: cout << "Creating process failed!" << endl;
               break;
      default: break;
    }
  sleep(1);
  }
  
  for(k = 0; k < M; k = k+2)
     wait(NULL);

  return 0;
}
