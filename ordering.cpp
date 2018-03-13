# include <iostream>
# include <iomanip>
const unsigned int odd_bits = 0x55555555u;
const unsigned int even_bits = 2*odd_bits;

unsigned int increment_x(unsigned int value)
{
  unsigned int odd = value & odd_bits;
  unsigned int even = value & even_bits;
  unsigned int result = (value | even_bits) + 1;
  result &= odd_bits;
  result |= even;
  return result;
};

unsigned int increment_y(unsigned int value)
{
  unsigned int odd = value & odd_bits;
  unsigned int even = value & even_bits;
  unsigned int result = (value | odd_bits) + 1;
  result &= even_bits;
  result |= odd;
  return result;
};

int main(void)
{
  for (int i = 0, v = 0; i < 16; i++, v = increment_y(v))
    {
      for (int j = 0, w = v; j < 16; j++, w = increment_x(w))
        std::cout << std::setw(3) << w << "  ";
      std::cout << std::endl;
    }
}
