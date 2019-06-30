#include <torch/torch.h>
#include <iostream>
#include <stdlib.h>
#include <torch/csrc/autograd/variable.h>

//using namespace std;

torch::Tensor function()
{
  torch::Tensor a = torch::ones({3, 33});
  return a;
}

torch::Tensor binary(torch::Tensor a, int l = 11)
{
  torch::Tensor b = torch::ones({1, l});
  int index = 0;
  while (l)
  {
    b[0][index++] = a % 2;
    a = (a - a % 2) / 2;
    l--;
  }
  //std::cout << "Binary here" << b;
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
      std::cout << temp[y][i];
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

torch::Tensor powersof2(torch::Tensor b, int rows = 3, int k = 3, int l = 11)
{
  torch::Tensor ans = torch::zeros({rows, k * l});
  for (int y = 0; y < rows; y++)
  {
    int size = 0;
    for (int i = 0; i < k; i++)
    {
      for (int j = 0; j < l; j++)
      {
        ans[rows][size++] = pow(2, j) * b[rows][i];
      }
    }
  }
  return ans;
}

