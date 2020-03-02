#pragma once

#include <atomic>
#include <thread>

#include "data_flow/DataFlow.hpp"

namespace DataFlowDemo {

class CProducer
{
public: // methods
    explicit CProducer(const DataFlowPtr &flow);
    ~CProducer();

private: // methods
    void run();

private: // fields
    DataFlowPtr m_flow;
    std::atomic_bool m_stop;
    std::thread m_run_thread;
};

} // namespace DataFlowDemo
