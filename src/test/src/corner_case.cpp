#include <iostream>

#include "data_flow/DataFlow.hpp"

namespace {

struct DummyType
{
    int value;
};

void test1()
{
    auto flow = DataFlowDemo::makeDataFlow();

    int local;
    flow->registerDataHandler<DummyType>([&](const auto &data) {
        // std::cout << "Received data!" << std::endl;
        local = data.value;
    });
    flow->send(DummyType{0});
}

void test2()
{
    auto flow = DataFlowDemo::makeDataFlow();

    int local;
    flow->registerDataHandler<DummyType>([&](const auto &data) {
        // std::cout << "Received data!" << std::endl;
        local = data.value;
    });
    flow->send(DummyType{0});
}

} // anonymous namespace

int main()
{
    test1();
    test2();

    return 0;
}
