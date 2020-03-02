#include "consumer/Consumer.hpp"

#include <iostream>

namespace DataFlowDemo {

CConsumer::CConsumer(const DataFlowPtr &flow)
{
    flow->registerDataHandler<Data>([this](const auto &data) { processData(data); });
}

void CConsumer::processData(const Data &data)
{
    std::cout << "[Consumer] Processing data\n    ts=" << data.ts << "\n    payload=[ ";
    for (const auto &elem : data.payload)
    {
        std::cout << elem << " ";
    }
    std::cout << "]" << std::endl;
}

} // namespace DataFlowDemo
