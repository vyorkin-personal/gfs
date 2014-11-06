#pragma once

#include "Prerequisites.hpp"
#include "ecs/Uid.hpp"
#include "ecs/Component.hpp"

namespace gfs {
    namespace ecs {
        class UidRegistry final {
            public:
                UidRegistry();
                ~UidRegistry();

                template<class T> const Uid& get() {
                    return get(typeid(T));
                }

                const Uid& get(const std::type_info& typeInfo) {
                    return get(typeInfo.hash_code());
                }

                const Uid& get(const String& str) {
                    return get(stringHasher(str));
                }

                const BitSet& getBit(const std::type_info& typeInfo) {
                    return get(typeInfo).getBit();
                }

                template<class T> const BitSet& getBit() {
                    return get<T>().getBit();
                }

                const BitSet& getBit(const String& str) {
                    return get(str).getBit();
                }

                template<class T> int getId() {
                    return get<T>().getId();
                }

                int getId(const String& str) {
                    return get(str).getId();
                }

                void clear();

            private:
                const Uid& get(const size_t hash);

                UidMap map;

                int nextId;
                BitSet nextBit;
                std::hash<String> stringHasher;
        };
    }
}
