set(This UniversalOrbitMap)
project(${This})

set(OutputDir ${Year}/day06)

set(Sources
  main.cpp
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
  ${CMAKE_BINARY_DIR}/${OutputDir}
  COPYONLY
)

add_executable(${This} ${Sources})
set_target_properties(${This} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OutputDir}"
)
target_compile_features(${This}
  PUBLIC cxx_std_17
)