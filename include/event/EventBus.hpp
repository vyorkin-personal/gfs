#pragma once

#include "Prerequisites.hpp"
#include "Uid.hpp"
#include "UidRegistry.hpp"
#include "event/Event.hpp"

namespace gfs {
    namespace event {
        class EventBus {
            public:
                EventBus(UidRegistry* uidRegistry);

                template<class E> void emit(E& event);
                template<class E, class S> void subscribe(
                    S* system, void (S::* callback) (E &));

            private:
                template <class E> class EventCallback {
                    public:
                        using EventFunc = std::function<void(E &)>;

                        EventCallback(EventFunc& func);
                        void operator()(Event& event);
                    private:
                        EventFunc callback;
                };

                UidRegistry* uidRegistry;
                EventHandlerMap eventHandlers;
        };
    }
}

#include "event/EventBus.inl"
