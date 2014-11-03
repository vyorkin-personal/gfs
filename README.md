gfs
===

Game foundation system (C++11)

Overview
===

Stuff that i use to make games.

Features
===

Lightweight &amp; simple entity component system (c++11) havily inspired by artemis entity system framework.
The idea is based on the [artemis](http://gamadu.com/artemis/) entity/component/system implemented in Java.

Here is some links to read about this concept:

* [Some articles on t-machine](http://entity-systems-wiki.t-machine.org/es-articles)
* [Entity Systems are the future of MMORPG](http://t-machine.org/index.php/2007/09/03/entity-systems-are-the-future-of-mmog-development-part-1/) blog series by Adam Martin
* [gameprogrammingpatterns.com](http://gameprogrammingpatterns.com/component.html)

Artemis framework C++ ports:
* [sreich/artemisxx](https://github.com/sreich/artemisxx)
* [Beernutts/Escape-System](https://github.com/Beernutts/Escape-System)
* [vinova/Artemis-Cpp](https://github.com/vinova/Artemis-Cpp)
* [simonracz/Artemis-Cpp](https://github.com/simonracz/Artemis-Cpp)

Other C++ entity systems:
* [miguelmartin75/anax](https://github.com/miguelmartin75/anax)
* [alecthomas/entityx](https://github.com/alecthomas/entityx)

Usage
===
### Components
Let's define a component that represents a position & rotation in 2D space:
```
struct Position: public gfs::Component {
	Position(const Vector2f& pos, const float rot):
		position{pos}, rotation{rot} {}

	void move(const Vector2f& velocity, const float delta) {
		position.x += velocity.x * delta;
		position.y += velocity.y * delta;
	}
	
	void rotate(const float speed, const float delta) {
		rotation += speed * delta;
	}

	Vector2f position;
	float rotation;
};
```
Next we need a motion component to represent a velocity & dumping + helper method to apply dumping:
```
struct Motion: public gfs::Component {
	Motion(const Vector2f& vel, const float angVel, const float& damp):
		velocity{vel}, angularVelocity{angVel}, damping{damp} {}
	
	void damp(const float rotation, const float delta) {
		if (damping <= 0.0F) return;
		
		auto xd = abs(cos(rotation) * damping * delta);
		auto yd = abs(sin(rotation) * damping * delta);
			
		velocity.x += getDampingValue(velocity.x, xd);
		velocity.y += getDampingValue(velocity.y, yd);
	}
	
	Vector2f velocity;
	float angularVelocity;
	float damping;
	
	private:
		float getDampingValue(const float coord, const float val) {
			if (coord > val)
				return -val;
			else if (coord < -val)
				return val;
			else
				return -coord;
		}
};
```
### Systems
So a movement system will look like this:
```
class MovementSystem: public gfs::System {
	public:
		void initialize() {
			watchComponents<Position, Motion>();
		}
		
		void processEntity(Entity* entity, const float delta) {
			auto position = entity.getComponent<Position>();
			auto motion = entity.getComponent<Motion>();
			
			position->move(motion->velocity, delta);
			position->rotate(motion->angularVelocity, delta);
			motion->damp(position->rotation, delta);
		}
};
```

### Initialization & processing
Note that systems should be created before adding components to entities, here is why: [[1]](https://github.com/vyorkin/gfs/blob/master/src/EntityManager.cpp#L76), [[2]](https://github.com/vyorkin/ecs/blob/master/src/EntityManager.cpp#L193), [[3]](https://github.com/vyorkin/ecs/blob/master/src/System.cpp#L5)
```
// before main loop
auto world = new World();
auto entityManager = world.getEntityManager();
auto systemManager = world.getSystemManager();

// systems should be created before entities
systemManager->create<MovementSystem>();
systemManager->create<RenderingSystem>();
systemManager->create<CollisionSystem>();
systemManager->create<InputSystem>();

auto asteriod = entityManager->create();
asteriod->addToGroup("asteriods");
asteroid->addComponents({
	new Collision(radius),
	new Position(Vector2f(x, y), 0.0F),
	new Motion(Vector2f(dx, dy), vel, damp),
	new Display(AsteroidView(numPoints))
});

auto player = entityManager->create();
player->setTag("player");
player->addComponents({
	new Collision(radius),
	new Position(Vector2f(cx, cy), 0.0F),
	new Motion(Vector2f(dx, dy), vel, damp),
	new Display(PlayerView()),
	new Gun(),
	new GunControl(),
	new MotionControl()
});

// somewhere in a game loop
world.setDelta(delta);
world.process();
```

## Systems
```
class FooSystem: public gfs::System {
	public:
		void initialize() {
			// there are 3 ways for a system to process entities
			
			watchComponents<FooComponent, BarComponent>(); // 1
			watchTags({"tag-foo", "tag2"});                // 2
			watchGroups({"enemy", "bar-group"});           // 3
			
			// 1 - entity contains a component of type
			// 2 - entity has a tag
			// 3 - entity belongs to group
			
			// if any of the conditions above is true
			// then entity will be processed by the system
		}
		
		void processEntity(Entity* entity, const float delta) {
			auto foo = entity.getComponent<FooComponent>();
			// ... and here goes entity processing code ...
		}
};
```

Subscription is implemented using bitsets, look [here](https://github.com/vyorkin/gfs/blob/master/src/System.cpp#L5) to see the details.

testing
===
I'm using [catch](https://github.com/philsquared/Catch) cuz of its simplicity.

Here is some example [components](https://github.com/vyorkin/gfs/tree/master/examples/include/components) & [systems](https://github.com/vyorkin/gfs/tree/master/examples/include/systems).

how to
===
* build a static library: `make` (remove -DDEBUG flags for a release version)
* run tests: `make test`
* run the example: `make ticket`

