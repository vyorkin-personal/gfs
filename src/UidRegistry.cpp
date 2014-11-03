#include "UidRegistry.hpp"

namespace gfs {
    UidRegistry::UidRegistry():
        nextId{1}, nextBit{1} {}

    UidRegistry::~UidRegistry() {
        clear();
    }

    const Uid& UidRegistry::get(const size_t hash) {
        auto uid = map[hash];

        if (uid == nullptr) {
            uid = new Uid(nextId, nextBit);
            map[hash] = uid;

            nextId++;
            nextBit <<= 1;
        }

        return *uid;
    }

    void UidRegistry::clear() {
        for (const auto& it: map)
            delete it.second;
        
        map.clear();
    }
}
