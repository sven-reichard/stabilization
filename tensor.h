# pragma once
# include <vector>
# include <iosfwd>

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
void collect( tensor& aTensor, int t);
tensor increaseArity(const tensor& aTensor);
tensor decreaseArity(const tensor& aTensor);
