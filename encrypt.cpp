#include <torch/torch.h>
#include <iostream>
#include <stdlib.h>
#include <torch/csrc/autograd/variable.h>
#include <cmath>
#include "basic_functions.h"

torch::Tensor GenSecretKey(int n, int q) {
  torch::Tensor t=torch::randint(q, {n+1, 1});
  t[0]=1;
  return t;
}

torch::Tensor GenPublicKey(torch::Tensor Sk, int n, int m, int q, float param) {
  torch::Tensor B=torch::randint(q, {m, n});
  torch::Tensor t=torch::narrow(Sk, 0, 1, n);
  torch::Tensor Bt=torch::remainder(torch::mm(B, -t),q);
  torch::Tensor e=torch::remainder(torch::rand_like(Bt)*param,q);
  torch::Tensor b=torch::remainder(torch::add(Bt,e),q);
  torch::Tensor A=torch::cat({b, B}, 1);
  return A;
}

torch::Tensor GSWEncrypt(torch::Tensor A, int message, int n, int m, int q) {
  //
  int l=floor(log2(q)+1);
  int N = l*(n+1);
  torch::Tensor R=torch::randint(2, {N, m});
  torch::Tensor RA=torch::remainder(torch::mm(R, A),q);
  torch::Tensor messageI= torch::remainder(message*torch::eye(N), q);
  torch::Tensor bd_RA=bit_decomp(RA,N,n+1,l);
  torch::Tensor C=torch::remainder(flatten(torch::add(messageI,bd_RA),N,n+1,l),q);
  return C;
}

int main()  {
  torch::Tensor Sk = GenSecretKey(10, 7);
  torch::Tensor Pk = GenPublicKey(Sk, 10, 9, 7, 0.1);
  torch::Tensor C = GSWEncrypt(Pk, 5, 10, 9, 7);
  //torch::Tensor m = torch::remainder(torch::mm(C, Sk),7);
  //std::cout<<C<<std::endl;
  //std::cout<<m[0]<<std::endl;
  return 0;
}
