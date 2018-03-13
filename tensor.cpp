// tensor.cpp
// (c) Sven Reichard 2018
//
// GPL etc...

# include <vector>
# include <iostream>
# include <iterator>
# include <cassert>
# include <string>

// perfect hash for vectors of integers
int horner(const std::vector<int>& coordinates, int order)
{
  int result = 0;
  for (std::vector<int>::const_iterator entry = coordinates.begin();
       entry != coordinates.end();
       entry++)
    {
      int value = *entry;
      assert(value >= 0);
      assert(value < order);
      result = result * order + value;
    }
  return result;
};

class tensor
{
public:
  tensor();
  void resize(int order, int dimension);
  int& operator[](const std::vector<int>& coordinates);
  int operator[](const std::vector<int>& coordinates) const;
  void read(std::istream& input);
  void write(std::ostream& output) const;
private:
  int order;
  int dimension;
  std::vector<int> data;
};

tensor::tensor()
{
  
};

void tensor::resize(int n, int k)
{
  order = n;
  dimension = k;
  int size = 1;
  for (int i = 0; i < dimension; i++)
    size *= order;
  data.resize(size);
}


int tensor::operator[](const std::vector<int>& coordinates) const
{
  assert((signed int)coordinates.size() == dimension);
  int entry = horner(coordinates, order);
  return data[entry];
};


void
tensor::write(std::ostream& output) const
{
  output << "order " << order << std::endl;
  output << "dimension " << dimension << std::endl;
  for (unsigned int i = 0; i < data.size(); i++)
    {
      output << data[i] << " ";
      // insert newlines for structure
      int k = i+1;
      while (k > 0 && (k%order == 0))
	{
	  output << std::endl;
	  k /= order;
	}
    }
}

void expect(const std::string& s1, const std::string& s2)
{
  if (s1 != s2)
    {
      std::cerr << "expected " << s2 << ", got " << s1 << std::endl;
      exit(1);
    }
}

void tensor::read(std::istream& input)
{
  std::string word;
  int n, k;
  input >> word >> n;
  expect(word, "order");
  input >> word >> k;
  expect(word, "dimension");
  resize(n, k);
  for (std::vector<int>::iterator entry = data.begin(); entry != data.end(); entry ++)
    {
      input >> *entry;
      if (!input)
	{
	  std::cerr<<"input ended unexpectedly "<<std::endl;
	  std::cerr<<"read " << entry - data.begin() << " values" << std::endl;
	  std::cerr<<"expected " << data.size() << " values" << std::endl;
	  exit(1);
	}
    }

}


bool nextTuple(std::vector<int>& tuple, int maxValue)
// enumerate [n]^k lexicographically
{
  for (std::vector<int>::reverse_iterator entry = tuple.rbegin();
       entry != tuple.rend(); ++entry)
    {
      (*entry)++;
      if (*entry < maxValue)
	return true;
      *entry = 0;
    }
  return false;
};

bool nextSet(std::vector<int>& set, int maxValue)
// assume that set is an increasing list of values between 0 and maxValue-1
// change it to the next such list (lexicographically)
{
  int i;
  int s = set.size();
  for (i = s-1; i >= 0; i --)
    if ( set[i] < maxValue - s + i)
      break;
  if (i < 0) return false;
  set[i] ++ ;
  for (i++; i < s; i++)
    set[i] = set[i-1] + 1;
  return true;
}
  

void printVector(const std::vector<int>& v)
{
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
}

int main(void)
{
  tensor t;
  //t.read(std::cin);
  //t.write(std::cout);

  int s = 3;
  std::vector<int> v(s);
  for (int i = 0; i < s; i++)
    v[i] = i;
  int count = 0;
  do {
    count ++;
    printVector(v);
  } while (nextSet(v, 7));
  std::cout << "found " << count << " sets" << std::endl;
  return 0;
};
