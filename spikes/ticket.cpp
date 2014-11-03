#include "Prerequisites.hpp"
#include "World.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"

#include "components/PositionComponent.hpp"
#include "components/VelocityComponent.hpp"
#include "components/RenderableComponent.hpp"

#include "systems/MovementSystem.hpp"

using namespace gfs;

int main() {
    auto world = World();
    auto entityManager = world.getEntityManager();
    auto systemManager = world.getSystemManager();

    systemManager->create<MovementSystem>();

    Entity* player = entityManager->create();
    Entity* other = entityManager->create();

    player->addComponents({
        new VelocityComponent(1.2F, 3.4F),
        new PositionComponent(1.0F, 1.0F)
    });

    other->addComponents({
        new RenderableComponent(),
        new VelocityComponent(1.2F, 3.4F),
        new PositionComponent(1.2F, 3.4F)
    );

    auto pos = player->getComponent<PositionComponent>();

    world.setDelta(0.0021F);

    while (true) {
        world.process();

        std::cout << "(" << pos->getX() << ", " << pos->getY() << ")" << std::endl;
    }

    return 0;
}
