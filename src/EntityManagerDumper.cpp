#include "EntityManagerDumper.hpp"

#ifdef DEBUG

namespace gfs {
    EntityManagerDumper::EntityManagerDumper(EntityManager* manager):
        entityManager{manager} {}

    String EntityManagerDumper::dump(const bool verbose) const {
        std::ostringstream oss;

        oss << "[EntityManager]" << std::endl
            << std::setfill('=')
            << std::setw(LINE_LENGTH * 2 + 1) << '=' << std::endl;

        dumpTotals(oss);

        if (verbose) {
            if (entityManager->activeEntities.size() > 0)
                dumpActiveEntities(oss);

            if (entityManager->entityPool.size() > 0)
                dumpEntityPool(oss);
        }

        return oss.str();
    }

    void EntityManagerDumper::dumpTotals(std::ostringstream& oss) const {
        oss << "\ttotals:" << std::endl
            << std::setfill(FILL_CHAR)
            << '\t' << std::setw(LINE_LENGTH) << FILL_CHAR << std::endl;

        const int width = LINE_LENGTH / 2;

        oss << std::setfill(' ')
            << '\t' << std::setw(width) << "created: " << entityManager->getTotalCreated() << std::endl
            << '\t' << std::setw(width) << "destroyed: " << entityManager->getTotalDestroyed() << std::endl
            << '\t' << std::setw(width) << "active: " << entityManager->getTotalActive() << std::endl
            << '\t' << std::setw(width) << "pool: " << entityManager->entityPool.size() << std::endl;

        oss << std::setfill(FILL_CHAR)
            << '\t' << std::setw(LINE_LENGTH) << FILL_CHAR << std::endl;
    }

    void EntityManagerDumper::dumpActiveEntities(std::ostringstream& oss) const {
        oss << "\tactive entities:" << std::endl
            << std::setfill(FILL_CHAR)
            << '\t' << std::setw(LINE_LENGTH) << FILL_CHAR << std::endl;

        for (auto& it: entityManager->activeEntities) {
            dumpEntity(oss, it.second);
        }

        oss << std::setfill(FILL_CHAR)
            << '\t' << std::setw(LINE_LENGTH) << FILL_CHAR << std::endl;
    }

    void EntityManagerDumper::dumpEntityPool(std::ostringstream& oss) const {
        auto pool = EntityQueue(entityManager->entityPool);

        oss << "\tentity pool:" << std::endl
            << std::setfill(FILL_CHAR)
            << '\t' << std::setw(LINE_LENGTH) << FILL_CHAR << std::endl;

        while (!pool.empty()) {
            dumpEntity(oss, pool.front());
            pool.pop();
        }

        oss << std::setfill(FILL_CHAR)
            << '\t' << std::setw(LINE_LENGTH) << FILL_CHAR << std::endl;
    }

    void EntityManagerDumper::dumpEntity(std::ostringstream& oss, Entity* entity) const {
        oss << "\t\t" << entity->toString();
        dumpEntityComponents(oss, entity);
    }

    void EntityManagerDumper::dumpEntityComponents(std::ostringstream& oss, Entity* entity) const {
        auto entityId = entity->getId();
        auto range = entityManager->entityComponents.equal_range(entityId);

        auto next = range.first;
        auto end = range.second;

        if (next != entityManager->entityComponents.end()) {
            oss << "\t\t\tcomponents:" << std::endl;
            while (next != end) {
                auto component = next->second;
                oss << "\t\t\t\tid: " << component->getId() << std::endl;
                next++;
            }
        }
    }
}

#endif
