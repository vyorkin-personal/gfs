gfs
===

Game foundation system (C++11)

Overview
===

Stuff that i use to make games.

Features
===

### Entity component system

Lightweight &amp; simple entity component system (c++11) havily inspired by [artemis](http://gamadu.com/artemis/) entity system framework implemented in Java.

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

### Event bus

Very simple implementation that provides `subscribe` & `emit` methods.

### Some basic math

* `Vector2<T>` aka `Point2<T>` `Point2f`, `Point2i`, `Size2i`, `Size2f`
* `Color4<T>` aka `Color4f`
* `Rectangle<T>`
* `Polygon`

Usage
===

### Example
Let's define a component that represents a position & rotation in 2D space:
```
struct Position: public Component {
    Position(const Vector2f& vector, const float rotation):
	vector{vector}, rotation{rotation} {}

    void move(const Vector2f& velocity) {
	vector += velocity;
    }
    
    void rotate(const float speed) {
	rotation += speed;

	if (rotation < 0.0f)
	    rotation += 360.0f;
	else if (rotation > 360.0f)
	    rotation -= 360.0f;
    }

    Vector2f vector;
    float rotation;
};
```
Next we need a motion component to represent a velocity & dumping + helper method to apply dumping:
```
struct Motion: public Component {
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
So a movement system will look like this:
```
class MovementSystem: public System {
    public:
	virtual void initialize() override {
	    watchComponents<Position, Motion>();
	}
	
	virtual void processEntity(Entity* entity) override {
	    auto position = entity.getComponent<Position>();
	    auto motion = entity.getComponent<Motion>();
	    auto dt = getDelta();
	    
	    position->move(motion->velocity, dt);
	    position->rotate(motion->angularVelocity, dt);
	    motion->damp(position->rotation, dt);
	}
};
```

### Initialization & processing
Note that systems should be created before adding components to entities, here is why: [[1]](https://github.com/vyorkin/gfs/blob/master/src/EntityManager.cpp#L76), [[2]](https://github.com/vyorkin/ecs/blob/master/src/EntityManager.cpp#L193), [[3]](https://github.com/vyorkin/ecs/blob/master/src/System.cpp#L5)
Be carefull not to add the same component to different entities.
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
class FooSystem: public System {
    public:
	virtual void initialize() override {
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
	
	virtual void processEntity(Entity* entity) override {
	    auto foo = entity.getComponent<FooComponent>();
	    // ... and here goes entity processing code ...
	}
};
```

Subscription is implemented using bitsets, look [here](https://github.com/vyorkin/gfs/blob/master/src/System.cpp#L5) to see the details.

## Math

TODO

## EventBus

So if i need to handle explosions i could write smth like this:
```
class ExplosionListener {
    public:
	ExplosionListener(EventBus& eventBus) {
	    eventBus.subscribe<ExplosionEvent>(this, &EventListener::onExplosion);
	}

	void onExplosion(const ExplosionEvent& event) {
	    // do smth with it
	}
};
```

Later, somewhere deep in a game logic...
```
eventBus.emit(ExplosionEvent(...));
```

--

Here is how i can use it with ECS to handle keyboard events.

First i'll define a KeyEvent struct:
```
struct KeyEvent: public Event {
    KeyEvent(const int keyCode, const char keyChar):
        keyCode{keyCode}, keyChar{keyChar} {}

    int keyCode;
    char keyChar;
};

```
Level scene emits the event:
```
void LevelScene::onKey(const int keyCode, const char keyChar) {
    world->getEventBus()->emit(KeyEvent(keyCode, keyChar));
}
```

Than i can subscribe to it in the system:
```
class BarSystem: public System {
    public:
	virtual void initialize() override {
	    getEventBus()->subscribe<KeyEvent>(this, &BarSystem::onKey);
	}
	
	void onKey(const KeyEvent& e) {
	    // handle key event somehow
	}
};
```

testing
===
I'm using [catch](https://github.com/philsquared/Catch) cuz of its simplicity.

Here is some example [components](https://github.com/vyorkin/gfs/tree/master/examples/include/components) & [systems](https://github.com/vyorkin/gfs/tree/master/examples/include/systems).

how to
===
* build a static library: `make` (remove -DDEBUG flags for a release version)
* run tests: `make test`
* run the example: `make ticket`

