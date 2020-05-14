#pragma once

// ============================================================================
// fmt
// ============================================================================
#include <fmt/format.h>
#include <fmt/ostream.h>

// ============================================================================
// tbb
// ============================================================================
#include <tbb/parallel_for.h>

// ============================================================================

#include <algorithm>
#include <atomic>
#include <bitset>
#include <chrono>
#include <condition_variable>
#include <exception>
#include <filesystem>
#include <fstream>
#include <limits>
#include <memory>
#include <mutex>
#include <new>
#include <numeric>
#include <optional>
#include <random>
#include <regex>
#include <shared_mutex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <thread>
#include <tuple>
#include <utility>
#include <variant>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

// ============================================================================

using namespace std::literals::chrono_literals;
using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

// ============================================================================

template <typename Rep, typename Period>
struct fmt::formatter<std::chrono::duration<Rep, Period>> : fmt::formatter<std::string_view> {
  template <typename FormatContext>
  auto format(const std::chrono::duration<Rep, Period>& duration, FormatContext& context) {
    const auto h = std::chrono::floor<std::chrono::hours>(duration);
    if constexpr (std::ratio_less_equal_v<Period, std::chrono::minutes::period>) {
      const auto m = std::chrono::floor<std::chrono::minutes>(duration - h);
      if constexpr (std::ratio_less_equal_v<Period, std::chrono::seconds::period>) {
        const auto s = std::chrono::floor<std::chrono::seconds>(duration - h - m);
        if constexpr (std::ratio_less_equal_v<Period, std::chrono::nanoseconds::period>) {
          const auto ns = std::chrono::floor<std::chrono::nanoseconds>(duration - h - m - s);
          return format_to(context.out(), "{:02}:{:02}:{:02}.{:09}", h.count(), m.count(), s.count(), ns.count());
        } else if constexpr (std::ratio_less_equal_v<Period, std::chrono::microseconds::period>) {
          const auto us = std::chrono::floor<std::chrono::microseconds>(duration - h - m - s);
          return format_to(context.out(), "{:02}:{:02}:{:02}.{:06}", h.count(), m.count(), s.count(), us.count());
        } else if constexpr (std::ratio_less_equal_v<Period, std::chrono::milliseconds::period>) {
          const auto ms = std::chrono::floor<std::chrono::milliseconds>(duration - h - m - s);
          return format_to(context.out(), "{:02}:{:02}:{:02}.{:03}", h.count(), m.count(), s.count(), ms.count());
        } else {
          return format_to(context.out(), "{:02}:{:02}:{:02}", h.count(), m.count(), s.count());
        }
      } else {
        return format_to(context.out(), "{:02}:{:02}", h.count(), m.count());
      }
    } else {
      return format_to(context.out(), "{:02}:00", h.count());
    }
  }
};

template <>
struct fmt::formatter<std::filesystem::path> : fmt::formatter<std::string_view> {
  template <typename FormatContext>
  auto format(const std::filesystem::path& path, FormatContext& context) {
    return fmt::formatter<std::string_view>::format(path.string(), context);
  }
};
