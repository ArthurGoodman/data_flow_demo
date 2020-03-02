set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftemplate-depth=1024")
set(CMAKE_BUILD_TYPE Release)

add_executable(data_flow_benchmark
    src/main.cpp
    )

target_link_libraries(data_flow_benchmark
    PRIVATE data_flow
    )
