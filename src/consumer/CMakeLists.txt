add_library(consumer STATIC
    src/Consumer.cpp
    )

target_link_libraries(consumer
    PRIVATE Threads::Threads
    PUBLIC common
    PUBLIC data_flow
    )

target_include_directories(consumer
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
