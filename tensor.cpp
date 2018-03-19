// tensor.cpp
// (c) Sven Reichard 2018
//
// GPL etc...

# include <vector>
# include <iostream>
# include <iterator>
# include <cassert>
# include <string>
# include <map>
# include <algorithm>
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
  int s = set.size();
  for (int i = 0; i < s; i++)
    set[i] = i;
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
  std::copy(v.begin(), v.end(),
	    std::ostream_iterator<int>(std::cout, " "));
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
collect( tensor& t)
{
  typedef std::map<std::vector<int>, int> Multiset;
  std::vector<Multiset> allResults;
  std::vector<int> pair(2);
  tensor newTensor(t);
  int n = t.getOrder();
  for (pair[0]= 0; pair[0] < n; pair[0]++)
    for (pair[1] = 0; pair[1] < n; pair[1] ++)
      {
	std::vector<int> triple(3);
	triple[0] = pair[0];
	triple[1] = pair[1];
	
	Multiset multiset;
	int n = t.getOrder();
	for (int i = 0; i < n; i++)
	  {
	    triple[2] = i;
	    std::vector<int> colors(3);
	    std::vector<int>::iterator color = colors.begin();
	    std::vector<int> coordinates(2);
	    for (firstSet(coordinates); color != colors.end();
		 color++, nextSet(coordinates, 3))
	      *color = t[apply(triple, coordinates)];
	    multiset[colors] ++;
	  }
	/*
	std::cout<<"multiset:"<<std::endl;
	for (Multiset::iterator it = multiset.begin();
	     it != multiset.end();
	     it++)
	  {
	    std::cout << it->second<<" * ";
	    printVector(it->first);
	  }
	*/
	int position;
	std::vector<Multiset>::const_iterator pointer =
	  std::find(allResults.begin(), allResults.end(), multiset);
	if (pointer == allResults.end())
	  {
	    position = allResults.size();
	    allResults.push_back(multiset);
	  }
	else
	  position = pointer - allResults.begin();
	//	std::cout<<"new color: " << position << std::endl;
	newTensor[pair] = position;
      }
  newTensor.setRank(allResults.size());
  std::cout << "rank: " << newTensor.getRank() << std::endl;
  std::swap(t, newTensor);
}

int main(void)
{
  tensor t;
  t.read(std::cin);
  int oldrank;
  do {
    oldrank = t.getRank();
    std::cout << "rank: " << t.getRank() << std::endl;
    collect(t);
  } while (oldrank != t.getRank());
  t.write(std::cout);
  return 0;
};
