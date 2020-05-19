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
	@cmake -P res/format.cmake

clean:
	@cmake -E remove_directory build/$(system)

build/windows/debug/rules.ninja: CMakeLists.txt
	@cmake -GNinja -DCMAKE_BUILD_TYPE=Debug \
	  -DCMAKE_INSTALL_PREFIX="$(MAKEDIR)\build\install" \
	  -DCMAKE_TOOLCHAIN_FILE="$(MAKEDIR)\res\toolchain.cmake" \
	  -B build/windows/debug

build/windows/release/rules.ninja: CMakeLists.txt
	@cmake -GNinja -DCMAKE_BUILD_TYPE=Release \
	  -DCMAKE_INSTALL_PREFIX="$(MAKEDIR)\build\install" \
	  -DCMAKE_TOOLCHAIN_FILE="$(MAKEDIR)\res\toolchain.cmake" \
	  -B build/windows/release

build/linux/debug/rules.ninja: CMakeLists.txt
	@cmake -GNinja -DCMAKE_BUILD_TYPE=Debug \
	  -DCMAKE_INSTALL_PREFIX="$(CURDIR)/build/install" \
	  -DCMAKE_TOOLCHAIN_FILE="$(CURDIR)/res/toolchain.cmake" \
	  -DENABLE_STATIC_ANALYSIS=ON \
	  -B build/linux/debug

build/linux/release/rules.ninja: CMakeLists.txt
	@cmake -GNinja -DCMAKE_BUILD_TYPE=Release \
	  -DCMAKE_INSTALL_PREFIX="$(CURDIR)/build/install" \
	  -DCMAKE_TOOLCHAIN_FILE="$(CURDIR)/res/toolchain.cmake" \
	  -DENABLE_STATIC_ANALYSIS=ON \
	  -B build/linux/release
