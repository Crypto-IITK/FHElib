#include "basic_functions.h"
#include "decrypt.h"
#include "encrypt.h"

int main()  {
  torch::Tensor Sk = GenSecretKey(10, 1024);
  torch::Tensor Pk = GenPublicKey(Sk, 10, 10, 1024, 0.001);
  torch::Tensor v = powersof2(Sk, 10, 1024);
  torch::Tensor C1 = GSWEncrypt(Pk, 10, 10, 10, 1024);
  torch::Tensor C2 = GSWEncrypt(Pk, 32, 10, 10, 1024);
  torch::Tensor C12 = torch::remainder(torch::add(C1,C2), 1024);
  torch::Tensor C21 = torch::remainder(torch::mm(C1,C2), 1024);
  torch::Tensor m1 = MPDecrypt(C1, v, 10, 1024);
  torch::Tensor m2 = MPDecrypt(C2, v, 10, 1024);
  torch::Tensor m12 = MPDecrypt(C12, v, 10, 1024);
  torch::Tensor m21 = MPDecrypt(C21, v, 10, 1024);
  std::cout<<m1<<std::endl;
  std::cout<<m2<<std::endl;
  std::cout<<m12<<std::endl;
  std::cout<<m21<<std::endl;

  return 0;
}