config = debug
system = linux
target = test

all: build/$(system)/$(config)/rules.ninja
	@cmake --build build/$(system)/$(config)

run: build/$(system)/$(config)/rules.ninja
	@cmake --build build/$(system)/$(config)
	@cmake -E chdir build/$(system)/$(config) ./$(target)

install: build/$(system)/release/rules.ninja
	@cmake --build build/$(system)/release --target install

format:
	@cmake -P "$(VCPKG_ROOT)/triplets/toolchains/format.cmake"

clean:
	@cmake -E remove_directory build/$(system)

build/$(system)/debug/rules.ninja: CMakeLists.txt
	@cmake -GNinja -DCMAKE_BUILD_TYPE=Debug \
	  -DCMAKE_TOOLCHAIN_FILE="$(VCPKG_ROOT)/triplets/toolchains/$(system).cmake" \
	  -DCMAKE_INSTALL_PREFIX="build/install" \
	  -DCMAKE_CXX_CLANG_TIDY="clang-tidy" \
	  -B build/$(system)/debug

build/$(system)/release/rules.ninja: CMakeLists.txt
	@cmake -GNinja -DCMAKE_BUILD_TYPE=Release \
	  -DCMAKE_TOOLCHAIN_FILE="$(VCPKG_ROOT)/triplets/toolchains/$(system).cmake" \
	  -DCMAKE_INSTALL_PREFIX="build/install" \
	  -DCMAKE_CXX_CLANG_TIDY="clang-tidy" \
	  -B build/$(system)/release
