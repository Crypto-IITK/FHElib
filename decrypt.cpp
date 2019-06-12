#include <iostream>
#include <cmath>
int lweSymDecrypt(int **sample, int *key, int n){
  float x=0;
  int max=0,i;
  for(int j=0;j<n;j++){
    if(key[j]>max)
      i=j;
  }
  for(int j=0;j<n;j++)
    x+=sample[i][j]*key[j];
  x=x/key[i];
  x=(int)floor(x);
  return x;
}