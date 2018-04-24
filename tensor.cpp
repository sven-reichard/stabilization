// tensor.cpp
// (c) Sven Reichard 2018
//
// GPL etc...

# include <vector>
# include <iostream>
# include <fstream>
# include <iterator>
# include <cassert>
# include <string>
# include <map>
# include <algorithm>
# include <numeric>
typedef std::map<std::vector<int>, int> Multiset;

// perfect hash for vectors of integers less than <order>
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
  int getOrder() const
  {
    return order;
  };
  int getRank() const
  {
    return rank;
  };
  void setRank(int r)
  {
    rank = r;
  };
  int getDimension() const
  {
    return dimension;
  };
private:
  int order;
  int dimension;
  int rank;
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
int& tensor::operator[](const std::vector<int>& coordinates)
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
  int rank = 0;
  for (unsigned int i = 0; i < data.size(); i++)
    {
      output << data[i] << " ";
      if (data[i] > rank) rank = data[i];
      // insert newlines for structure
      int k = i+1;
      while (k > 0 && (k%order == 0))
	{
	  output << std::endl;
	  k /= order;
	}
    }
  output << "rank " << rank+1 <<std::endl;
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
  rank = 0;
  input >> word >> n;
  expect(word, "order");
  input >> word >> k;
  expect(word, "dimension");
  resize(n, k);
  for (std::vector<int>::iterator entry = data.begin(); entry != data.end(); entry ++)
    {
      input >> *entry;
      if (*entry > rank) rank = *entry;
      if (!input)
	{
	  std::cerr<<"input ended unexpectedly "<<std::endl;
	  std::cerr<<"read " << entry - data.begin() << " values" << std::endl;
	  std::cerr<<"expected " << data.size() << " values" << std::endl;
	  exit(1);
	}
    }
  rank ++;
  
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



void firstSet(std::vector<int>& set)
{
  std::iota(set.begin(), set.end(), 0);
};

bool nextSet(std::vector<int>& set, int maxValue)
// assume that set is an increasing list of values
// between 0 and maxValue-1
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

std::vector<int>
apply(const std::vector<int>& v, const std::vector<int>& w)
{
  int s = w.size();
  std::vector<int> result(s);
  for (int i = 0; i < s; i++)
    result[i] = v[w[i]];
  return result;
};

void
printMultiset(const Multiset& multiset)
{
  for (auto it = multiset.begin(); it != multiset.end(); it++)
    {
      std::cout << it->second<<" * ";
      printVector(it->first);
    }
};

typedef std::map<std::vector<int>, int> Multiset;

Multiset collectColors(int t, const tensor& aTensor,
		       const std::vector<int>& edge)
{
  Multiset multiset;
  const int numberOfColors = t*(t-1)/2; // binomial coefficient
  const int k = aTensor.getDimension();
  std::vector<int> tuple(t);
  std::copy(edge.begin(), edge.end(), tuple.begin());
  int n = aTensor.getOrder();
  std::vector<int> aSet(t-k);
  for (;;)
    {
      std::copy(aSet.begin(), aSet.end(), tuple.begin() + k);
      std::vector<int> colors(numberOfColors);
      auto color = colors.begin();
      std::vector<int> coordinates(k);
      for (firstSet(coordinates); color != colors.end();
	   color++, nextSet(coordinates, t))
	{
	  *color = aTensor[apply(tuple, coordinates)];
	}
      multiset[colors] ++;
      if (!nextTuple(aSet, n))
	break;
    }
  return multiset;
};

// we use this to collect invariants
// we construct an injective function T->N
// if the object is know we return the known value
// else we assign a new value.
template <typename T>
class collection
{
  std::vector<T> data;
public:
  int operator[]( const T& multiset)
  // should use hashing
  {
    for (unsigned int i = 0; i < data.size(); i++)
      if (multiset == data[i])
	return i;
    data.push_back(multiset);
    return data.size() - 1;
  };
};

void
collect( tensor& aTensor, int t)
{
  const int k = aTensor.getDimension();
  const int n = aTensor.getOrder();
  collection<Multiset> results;
  std::vector<int> edge(k);
  tensor newTensor(aTensor);
  
  do
  {
    Multiset multiset = collectColors(t,  aTensor, edge);
    newTensor[edge] = results[multiset];
  } while (nextTuple(edge, n));
  std::swap(aTensor, newTensor);
}

void
stabilize(tensor& aTensor, int maximalT)
{
  
  int oldrank;
  int t = 2;
  do {
    oldrank = aTensor.getRank();
    std::cout<<"t = " << t << std::endl;
    collect(aTensor, t);
    std::cout << "rank: " << aTensor.getRank() << std::endl;
    if (oldrank == aTensor.getRank())
      t++;
    else
      t = 2;
  } while (t <= maximalT);
}

void
writeVector(const std::vector<int>& v)
{
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ", "));
  std::cout <<std::endl;
}

tensor
increaseDimension(const tensor& aTensor)
{
  tensor result;
  const int n = aTensor.getOrder();
  const int k = aTensor.getDimension();
  result.resize(n, k+1);
  std::vector<int> coordinates(k+1);
  collection<std::vector<int> > allTuples;
  do {
    std::vector<int> colors;
    colors.reserve((k+1)*k/2);
    std::vector<int> edge(k);
    std::vector<int> set(k);
    firstSet(set);
    do {
      edge = apply(coordinates, set);
      colors.push_back(aTensor[edge]);
    } while (nextSet(set, k+1));
    
    result[coordinates] = allTuples[colors];
  } while (nextTuple(coordinates, n));
  return result;
}

tensor
decreaseArity(const tensor& aTensor)
{
  tensor result;
  const int n = aTensor.getOrder();
  const int k = aTensor.getDimension();
  result.resize(n, k-1);
  std::vector<int> coordinates(k-1);
  collection<std::map<int, int>> allResults;
  do {
    std::vector<int> tuple(k);
    std::copy(coordinates.begin(), coordinates.end(), tuple.begin());
    std::map<int, int> m;
    for (tuple.back() = 0; tuple.back() < n; tuple.back() ++)
      m[aTensor[tuple]] ++;
    result[coordinates] = allResults[m];
  } while (nextTuple(coordinates, n));
  return result;
}

int main(void)
{
  std::ifstream input("Examples/4.1.wl");
  tensor aTensor;
  aTensor.read(input);
    aTensor = increaseDimension(aTensor);
  aTensor.write(std::cout);
  std::cout << "--------------------" << std::endl;
  collect(aTensor, 4);
  aTensor.write(std::cout);
  std::cout << "--------------------" << std::endl;
  aTensor = decreaseArity(aTensor);
  aTensor.write(std::cout);
  std::cout << "--------------------" << std::endl;
  //aTensor = decreaseArity(aTensor);
  //aTensor.write(std::cout);
  return 0;
};
