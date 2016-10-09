set(CMAKE_CXX_FLAGS " -fPIC -lm -pthread -Ofast -march=native -funroll-loops -Wno-unused-result")
add_executable(glove_test_cpp
        main.cpp
    )
target_link_libraries(glove_test_cpp
    glove_static
    )
