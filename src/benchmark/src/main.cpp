#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <future>
#include <iostream>
#include <typeinfo>

#include "data_flow/DataFlow.hpp"

namespace DataFlowDemo {

template <std::size_t N>
class DataTransferGenerator : public DataTransferGenerator<N - 1>
{
public: // types
    using Base = DataTransferGenerator<N - 1>;
    using Self = DataTransferGenerator<N>;

public: // methods
    explicit DataTransferGenerator(int value)
        : Base{value}
    {
    }

    static void registerHandlers(const DataFlowPtr &flow)
    {
        flow->registerDataHandler<Self>([](const auto &) {});
        Base::registerHandlers(flow);
    }

    static void sendData(const DataFlowPtr &flow)
    {
        flow->send(Self{std::rand()});
        Base::sendData(flow);
    }
};

template <>
class DataTransferGenerator<0>
{
public: // methods
    explicit DataTransferGenerator(int value)
        : m_value{value}
    {
    }

    static void registerHandlers(const DataFlowPtr &)
    {
    }

    static void sendData(const DataFlowPtr &)
    {
    }

public: // fields
    int m_value;
};

} // namespace DataFlowDemo

int main()
{
    static constexpr std::size_t c_receiver_count = 200;
    static constexpr std::size_t c_iteration_count = 1e6;

    using namespace DataFlowDemo;

    auto flow = makeDataFlow();

    using GeneratorType = DataTransferGenerator<c_receiver_count>;

    auto start = std::chrono::steady_clock::now();

    GeneratorType::registerHandlers(flow);

    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << elapsed.count();

    start = std::chrono::steady_clock::now();

    for (std::size_t i = 0; i < c_iteration_count; i++)
    {
        GeneratorType::sendData(flow);
    }

    end = std::chrono::steady_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << " " << elapsed.count() << std::endl;
}
