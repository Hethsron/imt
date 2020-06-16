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
            // Define line
            QString line;

            // Define status
            bool status = true;

            // Define times
            double firstTime = 0;
            double time;

            // Define json document
            QJsonDocument config;

            // Define text stream
            QTextStream in(&file);
            while (!in.atEnd()) {
                // Getting line
                line = in.readLine();

                // Getting json document
                config = QJsonDocument::fromJson(line.toUtf8());

                // Getting json object
                QJsonObject obj = config.object();

                // Check if it is first time
                if (status) {
                    firstTime = obj.value(QString("time")).toDouble();
                    status = false;
                }

                // Getting name of wearable
                const QString name = obj.value(QString("name")).toString();

                // Getting time
                time = obj.value(QString("time")).toDouble() - firstTime;

                // Check if given name exists in measurements
                if (contains(name)) {
                    // Appends time, accelerometer and gyroscope data
                    get(name)->append(time, obj);
                }
                else {
                    // Append new measurement data
                    measurements.append(new Measurements(name));

                    // Appends time, accelerometer and gyroscope data
                    get(name)->append(time, obj);
                }
            }

            // Close file
            file.close();
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