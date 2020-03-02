#include "producer/Producer.hpp"

#include <chrono>
#include <iostream>

#include "common/Types.hpp"

namespace DataFlowDemo {

CProducer::CProducer(const DataFlowPtr &flow)
    : m_flow{flow}
    , m_stop{false}
{
    m_run_thread = std::thread{[this]() { run(); }};
}

CProducer::~CProducer()
{
    m_stop.store(true);
    if (m_run_thread.joinable())
    {
        m_run_thread.join();
    }
}

void CProducer::run()
{
    while (!m_stop.load())
    {
        Data data;
        data.ts = std::chrono::steady_clock::now().time_since_epoch().count();
        for (auto &elem : data.payload)
        {
            elem = std::rand();
        }

        std::cout << "[Producer] Sending data; ts=" << data.ts << std::endl;

        m_flow->send(data);

        std::this_thread::sleep_for(std::chrono::milliseconds{100});
    }
}

} // namespace DataFlowDemo
