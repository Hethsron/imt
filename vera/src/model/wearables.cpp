#include <model/wearables.hpp>

Wearables::Wearables(const QJsonDocument& cfg)
    : Sensor(Type::Wearables, Pattern::Wearables, cfg) {}

Wearables::Wearables(const Wearables& other)
    : Sensor(other) {}

Wearables::~Wearables() {}

bool Wearables::isEmpty() const {
    return true;
}