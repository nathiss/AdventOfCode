set(This SecureContainer)
project(${This})

set(OutputDir ${Year}/day04)

set(Sources
  main.cpp
)

add_executable(${This} ${Sources})
set_target_properties(${This} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OutputDir}"
)
