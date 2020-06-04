#include <model/sensor.hpp>
#include <core/deepreader.hpp>
#include <core/reader.hpp>

Sensor::Sensor()
    :  type(Type::Unknown), name(QString()), location(QString()), storage(QList<QStringList>()) {}

Sensor::Sensor(Type category, const QString& key, const QJsonDocument& cfg)
    : type(category), name(key), location(QString()), storage(QList<QStringList>()) {
        // Getting default location
        location = Reader::release(cfg, name);

        // Getting default storage
        storage = DeepReader::release(location);
    }

Sensor::Sensor(const Sensor& other)
    : type(other.type), name(other.name), location(other.location), storage(other.storage) {}

Sensor::Sensor(std::nullptr_t)
    :  type(Type::Unknown), name(QString()), location(QString()), storage(QList<QStringList>()) {}

Sensor::~Sensor() {}

Type Sensor::getType() const {
    return type;
}

QString Sensor::getLocation() const {
    return location;
}

QList<QStringList> Sensor::getStorage() const {
    return storage;
}

int Sensor::count() const {
    return storage.count();
}

int Sensor::count(int i) const {
    return storage.at(i).count();
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