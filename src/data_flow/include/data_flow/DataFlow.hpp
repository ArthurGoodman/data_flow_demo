#pragma once

#include <functional>
#include <memory>

namespace DataFlowDemo {

class CDataFlow
{
public: // methods
    template <class T>
    void registerDataHandler(const std::function<void(const T &)> & /*handler*/)
    {
    }

    template <class T>
    void send(const T & /*data*/) const
    {
    }
};

using DataFlowPtr = std::shared_ptr<CDataFlow>;

inline DataFlowPtr makeDataFlow()
{
    return std::make_shared<CDataFlow>();
}

} // namespace DataFlowDemo
