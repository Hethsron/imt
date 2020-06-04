#include <model/ambiant.hpp>

Ambiant::Ambiant()
    : Sensor() {}

Ambiant::Ambiant(const QJsonDocument& cfg)
    : Sensor(Type::Ambiant, Pattern::Ambiant, cfg) {}

Ambiant::Ambiant(const Ambiant& other)
    : Sensor(other) {}

Ambiant::~Ambiant() {}

bool Ambiant::isEmpty() const {
    return true;
}