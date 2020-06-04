#include <model/sensor.hpp>

Sensor::Sensor()
    :  type(Type::Unknown), name(QString()), location(QString()) {}

Sensor::Sensor(Type category, const QString& key, const QJsonDocument& cfg)
    : type(category), name(key), location(QString()) {
        location = Reader::release(cfg, name);
    }

Sensor::Sensor(const Sensor& other)
    : type(other.type), name(other.name), location(other.location) {}

Sensor::~Sensor() {}

Type Sensor::getType() const {
    return type;
}

QString Sensor::getLocation() const {
    return location;
}

Sensor& Sensor::operator=(const Sensor& other) {
    // Avoid self assignment
    if (this != &other) {
        if (other.type != type) {
            name = other.name;
            location = other.location;
        }
    }
    return *this;
}

bool Sensor::operator==(const Sensor& other) const {
    return (other.type == type && other.name == name && other.location == location);
}

bool Sensor::operator!=(const Sensor& other) const {
    return (other.type != type || other.name != name || other.location != location);
}