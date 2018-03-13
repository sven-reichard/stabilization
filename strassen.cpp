# include <iostream>
# include <iomanip>
# include <vector>
# include <cstdlib>
# include <ctime>
using std::vector;
using namespace std;

int order = 2;
typedef vector<vector<unsigned int> > Matrix;
Matrix A;
Matrix B;
Matrix product;
Matrix product2;

void initialize()
{
  A.resize(order);
  B.resize(order);
  product.resize(order);
  product2.resize(order);
  for (int i = 0; i < order; i++)
    {
      A[i].resize(order);
      B[i].resize(order);
      product[i].resize(order);
      product2[i].resize(order);
      for (int j = 0; j < order; j++)
        {
          A[i][j] = rand();
          B[i][j] = rand();
        }
    }
}

void
normalProduct(Matrix& result, const Matrix& A, const Matrix& B)
{
  for (int i = 0; i < result.size(); i++)
    for (int j = 0; j < result.size(); j++)
      {
        unsigned value = 0;
        for (int k = 0; k < result.size(); k++)
          value += A[i][k] * B[k][j];
        result[i][j] = value;
      }
}

void
printMatrix(const Matrix& M)
{
  for (int i = 0; i < M.size(); i++)
    {
      for (int j = 0; j < M[i].size(); j++)
        cout << setw(10) << M[i][j] << " ";
      cout << endl;
    }
}

int main(void)
{
  srand(std::time(0));
  initialize();
  normalProduct(product, A, B);
  printMatrix(product);
  return 0;
}
