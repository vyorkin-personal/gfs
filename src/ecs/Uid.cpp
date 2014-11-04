#include "Uid.hpp"

namespace gfs {
    Uid Uid::None = Uid(std::numeric_limits<int>::max(), BitSet(0));

    String Uid::toString() const {
        std::ostringstream oss;
        oss << "[Uid("
            << "id: " << id << ", "
            << "bitset: " << bit.to_string()
            << ")]" << std::endl;

        return oss.str();
    }
}
