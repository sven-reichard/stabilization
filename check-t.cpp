# include <tensor.h>
# include <iostream>
# include <fstream>

// Filter for graphs with the t-vertex condition
// t is given as an argument; default is 3.
int main(int argc, const char* argv[])
{
  int t = 3;
  if (argc > 1)
    t = atoi(argv[1]);
  tensor aTensor;
  while(true)
    {
      aTensor.read(std::cin);
      if (!std::cin) break;
      const int rank = aTensor.getRank();
      collect(aTensor, t);
      if (rank ==  aTensor.getRank())
        aTensor.write(std::cout);
    }
  return 0;
};
