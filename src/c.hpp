#pragma once

extern int a();
extern int inline_a();
extern int b();
extern int inline_b();

#if defined(CONSTEXPR_VERSION_A)

constexpr int c()
{
  return 1;
}

inline constexpr int inline_c()
{
  return 1;
}

#elif defined(CONSTEXPR_VERSION_B)

constexpr int c()
{
  return 2;
}

inline constexpr int inline_c()
{
  return 2;
}

#endif
