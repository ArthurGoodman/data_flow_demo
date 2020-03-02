#pragma once

#include "common/Types.hpp"
#include "data_flow/DataFlow.hpp"

namespace DataFlowDemo {

class CConsumer
{
public: // methods
    explicit CConsumer(const DataFlowPtr &flow);

private: // methods
    void processData(const Data &data);
};

} // namespace DataFlowDemo
