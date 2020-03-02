add_library(producer STATIC
    src/Producer.cpp
    )

target_link_libraries(producer
    PRIVATE Threads::Threads
    PUBLIC common
    PUBLIC data_flow
    )

target_include_directories(producer
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
