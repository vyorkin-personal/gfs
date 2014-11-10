#pragma once

#include "Gfs.hpp"

using namespace gfs;
using namespace gfs::math;
using namespace gfs::event;
using namespace gfs::ecs;

#include "examples/event/ExplosionEvent.hpp"
#include "examples/event/KeyDownEvent.hpp"
#include "examples/event/EventListener.hpp"

#include "examples/ecs/components/AIComponent.hpp"
#include "examples/ecs/components/PlayerStateComponent.hpp"
#include "examples/ecs/components/PositionComponent.hpp"
#include "examples/ecs/components/RenderableComponent.hpp"
#include "examples/ecs/components/VelocityComponent.hpp"

#include "examples/ecs/systems/AISystem.hpp"
#include "examples/ecs/systems/InputSystem.hpp"
#include "examples/ecs/systems/MovementSystem.hpp"
#include "examples/ecs/systems/PlayerSystem.hpp"
#include "examples/ecs/systems/RenderingSystem.hpp"
