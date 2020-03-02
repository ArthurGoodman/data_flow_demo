#include <chrono>
#include <csignal>
#include <thread>

#include "consumer/Consumer.hpp"
#include "data_flow/DataFlow.hpp"
#include "producer/Producer.hpp"

namespace {

volatile std::sig_atomic_t g_stop{false};

void signalHandler(int /*sig*/)
{
    g_stop = true;
}

} // anonymous namespace

int main()
{
    std::signal(SIGINT, signalHandler);

    using namespace DataFlowDemo;

    auto flow = makeDataFlow();

    CConsumer consumer{flow};
    CProducer producer{flow};

    while (!g_stop)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds{100});
    }

    return 0;
}
