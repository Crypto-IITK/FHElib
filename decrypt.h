#include <torch/torch.h>
#include <iostream>
#include <stdlib.h>
#include <torch/csrc/autograd/variable.h>
#include <cmath>

// torch::Tensor MPDecrypt(torch::Tensor C, torch::Tensor key, int n, int q) {
//   int l=floor(log2(q)+1);
//   int i=0;
//   torch::Tensor g=torch::narrow(key, 0, 0, l-1);
//   torch::Tensor C_small=torch::narrow(C, 0, 0, l-1);
//   torch::Tensor m_array=torch::remainder(torch::mm(C_small,key), 1024);
//   torch::Tensor m_final=torch::ones(1);
//   m_final[0]=0;
//   torch::Tensor m_bit_array=torch::rand_like(m_array);
//   // for(i=l-2;i>=0;i--) {
//   //   m_bit_array[i]=((torch::remainder((m_array[i]/pow(2,i)).round(),pow(2,l-i-1))-m_final[0])/pow(2,l-i-2)).round();
//   //   m_final=m_final+m_bit_array[i]*g[l-2-i];
//   // }
//   // std::cout<<m_array<<std::endl;
//   // std::cout<<m_bit_array<<std::endl;
//   // std::cout<<m_final<<std::endl;
//   for(i=0;i<l-1;i++) {
//     m_bit_array[i]=((torch::remainder((m_array[i]/pow(2,i)).round(),pow(2,i+1))-m_final[0])/pow(2,i));
//     m_final=m_final+m_bit_array[i].round()*g[i];
//   }
//   std::cout<<m_array<<std::endl;
//   std::cout<<m_bit_array<<std::endl;
//   std::cout<<m_final<<std::endl;
//   return g;
// }

torch::Tensor MPDecrypt(torch::Tensor C, torch::Tensor key, int n, int q) {
  torch::Tensor m_array=torch::remainder(torch::mm(C,key), q);
  return m_array;
}

