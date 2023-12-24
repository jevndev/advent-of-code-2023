
add_executable(day_1 main.cpp)

set_target_properties(
    day_1
    PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    COMPILE_FLAGS "-Wall -Werror -Wextra -O1 -fconstexpr-steps=50000000 -fconstexpr-depth=500000000" 
)
