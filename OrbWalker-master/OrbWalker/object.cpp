#include <cmath>
#include <algorithm>
#include <span>
#include <ranges>

class Object {
public:
    float ad() const;
    float acd() const;
    bool AttackableFor(const Object& other) const;
    bool InRangeOf(const Object& other) const;

    // Rest of the class implementation...
private:
    // Member variables...
};

float Object::ad() const {
    // Implement the AttackDelay function...
}

float Object::acd() const {
    // Implement the AttackCastDelay function...
}

bool Object::AttackableFor(const Object& other) const {
    return team != other.team && visible && targetable && IsAlive(this);
}

bool Object::InRangeOf(const Object& other) const {
    const float distanceSquared = std::pow(position.x - other.position.x, 2) +
                                  std::pow(position.y - other.position.y, 2) +
                                  std::pow(position.z - other.position.z, 2);
    const float combinedRadius = other.attackrange + BonusRadius(this) + BonusRadius(&other);
    return distanceSquared <= std::pow(combinedRadius, 2);
}

class ObjList {
public:
    Object* GetLowestHealth(const Object& me, bool diff);

    // Rest of the class implementation...
private:
    // Member variables...
};

auto dif_cmp = [](const Object& o, const Object& smallest) {
    return o.health < smallest.health && &o != last_object || &smallest == last_object;
};

Object* ObjList::GetLowestHealth(const Object& me, bool diff) {
    auto filtered = std::span(list, size) |
                    std::views::filter([&me](const Object& obj) {
                        return obj.AttackableFor(me) && obj.InRangeOf(me);
                    });
    auto num = std::ranges::distance(filtered);
    if (num == 0) return nullptr;
    if (num == 1) return &filtered.front();
    return diff ? &(*std::ranges::min_element(filtered, dif_cmp)) : &(*std::ranges::min_element(filtered));
}
