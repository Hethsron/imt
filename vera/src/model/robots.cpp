#include <model/robots.hpp>

Robots::Robots(const QJsonDocument& cfg)
    : Sensor(Type::Robots, Pattern::Robots, cfg) {}

Robots::Robots(const Robots& other)
    : Sensor(other) {}

Robots::~Robots() {}

bool Robots::isEmpty() const {
    return true;
}