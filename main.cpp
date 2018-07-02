# include <tensor.h>
# include <iostream>
# include <fstream>
int main(int argc, const char* argv[])
{

  tensor aTensor;
  aTensor.read(std::cin);
  int min_t = aTensor.getDimension() + 1;
  int max_t = min_t;
  if (argc > 1)
    max_t = atoi(argv[1]);
  int t = min_t;
  while (t <= max_t)
    {
      std::cerr << "t = " << t << std::endl;
      int rank = aTensor.getRank();
      collect(aTensor, t);
      if (rank == aTensor.getRank())
        t ++;
      else
        t = min_t;
    }
  aTensor.write(std::cout);
  return 0;
};
