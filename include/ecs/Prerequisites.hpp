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

#include "Configuration.hpp"

namespace gfs {
    template <class T> class Vector2<T>;
    template <class T> class Color4<T>;

    using Vector2f = Vector2<GLfloat>;
    using Vector2d = Vector2<GLdouble>;
    using Vector2i = Vector2<GLint>;

    using Point2f = Vector2<GLfloat>;
    using Point2d = Vector2<GLdouble>;
    using Point2i = Vector2<GLint>;

    using Color4f = Color4<GLfloat>;
    using Color4d = Color4<GLdouble>;
    using Color4i = Color4<GLint>;

    using Size = Vector2i;

    template<class T>
    using var = std::initializer_list<T>;

    using String = std::string;
    using StringSet = std::unordered_set<String>;

    class Polygon;

    namespace ecs {
        class Uid;
        class Component;
        class EntityBits;
        class Entity;
        class System;
        class UidRegistry;
        class EntityManager;
        class EntityManagerDumper;
        class SystemManager;
        class GroupManager;
        class TagManager;
        class World;

        using BitSet = std::bitset<BITSIZE>;
        using EntitySet = std::unordered_set<Entity*>;
        using ComponentSet = std::multiset<Component*>;
        using BitSetMap = std::map<size_t, BitSet*>;
        using UidMap = std::map<size_t, Uid*>;
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
