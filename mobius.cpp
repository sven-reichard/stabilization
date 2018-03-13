# include <iostream>
# include <vector>
# include <cstdlib> // for atoi
int main(int nArguments, char* arguments[])
{
  int k = 3;
  if (nArguments > 1)
    k = std::atoi(arguments[1]);
  int n = 2*k;
  std::vector<std::vector<int> > matrix(n);
  for (int i = 0; i < n; i++)
    matrix[i].resize(n);
  for (int i = 0; i < n; i++)
    {
      matrix[i][(n+i+1)%n] = 1;
      matrix[i][(n+i-1)%n] = 1;
      matrix[i][(n+i+k)%n] = 1;
      matrix[i][i] = 2;
    }

  std::cout << "order " <<  n<<std::endl;
  std::cout << "dimension 2" << std::endl;
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
        std::cout << matrix[i][j]<<" ";
      std::cout << std::endl;
    }
  return 0; 
}
