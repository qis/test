#include "c.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
  std::cout << "a: " << a() << std::endl;
  std::cout << "b: " << b() << std::endl;

  std::cout << "inline a: " << inline_a() << std::endl;
  std::cout << "inline b: " << inline_b() << std::endl;
}
