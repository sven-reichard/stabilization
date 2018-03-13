# include <xunit.h>
# include <map>
class Product
{
  typedef std::map<std::pair<int,int>, int> map_type;
  map_type values;
public:
  int operator () (int x, int y) const
  {
    std::pair<int, int> p = std::make_pair(x,y);
    map_type::const_iterator it = values.find(p);
    if (it == values.end())
      return 0;
    return it->second;
  };
  void increment(int x, int y)
  {
    values[std::make_pair(x,y)] ++;
  };
};

class ProductTest
  : public TestCase<ProductTest>
{
public:
  ProductTest(memberFunction f)
    :TestCase(f)
  {};
  void testEmptyProduct()
  {
    Product p;
    testAssertEqual(0, p(1,2));
  };
  void testIncrement()
  {
    Product p;
    p.increment(1,2);
    testAssertEqual(1, p(1,2));
  };
};
int main()
{
  TestSuite suite;
  suite.add(new ProductTest(std::mem_fun(&ProductTest::testEmptyProduct)));
  suite.add(new ProductTest(std::mem_fun(&ProductTest::testIncrement)));
   TestResult result;
   suite.run(result);
   result.printReport();
  return 0;
};
