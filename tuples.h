# pragma once
# include <vector>

bool nextTuple(const std::vector<int>::iterator begin,
	       const std::vector<int>::iterator end,
	       int maxValue);


bool nextTuple(std::vector<int>& tuple, int maxValue);
void firstSet(std::vector<int>& set);


bool nextSet(const std::vector<int>::iterator begin, const std::vector<int>::iterator end, int maxValue);
  
bool nextSet(std::vector<int>& set, int maxValue);
