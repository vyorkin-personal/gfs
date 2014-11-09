#pragma once

#include "Prerequisites.hpp"

#include "examples/ecs/components/AIComponent.hpp"
#include "examples/ecs/components/InputComponent.hpp"
#include "examples/ecs/components/PlayerStateComponent.hpp"
#include "examples/ecs/components/PositionComponent.hpp"
#include "examples/ecs/components/RenderableComponent.hpp"
#include "examples/ecs/components/VelocityComponent.hpp"

#include "examples/ecs/systems/AISystem.hpp"
#include "examples/ecs/systems/InputSystem.hpp"
#include "examples/ecs/systems/MovementSystem.hpp"
#include "examples/ecs/systems/PlayerSystem.hpp"
#include "examples/ecs/systems/RenderingSystem.hpp"

#include "Uid.hpp"
#include "UidRegistry.hpp"
#include "ecs/Entity.hpp"
#include "ecs/EntityManager.hpp"
#include "ecs/EntityManagerDumper.hpp"
#include "ecs/System.hpp"
#include "ecs/SystemManager.hpp"
#include "ecs/GroupManager.hpp"
#include "ecs/TagManager.hpp"
#include "ecs/World.hpp"

using namespace gfs;
using namespace gfs::ecs;
using namespace gfs::math;
