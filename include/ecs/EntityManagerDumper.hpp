#pragma once

#include "Prerequisites.hpp"

#ifdef DEBUG

#include "ecs/EntityManager.hpp" 
#include "ecs/Entity.hpp"

namespace gfs {
    namespace ecs {
        class EntityManagerDumper final {
            public:
                EntityManagerDumper(EntityManager* manager);
                String dump(const bool verbose = true) const;

            private:
                const int LINE_LENGTH = 39;
                const char FILL_CHAR = '-';

                EntityManager* entityManager;

                void dumpTotals(std::ostringstream& oss) const;
                void dumpActiveEntities(std::ostringstream& oss) const;
                void dumpEntityPool(std::ostringstream& oss) const;
                void dumpEntity(std::ostringstream& oss, Entity* entity) const;
                void dumpEntityComponents(std::ostringstream& oss, Entity* entity) const;
        };
    }
}

#endif
