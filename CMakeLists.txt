cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(test VERSION 0.1.0 LANGUAGES CXX)

# Sources
file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.[hc]pp)

# Executable
add_executable(${PROJECT_NAME} ${sources} src/main.manifest)
target_precompile_headers(${PROJECT_NAME} PRIVATE src/main.hpp)
target_compile_definitions(${PROJECT_NAME} PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Dependencies
find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

find_package(TBB CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE TBB::tbb)

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

if(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  target_link_libraries(${PROJECT_NAME} PRIVATE stdc++fs)
  target_link_options(${PROJECT_NAME} PRIVATE -static-libstdc++)
endif()

# Install
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

if(WIN32 AND VCPKG_LIBRARY_LINKAGE STREQUAL "dynamic")
  install(CODE "
    file(GLOB libraries \"$<TARGET_FILE_DIR:${PROJECT_NAME}>/*.dll\")
    file(INSTALL $\{libraries} DESTINATION \"${CMAKE_INSTALL_PREFIX}/bin\")
  ")
endif()

# Visual Studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})