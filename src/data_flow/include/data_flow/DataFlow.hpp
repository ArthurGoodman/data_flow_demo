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
    using Self = TDataFlow<Tag>;

    using ClearFunc = std::function<void()>;

    template <class T>
    using HandlerFunc = std::function<void(const T &)>;

    template <class T>
    struct Storage
    {
        std::vector<HandlerFunc<T>> handlers;
        bool initialized{false};
    };

public: // methods
    static std::shared_ptr<Self> create()
    {
        if (s_instance_wptr.expired())
        {
            auto instance = std::shared_ptr<Self>{new Self};
            s_instance_wptr = instance;
            return instance;
        }
        else
        {
            return s_instance_wptr.lock();
        }
    }

    ~TDataFlow()
    {
        for (const auto &func : m_clear_funcs)
        {
            func();
        }
    }

    template <class T, class F>
    void registerDataHandler(F &&func)
    {
        if (!storage<T>().initialized)
        {
            m_clear_funcs.emplace_back([]() {
                storage<T>().handlers.clear();
                storage<T>().initialized = false;
            });
            storage<T>().initialized = true;
        }

        storage<T>().handlers.emplace_back(std::forward<F>(func));
    }

    template <class T>
    void send(const T &data)
    {
        for (const auto &handler : storage<T>().handlers)
        {
            handler(data);
        }
    }

private: // methods
    explicit TDataFlow() = default;

    template <class T>
    static auto &storage()
    {
        return s_storage<std::decay_t<T>>;
    }

private: // fields
    template <class T>
    static Storage<T> s_storage;

    static std::weak_ptr<Self> s_instance_wptr;

    std::vector<ClearFunc> m_clear_funcs;
};

template <class Tag>
template <class T>
typename TDataFlow<Tag>::template Storage<T> TDataFlow<Tag>::s_storage;

template <class Tag>
std::weak_ptr<TDataFlow<Tag>> TDataFlow<Tag>::s_instance_wptr;

struct DataFlowTag
{
};

using CDataFlow = TDataFlow<DataFlowTag>;
using DataFlowPtr = std::shared_ptr<CDataFlow>;

inline DataFlowPtr makeDataFlow()
{
    return CDataFlow::create();
}

} // namespace DataFlowDemo
