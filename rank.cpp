# include <tensor.h>
# include <iostream>

int main(void)
{
  for (;;)
    {
      tensor aTensor;
      aTensor.read(std::cin);
      if (!std::cin)
        break;
      std::cout << "order " << aTensor.getOrder() << ", rank " << aTensor.getRank()<<std::endl;
    }
  return 0;
};
