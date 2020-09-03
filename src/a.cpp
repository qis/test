#define CONSTEXPR_VERSION_A
#include "c.hpp"

int a()
{
  return 1 + c();
}

int inline_a()
{
  return 1 + inline_c();
}
