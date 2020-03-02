#pragma once

#include <functional>
#include <memory>
#include <utility>
#include <vector>

namespace DataFlowDemo {

template <class Tag>
class TDataFlow
{
private: // types
    template <class T>
    using HandlerFunc = std::function<void(const T &)>;

public: // methods
    template <class T, class F>
    static void registerDataHandler(F &&func)
    {
        handlers<T>().emplace_back(std::forward<F>(func));
    }

    template <class T>
    static void send(const T &data)
    {
        for (const auto &handler : handlers<T>())
        {
            handler(data);
        }
    }

private: // methods
    template <class T>
    static auto &handlers()
    {
        return s_handlers<std::decay_t<T>>;
    }

private: // fields
    template <class T>
    static std::vector<HandlerFunc<T>> s_handlers;
};

template <class Tag>
template <class T>
std::vector<typename TDataFlow<Tag>::template HandlerFunc<T>> TDataFlow<Tag>::s_handlers;

struct DataFlowTag
{
};

using CDataFlow = TDataFlow<DataFlowTag>;
using DataFlowPtr = std::shared_ptr<CDataFlow>;

inline DataFlowPtr makeDataFlow()
{
    return std::make_shared<CDataFlow>();
}

} // namespace DataFlowDemo
