namespace gfs {
    namespace event {
        template <class E>
        EventBus::EventCallback<E>::EventCallback(EventFunc& func):
            callback{func} {}

        template <class E>
        void EventBus::EventCallback<E>::operator()(Event& event) {
            callback(static_cast<E &>(event));
        }

        template <class E>
        void EventBus::emit(E& event) {
            const auto uid = uidRegistry->get<E>();
            auto range = eventHandlers.equal_range(uid);
            auto next = range.first;
            const auto end = range.second;
            
            if (next != eventHandlers.end()) {
                while (next != end) {
                    next->second(event);
                    next++;
                }
            }
        }

        template <class E, class S>
        void EventBus::subscribe(S* system, void (S::* callback) (E &)) {
            const auto uid = uidRegistry->get<E>();
            std::function<void(E &)> func = std::bind(
                callback, system, std::placeholders::_1);

            eventHandlers.insert(std::make_pair(uid, EventCallback<E>(func)));
        }
    }
}
