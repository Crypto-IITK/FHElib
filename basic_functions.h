#include <torch/torch.h>
#include <iostream>
#include <stdlib.h>
#include <torch/csrc/autograd/variable.h>
#include <cmath>

//using namespace std;

torch::Tensor function()
{
  torch::Tensor a = torch::ones({3, 33});
  return a;
}

torch::Tensor binaryVector(torch::Tensor a, int n, int q) {
  int l=floor(log2(q)+1);
  torch::Tensor b  = torch::ones({(n+1)*l, 1});
  int i=0, j=0;
  torch::Tensor k;
  while(i<=n) {
    j=0;
    k=a[i];
    while(j<l) {
      //std::cout<<b<<std::endl;
      b[i*l+l-j-1]=torch::remainder(k,2);
      k=(k-torch::remainder(k,2))/2;
      j++;
    }
    i++;
  }
  return b;
}

torch::Tensor binary(torch::Tensor a, int l = 11)
{
  torch::Tensor b = torch::ones({1,l});
  int index = 0;
  while (l)
  {
    b[0][index++] = a % 2;
    a = (a - a % 2) / 2;
    l--;
  }
  return b;
}

torch::Tensor bit_decomp(torch::Tensor temp, int rows = 5, int k = 3, int l = 11)
{
  torch::Tensor b = torch::ones({rows, k * l});
  for (int y = 0; y < rows; y++)
  {
    int i = 0, size = 0;
    for (int i = 0; i < k; i++)
    {
      torch::Tensor c = binary(temp[y][i], l);
      //std::cout << temp[y][i];
      for (int j = 0; j < l; j++)
      {
        b[y][size++] = c[0][j];
      }
    }
  }
  //std::cout << "Bit Decomp done" << b;
  return b;
}

torch::Tensor bit_decomp_inverse(torch::Tensor temp, int rows = 5, int k = 3, int l = 11)
{
  torch::Tensor b = torch::zeros({rows, k});
  for (int y = 0; y < rows; y++)
  {
    int i = 0, size = 0, N = k * l, count = 0;
    for (int i = 0; i < k; i++)
    {
      for (int j = 0; j < l; j++)
      {
        b[y][i] += pow(2, j) * temp[y][count++];
        //std::cout << "done here";
      }
    }
  }
  //std::cout << "Bit Decomp inverse done" << b;
  return b;
}

torch::Tensor flatten(torch::Tensor temp, int r = 5, int k = 3, int l = 11)
{
  torch::Tensor b = bit_decomp(bit_decomp_inverse(temp, r, k, l), r, k, l);
  return b;
}

torch::Tensor powersof2(torch::Tensor b, int n = 3, int q = 11) {
  int l=floor(log2(q)+1);
  torch::Tensor ans = torch::zeros({(n+1)*(l), 1});
  for (int i = 0; i <= n; i++)
  {
    for (int j = 0; j < l; j++)
    {
      ans[i*(l)+j] = torch::remainder(pow(2,j)*b[i],q);
    }
  }
  return ans;
}

