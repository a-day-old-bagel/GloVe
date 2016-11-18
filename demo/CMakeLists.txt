
if(WIN32)
   message(WARNING "cmaking for windows")
else()
   set(CMAKE_CXX_FLAGS " -fPIC -lm -pthread -Ofast -march=native -funroll-loops -Wno-unused-result")
endif()

add_executable(glove_test_cpp
        main.cpp
    )
target_link_libraries(glove_test_cpp
    glove_static
    )
