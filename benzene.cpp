# include <iostream>
# include <vector>
# include <cstdlib> // for atoi
int main(int nArguments, char* arguments[])
{
  int k = 3;
  if (nArguments > 1)
    k = std::atoi(arguments[1]);
  int n = 6*k;
  std::vector<std::vector<int> > matrix(n);
  for (unsigned int i = 0; i < matrix.size(); i++)
    matrix[i].resize(n);
  for (int i = 0; i < k; i++)
    {
      for (int j = 0; j < 5; j++)
        {
          matrix[6*i+j][6*i+j+1] = 1;
          matrix[6*i+j+1][6*i+j] = 1;
        }
      matrix[6*i][6*i+5] = 1;
      matrix[6*i+5][6*i] = 1;
      
    }
  for (int i = 0; i < k-1; i++)
    for (int j = 0; j < 6; j+= 2)
      {
        matrix[6*i + j + (i&1)][6*(i+1) + j + (i&1)] = 1;
        matrix[6*(i+1) + j + (i&1)][6*(i) + j + (i&1)] = 1;
      }
  for (int i = 0; i < n; i++)
    matrix[i][i] = 2;
  std::cout << "order " << n << std::endl;
  std::cout << "dimension "<< 2<<std::endl;
  for (unsigned int i = 0; i < matrix.size(); i++)
    {
      for (unsigned int j = 0; j < matrix.size(); j++)
        std::cout << matrix[i][j]<<" ";
      std::cout << std::endl;
    }
  return 0; 
}
