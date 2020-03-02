add_executable(data_flow_test
    src/test.cpp
    )

target_link_libraries(data_flow_test
    PRIVATE producer
    PRIVATE consumer
    PRIVATE data_flow
    )

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -O1")

add_executable(data_flow_corner_case
    src/corner_case.cpp
    )

target_link_libraries(data_flow_corner_case
    PRIVATE data_flow
    )
