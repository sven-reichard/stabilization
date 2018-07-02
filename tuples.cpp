

# include <tuples.h>
# include <numeric>
bool nextTuple(const std::vector<int>::iterator begin,
	       const std::vector<int>::iterator end,
	       int maxValue)
// enumerate [n]^k lexicographically
{
  for (auto entry = end-1; entry >= begin; --entry)
    {
      if (++(*entry) < maxValue)
	return true;
      *entry = 0;
    }
  return false;
};


bool nextTuple(std::vector<int>& tuple, int maxValue)
{
  return nextTuple(tuple.begin(), tuple.end(), maxValue);
}

void firstSet(std::vector<int>& set)
{
  std::iota(set.begin(), set.end(), 0);
};

bool nextSet(const std::vector<int>::iterator begin, const std::vector<int>::iterator end, int maxValue)
// assume that [begin,end) is an increasing list of values
// between 0 and maxValue-1
// change it to the next such list (lexicographically)
{
  auto element = end-1;
  for (; element >= begin; element--)
    if ( *element < maxValue - (end-element))
      break;
  if (element < begin) return false;
  std::iota(element, end, ++(*element)); // increase *element and fill up remaining values
  return true;
}
  
bool nextSet(std::vector<int>& set, int maxValue)
{
  return nextSet(set.begin(), set.end(), maxValue);
}
