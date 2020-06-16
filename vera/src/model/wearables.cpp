#include <model/wearables.hpp>

Wearables::Wearables()
    : Sensor(), measurements(QVector<Measurements*>()) {}

Wearables::Wearables(const QJsonDocument& cfg)
    : Sensor(Type::Wearables, Pattern::Wearables, cfg), measurements(QVector<Measurements*>()) {}

Wearables::Wearables(const Wearables& other)
    : Sensor(other), measurements(other.measurements) {}

Wearables::~Wearables() {}

bool Wearables::isEmpty() const {
    return true;
}