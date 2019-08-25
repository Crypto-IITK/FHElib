#include <torch/torch.h>
#include <iostream>
#include <stdlib.h>
#include <torch/csrc/autograd/variable.h>
#include <cmath>

torch::Tensor MPDecrypt(torch::Tensor C, torch::Tensor key, int n, int q) {
  int l=floor(log2(q)+1);
  int i=0;
  torch::Tensor C_small=torch::narrow(C, 0, 0, l-1);
  torch::Tensor m_array=torch::remainder(torch::mm(C_small,key), 1024);
  torch::Tensor m_final=torch::ones(1);
  m_final[0]=0;
  torch::Tensor m_bit_array=torch::rand_like(m_array);
  for(i=l-2;i>=0;i--) {
    m_bit_array[i]=(((m_array[i]/pow(2,i)).round()-m_final[0])/pow(2,l-2-i)).round();
    m_final=m_final+m_bit_array[i]*key[l-2-i];
  }
  return m_final;
}

// torch::Tensor MPDecrypt(torch::Tensor C, torch::Tensor key, int n, int q) {
//   torch::Tensor m_array=torch::remainder(torch::mm(C,key), q);
//   return m_array;
// }
