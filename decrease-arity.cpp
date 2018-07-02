# include <tensor.h>
# include <iostream>

int main(void)
{
  tensor aTensor;
  aTensor.read(std::cin);
  aTensor = decreaseArity(aTensor);
  aTensor.write(std::cout);
  return 0;
};
