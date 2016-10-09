if(GLOVE_BUILD_STATIC)
    add_library(glove_static STATIC
        cooccur.c
        glove.c
        shuffle.c
        vocab_count.c
        )
    target_link_libraries(glove_static
        )
    target_include_directories(glove_static
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
        )
endif()

if(GLOVE_BUILD_SHARED)
    add_library(glove_shared SHARED
        cooccur.c
        glove.c
        shuffle.c
        vocab_count.c
        )
    target_link_libraries(glove_shared
        )
    target_include_directories(glove_shared
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
        )
endif()