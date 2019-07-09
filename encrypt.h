#include <torch/torch.h>
#include <iostream>
#include <stdlib.h>
#include <torch/csrc/autograd/variable.h>
#include <cmath>

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
  int l=floor(log2(q)+1);
  int N = l*(n+1);
  torch::Tensor R=torch::randint(2, {n+1, n});
  torch::Tensor RA=torch::remainder(torch::mm(R, A),q);
  torch::Tensor messageI= torch::remainder(message*torch::eye(n+1), q);
  // torch::Tensor bd_RA=bit_decomp(RA,N,n+1,l);
  torch::Tensor C=torch::remainder(torch::add(messageI,RA),q);
  return C;
}

// torch::Tensor GSWEncrypt(torch::Tensor A, int message, int n, int m, int q) {
//   int l=floor(log2(q)+1);
//   int N = l*(n+1);
//   torch::Tensor R=torch::randint(2, {N, m});
//   torch::Tensor RA=torch::remainder(torch::mm(R, A),q);
//   torch::Tensor messageI= torch::remainder(message*torch::eye(N), q);
//   //std::cout<<RA<<std::endl;
//   torch::Tensor bd_RA=bit_decomp(RA,N,n+1,l);
//   //std::cout<<bit_decomp_inverse(bd_RA, N,n+1,l)<<std::endl;
//   torch::Tensor C=torch::remainder(flatten(torch::add(messageI,bd_RA),N,n+1,l),q);
//   return C;
// }


