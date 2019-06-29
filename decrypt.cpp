// #include <iostream>
// #include <cmath>
// int lweSymDecrypt(int **sample, int *key, int n){
//   float x=0;
//   int max=0,i;
//   for(int j=0;j<n;j++){
//     if(key[j]>max)
//       i=j;
//   }
//   for(int j=0;j<n;j++)
//     x+=sample[i][j]*key[j];
//   x=x/key[i];
//   x=(int)floor(x);
//   return x;
// }

#include <torch/torch.h>
#include <iostream>
#include <stdlib.h>
#include <torch/csrc/autograd/variable.h>
#include <cmath>

torch::Tensor lweSymDecrypt(torch::Tensor sample, torch::Tensor key, int n) {
  torch::Tensor x=torch::tensor(0).to(torch::kFloat64);
  torch::Tensor max=torch::tensor(0).to(torch::kFloat64);
  torch::Tensor i=torch::tensor(0);
  // std::cout<<key[0].item<float>()<<std::endl;
  // std::cout<<max.item<float>()<<std::endl;
  // if(key[0].item<float>()>max.item<float>())
  //   std::cout<<"yay";

  for(int j=0;j<n;j++){
    if(key[j].item<float>()>max.item<float>())
      i=torch::tensor(j);
  }
  //std::cout<<"i is "<<sample[i.item<int64_t>()][0]*key[0]<<std::endl;
  for(int j=0;j<n;j++)
    x=x+sample[i.item<int64_t>()][j]*key[j];
  //std::cout<<key[i.item<int64_t>()]<<std::endl;
  //std::cout<<x<<std::endl;
  x=x/key[i.item<int64_t>()];
  x=floor(x);
  //std::cout<<x<<std::endl;
  return x;

}

int main()  {
  torch::Tensor sample = torch::rand({4, 3});
  torch::Tensor key = torch::rand({3});
  torch::Tensor ans = lweSymDecrypt(sample, key, 3);
  std::cout<<"ans is "<<ans<<std::endl;
  return 0;
}