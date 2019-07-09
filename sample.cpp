#include "basic_functions.h"
#include "decrypt.h"
#include "encrypt.h"

int main()  {
  torch::Tensor Sk = GenSecretKey(10, 1024);
  // std::cout<<Sk<<std::endl;
  torch::Tensor Pk = GenPublicKey(Sk, 10, 10, 1024, 0.01);
  // std::cout<<Pk<<std::endl;
  torch::Tensor C1 = GSWEncrypt(Pk, 10, 10, 10, 1024);
  // std::cout<<1<<std::endl;
  // std::cout<<C1<<std::endl;
  torch::Tensor C2 = GSWEncrypt(Pk, 22, 10, 10, 1024);
  // std::cout<<1<<std::endl;
  torch::Tensor C12 = torch::remainder(torch::add(C1,C2), 1024);
  // std::cout<<1<<std::endl;
  //std::cout<<1<<std::endl;
  torch::Tensor C21 = torch::remainder(torch::mm(C2,C1), 1024);
  // std::cout<<1<<std::endl;
  //std::cout<<1<<std::endl;
  //torch::Tensor VSk = torch::transpose(Sk,0,1);
  // torch::Tensor VSk = powersof2(Sk, 10, 1024);
  // std::cout<<1<<std::endl;
  // std::cout<<VSk<<std::endl;
  //torch::Tensor m12 = lweSymDecrypt(C12,VSk);
  //std::cout<<1<<std::endl;
  //torch::Tensor m21 = lweSymDecrypt(C21,VSk);
  //std::cout<<1<<std::endl;
  torch::Tensor m1 = MPDecrypt(C1,Sk,10, 1024);
  torch::Tensor m2 = MPDecrypt(C2,Sk,10, 1024);
  torch::Tensor m12 = MPDecrypt(C12,Sk,10, 1024);
  // torch::Tensor m21 = MPDecrypt(C21,Sk,10, 1024);
  torch::Tensor m21 = torch::remainder(torch::mm(C1, m2), 1024);
  // std::cout<<torch::remainder(torch::mm(C1, VSk),1024)[0]<<std::endl;
  // std::cout<<torch::remainder(torch::mm(C2, VSk),1024)[0]<<std::endl;
  // std::cout<<torch::remainder(torch::mm(C12, VSk),1024)[0]<<std::endl;
  // std::cout<<torch::remainder(torch::mm(C21, VSk),1024)[0]<<std::endl;
  // torch::Tensor m2 = lweSymDecrypt(C2,VSk);
  std::cout<<m1[0]<<std::endl;
  std::cout<<m2[0]<<std::endl;
  std::cout<<m12[0]<<std::endl;
  std::cout<<floor(m21[0])<<std::endl;

  return 0;
}