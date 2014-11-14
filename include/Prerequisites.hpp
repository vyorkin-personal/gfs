#pragma once

#include <initializer_list>
#include <bitset>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <typeinfo>
#include <iostream>
#include <iomanip>
#include <functional>
#include <cstddef>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cmath>
#include <random>

#include "Configuration.hpp"

namespace gfs {
    template<class T>
    using var = std::initializer_list<T>;

    using String = std::string;
    using StringSet = std::unordered_set<String>;
    using BitSet = std::bitset<BITSIZE>;
    using BitSetMap = std::map<size_t, BitSet*>;

    class Uid;
    class UidRegistry;
    using UidMap = std::map<size_t, Uid*>;

    namespace math {
        template <class T> struct Vector2;
        template <class T> struct Color4;

        using Vector2f = Vector2<float>;
        using Vector2d = Vector2<double>;
        using Vector2i = Vector2<int>;

        template<class T> using Size2 = Vector2<T>;
        template<class T> using Point2 = Vector2<T>;

        using Point2f = Point2<float>;
        using Point2d = Point2<double>;
        using Point2i = Point2<int>;

        using Color4f = Color4<float>;
        using Color4d = Color4<double>;
        using Color4i = Color4<int>;

        using Size2i = Size2<int>;
        using Size2f = Size2<float>;

        struct Polygon;

        template <class T> struct Rectangle;

        using Rectanglei = Rectangle<int>;
        using Rectanglef = Rectangle<float>;
    }

    namespace event {
        struct Event;
        class EventBus;
        using EventHandlerFunc = std::function<void(const Event &)>;
        using EventHandlerMap = std::multimap<Uid, EventHandlerFunc>;
    }

    namespace ecs {
        class Component;
        struct EntityBits;
        class Entity;
        class System;
        class EntityManager;
        class EntityManagerDumper;
        class SystemManager;
        class GroupManager;
        class TagManager;
        class World;

        using EntitySet = std::unordered_set<Entity*>;
        using ComponentSet = std::multiset<Component*>;
        using IdEntityMap = std::map<int, Entity*>;
        using EntityQueue = std::queue<Entity*>;
        using TagEntityMap = std::map<String, Entity*>;
        using EntityTagMap = std::map<int, String>;
        using ComponentMap = std::map<int, Component*>;
        using EntityComponentMap = std::multimap<int, Component*>;
        using ComponentLookupMap = std::map<Uid, ComponentMap>;
        using SystemSet = std::multiset<System*>;
        using SystemMap = std::map<Uid, System*>;
        using GroupMap = std::multimap<int, String>;
        using EntitiesByGroupMap = std::map<String, EntitySet>;
    }
}
