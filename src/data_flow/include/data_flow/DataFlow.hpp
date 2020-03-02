#pragma once

#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <type_traits>
#include <typeindex>
#include <utility>
#include <vector>

namespace DataFlowDemo {

class CDataFlow
{
private: // types
    struct IHandler
    {
        virtual ~IHandler() = default;
    };

    template <class T>
    using HandlerCallback = std::function<void(const T &)>;

    template <class T>
    struct Handler final
        : HandlerCallback<T>
        , IHandler
    {
        explicit Handler(HandlerCallback<T> &&func)
            : HandlerCallback<T>{std::move(func)}
        {
        }
    };

private: // methods
    template <class T>
    static std::type_index TypeIndex()
    {
        return typeid(std::decay_t<T>);
    }

public: // methods
    template <class T, class F>
    void registerDataHandler(F &&func)
    {
        m_handlers[TypeIndex<T>()].emplace_back(new Handler<T>{std::forward<F>(func)});
    }

    template <class T>
    void send(const T &data) const
    {
        const auto &it = m_handlers.find(TypeIndex<T>());

        if (it == m_handlers.end())
        {
            std::cerr << "error: handler not found for type '" << TypeIndex<T>().name() << "'"
                      << std::endl;
            return;
        }

        for (const auto &ptr : it->second)
        {
            auto handler = dynamic_cast<Handler<T> *>(ptr.get());

            if (!handler)
            {
                assert(!"should not happen");
                return;
            }

            (*handler)(data);
        }
    }

private: // fields
    std::map<std::type_index, std::vector<std::unique_ptr<IHandler>>> m_handlers;
};

using DataFlowPtr = std::shared_ptr<CDataFlow>;

inline DataFlowPtr makeDataFlow()
{
    return std::make_shared<CDataFlow>();
}

} // namespace DataFlowDemo
