#pragma once

#include <cstdint>

namespace DataFlowDemo {

using Timestamp = std::uint64_t;

struct Data
{
    Timestamp ts;
    int payload[3];
};

} // namespace DataFlowDemo
