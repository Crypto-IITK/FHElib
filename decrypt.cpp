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
  // std::cout<<key[0].item<float>()<<std::endl;
  // std::cout<<max.item<float>()<<std::endl;
  // if(key[0].item<float>()>max.item<float>())
  //   std::cout<<"yay";
  torch::Tensor i=torch::argmax(key);
  //std::cout<<"i is "<<key<<std::endl;
  //std::cout<<"i is "<<sample[i.item<int64_t>()][0]*key[0]<<std::endl;
  // for(int j=0;j<n;j++)
  //   x=x+sample[i.item<int64_t>()][j]*key[j];
  //std::cout<<sample[i.item<int64_t>()].resize_({3,1})<<std::endl;
  //std::cout<<key.t()<<std::endl;
  //std::cout<<torch::transpose(key,0,1)<<std::endl;

  x=torch::mm(sample, key);
  // std::cout<<x<<std::endl;
  //std::cout<<key[i.item<int64_t>()]<<std::endl;
  //std::cout<<x<<std::endl;
  x=x/key[i.item<int64_t>()];
  torch::Tensor y=x.round();
  // x=floor(x);
  //std::cout<<y<<std::endl;
  return y;

}

int main()  {
  torch::Tensor sample = torch::rand({4, 3});
  torch::Tensor key = torch::rand({3,1});
  torch::Tensor a=torch::rand({3,2});
  torch::Tensor b=torch::rand({1,2});
  torch::Tensor c=a+b;
  //std::cout<<c<<std::endl;
  torch::Tensor ans = lweSymDecrypt(sample, key, 3);
  std::cout<<"ans is "<<ans<<std::endl;
  return 0;
}