#include <model/wearables.hpp>

Wearables::Wearables()
    : Sensor(), measurements(QVector<Measurements*>()) {}

Wearables::Wearables(const QJsonDocument& cfg)
    : Sensor(Type::Wearables, Pattern::Wearables, cfg), measurements(QVector<Measurements*>()) {}

Wearables::Wearables(const Wearables& other)
    : Sensor(other), measurements(other.measurements) {}

Wearables::~Wearables() {
    // Check if measurements data is not empty
    if (!isEmpty()) {
        // Clear measurements data
        clear();
    }
}

bool Wearables::isEmpty() const {
    return measurements.isEmpty();
}

bool Wearables::contains(const QString& name) const {
    // Define iterator
    QVectorIterator<Measurements*> iterator(measurements);
    while (iterator.hasNext()) {
        // Get local measurement
        Measurements* measurement = iterator.next();
        // Check if measurement name matches with given name
        if (measurement->getName() == name) {
            // Returns true
            return true;
        }
    }
    // Returns false
    return false;
}

Measurements* Wearables::get(const QString& name) const {
    // Define iterator
    QVectorIterator<Measurements*> iterator(measurements);
    while (iterator.hasNext()) {
        // Get local measurement
        Measurements* measurement = iterator.next();
        // Check if measurement name matches with given name
        if (measurement->getName() == name) {
            // Returns measurement data
            return measurement;
        }
    }
    // Returns nullptr
    return nullptr;
}

void Wearables::append(const QString& fileName) {
    // Define file instance
    QFile file(fileName);

    // Check if file exists
    if (file.exists()) {
        // Open file
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            
        }
    }
}

void Wearables::clear() {
    // Define iterator
    QVectorIterator<Measurements*> iterator(measurements);
    while (iterator.hasNext()) {
        // Clear measurements data
        iterator.next()->clear();
    }
    
    // Clear measurements data
    measurements.clear();
}