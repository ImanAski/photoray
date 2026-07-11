cmake_minimum_required(VERSION 3.15)

project(PhotonicRays
	VERSION 1.0.0
	LANGUAGES C
)

set(CMAKE_C_STANDARD 11)

find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)

set(SOURCES
  src/main.c
  src/component.c
  src/registry.c
  src/math/vector.c
  parser/phoray.c
)

add_executable(rays ${SOURCES})

target_include_directories(rays PRIVATE
  src
  parser
  src/math
)

target_link_libraries(rays
  PRIVATE
  SDL3::SDL3
  SDL3_ttf::SDL3_ttf
  m
)
