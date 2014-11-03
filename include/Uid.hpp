#pragma once

#include "Prerequisites.hpp"

namespace gfs {
    class Uid final {
        public:
            Uid(const int id, const BitSet& bit):
                id{id}, bit{bit} {}

            ~Uid() = default;

            int getId() const {
                return id;
            }

            const BitSet& getBit() const {
                return bit;
            }

            bool operator == (const Uid& other) const {
                return getBit() == other.getBit();
            }

            String toString() const;

            static Uid None;

        private:
            int id;
            BitSet bit;
    };
}

namespace std {
    template<>
    struct less<gfs::Uid> {
        bool operator() (const gfs::Uid& lhs,
            const gfs::Uid& rhs) const {

            return lhs.getId() < rhs.getId();
        }
    };
}
