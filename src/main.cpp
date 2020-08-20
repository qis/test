int main(int argc, char* argv[]) {
  try {
    const auto beg = std::chrono::high_resolution_clock::now();
    std::vector<int> v(1'000);

    tbb::parallel_for(tbb::blocked_range<std::size_t>(0, v.size()), [&](const auto& range) {
      for (auto i = range.begin(); i != range.end(); ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds{ 1 });
        v[i] = argc;
      }
    });
    const auto end = std::chrono::high_resolution_clock::now();
    fmt::print("TBB: {} ns\n", std::chrono::floor<std::chrono::nanoseconds>(end - beg).count());
  }
  catch (const std::exception& e) {
    fmt::print(stderr, "error: {}\n", e.what());
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
