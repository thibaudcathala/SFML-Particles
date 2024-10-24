cmake_minimum_required(VERSION 3.10)

project(Particles)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include(FetchContent)

FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)

set(PARTICLES_HEADERS
    "${PROJECT_SOURCE_DIR}/Particles/ParticleData.h"
    "${PROJECT_SOURCE_DIR}/Particles/ParticleGenerator.h"
    "${PROJECT_SOURCE_DIR}/Particles/ParticleSystem.h"
    "${PROJECT_SOURCE_DIR}/Particles/ParticleUpdater.h"
    "${PROJECT_SOURCE_DIR}/Particles/ParticleSpawner.h"
)

set(PARTICLES_SRC
    "${PROJECT_SOURCE_DIR}/Particles/ParticleData.cpp"
    "${PROJECT_SOURCE_DIR}/Particles/ParticleGenerator.cpp"
    "${PROJECT_SOURCE_DIR}/Particles/ParticleSystem.cpp"
    "${PROJECT_SOURCE_DIR}/Particles/ParticleUpdater.cpp"
    "${PROJECT_SOURCE_DIR}/Particles/ParticleSpawner.cpp"
)

add_library(Particles-s STATIC ${PARTICLES_SRC} ${PARTICLES_HEADERS})
target_include_directories(Particles-s PUBLIC "${PROJECT_SOURCE_DIR}/")
target_link_libraries(Particles-s sfml-system sfml-graphics)
