# pragma once

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
  int size() const
  {
    return data.size();
  };
};
