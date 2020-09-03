#define CONSTEXPR_VERSION_B
#include "c.hpp"

int b()
{
  return 1 + c();
}

int inline_b()
{
  return 1 + inline_c();
}
